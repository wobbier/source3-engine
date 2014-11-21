/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// NewDestruction specific product patches applied to release 2013_1.
// This file is #included by hkndPatches_2013_1.cpp

HK_PATCH_BEGIN("hkndBitFieldhkArrayunsignedinthkContainerHeapAllocator", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_MEMBER_REMOVED("offset", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("words", TYPE_ARRAY_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndSerializableArrayBitField", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hkndBitFieldhkArrayunsignedinthkContainerHeapAllocator", HK_NULL)
	HK_PATCH_DEPENDS("hkndBitFieldhkArrayunsignedinthkContainerHeapAllocator", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndBreakableBodySnapshot", 0, "hkndBreakableBodySnapshot", 1)
	HK_PATCH_MEMBER_RENAMED("enabledPieces", "old_enabledPieces")
	HK_PATCH_MEMBER_RENAMED("enabledConnections", "old_enabledConnections")
	HK_PATCH_MEMBER_ADDED("enabledPieces", TYPE_STRUCT, "hkOffsetBitField", 0)
	HK_PATCH_MEMBER_ADDED("enabledConnections", TYPE_STRUCT, "hkOffsetBitField", 0)
	HK_PATCH_FUNCTION(hkndBreakableBodySnapshot_0_to_1)
	HK_PATCH_MEMBER_REMOVED("old_enabledPieces", TYPE_STRUCT, "hkndBitFieldhkArrayunsignedinthkContainerHeapAllocator", 0)
	HK_PATCH_MEMBER_REMOVED("old_enabledConnections", TYPE_STRUCT, "hkndBitFieldhkArrayunsignedinthkContainerHeapAllocator", 0)
	HK_PATCH_DEPENDS("hkOffsetBitField", 0)
	HK_PATCH_DEPENDS("hkBitFieldBasehkOffsetBitFieldStoragehkArrayunsignedinthkContainerHeapAllocator", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndShapeInstance", 0, "hkndShapeInstance", 1)
	HK_PATCH_MEMBER_ADDED_INT("shapeSizeDiv16", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDynamicFracture", 0, "hkndDynamicFractureContext", 1) 
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkndDeterminismUtil", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

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
