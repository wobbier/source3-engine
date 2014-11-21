/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


hkCommand::hkCommand( PrimaryType type, hkUint16 subType, int sizeInBytes)
{
#if defined (HK_WANT_DETERMINISM_CHECKS)
	// Fill memory for determinism.
	hkString::memSet(this, 0xdead, sizeInBytes);
	// Remember the actual size for determinism checks.
	m_determinismSizeInBytes = hkUint16(sizeInBytes);
#endif
	m_sizePaddedTo16 = hkUint16(HK_NEXT_MULTIPLE_OF(16,sizeInBytes));
	m_filterBits = 0;
	m_primaryType = type;
	m_secondaryType = subType;
}

HK_FORCE_INLINE void* hkBlockStreamCommandWriter::allocBuffer( int size )
{
	size = HK_NEXT_MULTIPLE_OF( 16, size );
	void* data = m_writer.reserve( size );
 	m_writer.advance( size );
 	return data;
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
