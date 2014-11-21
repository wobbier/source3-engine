/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_GEOMETRY_PROCESSING_SIMPLEX_NOISE_H
#define HK_GEOMETRY_PROCESSING_SIMPLEX_NOISE_H

#include <Common/Base/Config/hkProductFeatures.h>

namespace	hkgpSimplexNoise
{
	// Deterministic isotropic noise in N dimensions.
	// - 'positions' must hold N elements.
	// - If FIRST_DER (Gradient) is true, 'der1' must be non-null and large enough to accomodate the N elements of the first derivative.
	// - If SECOND_DER (Laplacian) is true, 'der2' must be non-null and large enough to accomodate the (N*(1+N))/2 elements of the second derivative lower diagonal matrix (row major).
	template <int N, bool FIRST_DER, bool SECOND_DER>
	inline hkReal	evaluate(const hkReal* positions, hkReal* der1 = HK_NULL, hkReal* der2 = HK_NULL);

	// fBm simplex noise.
	template <int N>
	inline hkReal	fBm(const hkVector4& x, int octaves, hkReal offset, hkReal persistence);
};

#include <Common/Internal/GeometryProcessing/SimplexNoise/hkgpSimplexNoise.inl>

#endif // HK_GEOMETRY_PROCESSING_SIMPLEX_NOISE_H

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
