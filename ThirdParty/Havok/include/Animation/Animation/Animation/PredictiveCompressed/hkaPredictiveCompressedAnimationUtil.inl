/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#include <Animation/Internal/Compression/Predictive/hkaPredictiveBlockCompression.h>
#include <Animation/Animation/Animation/PredictiveCompressed/hkaPredictiveCompressedAnimation.h>
#include <Common/Base/Math/Vector/hkVector4Util.h>



// This file contains some private implementation details of hkaPredictiveCompressedAnimation
// They are pulled out into a separate file so that they can be unit-tested.




namespace hkaPredictiveCompressedAnimationUtil
{

using namespace hkaPredictiveBlockCompression;

typedef hkaPredictiveCompressedAnimation PCA;

// Used to write the bitmaps used for decompression
template <int Width, class StorageT = hkUint32>
class HK_EXPORT_ANIMATION BitmapWriteIterator
{
	HK_COMPILE_TIME_ASSERT((sizeof(StorageT)*8) % Width == 0);
	HK_COMPILE_TIME_ASSERT((static_cast<StorageT>(-1) > static_cast<StorageT>(0))); // unsigned types only

		HK_FORCE_INLINE void store()
		{
			m_data.pushBack(m_cache);
			m_cache = 0;
			m_bitsCached = 0;
		}

	public:
		HK_FORCE_INLINE BitmapWriteIterator(hkArray<StorageT>& data)
			: m_data(data), m_cache(0), m_bitsCached(0)
		{
		}
		HK_FORCE_INLINE void write(StorageT v)
		{
			v &= hkBitmask(Width);
			m_cache |= v << m_bitsCached;
			m_bitsCached += Width;
			if (m_bitsCached == sizeof(m_cache)*8)
			{
				store();
			}
		}
		HK_FORCE_INLINE void flush()
		{
			if ( m_bitsCached > 0 )
			{
				store();
			}
		}
		// flush the cached bits after filling in the rest of the last StorageT with fill
		HK_FORCE_INLINE void flush( StorageT fill )
		{
			while ( m_bitsCached > 0 )
			{
				write(fill);
			}
		}

	private:
		hkArray<StorageT>& m_data;
		// bits are cached here until we fill it up
		StorageT m_cache;
		int m_bitsCached;
};

// Finds the span (i.e. min, max) of a channel and quantizes values
class HK_EXPORT_ANIMATION Range
{
	// This class performs quantization with a tolerance, which is somewhat subtle.
	// The quantization bins are chosen so that:
	//   1. there are an equal number of bins to the left and right of the center-point
	//   2. there is one bin covering both center+epsilon and center-epsilon
	//   3. each value is quantized to the *nearest* bin, not quantized via truncation
	//   4. if the tolerance is large, the binwidths are increased accordingly
	//
	// 1 and 2 mean that signals very close to the center point (often 0) don't jump quickly
	// between two values. It requires that there are an odd number of bins in total. This
	// is why the code below sets MIN_QVAL to MIN_CODEABLE + 1, as two's complement arithmetic
	// normally has one more negative value than positive.
	//
	// 3 means the average error is binwidth/4 rather than binwidth/2, giving the equivalent
	// of an extra bit of precision for free.
	//
	// 4 means that, when tolerance is large, samples are represented by less than the whole
	// range of values, which makes the predictive compression more effective.
	//
	// These properties are tested in the PredictiveCompression.cpp unit test

	HK_COMPILE_TIME_ASSERT(Block::MIN_CODEABLE == -(1<<13) && Block::MAX_CODEABLE == (1<<13)-1);
	public:
		enum { MIN_QVAL = -(1<<13) + 1, MAX_QVAL = (1<<13) - 1};

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ANIM_COMPRESSED,hkaPredictiveCompressedAnimationUtil::Range);
		
		Range()
			// setting min to a large number and max to a small one means that the first sample
			// will change both min and max.
		{
			m_min = hkSimdReal_Max;
			m_max = hkSimdReal_MinusMax;
			m_tolerance.setZero();
		}
		inline void calcParams(hkSimdReal& scale, hkSimdReal& offset) const
		{
			HK_ASSERT(0xabd3ba32, m_max >= m_min);
			HK_ASSERT(0xabd3ba32, hkMath::isFinite(m_max.getReal()));
			HK_ASSERT(0xabd3ba32, hkMath::isFinite(m_min.getReal()));
			// Ranges are stored as (scale, offset)
			// such that for a quantized value q, the dequantized value will be q * scale + offset
			// and the abs. difference between the quantized and dequantized values will be less
			// than or equal to m_tolerance.
			scale.setAdd(m_tolerance, m_tolerance);
			offset.setAdd(m_max, m_min);
			offset.mul(hkSimdReal_Half);
		}

