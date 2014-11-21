/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_POINTER_MULTI_MAP_H
#define HKBASE_POINTER_MULTI_MAP_H

#include <Common/Base/Container/PointerMap/hkMap.h>
#include <Common/Base/Container/PointerMultiMap/hkMultiMap.h>
#include <Common/Base/Container/PointerMap/hkPointerMap.h>

// Helpers to get the hkMultiMap implementation for a given key size.
template <int N>
struct HK_EXPORT_COMMON hkPointerMultiMapStorage
{
	typedef hkUlong Type;
};

template<>
struct hkPointerMultiMapStorage<8>
{
	typedef hkUint64 Type;
};

// Chooses opertations used

template <typename T>
struct HK_EXPORT_COMMON hkPointerMultiMapSelectOperations
{
	typedef hkMultiMapOperations<T> Operations;
};

template <>
struct hkPointerMultiMapSelectOperations<int>
{
	typedef hkMultiMapIntegralOperations Operations;
};
template <>
struct hkPointerMultiMapSelectOperations<hkUint32>
{
	typedef hkMultiMapIntegralOperations Operations;
};

/// A class to map between pointer or integer keys and arbitrary pointer/integer values.
/// The key is not allowed to be -1.
template <typename K, typename V>
class hkPointerMultiMap //+reflected(false)
{
	public:
		typedef hkPointerMultiMap<K, V> ThisType;
        HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_MAP, ThisType );

		// Note: pick the larger type for storage, so we don't truncate one
		typedef typename hkPointerMultiMapStorage<sizeof(K) >= sizeof(V) ? sizeof(K) : sizeof(V)>::Type Storage;

		template< typename T >
		static Storage StoreCast(T t)
		{
			return hkPointerMapCast<T, Storage>::StoreCast(t);
		};

		template< typename T >
		static T LoadCast( Storage s)
		{
			return hkPointerMapCast<T, Storage>::LoadCast(s);
		};

			/// Iterator class.
			/// All iterators are invalidated after a mutating operation, i.e., insertion, removal.
        typedef typename hkMultiMap<Storage, Storage>::Iterator Iterator;
		typedef typename hkPointerMultiMapSelectOperations<Storage>::Operations Operations;

			/// Create an empty pointermap.
        hkPointerMultiMap()
		{
		}

			/// Create pointer map initially using preallocated memory block.
			/// Use the getSizeInBytesFor(int numKeys) method to find the buffer size
			/// required for a given number of keys.
        hkPointerMultiMap(void* ptr, int sizeInBytes) : m_map(ptr, sizeInBytes)
		{
		}

			///	Insert key with associated value val. Keys are unique and cannot be -1.
			/// If key already exists it is overwritten. Returns true if the key is new
			/// and false if an existing key was overwritten.
		HK_FORCE_INLINE void insert( K key, V val )
		{
			m_map.insert( StoreCast(key), StoreCast(val) );
		}

			///	Try to insert key with associated value val. Keys are unique and cannot be -1.
			/// If key already exists it is overwritten. Returns true if the key is new
			/// and false if an existing key was overwritten.
			/// If insertion fails (due to being unable to expand the table), the return value
			/// is HK_FAILURE. Otherwise it is HK_SUCCESS.
		HK_FORCE_INLINE hkResult tryInsert( K key, V val )
		{
			return m_map.tryInsert( StoreCast(key), StoreCast(val) );
		}

			/// Return the iterator associated with key or the end iterator if not present.
		HK_FORCE_INLINE Iterator findKey( K key ) const
		{
			return m_map.findKey( StoreCast(key) );
		}
			/// Return the iterator associated with key and value or the end iterator if not present.
		HK_FORCE_INLINE Iterator findKeyWithValue( K key, V val) const
		{
			return m_map.findKeyWithValue( StoreCast(key), StoreCast(val) );
		}
			/// If key is present return its iterator, else insert (key,val) and return the new iterator.
			/// Thus the returned iterator is always valid.
		HK_FORCE_INLINE Iterator findOrInsertKey( K key, V val )
		{
			return m_map.findOrInsertKey( StoreCast(key), StoreCast(val) );
		}

			/// Return if this map contains the given key.
		HK_FORCE_INLINE hkBool hasKey( K key ) const
		{
			return m_map.hasKey( StoreCast(key) );
		}

			/// Return the value associated with key or def if not present.
		HK_FORCE_INLINE V getWithDefault( K key, V def ) const
		{

			return LoadCast<V>( m_map.getWithDefault( StoreCast(key), StoreCast(def) ) );
		}

			/// If key present, write value into out and return HK_SUCCESS. Else return HK_FAILURE.
		hkResult get( K key, V* out ) const
		{
			Storage tmp;
			if( m_map.get( StoreCast(key), &tmp ) == HK_SUCCESS )
			{
				*out = LoadCast<V>(tmp);
				return HK_SUCCESS;
			}
			return HK_FAILURE;
		}

			/// Remove pair at it.
		void remove( Iterator it )
		{
			m_map.remove( it );
		}

            /// Remove all with the key. Returns the amount returned.
        int removeAll(K key)
        {
            return m_map.removeAll(StoreCast(key) );
        }

			/// If key present, remove it and return HK_SUCCESS. Otherwise return HK_FAILURE.
		hkResult remove( K key )
		{
			return m_map.remove( StoreCast(key) );
		}
			/// Remove entry with both key and value - return HK_SUCCESS if found
		hkResult remove( K key, V val)
		{
			return m_map.remove(StoreCast(key), StoreCast(val));
		}
			/// Return the number of elements in this map.
		int getSize() const
		{
			return m_map.getSize();
		}

			/// Return the number of elements that can be stored in this map without reallocation.
		int getCapacity() const
		{
			return m_map.getCapacity();
		}

			/// Return the amount of allocated memory in bytes. Use for statistics.
		int getMemSize() const
		{
			return m_map.getMemSize();
		}

			/// Return the start address in memory of the hashmap. Use for statistics.
		void* getMemStart() const
		{
			return m_map.getMemStart();
		}

			/// Perform internal consistency check.
		hkBool isOk() const
		{
			return m_map.isOk();
		}

			/// Get an iterator over the keys of this map.
		Iterator getIterator() const
		{
			return m_map.getIterator();
		}

			/// Get the key at iterator i.
		K getKey( Iterator i ) const
		{
			return LoadCast<K>( m_map.getKey(i) );
		}

			/// Get the value at iterator i.
		V getValue( Iterator i ) const
		{
			return LoadCast<V>( m_map.getValue(i) );
		}

			/// Overwrite the value at iterator i.
		void setValue( Iterator i, V val )
		{
			m_map.setValue(i, StoreCast(val) );
		}

			/// Get the next iterator after i.
		Iterator getNext( Iterator i ) const
		{
			return m_map.getNext(i);
		}

            /// Get the next iterator after i - with the key value.
            /// Only meaningful when the iterator was created with findKey
        Iterator getNext( Iterator i, K key) const
        {
            return m_map.getNext(i, StoreCast(key));
        }

            /// Determine the number of entries with the key
        int findNumEntries(K key) const
        {
            return m_map.findNumEntries(StoreCast(key));
        }

            /// Find the number of entries with the same key and value
        int findNumEntries(K key, V val) const
        {
            return m_map.findNumEntries(StoreCast(key), StoreCast(val));
        }

			/// Return if the iterator has reached the end.
		hkBool isValid( Iterator i ) const
		{
			return m_map.isValid(i);
		}

			/// clear the table
		void clear()
		{
			m_map.clear();
		}

			/// Estimates and sets the appropriate table size for a given number of elements.
		void reserve( int numElements )
		{
			m_map.reserve(numElements);
		}

			/// Swap the internal representation with another map.
        void swap( hkPointerMultiMap& other )
		{
			m_map.swap( other.m_map );
		}

			/// Return true if the map was constructed with a buffer which was too small.
		inline hkBool wasReallocated() const { return m_map.wasReallocated(); }

			/// Calculates buffer size required to store the specified number of keys.
        static int HK_CALL getSizeInBytesFor(int numOfKeys) { return hkMultiMap<Storage,Storage>::getSizeInBytesFor(numOfKeys); }

	private:

        void operator = (const hkPointerMultiMap<K,V>& map) {}
        hkPointerMultiMap ( const hkPointerMultiMap<K,V>& map ) {}

	public:

	protected:

        hkMultiMap<Storage, Storage, Operations> m_map;	
};

#endif // HKBASE_POINTER_MULTI_MAP_H

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
