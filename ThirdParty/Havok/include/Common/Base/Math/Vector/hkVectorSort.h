/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MATH_VECTOR_SORT_H
#define HK_MATH_VECTOR_SORT_H

#ifndef HK_MATH_MATH_H
#	error You need to include Common/Base/hkBase.h before this file.
#endif

/// Set of sorting method for vectors, hkIntVector (four signed integers) and hkVector4.
struct hkVectorSort
{
	/// Compare two hkIntVector.
	template <hkMathSortDir ORDER>
	static HK_FORCE_INLINE hkVector4Comparison vectorCompareT(const hkIntVector& a, const hkIntVector& b) { return (ORDER == HK_SORT_ASCENDING) ? a.compareLessThanS32(b) : b.compareLessThanS32(a); }

	/// Compare two hkVector4.
	template <hkMathSortDir ORDER>
	static HK_FORCE_INLINE hkVector4Comparison vectorCompareT(const hkVector4& a, const hkVector4& b) { return (ORDER == HK_SORT_ASCENDING) ? a.less(b) : b.less(a); }

	/// Sort a vector.
	template <hkMathSortDir ORDER, typename KEYS>
	static HK_FORCE_INLINE void sort(const KEYS& keys, KEYS* HK_RESTRICT keysOut);
	
	/// Sort a key and value pair of vectors.
	template <hkMathSortDir ORDER, typename KEYS, typename VALUES>
	static HK_FORCE_INLINE void sort(const KEYS& keys, const VALUES& values, KEYS* HK_RESTRICT keysOut, VALUES* HK_RESTRICT valuesOut);
	
	/// Sort a key and value pair of vectors.
	template <hkMathSortDir ORDER, typename KEYS, typename VALUES0, typename VALUES1>
	static HK_FORCE_INLINE void sort(const KEYS& keys, const VALUES0& values0, const VALUES1& values1, KEYS* HK_RESTRICT keysOut, VALUES0* HK_RESTRICT values0Out, VALUES1* HK_RESTRICT values1Out);
};

#include <Common/Base/Math/Vector/hkVectorSort.inl>

#endif //HK_MATH_VECTOR_SORT_H

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
