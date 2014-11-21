/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Returns the collection of planes

HK_FORCE_INLINE const hkcdPlanarGeometryPlanesCollection* hkcdVertexGeometry::getPlanesCollection() const	{	return m_planes;	}
HK_FORCE_INLINE hkcdPlanarGeometryPlanesCollection* hkcdVertexGeometry::accessPlanesCollection()			{	return m_planes;	}

//
//	Returns the vertices

HK_FORCE_INLINE const hkArray<hkcdVertexGeometry::Vertex>& hkcdVertexGeometry::getVertices() const	{	return m_vertices;	}
HK_FORCE_INLINE hkArray<hkcdVertexGeometry::Vertex>& hkcdVertexGeometry::accessVertices()			{	return m_vertices;	}

//
//	Returns the edge associated with the given Id

HK_FORCE_INLINE const hkcdVertexGeometry::Edge& hkcdVertexGeometry::getEdge(EdgeId edgeId) const	{	return m_edges[edgeId.value() & (~FLIPPED_EDGE_FLAG)];	}
HK_FORCE_INLINE hkcdVertexGeometry::Edge& hkcdVertexGeometry::accessEdge(EdgeId edgeId)				{	return m_edges[edgeId.value() & (~FLIPPED_EDGE_FLAG)];	}

//
//	Returns the line associated with the given Id

HK_FORCE_INLINE const hkcdVertexGeometry::Line& hkcdVertexGeometry::getLine(hkcdVertexGeometry::LineId lineId) const	{	return m_lines[lineId.value()];	}
HK_FORCE_INLINE hkcdVertexGeometry::Line& hkcdVertexGeometry::accessLine(hkcdVertexGeometry::LineId lineId)				{	return m_lines[lineId.value()];	}

//
//	Returns the collection of polygons

HK_FORCE_INLINE const hkcdVertexGeometry::VPolygonCollection& hkcdVertexGeometry::getPolygons() const	{	return m_polys;	}
HK_FORCE_INLINE hkcdVertexGeometry::VPolygonCollection& hkcdVertexGeometry::accessPolygons()			{	return m_polys;	}

//
//	Sets the planes and vertex Id

HK_FORCE_INLINE void hkcdVertexGeometry::Vertex::setPlanesAndId(PlaneId planeIdA, PlaneId planeIdB, PlaneId planeIdC, int vtxId)
{
	const int mask		= ~hkcdPlanarGeometryPrimitives::FLIPPED_PLANE_FLAG;
	hkIntVector vtx;	vtx.set(planeIdA.value() & mask, planeIdB.value() & mask, planeIdC.value() & mask, vtxId);
	m_planes.setSortS32<3, HK_SORT_ASCENDING>(vtx);
}

//
//	Sets the planes

HK_FORCE_INLINE void hkcdVertexGeometry::Line::set(PlaneId planeIdA, PlaneId planeIdB, LineId lineId)
{
	const int mask	= ~hkcdPlanarGeometryPrimitives::FLIPPED_PLANE_FLAG;
	hkIntVector v;	v.set(planeIdA.value() & mask, planeIdB.value() & mask, 0, lineId.value());
	
	m_data.setSortS32<2, HK_SORT_ASCENDING>(v);
}

//
//	Sets the line Id

HK_FORCE_INLINE void hkcdVertexGeometry::Line::setId(LineId lineId)
{
	m_data.setComponent<3>(lineId.value());
}

//
//	Sets the edge data

HK_FORCE_INLINE void hkcdVertexGeometry::Edge::set(int vtxA, int vtxB, LineId lineId, EdgeId edgeId)
{
	hkIntVector v;	v.set(vtxA, vtxB, lineId.valueUnchecked(), edgeId.valueUnchecked());
	m_data.setSortS32<2, HK_SORT_ASCENDING>(v);
}

//
//	Returns true if the edge contains the given vertex

HK_FORCE_INLINE bool hkcdVertexGeometry::Edge::hasVertex(int vertexId) const
{
	return (getStartVertex() == vertexId) || (getEndVertex() == vertexId);
}

//
//	Gets / sets the material id

HK_FORCE_INLINE hkUint32 hkcdVertexGeometry::VPolygon::getMaterialId() const
{
	return m_materialId & VPolygonCollection::PAYLOAD_MASK;
}

HK_FORCE_INLINE void hkcdVertexGeometry::VPolygon::setMaterialId(int mtlId)
{
	HK_ASSERT(0x1cf0dcaf, !(mtlId & VPolygonCollection::BLOCK_FLAGS_MASK));
	m_materialId = (mtlId & VPolygonCollection::PAYLOAD_MASK) | (m_materialId & VPolygonCollection::BLOCK_FLAGS_MASK);
}

//
//	Returns the i-th boundary edge Id

HK_FORCE_INLINE hkcdVertexGeometry::EdgeId hkcdVertexGeometry::VPolygon::getBoundaryEdgeId(int i) const
{
	return EdgeId((&m_userData)[1 + i] & VPolygonCollection::PAYLOAD_MASK);
}

HK_FORCE_INLINE void hkcdVertexGeometry::VPolygon::setBoundaryEdgeId(int i, EdgeId pid)
{
	hkUint32& p = (&m_userData)[1 + i];
	p = (p & VPolygonCollection::BLOCK_FLAGS_MASK) | (pid.valueUnchecked() & VPolygonCollection::PAYLOAD_MASK);
}

//
//	Gets / sets the user data

