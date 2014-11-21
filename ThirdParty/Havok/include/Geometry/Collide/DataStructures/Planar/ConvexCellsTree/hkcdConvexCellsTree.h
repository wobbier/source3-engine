/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_HAVOK_ASSEMBLY_EXCLUDE_FILE

#ifndef HKCD_CONVEX_CELLS_TREE_H
#define HKCD_CONVEX_CELLS_TREE_H

#include <Geometry/Collide/DataStructures/Planar/Solid/hkcdPlanarSolid.h>
#include <Geometry/Collide/DataStructures/Planar/Memory/hkcdConvexCellsCollection.h>
#include <Geometry/Collide/DataStructures/IntAabb/hkcdIntAabb.h>

#include <Common/Base/Container/LocalArray/hkLocalBuffer.h>
#include <Common/Base/Algorithm/Collide/1AxisSweep/hk1AxisSweep.h>

class hkcdPlanarSolid;

/// Base class for a convex cells tree
template <class CellType, class CellIdType, class CellStorage>
class hkcdConvexCellsTree : public hkcdPlanarEntity
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY);

	public:

		// Types
		typedef CellType					Cell;
		typedef CellIdType					CellId;
		typedef hkcdPlanarSolid::NodeId		NodeId;
		typedef hkcdPlanarSolid::Node		Node;
		typedef PlanesCollection::Bounds	Bounds;

	public:

		/// Constructor
		hkcdConvexCellsTree(hkcdPlanarGeometry* geom);

		/// Constructor from data pointers
		hkcdConvexCellsTree(CellStorage* cells, hkcdPlanarGeometry* geom);

		/// Copy constructor. The geometry will not be shared!
		hkcdConvexCellsTree(const hkcdConvexCellsTree& other);

	public:
		
		/// Returns the cells collection
		HK_FORCE_INLINE const CellStorage* getCells() const;
		HK_FORCE_INLINE CellStorage* accessCells();

		/// Returns the mesh
		HK_FORCE_INLINE const hkcdPlanarGeometry* getGeometry() const;
		HK_FORCE_INLINE hkcdPlanarGeometry* accessGeometry();

	protected:

 		hkRefPtr<CellStorage> m_cells;			///< The array of cells
 		hkRefPtr<hkcdPlanarGeometry> m_mesh;	///< A planar mesh, to manage the planes and polygons
};

#include <Geometry/Collide/DataStructures/Planar/ConvexCellsTree/hkcdConvexCellsTree.inl>

#endif	// HKCD_CONVEX_CELLS_TREE_H

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
