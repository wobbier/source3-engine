/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef __HAVOK_PARSER__



//
//	Accessors (Node Storage)

HK_FORCE_INLINE const hkcdPlanarSolid::Node& hkcdPlanarSolid::NodeStorage::getNode(NodeId nodeId) const
{
	return m_storage[nodeId.value()];
}

HK_FORCE_INLINE hkcdPlanarSolid::Node& hkcdPlanarSolid::NodeStorage::accessNode(NodeId nodeId)
{
	return m_storage[nodeId.value()];
}

//
//	Allocation (Node Storage)

HK_FORCE_INLINE hkcdPlanarSolid::NodeId hkcdPlanarSolid::NodeStorage::allocate()
{
	// Check if space
	if ( m_firstFreeNodeId.isValid() )
	{
		const NodeId ret	= m_firstFreeNodeId;
		m_firstFreeNodeId	= getNode(m_firstFreeNodeId).m_nextFreeNodeId;
		accessNode(ret).m_nextFreeNodeId = NodeId::invalid();
		return ret;
	}
	else
	{
		m_storage.expandOne().m_nextFreeNodeId = NodeId::invalid();
		return NodeId(m_storage.getSize() - 1);
	}
}

HK_FORCE_INLINE void hkcdPlanarSolid::NodeStorage::clear()
{
	m_storage.clear();
	m_firstFreeNodeId		= NodeId::invalid();
}

HK_FORCE_INLINE int hkcdPlanarSolid::NodeStorage::getCapacity() const
{
	return m_storage.getSize();
}

HK_FORCE_INLINE void hkcdPlanarSolid::NodeStorage::release(NodeId nodeId)
{
	accessNode(nodeId).m_nextFreeNodeId = m_firstFreeNodeId;
	accessNode(nodeId).clear();
	m_firstFreeNodeId = nodeId;
}

//
//	Other (Node storage)

HK_FORCE_INLINE void hkcdPlanarSolid::NodeStorage::swapStorage(hkArray<Node>& storage)
{
	m_storage.swap(storage);
	m_firstFreeNodeId		= NodeId::invalid();
}

HK_FORCE_INLINE void hkcdPlanarSolid::NodeStorage::compact()
{
	m_storage.optimizeCapacity(0, true);
	m_firstFreeNodeId		= NodeId::invalid();
}

//
//	Gets the node having the given Id.

HK_FORCE_INLINE const hkcdPlanarSolid::Node& hkcdPlanarSolid::getNode(NodeId nodeId) const	{	return m_nodes->getNode(nodeId);	}
HK_FORCE_INLINE hkcdPlanarSolid::Node& hkcdPlanarSolid::accessNode(NodeId nodeId)			{	return m_nodes->accessNode(nodeId);	}

//
//	Returns the nodes

HK_FORCE_INLINE const hkcdPlanarSolid::NodeStorage* hkcdPlanarSolid::getNodes() const
{
	return m_nodes;
}

HK_FORCE_INLINE hkcdPlanarSolid::NodeStorage* hkcdPlanarSolid::accessNodes()
{
	return m_nodes;
}

//
//	Returns the collection of planes used by this solid

HK_FORCE_INLINE hkcdPlanarGeometryPlanesCollection* hkcdPlanarSolid::accessPlanesCollection()			{	return const_cast<hkcdPlanarGeometryPlanesCollection*>(m_planes.val());	}
HK_FORCE_INLINE const hkcdPlanarGeometryPlanesCollection* hkcdPlanarSolid::getPlanesCollection() const	{	return m_planes;	}

//
//	Returns true if the tree is valid

HK_FORCE_INLINE bool hkcdPlanarSolid::isValid() const
{
	return m_rootNodeId.isValid();
}

//
//	Returns true if the tree represent the empty set

HK_FORCE_INLINE bool hkcdPlanarSolid::isEmpty() const
{
	return (isValid() && getNodeLabel(m_rootNodeId) == NODE_TYPE_OUT);
}

//
//	Returns true if the given node is internal

HK_FORCE_INLINE bool hkcdPlanarSolid::isInternal(NodeId nodeId) const
{
	if ( nodeId.isValid() )
	{
		const Node& node = getNode(nodeId);
		return node.isAllocated() && (node.m_typeAndFlags == NODE_TYPE_INTERNAL);
	}
	return false;
}

//
//	Returns the Id of the root node

HK_FORCE_INLINE const hkcdPlanarSolid::NodeId hkcdPlanarSolid::getRootNodeId() const
{
	return m_rootNodeId;
}

