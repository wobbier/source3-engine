/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

template<class PTYPE, class ITYPE, ITYPE MASK>
HK_FORCE_INLINE hkPtrAndInt<PTYPE, ITYPE, MASK>::hkPtrAndInt()
	: m_ptrAndInt(0)
{
}

template<class PTYPE, class ITYPE, ITYPE MASK>
HK_FORCE_INLINE hkPtrAndInt<PTYPE, ITYPE, MASK>::hkPtrAndInt(PTYPE* pntr, ITYPE i)
	: m_ptrAndInt(reinterpret_cast<hkUlong>(pntr) | static_cast<hkUlong>(i))
{
	HK_ASSERT(0x1a1424b7, (i & ~MASK) == 0);
}

template<class PTYPE, class ITYPE, ITYPE MASK>
HK_FORCE_INLINE hkPtrAndInt<PTYPE, ITYPE, MASK>::hkPtrAndInt(const hkPtrAndInt& p)
	: m_ptrAndInt(p.m_ptrAndInt)
{
}

template<class PTYPE, class ITYPE, ITYPE MASK>
HK_FORCE_INLINE void hkPtrAndInt<PTYPE, ITYPE, MASK>::operator=(const hkPtrAndInt& p)
{
	m_ptrAndInt = p.m_ptrAndInt;
}

template<class PTYPE, class ITYPE, ITYPE MASK>
HK_FORCE_INLINE PTYPE* hkPtrAndInt<PTYPE, ITYPE, MASK>::getPtr() const
{
	return reinterpret_cast<PTYPE*>(hkClearBits(m_ptrAndInt, MASK));
}

template<class PTYPE, class ITYPE, ITYPE MASK>
HK_FORCE_INLINE PTYPE* hkPtrAndInt<PTYPE, ITYPE, MASK>::operator->() const
{
	return getPtr();
}

template<class PTYPE, class ITYPE, ITYPE MASK>
HK_FORCE_INLINE hkPtrAndInt<PTYPE, ITYPE, MASK>::operator PTYPE*() const
{
	return getPtr();
}

template<class PTYPE, class ITYPE, ITYPE MASK>
HK_FORCE_INLINE ITYPE hkPtrAndInt<PTYPE, ITYPE, MASK>::getInt() const
{
	return static_cast<ITYPE>(m_ptrAndInt) & MASK;
}

template<class PTYPE, class ITYPE, ITYPE MASK>
HK_FORCE_INLINE void hkPtrAndInt<PTYPE, ITYPE, MASK>::setPtr(PTYPE* e)
{
	m_ptrAndInt = reinterpret_cast<hkUlong>(e) | getInt();
}

template<class PTYPE, class ITYPE, ITYPE MASK>
HK_FORCE_INLINE void hkPtrAndInt<PTYPE, ITYPE, MASK>::setInt(ITYPE p)
{
	m_ptrAndInt = reinterpret_cast<hkUlong>(getPtr()) | static_cast<hkUlong>(p);
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
