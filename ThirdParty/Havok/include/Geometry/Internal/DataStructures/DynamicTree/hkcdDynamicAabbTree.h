/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_DYNAMIC_TREE
#define HK_DYNAMIC_TREE
//HK_HAVOK_ASSEMBLY_EXCLUDE_FILE
#include <Geometry/Internal/Algorithms/TreeQueries/hkcdAabbTreeQueries.h>

extern HK_EXPORT_COMMON const class hkClass hkcdDynamicTreeDefaultTree48StorageClass;
extern HK_EXPORT_COMMON const class hkClass hkDynamicTreeClass;

	/// A bounding volume tree that can be dynamically updated.
	/// When adding a leaf, a handle is returned; this must be tracked if the leaf can later be removed or updated.
	/// After all leaves have been added, the tree can be rebuilt to improve query performance.
class HK_EXPORT_COMMON hkcdDynamicAabbTree : public hkReferencedObject
{
public:
		//+version(1)
	HK_DECLARE_REFLECTION();
	HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_GEOMETRY );

	typedef hkUint32 TreeHandle;

	hkcdDynamicAabbTree();
	hkcdDynamicAabbTree( hkFinishLoadedObjectFlag f);
	virtual ~hkcdDynamicAabbTree();

		/// Allocate memory for an additional number of leaves
	hkResult reserveLeaves( int numLeaves );

		/// Add a leaf with the specified AABB and key. The key will be used during query callbacks
	TreeHandle insert( const hkAabb& aabb, hkUint32 key );

		/// Add a leaf with the specified point and key. The key will be used during query callbacks
	TreeHandle insertPoint( hkVector4Parameter point, hkUint32 key );

		/// Add a leaf with the specified AABB and key. The hkResult will be set to HK_SUCCESS if all memory allocations succeed, or to HK_FAILURE otherwise.
	TreeHandle tryInsert( const hkAabb& aabb, hkUint32 key, hkResult& res );

		/// Add a leaf with the specified point and key. The hkResult will be set to HK_SUCCESS if all memory allocations succeed, or to HK_FAILURE otherwise.
	TreeHandle tryInsertPoint( hkVector4Parameter point, hkUint32 key, hkResult& res );

		/// Change the AABB of the leaf.
	void update( TreeHandle handle, const hkAabb& aabb );

		/// Remove a leaf
	void remove( TreeHandle handle );

		/// Rebuild the tree to improve query performance.
	hkResult rebuild();

		/// Do a fast, in-place optimization on the tree to improve query performance.
	void rebuildFast( int numPasses );

		/// Incremental optimization of the tree. This is suitable to be called every frame if objects have moved.
	void optimizeIncremental(int passes, int lookahead = 2);

		/// Completely clears the tree.
	void clear();

		/// Returns the leaf data for the specified handle.
	hkUint32 getLeafData( TreeHandle handle );
	
		/// Cast a ray through the tree. The collector's callback is triggered for each leaf in the tree that is hit
	hkBool32 castRay( hkVector4Parameter start, hkVector4Parameter end, hkcdAabbTreeQueries::RaycastCollector* collector) const;

		/// Cast a ray through the tree. The collector's callback is triggered for each leaf in the tree that is hit
	hkBool32 castSphere( hkVector4Parameter start, hkVector4Parameter end, hkSimdRealParameter radius, hkcdAabbTreeQueries::RaycastCollector* collector) const;

		/// AABB check on the tree. The collector's callback is triggered for each leaf that overlaps with the AABB.
	void queryAabb( const hkAabb& aabb, hkcdAabbTreeQueries::AabbCollector* collector) const;

		/// Special-case AABB query where only the leaf IDs are saved.
		/// This is about 10% faster than the collector-based version (depending on platform).
	hkResult queryAabb( const hkAabb& aabb, hkArray<hkUint32>::Temp& hits ) const;

		/// Find the closest leaf in the tree. The collector's callback is triggered for each leaf that is closer to the current smallest distance, starting at maxDistance.
	hkUint32 getClosestPoint( hkVector4Parameter point, hkSimdRealParameter maxDistance, hkcdAabbTreeQueries::ClosestPointCollector* collector, hkVector4& closestPointOut ) const;

		/// Find the closest leaf in the tree. The distance to the leaf will be taken as the distance to the AABB.
	hkUint32 getClosestPoint( hkVector4Parameter point, hkSimdRealParameter maxDistance, hkVector4& closestPointOut ) const;

		/// Finds all pairs of overlapping leaves in this tree.
	void getAllPairs( hkcdAabbTreeQueries::AllPairsCollector* collector ) const;

		/// Finds all leaves in this tree that overlap with leaves in the other tree.
	void getAllPairs( const hkcdDynamicAabbTree* otherTree, hkcdAabbTreeQueries::AllPairsCollector* collector ) const;

		/// Returns the size (in bytes) of the tree.
	int getMemoryFootPrint() const;

		/// Returns the number of leaves in the tree.
	int getNumLeaves() const;

		/// Accessor for the internal tree.
	const void* getTreePtr() const { return m_treePtr; }

		/// Accessor for the internal tree.
	void* getTreePtr() { return m_treePtr; }

		/// Whether or not the tree should be deleted in hkcdStaticAabbTree destructor.
		/// This is set automatically depending on whether or not the hkcdStaticAabbTree is reference-counted,
		/// but can be overridden.
	hkBool m_shouldDeleteTree; //+nosave

protected:

	void* m_treePtr; //+overridetype(hkcdDynamicTree::DefaultTree48Storage*)
};

#endif //HK_DYNAMIC_TREE

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
