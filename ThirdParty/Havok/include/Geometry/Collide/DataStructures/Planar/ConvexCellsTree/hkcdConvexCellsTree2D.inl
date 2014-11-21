/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Split a cell returning inside and outside polys ids

HK_FORCE_INLINE void hkcdConvexCellsTree2D::splitCell(hkcdPlanarSolid* solid, CellId cellId, PlaneId splitPlaneId, CellId& insideCellIdOut, CellId& outsideCellIdOut)
{
	const Orientation orientation = m_cells->classify(cellId, splitPlaneId);
	switch ( orientation )
	{
	case hkcdPlanarGeometryPredicates::BEHIND:
		{
			insideCellIdOut		= cellId;
			outsideCellIdOut	= CellId::invalid();
		}
		break;

	case hkcdPlanarGeometryPredicates::IN_FRONT_OF:
		{
			insideCellIdOut		= CellId::invalid();
			outsideCellIdOut	= cellId;
		}
		break;

	case hkcdPlanarGeometryPredicates::ON_PLANE:
		{
			insideCellIdOut		= CellId::invalid();
			outsideCellIdOut	= CellId::invalid();
		}
		break;

	default:
		{
			HK_ASSERT(0x34e3b52d, orientation == hkcdPlanarGeometryPredicates::INTERSECT);
			m_cells->split(cellId, splitPlaneId, insideCellIdOut, outsideCellIdOut);
		}
		break;
	}
}

//
//	Gets / sets the support plane

HK_FORCE_INLINE hkcdConvexCellsTree2D::PlaneId hkcdConvexCellsTree2D::getSupportPlaneId() const	{	return m_supportPlaneId;		}
HK_FORCE_INLINE void hkcdConvexCellsTree2D::setSupportPlaneId(PlaneId supportId)				{	m_supportPlaneId = supportId;	}

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
