/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE hkReferencedObject::hkReferencedObject()
:	m_memSizeAndRefCount(0xFFFF0001)
{}

HK_FORCE_INLINE hkReferencedObject::hkReferencedObject( const hkReferencedObject& originalObject )
:	hkBaseObject()
,	m_memSizeAndRefCount(0xFFFF0001)
{}

HK_FORCE_INLINE void hkReferencedObject::operator=( const hkReferencedObject& originalObject )
{
	// do nothing
}


HK_FORCE_INLINE int hkReferencedObject::getReferenceCount() const
{
	return (m_memSizeAndRefCount & 0xFFFF);
}

HK_FORCE_INLINE int hkReferencedObject::getMemorySizeAndFlags() const
{
	return (m_memSizeAndRefCount >> 16) & 0xFFFF;
}


HK_FORCE_INLINE int hkReferencedObject::getAllocatedSize() const
{
	return getMemorySizeAndFlags() & 0x7FFF;
}

//
//	Sets the memory size and flags

inline void hkReferencedObject::setMemorySizeAndFlags(int newMemSizeAndFlags)
{

	// Set the reference count atomically
	hkUint32 volatile* addr = &m_memSizeAndRefCount;
	hkUint32 oldVal, newVal;
	do
	{
		// Read current state and change
		oldVal = *addr;
		newVal = (newMemSizeAndFlags << 16) | (oldVal & 0xFFFF);
	} while ( !hkAtomic::compareAndSwap<hkUint32>(addr, oldVal, newVal) );

	// We will only get here if we succeeded in setting both memSizeAndFlags and referenceCount in the same go
}

//
//	Sets the reference count

inline void hkReferencedObject::setReferenceCount(int newRefCount)
{

	// Set the reference count atomically
	hkUint32 volatile* addr = &m_memSizeAndRefCount;
	hkUint32 oldVal, newVal;
	do
	{
		// Read current state and change
		oldVal = *addr;
		newVal = (oldVal & 0xFFFF0000) | (newRefCount & 0xFFFF);
	} while ( !hkAtomic::compareAndSwap<hkUint32>(addr, oldVal, newVal) );

	// We will only get here if we succeeded in setting both memSizeAndFlags and referenceCount in the same go
}

//
//	Sets the memory size, flags and reference count

inline void hkReferencedObject::setMemorySizeFlagsAndReferenceCount(int newMemSizeAndFlags, int newRefCount)
{

	// Set the reference count atomically
	hkUint32 volatile* addr = &m_memSizeAndRefCount;
	const hkUint32 newVal	= (newMemSizeAndFlags << 16) | (newRefCount & 0xFFFF);
	hkUint32 oldVal;
	do
	{
		// Read current state
		oldVal = *addr;
	} while ( !hkAtomic::compareAndSwap<hkUint32>(addr, oldVal, newVal) );

	// We will only get here if we succeeded in setting both memSizeAndFlags and referenceCount in the same go
}

//
//	Atomically increments the reference count

inline void hkReferencedObject::addReference() const
{
	// We don't bother keeping references if the reference is going to be ignored.
	if ( getMemorySizeAndFlags() != 0 )
	{
		hkUint32 volatile* addr = const_cast<hkUint32*>(&m_memSizeAndRefCount);
		hkUint32 oldVal, newVal;
		do
		{
			// Get old value
			oldVal = *addr;
			newVal = (oldVal & 0xFFFF0000) | (((oldVal & 0xFFFF) + 1) & 0xFFFF);

			// Loop until we can set it
		} while ( !hkAtomic::compareAndSwap<hkUint32>(addr, oldVal, newVal) );

#	if defined(HK_DEBUG)
		if ( (newVal & 0xFFFF) <= 1 )
		{
			extern void HK_CALL hkReferenceCountError(const hkReferencedObject*,const char*);
			hkReferenceCountError(this, "addReference");
		}
#	endif
	}
}

//
//	Atomically decrements the reference count

inline void hkReferencedObject::removeReference() const
{
	if ( getMemorySizeAndFlags() != 0 )	
	{
		hkUint32 volatile* addr = const_cast<hkUint32*>(&m_memSizeAndRefCount);
		hkUint32 oldVal, newVal;
		do
		{
			// Read old state
			oldVal = *addr;
			newVal = (oldVal & 0xFFFF0000) | (((oldVal & 0xFFFF) - 1) & 0xFFFF);

			// Loop until we can set it
		} while ( !hkAtomic::compareAndSwap<hkUint32>(addr, oldVal, newVal) );

		if ( (newVal & 0xFFFF) == 0 )
		{
			deleteThisReferencedObject();
		}
#	if defined(HK_DEBUG)
		else if ( (newVal & 0xFFFF) == 0xFFFF )	// Negative!
		{
			extern void HK_CALL hkReferenceCountError(const hkReferencedObject*,const char*);
			hkReferenceCountError(this, "removeReference");
		}
#	endif
	}
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
