/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Math/Vector/hkIntVector.h>

extern HK_EXPORT_COMMON const hkUint32 hkPackedVector3_exponentMask[4];
extern HK_EXPORT_COMMON const hkUint32 hkPackedVector3_offsetCst[4];
extern HK_EXPORT_COMMON const hkUint32 hkPackedVector3_8_offsetCst[4];

extern HK_EXPORT_COMMON const hkUint32 hkPackedVector3_rounding[4];
extern HK_EXPORT_COMMON const hkUint32 hkPackedVector8_3_rounding[4];

extern HK_EXPORT_COMMON const hkUint32 hkPackedVector3_roundingCorrectionCst[4];
extern HK_EXPORT_COMMON const hkUint32 hkPackedVector8_3_roundingCorrectionCst[4];
extern HK_EXPORT_COMMON HK_ALIGN16(const hkUchar  hkPackedVector3_PermuteMask[16]);
extern HK_EXPORT_COMMON HK_ALIGN16(const hkUchar  hkPackedVector8_3_PermuteMask[16]);


HK_FORCE_INLINE void hkPackedVector3::_pack( hkVector4fParameter vIn )
{
	//
	// get the maximum absolute value3 and remove any mantissa bits
	//
	hkIntVector iMa;
	{
		//
		//	We set the .w component to a very tiny number, so that our horizontalMax4
		//  always returns a 'normal' number, even if vIn is zero
		//
		hkVector4f v; v.setXYZ_W( vIn, hkSimdFloat32_EpsSqrd );

		//
		// we need to increase the max by the rounding done later to avoid an overflow
		//
		hkVector4f vRounded; vRounded.load<4>( reinterpret_cast<const hkFloat32*>(hkPackedVector3_rounding)); vRounded.mul(v);

		hkIntVector mask; mask.load<4>(hkPackedVector3_exponentMask);
		iMa.loadAsFloat32BitRepresentation(vRounded);
		iMa.setAnd(iMa, mask);
		//iMa.blend<0001>(iMa, mask);	// get this working, mask[3] =eps^2, no need for setXYZ_W in the first line

		// horizontal max, much faster using int in SIMD 4.2
#if defined(HK_INT_VECTOR_NATIVE_HORIZONTAL_MAX)
		{
			iMa.setHorizontalMaxS32<4>( iMa );
		}
#else
		{
			hkVector4f ma;	 iMa.storeAsFloat32BitRepresentation(ma);
			ma.setHorizontalMax<4>( ma );
			iMa.loadAsFloat32BitRepresentation(ma);
		}
#endif
	}

	//
	// divide by maximum exponent
	//
	hkVector4 correctedV;
	{
		hkIntVector iv;		iv.loadAsFloat32BitRepresentation(vIn);
		hkIntVector offset; offset.load<4>(hkPackedVector3_offsetCst);

		iv.setAddU32( iv, offset );
		iv.setSubU32( iv, iMa );
		iMa.setSubU32( iMa, offset );		// now prepare the reverse operation for the unpack
		iv.storeAsFloat32BitRepresentation( correctedV );
	}


	//
	// Convert to integer
	//
	hkIntVector result; result.setConvertF32toS32( correctedV );

	//
	//	Rounding correction
	//
	hkIntVector roundingCorrection; roundingCorrection.load<4>(hkPackedVector3_roundingCorrectionCst);

#if defined(HK_USING_GENERIC_INT_VECTOR_IMPLEMENTATION) || !defined(HK_INT_VECTOR_NATIVE_PERMUTE8) 
	result.setAddU32( result, roundingCorrection);
	#if HK_ENDIAN_LITTLE == 1
		const int endianOffset = 1;
	#else
		const int endianOffset = 0;
	#endif
	int maW = iMa.getU32<3>() + hkPackedVector3_roundingCorrectionCst[3];
	m_values[0] = result.getU16<0+endianOffset>();
	m_values[1] = result.getU16<2+endianOffset>();
	m_values[2] = result.getU16<4+endianOffset>();
	m_values[3] = (hkUint16)(maW>>16);	// 1.0f / correction 
#else
	result.setSelect<hkVector4ComparisonMask::MASK_XYZ>( result, iMa );	// get iMa into the .w component
	result.setAddU32( result, roundingCorrection);
	result.setPermuteU8( result, (hkIntVector&)hkPackedVector3_PermuteMask );
	result.store<2>( (hkUint32*)&m_values[0] );
#endif
}




