/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


inline bool hkUuid::operator==(const hkUuid& rhs) const
{
	return (
		(m_data[0] == rhs.m_data[0]) &&
		(m_data[1] == rhs.m_data[1]) &&
		(m_data[2] == rhs.m_data[2]) &&
		(m_data[3] == rhs.m_data[3])
	);
}

inline bool hkUuid::operator!=(const hkUuid& rhs) const
{
	return (
		(m_data[0] != rhs.m_data[0]) ||
		(m_data[1] != rhs.m_data[1]) ||
		(m_data[2] != rhs.m_data[2]) ||
		(m_data[3] != rhs.m_data[3])
	);
}

//
//	Gets the data

template <int I> HK_FORCE_INLINE hkUint32 hkUuid::getData() const	{	return m_data[I];	}
HK_FORCE_INLINE hkUint32 hkUuid::getData(int I) const				{	return m_data[I];	}

//
//	Sets the data

template <int I> HK_FORCE_INLINE void hkUuid::setData(hkUint32 v)	{	m_data[I] = v;		}
HK_FORCE_INLINE void hkUuid::setData(int I, hkUint32 v)				{	m_data[I] = v;		}

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
