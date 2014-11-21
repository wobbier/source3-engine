/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Cloth specific product patches applied to release 2013_1.
// This file is #included by hclPatches_2013_1.cpp

HK_PATCH_BEGIN("hclUpdateAllVertexFramesOperator", 2, "hclUpdateAllVertexFramesOperator", 3)
	HK_PATCH_MEMBER_RENAMED("triangleFlips", "old_triangleFlips")
	HK_PATCH_MEMBER_ADDED("triangleFlips", TYPE_ARRAY_BYTE, HK_NULL, 0)
	HK_PATCH_FUNCTION(hclUpdateAllVertexFramesOperator_2_to_3)
	HK_PATCH_MEMBER_REMOVED("old_triangleFlips", TYPE_ARRAY_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclUpdateSomeVertexFramesOperator", 2, "hclUpdateSomeVertexFramesOperator", 3)
	HK_PATCH_MEMBER_RENAMED("triangleFlips", "old_triangleFlips")
	HK_PATCH_MEMBER_ADDED("triangleFlips", TYPE_ARRAY_BYTE, HK_NULL, 0)
	HK_PATCH_FUNCTION(hclUpdateSomeVertexFramesOperator_2_to_3)
	HK_PATCH_MEMBER_REMOVED("old_triangleFlips", TYPE_ARRAY_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hclSimClothData", 9, "hclSimClothData", 10)
	HK_PATCH_MEMBER_RENAMED("triangleFlips", "old_triangleFlips")
	HK_PATCH_MEMBER_ADDED("triangleFlips", TYPE_ARRAY_BYTE, HK_NULL, 0)
	HK_PATCH_FUNCTION(hclSimClothData_9_to_10)
	HK_PATCH_MEMBER_REMOVED("old_triangleFlips", TYPE_ARRAY_INT, HK_NULL, 0)
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
