/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_HAVOK_ASSEMBLY_EXCLUDE_FILE

#ifndef HKCD_PLANAR_GEOMETRY_PRIMITIVES_COLLECTION_MANAGER_H
#define HKCD_PLANAR_GEOMETRY_PRIMITIVES_COLLECTION_MANAGER_H

#include <Geometry/Collide/DataStructures/Planar/Memory/hkcdPlanarGeometryPrimitivesCollection.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>

namespace hkcdPlanarGeometryPrimitives
{
	/// Low-level memory management for a collection of primitives
	template <class Coll>
	class CollectionManager : public hkReferencedObject
	{
		public:
			HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_DESTRUCTION);

			/// Constants
			enum
			{
				MANAGER_DEFAULT_MAX_SIZE = 200,
			};

			/// Constructor
			CollectionManager();

			/// Returns a unused collection (a new one will be allocated if no one is free)
			void getUnusedCollection(hkRefPtr<Coll>& collection);
	
			/// Expands the number of free collection by the specified amount (clamped to the maximum size).
			void expandCollectionPoolBy(int num, hkUint32 allocSize);

			/// Sets the maximum size allowed for the collection pool
			HK_FORCE_INLINE void setMaxSize(int maxSize);

		public:

			int m_maxSize;									///< Maximum size of the collection pool
			int m_lastReturnedCollectionId;					///< Index in the collection array of the last return collection id
			hkArray< hkRefPtr<Coll> > m_collectionsArray;	///< Static preallocated collections
			hkCriticalSection m_criticalSection;			///< For safe multithread access
	};
}

#include <Geometry/Collide/DataStructures/Planar/Memory/hkcdPlanarGeometryPrimitivesCollectionManager.inl>

#endif	//	HKCD_PLANAR_GEOMETRY_PRIMITIVES_COLLECTION_MANAGER_H

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
