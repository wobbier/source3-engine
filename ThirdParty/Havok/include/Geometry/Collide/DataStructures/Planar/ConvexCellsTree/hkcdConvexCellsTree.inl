/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Constructor

template <class CT, class IDT, class CS>
hkcdConvexCellsTree<CT, IDT, CS>::hkcdConvexCellsTree(hkcdPlanarGeometry* geom)
:	hkcdPlanarEntity(geom->accessDebugger())
,	m_mesh(geom)
{
	m_cells.setAndDontIncrementRefCount(new CS());
}

//
//	Constructor 2

template <class CT, class IDT, class CS>
hkcdConvexCellsTree<CT, IDT, CS>::
hkcdConvexCellsTree(CS* cells, hkcdPlanarGeometry* geom)
:	hkcdPlanarEntity(geom->accessDebugger())
,	m_cells(cells)
,	m_mesh(geom)
{}

//
//	Copy constructor. The geometry will not be shared!

template <class CT, class IDT, class CS>
hkcdConvexCellsTree<CT, IDT, CS>::hkcdConvexCellsTree(const hkcdConvexCellsTree& other)
:	hkcdPlanarEntity(other)
{
	// Duplicate geometry
	m_mesh.setAndDontIncrementRefCount(new hkcdPlanarGeometry(*other.m_mesh));

	// Copy the cells
	m_cells.setAndDontIncrementRefCount(new CS());
	m_cells->copy(*other.m_cells);
}

//
//	Returns the cells collection

template <class CT, class IDT, class CS>
HK_FORCE_INLINE const CS* hkcdConvexCellsTree<CT, IDT, CS>::getCells() const					{	return m_cells;	}

template <class CT, class IDT, class CS>
HK_FORCE_INLINE CS* hkcdConvexCellsTree<CT, IDT, CS>::accessCells()								{	return m_cells;	}

//
//	Returns the geometry

template <class CT, class IDT, class CS>
HK_FORCE_INLINE const hkcdPlanarGeometry* hkcdConvexCellsTree<CT, IDT, CS>::getGeometry() const	{	return m_mesh;	}

template <class CT, class IDT, class CS>
HK_FORCE_INLINE hkcdPlanarGeometry* hkcdConvexCellsTree<CT, IDT, CS>::accessGeometry()			{	return m_mesh;	}

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