//
//	Returns the label of a given leaf node

HK_FORCE_INLINE hkcdPlanarSolid::NodeTypes hkcdPlanarSolid::getNodeLabel(NodeId nodeId) const
{
	const Node& node = getNode(nodeId);
	return (hkcdPlanarSolid::NodeTypes)node.m_typeAndFlags;
}

//
//	Creates a new internal node

HK_FORCE_INLINE hkcdPlanarSolid::NodeId hkcdPlanarSolid::createNode(PlaneId splitPlaneId, NodeId leftChild, NodeId rightChild)
{
	const NodeId nodeId = m_nodes->allocate();
	Node& node = accessNode(nodeId);

	node.m_planeId		= splitPlaneId;
	node.m_left			= leftChild;
	node.m_right		= rightChild;
	node.m_typeAndFlags	= NODE_TYPE_INTERNAL;
	node.m_data			= 0;
	return nodeId;
}

//
// Default nodes accessors

HK_FORCE_INLINE hkcdPlanarSolid::NodeId hkcdPlanarSolid::createInsideNode(NodeId parentId)
{
	NodeId inNodeId				= m_nodes->allocate();
	Node& nodeIn				= accessNode(inNodeId);
	nodeIn.m_left				= NodeId::invalid();
	nodeIn.m_right				= NodeId::invalid();
	nodeIn.m_typeAndFlags		= NODE_TYPE_IN;
	nodeIn.m_planeId			= PlaneId::invalid();
	nodeIn.m_parent				= parentId;
	nodeIn.m_data				= 0;
	return inNodeId;
}

HK_FORCE_INLINE hkcdPlanarSolid::NodeId hkcdPlanarSolid::createOutsideNode(NodeId parentId)
{
	NodeId outNodeId			= m_nodes->allocate();
	Node& nodeOut				= accessNode(outNodeId);
	nodeOut.m_left				= NodeId::invalid();
	nodeOut.m_right				= NodeId::invalid();
	nodeOut.m_typeAndFlags		= NODE_TYPE_OUT;
	nodeOut.m_planeId			= PlaneId::invalid();
	nodeOut.m_parent			= parentId;
	nodeOut.m_data				= 0;
	return outNodeId;
}

HK_FORCE_INLINE hkcdPlanarSolid::NodeId hkcdPlanarSolid::createUnknownNode(NodeId parentId)
{
	NodeId unknownNodeId		= m_nodes->allocate();
	Node& nodeUnknown			= accessNode(unknownNodeId);
	nodeUnknown.m_left			= NodeId::invalid();
	nodeUnknown.m_right			= NodeId::invalid();
	nodeUnknown.m_typeAndFlags	= NODE_TYPE_UNKNOWN;
	nodeUnknown.m_planeId		= PlaneId::invalid();
	nodeUnknown.m_parent		= parentId;
	nodeUnknown.m_data			= 0;
	return unknownNodeId;
}

//
//	Sets the root node

HK_FORCE_INLINE void hkcdPlanarSolid::setRootNode(NodeId rootNodeId)
{
	m_rootNodeId = rootNodeId;
}

//
//	Returns true if the given node can be collapsed to its parent

HK_FORCE_INLINE bool hkcdPlanarSolid::canCollapse(NodeId nodeId) const
{
	if ( !nodeId.isValid() ) return false;
	const Node& node		= getNode(nodeId);
	const Node& nodeLeft	= getNode(node.m_left);
	const Node& nodeRight	= getNode(node.m_right);
	return	(nodeLeft.m_typeAndFlags == nodeRight.m_typeAndFlags) &&
			((nodeLeft.m_typeAndFlags == hkcdPlanarSolid::NODE_TYPE_IN) || (nodeLeft.m_typeAndFlags == hkcdPlanarSolid::NODE_TYPE_OUT));
}

//
//	Returns true if the triangle is allocated

HK_FORCE_INLINE bool hkcdPlanarSolid::Node::isAllocated() const
{
	return m_typeAndFlags != NODE_TYPE_FREE;
}

//
//	Marks this node as not-allocated

HK_FORCE_INLINE void hkcdPlanarSolid::Node::clear()
{
	m_typeAndFlags = NODE_TYPE_FREE;
}

//
//	Called by the free-list to initialize an unallocated entry

HK_FORCE_INLINE void hkcdPlanarSolid::Node::setEmpty(Node& element, hkUint32 next)
{
	(hkUint32&)element = next;	element.clear();
}

