/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HKCD_RAY_TRIANGLE_INTERSECTION_H
#define HKCD_RAY_TRIANGLE_INTERSECTION_H

#include <Geometry/Internal/Types/hkcdRay.h>
#include <Geometry/Internal/Types/hkcdRayBundle.h>

struct hkcdRayBundle;

// Uncomment the next line to enable Ray-Triangle false negatives detection. Warning: This is VERY slow.
//#define HKCD_DETECT_RAY_TRIANGLE_FALSE_NEGATIVES

/// Internal triangle functions, read the function comments carefully before using these functions.
namespace hkcdRayCastTriangle
{
	/// Intersect a ray with a triangle.
	/// This function ensures that a ray never passes through a closed mesh, however it might report hits slightly
	/// outside the epsilon boundary of a triangle.
	/// Triangles are considered two sided by default, but can be seen as one sided by setting the query flags.
	///
	/// Usage: This function is optimized for performance, not for usability! So please note that:
	///		-	The endpoint of the ray is calculated by ray.start + ray.directon * fractionInOut
	///		-	fractionInOut must be initialized (e.g. by ray.getFraction()).
	///     -   ray.getFraction() is not used.
	///		-   fractionInOut and normalOut are modified regardless whether you have a hit or not.
	///			So you need to make sure that you only modify the input fraction of the next ray-triangle test if a
	///			previous test had a hit.
	/// Quality:
	///     -	The ray will not go through a closed mesh.
	///		-	If the start point is on a triangle, the ray might or might not hit.
	///		-	If the end   point is on a triangle, the ray might or might not hit.
	///         This is due to the fact that we are working with floating point numbers and it does not make sense
	///         to fix this for some rare esoteric cases (like axis aligned triangles) and thereby making this code slower for
	///         normal usage.
	///     -   If a ray hits a triangle where the ray direction is nearly perpendicular to the triangle normal,
	///         this function might return UNDEFINED_FACE_HIT. But if you change the ray so that it hits another part
	///			of the triangle you might get a different result.
	///		-   2 concatenated rays (the second ray's start-point is identical to the first rays end-point) 
	///			might go through a mesh at the shared point
	///     -   To account for numerical drift when you have tiled meshes, this function also inflates the triangles by
	///			hkcdRayCastTriangle::g_tolerance (set to 0.01f by default).
	/// 
	/// Note about the implementation: The implementation calculates the perfect epsilon of how to expand the edges 
	/// so we do not miss collisions. However if 2 edges form a very sharp angle (as seen from the ray start point),
	/// the intersection of the 2 expanded edges (as seen from the ray start point) might be slightly outside the triangle.
	/// Since the expanded edges are used to decide whether the ray hits, the ray might hit slightly outside the triangle.
	/// Example: Your raylength is 100km, so we roughly expand the edges by 2.0f * 100km * FLOAT_EPS(=1e-7) = 2cm.
	///          If our triangle corner is very sharp as seen from the ray start point (~1degree), the ray might hit the
	///          triangle easily 20 or more centimeters outside the triangle.
	HK_EXPORT_COMMON hkcdRayCastResult HK_CALL safeUsingDynamicTolerance(
		const hkcdRay& ray,	hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC,
		hkFlags<hkcdRayQueryFlags::Enum,hkUint32> flags, 
		hkSimdReal& fractionInOut, hkVector4& nonUnitNormalOut );

	/// Intersect a ray with a triangle.
	/// Same as safeUsingDynamicTolerance() but without dynamic tolerance.
	/// Good numerical accuracy, about 30% faster than safeUsingDynamicTolerance(), but might pass through a mesh.
	/// Also the likelihood of hitting a triangle outside its area is reduced by factor of 10.
	/// Also this function never returns UNDEFINED_FACE_HIT.
	/// Also this version ignores hkcdRayCastTriangle::g_tolerance
	HK_EXPORT_COMMON hkcdRayCastResult HK_CALL fastUsingZeroTolerance(
		const hkcdRay& ray,	hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC,
		hkFlags<hkcdRayQueryFlags::Enum,hkUint32> flags, 
		hkSimdReal& fractionInOut, hkVector4& nonUnitNormalOut );


	/// DEPRECATED: Intersects a ray bundle with the triangle. Not so fast and bad epsilon behavior.
	HK_EXPORT_COMMON hkVector4Comparison HK_CALL hkcdSegmentBundleTriangleIntersect(
		const hkcdRayBundle& rayBundle, hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC,
		hkSimdRealParameter tolerance,
		hkFourTransposedPoints& normalsOut, hkVector4& fractionsInOut );

	/// Intersect a sphere (ray + radius) with a triangle. 
	HK_EXPORT_COMMON hkBool32 HK_CALL sphereCastTriangle(
		const hkcdRay& ray, hkSimdRealParameter radius,
		hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC,
		hkSimdReal* fractionOut, hkVector4* planeOut );

	/// Inline implementation of safeUsingDynamicTolerance() and fastZeroTolerance(), only available if you have access to the .inl file
	template<bool ENABLE_DYNAMIC_TOLERANCE, bool SORT_EDGES, bool ENABLE_BEVEL_PLANE_CHECK>
	HK_FORCE_INLINE hkcdRayCastResult HK_CALL _rayTriangleImpl(
		const hkcdRay& ray, hkVector4Parameter vA, hkVector4Parameter vB, hkVector4Parameter vC,
		hkFlags<hkcdRayQueryFlags::Enum,hkUint32> flags, hkSimdReal& fractionInOut, hkVector4& nonUnitNormalOut );


	/// When a ray is cast against triangles using safeUsingDynamicTolerance(), the triangles are virtually inflated
	/// by this tolerance. This might be necessary if your have subdivided a mesh into multiple bodies and you get small
	/// gaps between neighboring meshes due to numerical inaccuracies.
	/// The default value is 1cm, which is good for tiled meshes up to 100km away from the origin.
	/// If you have a perfect mesh, you can set this value to 0.
	extern hkSimdReal g_tolerance;

	/// The default value for g_tolerance.
	extern const hkSimdReal g_defaultTolerance;
}

#endif	//	HKCD_RAY_TRIANGLE_INTERSECTION_H

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
