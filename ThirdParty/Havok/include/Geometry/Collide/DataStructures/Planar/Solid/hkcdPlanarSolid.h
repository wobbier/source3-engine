/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_HAVOK_ASSEMBLY_EXCLUDE_FILE

#ifndef HKCD_SOLID_PLANAR_GEOMETRY_H
#define HKCD_SOLID_PLANAR_GEOMETRY_H

#include <Common/Base/Types/hkHandle.h>
#include <Common/Base/Container/FreeListArray/hkFreeListArray.h>
#include <Common/Base/Algorithm/PseudoRandom/hkPseudoRandomGenerator.h>
#include <Common/Base/Algorithm/Collide/1AxisSweep/hk1AxisSweep.h>

#include <Geometry/Collide/DataStructures/Planar/Geometry/hkcdPlanarGeometry.h>

/// A solid geometry, represented as a Bsp tree. The actual geometry is managed by a hkcdPlanarGeometry
class HK_EXPORT_COMMON hkcdPlanarSolid : public hkcdPlanarEntity
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY);
		HK_DECLARE_REFLECTION();

	public:

		// Types
		struct Node;
		HK_DECLARE_HANDLE(NodeId, hkUint32, 0xFFFFFFFFU);
		struct NodeStorage : public hkReferencedObject
		{
			HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION);
			HK_DECLARE_REFLECTION();

			/// Constructor
			NodeStorage()
			:	hkReferencedObject()
			,	m_firstFreeNodeId(NodeId::invalid())
			{}

			/// Copy constructor
			NodeStorage(const NodeStorage& other)
			:	hkReferencedObject()
			,	m_firstFreeNodeId(other.m_firstFreeNodeId)
			{
				m_storage.append(other.m_storage);
			}

			/// Serialization constructor
			NodeStorage(class hkFinishLoadedObjectFlag flag)
			:	hkReferencedObject(flag)
			,	m_storage(flag)
			,	m_firstFreeNodeId(flag)
			{}

			virtual ~NodeStorage()
			{}

		public:

			/// Accessors
			HK_FORCE_INLINE const Node& getNode(NodeId nodeId) const;
			HK_FORCE_INLINE Node& accessNode(NodeId nodeId);

			/// Allocation
			HK_FORCE_INLINE NodeId allocate();
			HK_FORCE_INLINE void clear();
			HK_FORCE_INLINE int getCapacity() const;
			HK_FORCE_INLINE void release(NodeId nodeId);
			
			/// Other
			HK_FORCE_INLINE void swapStorage(hkArray<Node>& storage);
			HK_FORCE_INLINE void compact();

		protected:

			hkArray<Node> m_storage;
			NodeId m_firstFreeNodeId;			//+overridetype(hkUint32)
		};

	public:

		// Node type
		enum NodeTypes
		{
			NODE_TYPE_INTERNAL	= 0x0,	///< Internal BSP node
			NODE_TYPE_IN		= 0x1,	///< Leaf SOLID node, shared by all internal nodes
			NODE_TYPE_OUT		= 0x2,	///< Leaf EMPTY / OUTSIDE node, shared by all internal nodes
			NODE_TYPE_UNKNOWN	= 0x3,	///< Leaf unlabeled node, shared by all internal nodes
			NODE_TYPE_INVALID	= 0x4,	///< Value used to mark pre-allocated nodes that will no longer be used when these nodes will be removed from the code.
			NODE_TYPE_FREE		= 0xF,	///< The node is not allocated
		};

		// Node in the BSP tree
		struct Node
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdPlanarSolid::Node);
			HK_DECLARE_REFLECTION();

			/// Constructor
			HK_FORCE_INLINE Node()
			:	m_parent(NodeId::invalid())
			,	m_typeAndFlags(NODE_TYPE_FREE)
			{}

			/// Serialization constructor
			HK_FORCE_INLINE Node(class hkFinishLoadedObjectFlag flag)
			{}

			/// Returns true if the triangle is allocated
			HK_FORCE_INLINE bool isAllocated() const;

			/// Marks this node as not-allocated
			HK_FORCE_INLINE void clear();

			/// Called by the free-list to initialize an unallocated entry
			HK_FORCE_INLINE static void setEmpty(Node& element, hkUint32 next);

			/// Returns the index of the next free element. Will be called only with empty elements
			HK_FORCE_INLINE static hkUint32 getNext(const Node& element);

			/// Sets the given child id
			HK_FORCE_INLINE void setChildId(int childIdx, NodeId childNodeId);
			
			/// Parent node
			NodeId	m_parent;			//+overridetype(hkUint32) 

			/// Left child, contains the space behind the splitting plane (inside)
			NodeId	m_left;				//+overridetype(hkUint32) 

			/// Right child, contains the space in front of the splitting plane (outside)
			NodeId	m_right;			//+overridetype(hkUint32) 

			/// Address of the next free node
			NodeId	m_nextFreeNodeId;	//+overridetype(hkUint32) 

			/// Splitting plane
			PlaneId m_planeId;			//+overridetype(hkUint32) 

			/// User data, typically used to store a spatial CellId
			hkUint32 m_data;

			///< Type and flags, a combination of values in NodeTypes
			hkUint32 m_typeAndFlags;
		};

		/// Array slot. Basically an offset + length into a common, shared memory buffer
		struct ArraySlot
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY, hkcdPlanarSolid::ArraySlot);
			HK_DECLARE_POD_TYPE();

			/// Constructor
			HK_FORCE_INLINE ArraySlot() {}

			hkUint32 m_offset;	///< Array start offset in the shared buffer
			hkUint32 m_size;	///< Number of elements in the array
		};

		/// A unique Id for an ArraySlot
		HK_DECLARE_HANDLE(ArrayId, hkUint32, 0xFFFFFFFFU);

		/// Manages the arrays allocated during classifyPolygons
		struct ArrayMgr : public hkcdPlanarGeometryPrimitives::Collection<hkcdPlanarGeometryPrimitives::FLIPPED_PLANE_BIT>
		{
		public:

			HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_GEOMETRY);

		public:

			/// Constructor
			HK_FORCE_INLINE ArrayMgr();

		public:

			/// Allocates an array slot. The storage for the array is not yet allocated
			HK_FORCE_INLINE ArrayId allocArraySlot();

			/// Returns the array slot at the given Id
			HK_FORCE_INLINE ArraySlot& getArraySlot(ArrayId aid);

			/// Returns the array storage for the given Id
			HK_FORCE_INLINE PolygonId getPolygonId(ArrayId aid, int k);

			/// Allocates storage for numPolygons in the array at the given slot
			HK_FORCE_INLINE void allocArrayStorage(ArrayId arraySlot, const PolygonId* HK_RESTRICT srcPolyIds, int numPolygons);
			HK_FORCE_INLINE void allocArrayStorage(ArrayId arraySlot, const hkArray<PolygonId>& srcPolyIds);
			HK_FORCE_INLINE void freeArray(ArrayId arraySlot);

			/// Resets the manager for a new use
			HK_FORCE_INLINE void reset();

		protected:

			hkFreeListArray<ArraySlot, ArrayId, 128> m_arrays;
		};


	public:

		/// Constructor
		hkcdPlanarSolid(const PlanesCollection* planesCollection, int initialNodeCapacity = 0, hkcdPlanarEntityDebugger* debugger = HK_NULL);

		/// Constructor from collection pointers
		hkcdPlanarSolid(NodeStorage* nodeStorage, NodeId rootNodeId, const PlanesCollection* planesCollection, hkcdPlanarEntityDebugger* debugger = HK_NULL);

		/// Copy constructor
		hkcdPlanarSolid(const hkcdPlanarSolid& other);

		/// Serialization constructor
		hkcdPlanarSolid(class hkFinishLoadedObjectFlag flag);

		/// Destructor
		virtual ~hkcdPlanarSolid();

	public:

		/// Builds a convex solid from an array of planes. The planes are assumed to bound a closed convex region, there are no checks to validate the assumption!
		void buildConvex(const PlaneId* HK_RESTRICT planesIn, int numPlanes);

		/// Builds the tree for the given set of planes
		void buildTree(hkcdPlanarGeometry& polySoup, hkPseudoRandomGenerator& rng, hkArray<PlaneId>& planes, const hkArray<PolygonId>& polygons, bool useBoundaryPlanes, hkcdPlanarEntityDebugger* debugger);

		/// Builds the tree for the given set of planes, considering the plane as delimiting a flat surface
		void buildTree2D(hkcdPlanarGeometry& polySoup, hkPseudoRandomGenerator& rng, hkArray<PlaneId>& planes, const hkArray<PolygonId>& polygons, hkcdPlanarEntityDebugger* debugger);

		/// Sets a new planes collection. If the plane remapping table is non-null, the plane Ids on all nodes will be re-set as well (i.e. to match the plane Ids in the new collection)
		void setPlanesCollection(const PlanesCollection* newPlanes, int* HK_RESTRICT planeRemapTable, bool addMissingPlanes = false);

		/// Shift all plane ids on the nodes of the tree
		void shiftPlaneIds(int offsetValue);

		/// Simplifies the tree by collapsing nodes with identical labels. Returns true if something was collapsed
		hkBool32 collapseIdenticalLabels();

		/// Optimizes the storage, by moving all unallocated nodes at the end and releasing unused memory. This will
		/// modify the Ids of the nodes!
		void optimizeStorage();

		/// Collapses any nodes still marked as unknown
		hkBool32 collapseUnknownLabels();

		/// Classifies the polygons into inside, boundary, and outside parts
		HK_FORCE_INLINE void classifyPolygons(	hkcdPlanarGeometry& polySoup, const hkArray<PolygonId>& polygonsIn,
												hkArray<PolygonId>& insidePieces, hkArray<PolygonId>& boundaryPieces, hkArray<PolygonId>& outsidePieces, ArrayMgr* arrayMgr = HK_NULL) const;

		/// Special case of the classifies, where only the inside OR the boundary polys are needed
		void classifyInsideOrBoundaryPolygons(hkcdPlanarGeometry& polySoup, const hkArray<PolygonId>& polygonsIn, hkArray<PolygonId>& insideOrBoundPolyIds, ArrayMgr* arrayMgr = HK_NULL);

		/// Collects all the plane Ids used by the Bsp tree
		void collectUsedPlaneIds(hkBitField& usedPlaneIdsOut) const;

		/// Computes a set of polygons that cover the boundary of the solid
		void computeBoundary(class hkcdConvexCellsTree3D* cellGraph, hkcdPlanarGeometry& boundaryGeomOut, hkcdPlanarEntityDebugger* debugger = HK_NULL);

		/// Returns the maximum depth of the tree
		int computeMaxDepth() const;

		// Clears the tree
		void clear();
		
		/// Replaces allocated nodes by default ones when possible
		void replaceAllocatedNodesByDefaultNodes();

		/// Computes the number of nodes with the specified label
		int computeNumNodesWithLabel(hkUint32 label) const;

		/// Computes the number of leaf nodes
		int computeNumLeafNodes() const;

		/// Debug. Prints all the tree data
		void dbgPrint() const;

	public:

		/// Gets the node having the given Id.
		HK_FORCE_INLINE const Node& getNode(NodeId nodeId) const;
		HK_FORCE_INLINE Node& accessNode(NodeId nodeId);

		/// Returns the nodes
		HK_FORCE_INLINE const NodeStorage* getNodes() const;
		HK_FORCE_INLINE NodeStorage* accessNodes();

		/// Returns the collection of planes used by this solid
		HK_FORCE_INLINE PlanesCollection* accessPlanesCollection();
		HK_FORCE_INLINE const PlanesCollection* getPlanesCollection() const;

		/// Returns true if the tree is valid
		HK_FORCE_INLINE bool isValid() const;

		/// Returns true if the tree represent the empty set
		HK_FORCE_INLINE bool isEmpty() const;

		/// Returns true if the given node is internal
		HK_FORCE_INLINE bool isInternal(NodeId nodeId) const;

		/// Default nodes accessors
		HK_FORCE_INLINE NodeId createInsideNode(NodeId parentId);
		HK_FORCE_INLINE NodeId createOutsideNode(NodeId parentId);
		HK_FORCE_INLINE NodeId createUnknownNode(NodeId parentId);

		/// Returns the Id of the root node
		HK_FORCE_INLINE const NodeId getRootNodeId() const;

		/// Returns the label of a given leaf node
		HK_FORCE_INLINE NodeTypes getNodeLabel(NodeId nodeId) const;

		/// Creates a new internal node
		HK_FORCE_INLINE NodeId createNode(PlaneId splitPlaneId, NodeId leftChild, NodeId rightChild);

		/// Sets the root node
		HK_FORCE_INLINE void setRootNode(NodeId rootNodeId);

		/// Returns true if the given node can be collapsed to its parent
		HK_FORCE_INLINE bool canCollapse(NodeId nodeId) const;	

	protected:

		// Selects a splitting plane from the given list
		int pickSplittingPlane(	const hkcdPlanarGeometry& polySoup, hkPseudoRandomGenerator& rng,
								const PlaneId* HK_RESTRICT planeIds, int numPlaneIds,
								const PolygonId* HK_RESTRICT polygonIds, int numPolygonIds);

		/// Classifies the polygons into inside, boundary, and outside parts
		void classifyPolygons(	hkcdPlanarGeometry& polySoup, NodeId nodeId,
								const hkArray<PolygonId>& polygonsIn,
								hkArray<PolygonId>& insidePieces, hkArray<PolygonId>& boundaryPieces, hkArray<PolygonId>& outsidePieces, ArrayMgr& arrayMgr) const;

	protected:

		/// The nodes in the Bsp tree
		hkRefPtr<NodeStorage> m_nodes;

		/// The planes collection
		hkRefPtr<const PlanesCollection> m_planes;	

		/// The root node
		NodeId m_rootNodeId;			//+overridetype(hkUint32) 
};

#include <Geometry/Collide/DataStructures/Planar/Solid/hkcdPlanarSolid.inl>

#endif	//	HKCD_SOLID_PLANAR_GEOMETRY_H

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
