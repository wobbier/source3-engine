/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_HAVOK_ASSEMBLY_EXCLUDE_FILE
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HKCD_MATH_ERROR_BOUNDS_CALCULATOR_H
#define HKCD_MATH_ERROR_BOUNDS_CALCULATOR_H

#include <Common/Base/Math/LargeInt/hkLargeIntTypes.h>

/// Arithmetic operations error calculator
struct hkcdMathErrorBoundsCalculator
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION, hkcdMathErrorBoundsCalculator);

	/// Returnsthe unit in the last place for the given number, x
	///		x		= 1.M * 2^E
	///		ulpOut	= 1.0 * 2^(E - numMantissaBits)
	static HK_FORCE_INLINE void HK_CALL ulp(hkVector4dParameter xIn, hkVector4d& ulpOut);
	static HK_FORCE_INLINE void HK_CALL ulp(hkSimdDouble64Parameter xIn, hkSimdDouble64& ulpOut);

	/// Scalar
	struct Scalar
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION, hkcdMathErrorBoundsCalculator::Scalar);

		/// Adds the scalars
		HK_FORCE_INLINE void setAdd(const Scalar& vA, const Scalar& vB);

		/// Multiplies the vectors
		HK_FORCE_INLINE void setMul(const Scalar& vA, const Scalar& vB);

		/// Sets this = 1 / x
		HK_FORCE_INLINE void setReciprocal(const Scalar& x);

		/// Sets this = x / y
		HK_FORCE_INLINE void setDiv(const Scalar& x, const Scalar& y);
		
		hkSimdDouble64 m_val;	///< The value
		hkSimdDouble64 m_err;	///< The error
	};

	/// Vector
	struct Vector
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION, hkcdMathErrorBoundsCalculator::Vector);

		/// Sets the vector value and computes the error
		HK_FORCE_INLINE void set(hkVector4dParameter x);
		
		/// Sets the vector value
		HK_FORCE_INLINE void set(const Scalar& x, const Scalar& y, const Scalar& z, const Scalar& w);
		
		/// Adds the vectors
		HK_FORCE_INLINE void setAdd(const Vector& vA, const Vector& vB);
		
		/// Multiplies the vectors
		HK_FORCE_INLINE void setMul(const Vector& vA, const Vector& vB);
		
		/// Permutes the vector
		template <hkVectorPermutation::Permutation p>
		HK_FORCE_INLINE void setPermutation(const Vector& x);
		
		/// Negates the vector
		HK_FORCE_INLINE void setNeg(const Vector& x);
		
		/// Subtracts the vectors
		HK_FORCE_INLINE void setSub(const Vector& vA, const Vector& vB);

		/// Computes the cross produt
		HK_FORCE_INLINE void setCross(const Vector& vA, const Vector& vB);

		/// Computes the dot product
		template <int N>
		static HK_FORCE_INLINE void HK_CALL dot(const Vector& vA, const Vector& vB, Scalar& dotAB);

		/// Returns the I-th component
		template <int I>
		HK_FORCE_INLINE void getComponent(Scalar& componentOut) const;

		/// Sign flip
		HK_FORCE_INLINE void setFlipSign(const Vector& v, hkVector4dComparisonParameter m);

		hkVector4d m_val;	///< The value
		hkVector4d m_err;	///< The absolute error
	};
};

#include <Geometry/Collide/DataStructures/Planar/Utils/hkcdMathErrorBoundsCalculator.inl>

#endif	// HKCD_MATH_ERROR_BOUNDS_CALCULATOR_H

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
