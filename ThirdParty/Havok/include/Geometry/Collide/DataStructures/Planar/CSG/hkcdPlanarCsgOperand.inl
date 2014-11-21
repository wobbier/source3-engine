/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Gets / sets the geometry

HK_FORCE_INLINE const hkcdPlanarGeometry* hkcdPlanarCsgOperand::getGeometry() const
{
	HK_ASSERT(0x7382463b, !m_regions || !m_solid || m_regions->getGeometry()->getPlanesCollection() == m_solid->getPlanesCollection());
	HK_ASSERT(0x2c121998, !m_geometry|| !m_solid || m_geometry->getPlanesCollection() == m_solid->getPlanesCollection());
	return m_geometry;
}

HK_FORCE_INLINE hkcdPlanarGeometry* hkcdPlanarCsgOperand::accessGeometry()
{
	HK_ASSERT(0x396f02fd, !m_regions || !m_solid || m_regions->getGeometry()->getPlanesCollection() == m_solid->getPlanesCollection());
	HK_ASSERT(0x6e63604e, !m_geometry|| !m_solid || m_geometry->getPlanesCollection() == m_solid->getPlanesCollection());
	return m_geometry;
}

HK_FORCE_INLINE void hkcdPlanarCsgOperand::setGeometry(hkcdPlanarGeometry* geom)
{
	HK_ASSERT(0x536b85c7, !geom || !m_solid || geom->getPlanesCollection() == m_solid->getPlanesCollection());
	m_geometry = geom;
}

//
//	Gets / sets the dangling geometry

HK_FORCE_INLINE const hkcdPlanarGeometry* hkcdPlanarCsgOperand::getDanglingGeometry() const
{
	return m_danglingGeometry;
}

HK_FORCE_INLINE hkcdPlanarGeometry* hkcdPlanarCsgOperand::accessDanglingGeometry()
{
	return m_danglingGeometry;
}

HK_FORCE_INLINE void hkcdPlanarCsgOperand::setDanglingGeometry(hkcdPlanarGeometry* geom)
{
	m_danglingGeometry = geom;
}

//
//	Gets / sets the solid

HK_FORCE_INLINE const hkcdPlanarSolid* hkcdPlanarCsgOperand::getSolid() const
{
	HK_ASSERT(0x6be09d91, !m_regions || !m_solid || m_regions->getGeometry()->getPlanesCollection() == m_solid->getPlanesCollection());
	HK_ASSERT(0x593ebdbb, !m_geometry|| !m_solid || m_geometry->getPlanesCollection() == m_solid->getPlanesCollection());
	return m_solid;
}

HK_FORCE_INLINE hkcdPlanarSolid* hkcdPlanarCsgOperand::accessSolid()
{
	HK_ASSERT(0x67e41692, !m_regions || !m_solid || m_regions->getGeometry()->getPlanesCollection() == m_solid->getPlanesCollection());
	HK_ASSERT(0x494afe7b, !m_geometry|| !m_solid || m_geometry->getPlanesCollection() == m_solid->getPlanesCollection());
	return m_solid;
}

HK_FORCE_INLINE void hkcdPlanarCsgOperand::setSolid(hkcdPlanarSolid* solid)
{
	HK_ASSERT(0x2dabfd93, !m_geometry || !solid || m_geometry->getPlanesCollection() == solid->getPlanesCollection());
	m_solid = solid;
}

//
//	Gets / sets the regions

HK_FORCE_INLINE const hkcdConvexCellsTree3D* hkcdPlanarCsgOperand::getRegions() const
{
	HK_ASSERT(0xd18532d, !m_regions || !m_solid || m_regions->getGeometry()->getPlanesCollection() == m_solid->getPlanesCollection());
	return m_regions;
}

HK_FORCE_INLINE hkcdConvexCellsTree3D* hkcdPlanarCsgOperand::accessRegions()
{
	HK_ASSERT(0x3f373b82, !m_regions || !m_solid || m_regions->getGeometry()->getPlanesCollection() == m_solid->getPlanesCollection());
	return m_regions;
}

HK_FORCE_INLINE void hkcdPlanarCsgOperand::setRegions(hkcdConvexCellsTree3D* regions)
{
	HK_ASSERT(0x664695a9, !regions || !m_solid || regions->getGeometry()->getPlanesCollection() == m_solid->getPlanesCollection());
	m_regions = regions;
}

//
//	Gets / sets the geometry sources

HK_FORCE_INLINE void hkcdPlanarCsgOperand::appendGeometrySources(const hkArray<GeomSource>& geomSources, bool flipGeoms)
{
	for (int g = 0 ; g < geomSources.getSize() ; g++)
	{
		GeomSource newSrc		= geomSources[g];
		newSrc.m_flipPolygons	= flipGeoms ? !newSrc.m_flipPolygons : newSrc.m_flipPolygons;
		addGeometrySource(newSrc);
	}
}

HK_FORCE_INLINE const hkArray<hkcdPlanarCsgOperand::GeomSource>& hkcdPlanarCsgOperand::getGeometrySources() const
{
	return m_geomSources;
}

HK_FORCE_INLINE hkArray<hkcdPlanarCsgOperand::GeomSource>& hkcdPlanarCsgOperand::accessGeometrySources()
{
	return m_geomSources;
}

HK_FORCE_INLINE void hkcdPlanarCsgOperand::removeGeometrySources()
{
	m_geomSources.clearAndDeallocate();
}

//
//	Retrieves the common, shared planes collection

HK_FORCE_INLINE hkcdPlanarGeometryPlanesCollection* hkcdPlanarCsgOperand::accessPlanesCollection()
{
	const hkcdPlanarGeometryPlanesCollection* planesCol = getPlanesCollection();
	return const_cast<hkcdPlanarGeometryPlanesCollection*>(planesCol);
}

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
