/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SHAPE_BUFFER_H
#define HK_SHAPE_BUFFER_H

/// Attributes of the buffer used in getChildShape.
enum hkpBufferSize
{
	HK_SHAPE_BUFFER_SIZE = 512 
};

/// A buffer type, allocated locally on the stack by calling functions,
/// to be passed to getChildShape.
struct hkpShapeBufferStorage
{
    char m_storage[HK_SHAPE_BUFFER_SIZE];
    
    // Previously hkpShapeBuffer was a character array, this allows it to be
    // implicitly cast to a pointer
    
    template<typename T>
    operator T*() { return reinterpret_cast<T*>(m_storage); }
};

// Some compilers need a struct to perform the alignment correctly
typedef HK_ALIGN_REAL(hkpShapeBufferStorage) hkpShapeBuffer;

#endif // HK_SHAPE_BUFFER_H

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
