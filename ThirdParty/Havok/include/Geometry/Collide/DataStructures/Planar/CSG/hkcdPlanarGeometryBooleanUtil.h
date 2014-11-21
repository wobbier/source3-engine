/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_HAVOK_ASSEMBLY_EXCLUDE_FILE

#ifndef HKCD_PLANAR_GEOMETRY_BOOLEAN_UTIL_H
#define HKCD_PLANAR_GEOMETRY_BOOLEAN_UTIL_H

#include <Geometry/Collide/DataStructures/Planar/CSG/hkcdPlanarCsgOperand.h>
#include <Geometry/Collide/DataStructures/Planar/Memory/hkcdPlanarGeometryPrimitivesCollectionManager.h>

/// Utility for computing boolean operations between planar geometries
class HK_EXPORT_COMMON hkcdPlanarGeometryBooleanUtil
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdPlanarGeometryBooleanUtil);

		// Types
		typedef hkcdPlanarGeometry::PlaneId					PlaneId;
		typedef hkcdPlanarGeometry::Polygon					Polygon;
		typedef hkcdPlanarGeometry::PolygonId				PolygonId;
		typedef hkcdPlanarGeometryPrimitives::CollectionManager<hkcdPlanarGeometryPolygonCollection>	PolyCollManager;
		typedef hkcdPlanarGeometryPrimitives::CollectionManager<hkcdConvexCellsCollection>				CellCollManager;

	public:

		/// Supported operations
		enum Operation
		{
			OP_UNION			= 0,	///< Computes the union of A and B
			OP_INTERSECTION		= 1,	///< Computes the intersection of A and B
			OP_DIFFERENCE		= 2,	///< Computes the difference A - B
		};

		/// Boolean state, to be maintained between operations
		struct BooleanState
		{};

	public:

		/// Initialize an in-place boolean operation.
		static BooleanState* HK_CALL setOperatorsForInPlaceMerge(hkcdPlanarCsgOperand* inputOutputOperand, hkcdPlanarGeometry& commonGeom);

		/// Merge in-place. Use this instead of "compute" whenever you need to stack several boolean operation on the same BSP tree.
		static void HK_CALL mergeInPlace(BooleanState* bState, const hkcdPlanarCsgOperand* operandToMergeWith, Operation op, bool collapse = true);

		/// Finalize th in-place merge.
		static void HK_CALL finalizeInPlaceMerge(BooleanState* bState, hkcdPlanarCsgOperand* operandInOut, bool collapse = false);

		/// Computes A op B. Will assert if called with OP_DIFFERENCE, as that would require flipping the solidB.
		static void HK_CALL compute(const hkcdPlanarCsgOperand* operandA, Operation op, const hkcdPlanarCsgOperand* operandB,
									hkRefPtr<const hkcdPlanarCsgOperand>* resultOut, hkRefPtr<const hkcdPlanarCsgOperand>* dualResultOut, 
									bool manifoldCells, bool dynamicSplit, 
									PolyCollManager* polysCollManager = HK_NULL, CellCollManager* cellsCollManager = HK_NULL);

		/// Projects the given coplanar polygons on the boundary of (A op B) and adds the result to the mesh
		static void HK_CALL addCoplanarPolygonsToMesh(hkcdPlanarGeometry& workingGeom, const hkArray<PolygonId>& coplanarPolysIn, int numPolysOfA, hkArray<PolygonId>& meshPolysOut);

		/// Projects the given coplanar polygons on the boundary of (A op B) and adds the result to the mesh
		/// This version check intersection between polygons of A against polygons of B (simple algorithm with square complexity)
		static void HK_CALL addCoplanarPolygonsToMeshPairedIntersectionTest(hkcdPlanarGeometry& workingGeom, const hkArray<PolygonId>& coplanarPolysIn, int numPolysOfA, hkArray<PolygonId>& meshPolysOut);

};

#endif	//	HKCD_PLANAR_GEOMETRY_BOOLEAN_UTIL_H

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