HK_FORCE_INLINE hkUint32 hkcdVertexGeometry::VPolygon::getUserData() const
{
	return m_userData & VPolygonCollection::PAYLOAD_MASK;
}

HK_FORCE_INLINE void hkcdVertexGeometry::VPolygon::setUserData(hkUint32 userData)
{
	m_userData = (m_userData & VPolygonCollection::BLOCK_FLAGS_MASK) | (userData & VPolygonCollection::PAYLOAD_MASK);
}

//
//	Allocates a polygon

HK_FORCE_INLINE hkcdVertexGeometry::VPolygonId hkcdVertexGeometry::VPolygonCollectionBase::alloc(hkUint32 materialId, hkUint32 userData, int numEdges)
{
	// Allocate polygon storage
	hkUint32 allocSize = hkMath::max2<hkUint32>(MIN_BLOCK_SIZE, (sizeof(VPolygon) / sizeof(int)) + numEdges);
	const VPolygonId polyId(blockAlloc(allocSize));

	// Set it up
	VPolygon& poly = *reinterpret_cast<VPolygon*>(&m_storage[polyId.value()]);
	poly.setMaterialId(materialId);
	poly.setUserData(userData);

	// Get edges and mark the last one
	hkUint32* edges = reinterpret_cast<hkUint32*>(&poly.m_userData);
	edges[numEdges] |= END_PAYLOAD_FLAG;

	// Sanity checks
#ifdef HK_DEBUG
	{
		// There should be just one plane marked as the end plane
		for (int k = 0; k < numEdges; k++)
		{
			HK_ASSERT(0x5e96e8a3, !(edges[k] & END_PAYLOAD_FLAG));
		}

		// There should be and end block marker
		HK_ASSERT(0x27fb4c, edges[allocSize - VPolygon::BOUNDARY_EDGES_OFFSET] & END_BLOCK_FLAG);

		// There should be no other end block marker
		for (hkUint32 k = 0; k < allocSize - VPolygon::BOUNDARY_EDGES_OFFSET; k++)
		{
			HK_ASSERT(0x20fa5bdb, !(edges[k] & END_BLOCK_FLAG));
		}
	}
#endif

	return polyId;
}

//
//	Frees the given polygon

HK_FORCE_INLINE void hkcdVertexGeometry::VPolygonCollectionBase::free(VPolygonId polyId)
{
	blockFree(polyId.value());
}

//
//	Retrieves the polygon at the given Id.

HK_FORCE_INLINE const hkcdVertexGeometry::VPolygon& hkcdVertexGeometry::VPolygonCollection::getPolygon(VPolygonId polyId) const
{
	return *reinterpret_cast<const VPolygon*>(&m_storage[polyId.value()]);
}

HK_FORCE_INLINE hkcdVertexGeometry::VPolygon& hkcdVertexGeometry::VPolygonCollection::accessPolygon(VPolygonId polyId)
{
	return *reinterpret_cast<VPolygon*>(&m_storage[polyId.value()]);
}

//
//	Computes the number of boundary edges

HK_FORCE_INLINE int hkcdVertexGeometry::VPolygonCollection::getNumBoundaryEdges(VPolygonId polyId) const
{
	const int* planes = &m_storage[polyId.value() + VPolygon::USER_DATA_OFFSET];

	int count = 0;
	while ( !(planes[count++] & END_PAYLOAD_FLAG) ) {}
	return count - 1;
}

//
//	Returns the first valid polygon Id

HK_FORCE_INLINE hkcdVertexGeometry::VPolygonId hkcdVertexGeometry::VPolygonCollection::getFirstPolygonId() const
{
	return getNextPolygonId(VPolygonId(INVALID_BLOCK_ADDR));
}

//
//	Returns the last valid polygon Id

HK_FORCE_INLINE hkcdVertexGeometry::VPolygonId hkcdVertexGeometry::VPolygonCollection::getLastPolygonId() const
{
	return getPrevPolygonId(VPolygonId(m_storage.getSize() - MIN_BLOCK_SIZE));
}

//
//	Returns the next valid polygon Id

HK_FORCE_INLINE hkcdVertexGeometry::VPolygonId hkcdVertexGeometry::VPolygonCollection::getNextPolygonId(VPolygonId polyId) const
{
	return VPolygonId(getNextAllocatedAddress(polyId.valueUnchecked()));
}

//
//	Returns the next valid polygon Id

HK_FORCE_INLINE hkcdVertexGeometry::VPolygonId hkcdVertexGeometry::VPolygonCollection::getPrevPolygonId(VPolygonId polyId) const
{
	return VPolygonId(getPrevAllocatedAddress(polyId.valueUnchecked()));
}

//
//	Returns the number of valid polygon Ids stored

HK_FORCE_INLINE int hkcdVertexGeometry::VPolygonCollection::getNumPolygons() const
{
	int count = 0;
	for (VPolygonId pid = getFirstPolygonId(); pid.isValid(); pid = getNextPolygonId(pid))
	{
		count++;
	}
	return count;
}

//
//	Returns the I-th vertex of the given edge

template <int I>
HK_FORCE_INLINE int hkcdVertexGeometry::getEdgeVertex(EdgeId edgeId) const
{
	const int edgeIdx	= edgeId.value();
	const Edge& edge	= m_edges[edgeIdx & (~FLIPPED_EDGE_FLAG)];
	const int vtxIdx	= ((edgeIdx >> FLIPPED_EDGE_BIT) ^ I) & 1;
	return edge.getVertex(vtxIdx);
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
