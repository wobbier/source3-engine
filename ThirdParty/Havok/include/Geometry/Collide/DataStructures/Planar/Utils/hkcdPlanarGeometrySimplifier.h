/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_HAVOK_ASSEMBLY_EXCLUDE_FILE

#ifndef HKCD_PLANAR_GEOMETRY_SIMPLIFIER_H
#define HKCD_PLANAR_GEOMETRY_SIMPLIFIER_H

#include <Geometry/Collide/DataStructures/Planar/Geometry/hkcdVertexGeometry.h>

class hkcdPlanarSolid;

/// Utility class that simplifies the polygons in a hkcdPlanarGeometry.
/// It works by rebuilding the 2D boundaries of all polygons sharing the same material Id.
class hkcdPlanarGeometrySimplifier
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdPlanarGeometrySimplifier);

	public:

		/// Performs the simplification. It expects a hkcdVertexGeometry created from
		/// the given planar geometry.
		static void HK_CALL execute(hkcdPlanarGeometry* planarGeometry, const hkcdVertexGeometry* vertexGeometry);

		/// Builds a BSP from the boundary of the surface represented by a group of polygons
		static void HK_CALL buildSimplifyingSolidForPolygonGroup(hkcdPlanarGeometry* planarGeometry, const hkcdVertexGeometry* vertexGeometry, const hkArray<hkcdVertexGeometry::VPolygonId>& vPolyIds,
																hkcdPlanarSolid* solidOut);
};

#endif	// HKCD_PLANAR_GEOMETRY_SIMPLIFIER_H

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
