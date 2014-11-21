/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Common specific product patches applied to release 2013_2.
// This file is #included by hkPatches_2013_2.cpp

HK_PATCH_BEGIN("hkPackfileHeader", 1, "hkPackfileHeader", 2)
	HK_PATCH_MEMBER_REMOVED("pad", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxpredicate", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("predicateArraySizePlusPadding", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkAabbHalf", 0, "hkAabbHalf", 1)
	HK_PATCH_MEMBER_RENAMED("data","data_old")
	HK_PATCH_MEMBER_ADDED("data", TYPE_TUPLE_INT, HK_NULL, 8)
	HK_PATCH_FUNCTION(hkAabbHalf_0_to_1)
	HK_PATCH_MEMBER_REMOVED("data_old", TYPE_TUPLE_INT, HK_NULL, 6)
	HK_PATCH_MEMBER_REMOVED("extras", TYPE_TUPLE_INT, HK_NULL, 2)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkUuid", 0)
	HK_PATCH_MEMBER_ADDED("data", TYPE_TUPLE_INT, HK_NULL, 4)
HK_PATCH_END()

HK_PATCH_BEGIN("hkUuid", 0, "hkUuid", 1) 
HK_PATCH_END()

HK_PATCH_BEGIN("hkUiAttribute", 2, "hkUiAttribute", 3)
	HK_PATCH_MEMBER_ADDED_BYTE("editable", 0)
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
