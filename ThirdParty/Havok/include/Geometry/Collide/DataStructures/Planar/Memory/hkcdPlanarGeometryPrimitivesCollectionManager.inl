/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Constructor
template <class Coll>
hkcdPlanarGeometryPrimitives::CollectionManager<Coll>::CollectionManager()
:	hkReferencedObject()
,	m_maxSize(MANAGER_DEFAULT_MAX_SIZE)
,	m_lastReturnedCollectionId(-1)
{}

//
//	Returns a unused collection (a new one will be allocated if no one is free)

template <class Coll>
void hkcdPlanarGeometryPrimitives::CollectionManager<Coll>::getUnusedCollection(hkRefPtr<Coll>& collection)
{
	m_criticalSection.enter();

	// Loop until we find a free collection
	if ( m_lastReturnedCollectionId >= 0 )
	{
		int nbSearches			= 0;
		const int nbColls		= m_collectionsArray.getSize();
		while ( m_collectionsArray[m_lastReturnedCollectionId]->getReferenceCount() > 1 && nbSearches < nbColls )
		{
			nbSearches++;
			m_lastReturnedCollectionId++;
			if ( m_lastReturnedCollectionId >= nbColls - 1 )
			{
				m_lastReturnedCollectionId = 0;
			}
		}
	}
	
	if ( m_lastReturnedCollectionId < 0 || m_collectionsArray[m_lastReturnedCollectionId]->getReferenceCount() > 1 )
	{
		// No more free collection, allocate a new one
		if ( m_collectionsArray.getSize() > m_maxSize )
		{
			// Maximum size reached
			HK_WARN_ONCE(0xde333a1b, "Maximum size reached for the collection manager, returning newly allocated collection. Consider increasing the max size of the collection manager");
			collection.setAndDontIncrementRefCount(new Coll());
			m_criticalSection.leave();
			return;
		}	
		m_collectionsArray.expandOne();
		m_lastReturnedCollectionId = m_collectionsArray.getSize() - 1;
		m_collectionsArray[m_lastReturnedCollectionId].setAndDontIncrementRefCount(new Coll());
	}

	collection = m_collectionsArray[m_lastReturnedCollectionId];

	m_criticalSection.leave();

	collection->clear();
}

//
// Expands the number of free collection by the specified amount

template <class Coll>
void hkcdPlanarGeometryPrimitives::CollectionManager<Coll>::expandCollectionPoolBy(int num, hkUint32 allocSize)
{	
	m_criticalSection.enter();

	// Check if the maximum size allow the growth
	int numNewColl = hkMath::min2(m_maxSize - m_collectionsArray.getSize(), num);
	if ( numNewColl < num )
	{
		HK_WARN_ALWAYS(0xde333a1c, "Cannot grow the collection manager by the specified size. Consider increasing the max size of the collection manager.");
	}

	if ( numNewColl > 0 )
	{
		hkRefPtr<Coll>* newCollections = m_collectionsArray.expandBy(numNewColl);

		// Allocate the new collections
		for (int i = 0 ; i < numNewColl ; i++)
		{
			newCollections[i].setAndDontIncrementRefCount(new Coll());
			newCollections[i]->expandStorage(allocSize);
		}
	}

	m_criticalSection.leave();
}

/// Sets the maximum size allowed for the collection pool
template <class Coll>
HK_FORCE_INLINE void hkcdPlanarGeometryPrimitives::CollectionManager<Coll>::setMaxSize(int maxSize)
{
	m_maxSize = maxSize;
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
