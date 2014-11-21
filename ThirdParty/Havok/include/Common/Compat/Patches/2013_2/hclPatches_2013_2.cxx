/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Cloth specific product patches applied to release 2013_2.
// This file is #included by hclPatches_2013_2.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hclTransformSetUsageTransformTracker", 0)
	HK_PATCH_MEMBER_ADDED("read", TYPE_STRUCT, "hkBitField", 0)
	HK_PATCH_MEMBER_ADDED("readBeforeWrite", TYPE_STRUCT, "hkBitField", 0)
	HK_PATCH_MEMBER_ADDED("written", TYPE_STRUCT, "hkBitField", 0)
	HK_PATCH_DEPENDS("hkBitField", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hclTransformSetUsage", 0, "hclTransformSetUsage", 1)
	HK_PATCH_MEMBER_ADDED("perComponentTransformTrackers", TYPE_ARRAY_STRUCT, "hclTransformSetUsageTransformTracker", 0)
	HK_PATCH_DEPENDS("hclTransformSetUsageTransformTracker", 0)
	//HK_PATCH_FUNCTION(hclTransformSetUsage_0_to_1)
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
