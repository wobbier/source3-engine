/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HKCD_EXACT_H
#define HKCD_EXACT_H

#include <Geometry/Internal/Types/hkcdRay.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>

// Exact implementation of some critical CD methods.
// This is extremely slow and should be used only when exact results or predicates are required.

// todo: triangleAabb
// todo: triangleTriangle
// todo: others ?

/// Intersect a ray with a triangle.
/// Notes: the result of this method (hkcdRayCastResult) is exact and outputs (fractionInOut, normalOut, hitOut) should be within 0.5 ULP of ground truth.
hkcdRayCastResult HK_CALL hkcdIntersectRayTriangle_Exact(	const hkcdRay& ray, hkFlags<hkcdRayQueryFlags::Enum,hkUint32> rayFlags,
															hkVector4Parameter a, hkVector4Parameter b, hkVector4Parameter c, hkSimdReal& fractionInOut,
															hkVector4* normalOut = HK_NULL, hkVector4* hitOut = HK_NULL );

/// Intersect a ray with an AABB.
/// Notes: the result of this method (bool) is exact and output fractionInOut should be within 0.5 ULP of ground truth.
bool HK_CALL hcdIntersectRayAabb_Exact( const hkcdRay& ray, const hkAabb& aabb, hkSimdReal& fractionInOut );


#endif	//	HKCD_EXACT_H

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