		inline hkInt16 quantize(hkSimdRealParameter x) const
		{
			HK_ASSERT(0xabd3ba32, m_max >= m_min);
			HK_ASSERT(0xabd3ba32, hkMath::isFinite(m_max.getReal()));
			HK_ASSERT(0xabd3ba32, hkMath::isFinite(m_min.getReal()));

			hkSimdReal scale, offset;
			calcParams(scale, offset);
			
			hkSimdReal q; 
			q.setReciprocal<HK_ACC_FULL,HK_DIV_SET_HIGH>(scale); 
			q.mul(x - offset);


			// We need round-to-nearest, not truncating conversion
			// This gives us a full extra bit of precision
			hkSimdReal qRounded;
			qRounded.setFlipSign(hkSimdReal_Half, q.lessZero());
			qRounded.add(q);
			int i; qRounded.storeSaturateInt32(&i);
			
			// these out-of-bounds cases shouldn't really happen, but may crop up due to rounding error
			i = hkMath::clamp(i, (int)MIN_QVAL, (int)MAX_QVAL);
			return (hkInt16)i;
		}

		inline void addToRange(hkSimdRealParameter x)
		{
			m_max.setMax(x, m_max);
			m_min.setMin(x, m_min);
		}

		inline void setTolerance(hkSimdRealParameter tolerance)
		{
			hkSimdReal minPossibleTolerance = hkSimdReal_Half * (m_max - m_min) * hkSimdReal::fromFloat(hkReal(1) / hkReal(MAX_QVAL - MIN_QVAL));
			m_tolerance.setMax(tolerance, minPossibleTolerance);
		}

		inline PCA::StorageClass getStorageClass(hkSimdRealParameter refValue)
		{
			if ((m_max - m_min) < (m_tolerance + m_tolerance))
			{
				hkSimdReal absMax; absMax.setAbs(m_max-refValue);
				hkSimdReal absMin; absMin.setAbs(m_min-refValue);
				hkSimdReal both; both.setMax(absMax,absMin);
				if (both.isLess(m_tolerance))
				{
					return PCA::STORAGE_REFERENCE;
				}
				else
				{
					return PCA::STORAGE_STATIC;
				}
			}
			else
			{
				return PCA::STORAGE_DYNAMIC_RANGE;
			}
		}

		inline hkSimdReal center()
		{
			return (m_max + m_min) * hkSimdReal_Half;
		}
	public:
		// smallest value seen in the channel
		hkSimdReal m_min;
		// largest value seen in the channel
		hkSimdReal m_max;
		// maximum acceptable error
		// average error for uniform data is m_tolerance/2
		// due to floating-point inaccuracies, it is sometimes possible for the error to exceed tolerance by
		// about 1 ulp (i.e. a factor of 1 + HK_REAL_EPSILON).
		hkSimdReal m_tolerance;
};


HK_FORCE_INLINE void quaternionRecoverW(hkVector4& v)
{
#if defined(HK_PREDICTIVE_QUATERNION_MANHATTAN)
	hkVector4 abs;
	abs.setAbs(v);
	hkSimdReal w; w.setClampedZeroOne(hkSimdReal_1 - abs.horizontalAdd<3>());
	v.setW( w );
#else
	hkSimdReal w; w.setClampedZeroOne(hkSimdReal_1 - v.lengthSquared<3>());
	v.setW(w.sqrt<HK_ACC_FULL,HK_SQRT_SET_ZERO>());
#endif
}

HK_FORCE_INLINE void quaternionRecoverW4(hkVector4& a, hkVector4& b, hkVector4& c, hkVector4& d)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_DISABLED)
	quaternionRecoverW(a);
	quaternionRecoverW(b);
	quaternionRecoverW(c);
	quaternionRecoverW(d);
#else

	hkVector4 zero; zero.setZero();
	hkVector4 one = hkVector4::getConstant<HK_QUADREAL_1>();

	hkVector4Util::transpose(a,b,c,d);

#if defined(HK_PREDICTIVE_QUATERNION_MANHATTAN)
	hkVector4 manhattanNorm, tmp;
	manhattanNorm.setAbs(a);
	tmp.setAbs(b); manhattanNorm.add(tmp);
	tmp.setAbs(c); manhattanNorm.add(tmp);
	d.setSub(one, manhattanNorm);
	d.setClamped(d, zero, one);
#else
	hkVector4 tmp;
	tmp.setMul(a,a);
	tmp.addMul(b,b);
	tmp.addMul(c,c);
	tmp.setSub( one, tmp );
	tmp.setClamped(tmp, zero, one);
	d.setSqrt<HK_ACC_FULL,HK_SQRT_SET_ZERO>(tmp);
#endif

	hkVector4Util::transpose(a,b,c,d);

#endif
}

}

/*
 * Havok SDK - NO SOURCE PC DOWNLOAD, BUILD(#20140907)
 * 
 * Confidential Information of Havok.  (C) Copyright 1999-2014
 * Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
 * Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
 * rights, and intellectual property rights in the Havok software remain in
 * Havok and/or its suppliers.
 * 
 * Use of this software for evaluation purposes is subject to and indicates
 * acceptance of the End User licence Agreement for this product. A copy of
 * the license is included with this software and is also available at www.havok.com/tryhavok.
 * 
 */
