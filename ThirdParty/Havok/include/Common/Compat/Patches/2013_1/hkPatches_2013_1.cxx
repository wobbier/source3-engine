/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Common specific product patches applied to release 2013_1.
// This file is #included by hkPatches_2013_1.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkBitFieldStoragehkArrayunsignedinthkContainerHeapAllocator", 0)
	HK_PATCH_MEMBER_ADDED("words", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numBits", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkBitFieldBasehkBitFieldStoragehkArrayunsignedinthkContainerHeapAllocator", 0)
	HK_PATCH_MEMBER_ADDED("storage", TYPE_STRUCT, "hkBitFieldStoragehkArrayunsignedinthkContainerHeapAllocator", 0)
	HK_PATCH_DEPENDS("hkBitFieldStoragehkArrayunsignedinthkContainerHeapAllocator", 0)
HK_PATCH_END()

// We rename to hkBitField_new and then back to hkBitField in case there are hkBitField_new
// serialized objects
HK_PATCH_BEGIN("hkBitField", 0, "hkBitField_new", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkBitFieldBasehkBitFieldStoragehkArrayunsignedinthkContainerHeapAllocator")
	HK_PATCH_DEPENDS("hkBitFieldBasehkBitFieldStoragehkArrayunsignedinthkContainerHeapAllocator", 0)
	HK_PATCH_FUNCTION(hkBitField_0_hkBitField_new_1)
	HK_PATCH_MEMBER_REMOVED("words", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("numBits", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkOffsetBitFieldStoragehkArrayunsignedinthkContainerHeapAllocator", 0)
	HK_PATCH_MEMBER_ADDED("words", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("offset", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkBitFieldBasehkOffsetBitFieldStoragehkArrayunsignedinthkContainerHeapAllocator", 0)
	HK_PATCH_MEMBER_ADDED("storage", TYPE_STRUCT, "hkOffsetBitFieldStoragehkArrayunsignedinthkContainerHeapAllocator", 0)
	HK_PATCH_DEPENDS("hkOffsetBitFieldStoragehkArrayunsignedinthkContainerHeapAllocator", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkMemoryMeshMaterial", 1, "hkMemoryMeshMaterial", 2)
	HK_PATCH_MEMBER_ADDED("userData", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("tesselationFactor", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("displacementAmount", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxMaterial", 4, "hkxMaterial", 5)
	HK_PATCH_MEMBER_ADDED_INT("userData", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkMeshTextureRawBufferDescriptor", 0)
	HK_PATCH_MEMBER_ADDED("offset", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("stride", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numElements", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkOffsetBitField", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkBitFieldBasehkOffsetBitFieldStoragehkArrayunsignedinthkContainerHeapAllocator")
	HK_PATCH_DEPENDS("hkBitFieldBasehkOffsetBitFieldStoragehkArrayunsignedinthkContainerHeapAllocator", 0)
HK_PATCH_END()

// Now rename back to hkBitField
HK_PATCH_BEGIN("hkBitField_new", 1, "hkBitField", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkPackfileSectionHeader", 0, "hkPackfileSectionHeader", 1)
	HK_PATCH_MEMBER_ADDED("pad", TYPE_TUPLE_INT, HK_NULL, 4)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkSetunsignedlonglonghkContainerHeapAllocatorhkMapOperationsunsignedlonglong",0)
	HK_PATCH_MEMBER_ADDED("elem", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numElems", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkSetUint64", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkSetunsignedlonglonghkContainerHeapAllocatorhkMapOperationsunsignedlonglong")
	HK_PATCH_DEPENDS("hkSetunsignedlonglonghkContainerHeapAllocatorhkMapOperationsunsignedlonglong", 0)
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
