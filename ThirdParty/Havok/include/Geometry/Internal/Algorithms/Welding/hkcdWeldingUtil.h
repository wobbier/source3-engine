/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HKCD_WELDING_UTIL_H
#define HKCD_WELDING_UTIL_H

#include <Geometry/Internal/Algorithms/Gsk/hkcdGsk.h>
#include <Geometry/Internal/Types/hkcdManifold4.h>
#include <Geometry/Internal/Types/hkcdVertex.h>

namespace hkcdGsk { struct Cache; }

/// Utility to help with welding
struct HK_EXPORT_COMMON hkcdWeldingUtil
{
	struct Config
	{
		Config( hkReal radiusA ) { m_radiusA = radiusA; m_tolerance = 0.05f; }
		HK_PAD_ON_SPU(hkReal) m_radiusA;
		HK_PAD_ON_SPU(hkReal) m_tolerance;
	};

	struct MotionWeldConfig
	{
		// parameters valid for convex vs composite
		hkTransform m_transformA;
		HK_PAD_ON_SPU(const hkcdVertex*) m_verticesA;
		HK_PAD_ON_SPU(int) m_numVerticesA;
		HK_PAD_ON_SPU(const void*) m_shapeA;

		hkVector4 m_velocityDirection;				// the normalized direction of the relative linear velocity in world space
		hkVector4 m_velocityDirectionA;				// the normalized direction of the relative linear velocity in A-space
		hkSimdReal m_relLinearVelocity;				// the length of m_velocityDirection before it got normalized

		hkSimdReal m_maxAllowedTotalCastDistance;
		hkSimdReal m_gskDistance;			// assuming radius 0.0f
		hkSimdReal m_extraConvexRadius;		// convex radius to be used, the smaller the better the algorithm works (so try 0.0f if possible)
		hkSimdReal m_allowedApproachingVelocity;

		// parameters needed to be set for each child shape of the composite shape

		hkTransform m_aTb;					// relative transform between b and a

		HK_PAD_ON_SPU(const hkcdVertex*) m_verticesB;
		HK_PAD_ON_SPU(int)			m_numVerticesB;
		HK_PAD_ON_SPU(const void*) m_shapeB;
		hkSimdReal m_allowedPenetration;
	};

	typedef hkcdGsk::GetClosestPointStatus (*getClosestPountsFunc)(
		const void* shapeA, const hkcdVertex* vertsA, int numVertsA,
		const void* shapeB, const hkcdVertex* vertsB, int numVertsB,
		const hkcdGsk::GetClosestPointInput& input, hkcdGsk::Cache* HK_RESTRICT cache,
		hkcdGsk::GetClosestPointOutput& output );

	/// Perform a motion weld on a single convex versus convex
	static hkResult HK_CALL motionWeldCvxVsCvx( 
		const MotionWeldConfig& config,	const hkcdGsk::Cache& gskCacheBlueprint, hkVector4* weldedNormalInOut );

	/// Perform a motion weld on a single convex versus convex objects, using a dedicated getClosestPoints function.
	static hkResult HK_CALL motionWeldCvxVsCvx( 
		getClosestPountsFunc func, const MotionWeldConfig& config, const hkcdGsk::Cache& gskCacheBlueprint,
		hkVector4* weldedNormalInOut );

	/// Modify the normal on a manifold. This will try to guess the new distances
	static void applyModifiedNormal(
		hkVector4Parameter newNormal, hkSimdRealParameter radiusA,
		hkcdManifold4* HK_RESTRICT manifoldBInOut );

	/// inline version of applyModifiedNormal(), include hkcdWeldingUtil.inl if you want to use this.
	static HK_FORCE_INLINE void _applyModifiedNormal(
		hkVector4Parameter newNormal, hkSimdRealParameter radiusA,
		hkcdManifold4* HK_RESTRICT manifoldBInOut );
};


#endif //HKCD_WELDING_UTIL_H

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