void hkPackedVector8_3::_pack( hkVector4fParameter vIn )
{

	//
	// get the maximum absolute value3 and remove any mantissa bits
	//
	hkIntVector iMa;
	{
		//
		// We set the .w component to a very tiny number, so that our horizontalMax4
		// always returns a 'normal' number, even if vIn is zero
		//
		hkVector4f v; v.setXYZ_W( vIn, hkSimdFloat32_EpsSqrd );

		//
		// we need to increase the max by the rounding done later to avoid an overflow
		//
		hkVector4f vRounded; vRounded.load<4>( reinterpret_cast<const hkFloat32*>(hkPackedVector8_3_rounding)); vRounded.mul(v);

		hkIntVector mask; mask.load<4>(hkPackedVector3_exponentMask);
		iMa.loadAsFloat32BitRepresentation(vRounded);
		iMa.setAnd(iMa, mask);
		//iMa.blend<0001>(iMa, mask);	// get this working, mask[3] =eps^2, no need for setXYZ_W in the first line

		// horizontal max, much faster using int in SIMD 4.2
#if defined(HK_INT_VECTOR_NATIVE_HORIZONTAL_MAX)
		{
			iMa.setHorizontalMaxS32<4>( iMa );
		}
#else
		{
			hkVector4f ma;	 iMa.storeAsFloat32BitRepresentation(ma);
			ma.setHorizontalMax<4>( ma );
			iMa.loadAsFloat32BitRepresentation(ma);
		}
#endif
	}

	//
	// divide by maximum exponent
	//
	hkVector4 correctedV;
	{
		hkIntVector iv;		iv.loadAsFloat32BitRepresentation(vIn);
		hkIntVector offset; offset.load<4>(hkPackedVector3_8_offsetCst);

		iv.setAddU32( iv, offset );
		iv.setSubU32( iv, iMa );
		iMa.setSubU32( iMa, offset );		// now prepare the reverse operation for the unpack
		iv.storeAsFloat32BitRepresentation( correctedV );
	}

	//
	// Convert to integer
	//
	hkIntVector result; result.setConvertF32toS32( correctedV );

	//
	//	Rounding correction
	//
	hkIntVector roundingCorrection; roundingCorrection.load<4>(hkPackedVector8_3_roundingCorrectionCst);

#if defined(HK_USING_GENERIC_INT_VECTOR_IMPLEMENTATION) || !defined(HK_INT_VECTOR_NATIVE_PERMUTE8) 
	result.setAddU32( result, roundingCorrection);
	#if HK_ENDIAN_LITTLE == 1
		const int endianOffset8  = 3;
	#else
		const int endianOffset8 = 0;
	#endif
	int maW = (iMa.getU32<3>()*2) + hkPackedVector8_3_roundingCorrectionCst[3];
	m_values.m_u8[0] = result.getU8<0+endianOffset8>();
	m_values.m_u8[1] = result.getU8<4+endianOffset8>();
	m_values.m_u8[2] = result.getU8<8+endianOffset8>();
	m_values.m_u8[3] = (hkUint8)(maW>>24);	// 1.0f / correction
#else
	iMa.setAddU32(iMa, iMa);	// shift left by one.
	result.setSelect<hkVector4ComparisonMask::MASK_XYZ>( result, iMa );	// get iMa into the .w component
	result.setAddU32( result, roundingCorrection);
	result.setPermuteU8( result, (hkIntVector&)hkPackedVector8_3_PermuteMask );
	result.store<1>( &m_values.m_u32 );
#endif
}

HK_FORCE_INLINE void hkPackedVector3::_pack( hkVector4dParameter vIn )
{
	hkVector4f p;
	hkVector4dUtil::convertVector(vIn, p);
	_pack(p);
}

HK_FORCE_INLINE void hkPackedVector8_3::_pack( hkVector4dParameter vIn )
{
	hkVector4f p;
	hkVector4dUtil::convertVector(vIn, p);
	_pack(p);
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