//
//	Returns the index of the next free element. Will be called only with empty elements

HK_FORCE_INLINE hkUint32 hkcdPlanarSolid::Node::getNext(const Node& element)
{
	return (hkUint32&)element;
}

//
//	Sets the given child id

HK_FORCE_INLINE void hkcdPlanarSolid::Node::setChildId(int childIdx, NodeId childNodeId)
{
	(&m_left)[childIdx] = childNodeId;
}

//
//	Classifies the polygons into inside, boundary, and outside parts

HK_FORCE_INLINE void hkcdPlanarSolid::classifyPolygons(	hkcdPlanarGeometry& polySoup, const hkArray<PolygonId>& polygonsIn,
														hkArray<PolygonId>& insidePieces, hkArray<PolygonId>& boundaryPieces, hkArray<PolygonId>& outsidePieces, ArrayMgr* arrayMgr) const
{
	if ( arrayMgr == HK_NULL )
	{
		ArrayMgr localArrayMgr;
		classifyPolygons(polySoup, getRootNodeId(), polygonsIn, insidePieces, boundaryPieces, outsidePieces, localArrayMgr);
	}
	else
	{
		classifyPolygons(polySoup, getRootNodeId(), polygonsIn, insidePieces, boundaryPieces, outsidePieces, *arrayMgr);
	}
}

//
//	Constructor

HK_FORCE_INLINE hkcdPlanarSolid::ArrayMgr::ArrayMgr()
{
	clear();
}

//
//	Allocates an array slot. The storage for the array is not yet allocated

HK_FORCE_INLINE hkcdPlanarSolid::ArrayId hkcdPlanarSolid::ArrayMgr::allocArraySlot()
{
	const ArrayId aid	= m_arrays.allocate();
	ArraySlot& slot		= m_arrays[aid];
	slot.m_offset	= 0;
	slot.m_size		= 0;

	return aid;
}

//
// Returns the array slot at the given Id

HK_FORCE_INLINE hkcdPlanarSolid::ArraySlot& hkcdPlanarSolid::ArrayMgr::getArraySlot(ArrayId aid)			
{	
	return m_arrays[aid];
}

//
// Returns the array storage for the given Id

HK_FORCE_INLINE hkcdPlanarSolid::PolygonId hkcdPlanarSolid::ArrayMgr::getPolygonId(ArrayId aid, int k)		
{	
	return PolygonId(m_storage[getArraySlot(aid).m_offset + k] & PAYLOAD_MASK);	
}

//
//	Allocates storage for numPolygons in the array at the given slot

HK_FORCE_INLINE void hkcdPlanarSolid::ArrayMgr::allocArrayStorage(ArrayId arraySlot, const PolygonId* HK_RESTRICT srcPolyIds, int numPolygons)
{
	// Allocate polygons
	ArraySlot& arrayElement = m_arrays[arraySlot];
	hkUint32 allocSize		= hkMath::max2<hkUint32>(MIN_BLOCK_SIZE, numPolygons);
	arrayElement.m_offset	= blockAlloc(allocSize);
	arrayElement.m_size		= numPolygons;

	// Copy
	int* ptr = &m_storage[arrayElement.m_offset];
	for (int k = numPolygons - 1; k >= 0; k--)
	{
		ptr[k] = (ptr[k] & BLOCK_FLAGS_MASK) | (srcPolyIds[k].value() & PAYLOAD_MASK);
	}
	ptr[numPolygons - 1] |= END_PAYLOAD_FLAG;
}

HK_FORCE_INLINE void hkcdPlanarSolid::ArrayMgr::allocArrayStorage(ArrayId arraySlot, const hkArray<PolygonId>& srcPolyIds)
{
	HK_ASSERT(0x2bc0d8cd, srcPolyIds.getSize());
	allocArrayStorage(arraySlot, srcPolyIds.begin(), srcPolyIds.getSize());
}

HK_FORCE_INLINE void hkcdPlanarSolid::ArrayMgr::freeArray(ArrayId arraySlot)
{
	ArraySlot& arrayElement = m_arrays[arraySlot];
	if ( arrayElement.m_offset )
	{
		blockFree(arrayElement.m_offset, arrayElement.m_size);
	}
	m_arrays.release(arraySlot);
}

//
//	Resets the manager for a new use

HK_FORCE_INLINE void hkcdPlanarSolid::ArrayMgr::reset()
{
	clear();
	m_arrays.clear();
}

#endif

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
