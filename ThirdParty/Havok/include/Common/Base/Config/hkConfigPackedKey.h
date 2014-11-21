/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
// Build configuration settings
// These are compile time settings for the libraries.
// Changing these values with compiled libs will not work,

// If this setting is changed you must rebuild all Havok libs

// Determines whether hkaiPackedKey should be 32-bit or 64-bit, allowing more than 1024 instance loaded in an
// hkaiStreamingCollection at once.


#ifndef HK_BASE_CONFIG_PACKEDKEY_H
#define HK_BASE_CONFIG_PACKEDKEY_H

#ifndef HKBASE_HKBASEDEFS_H
#	error Include hkBaseDefs.h first
#endif

#define HK_CONFIG_PACKED_KEY_32_BIT 0 // 32-bit packed keys
#define HK_CONFIG_PACKED_KEY_64_BIT 1 // 64-bit packed keys

// Default to 64-bit keys in double-precision builds.
#ifdef HK_REAL_IS_DOUBLE
#	define HK_CONFIG_PACKED_KEY_DEFAULT HK_CONFIG_PACKED_KEY_64_BIT
#else
#	define HK_CONFIG_PACKED_KEY_DEFAULT HK_CONFIG_PACKED_KEY_32_BIT
#endif


#ifdef HK_CONFIG_PACKED_KEY
#	if (HK_CONFIG_PACKED_KEY != HK_CONFIG_PACKED_KEY_32_BIT) && (HK_CONFIG_PACKED_KEY != HK_CONFIG_PACKED_KEY_64_BIT)
#		error Invalid value for HK_CONFIG_PACKED_KEY
#	endif
#else

// VALUE:
#	define HK_CONFIG_PACKED_KEY HK_CONFIG_PACKED_KEY_DEFAULT

#endif // #ifndef HK_CONFIG_PACKED_KEY

#endif // HK_BASE_CONFIG_PACKEDKEY_H

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
