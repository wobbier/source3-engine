/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Behavior specific product patches applied to release 2013_1.
// This file is #included by hkbPatches_2013_1.cpp

HK_PATCH_BEGIN("hkbLayer", 0, "hkbLayer", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("forceFullFadeDurations", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbGeneratorTransitionEffectInternalState", 0, "hkbGeneratorTransitionEffectInternalState", 1)
        HK_PATCH_MEMBER_REMOVED("echoToGenerator", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("toGeneratorSelfTransitionMode", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbBlendingTransitionEffectInternalState", 0, "hkbBlendingTransitionEffectInternalState", 1)
        HK_PATCH_MEMBER_REMOVED("applySelfTransition", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("resetToGenerator", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("toGeneratorSelfTranstitionMode", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbCustomTestGenerator", 1, "hkbCustomTestGenerator", 2)
        HK_PATCH_MEMBER_ADDED("boneIndexOld", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("boneIndex", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("boneChainIndex0", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("boneChainIndex1", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("boneChainIndex2", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("boneGroupIndex0", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("boneGroupIndex1", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("boneGroupIndex2", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("boneWeightArray", TYPE_OBJECT, "hkbBoneWeightArray", 0)
        HK_PATCH_MEMBER_ADDED("boneIndexArray", TYPE_OBJECT, "hkbBoneIndexArray", 0)
        HK_PATCH_DEPENDS("hkbBoneIndexArray", 0)
        HK_PATCH_DEPENDS("hkbBoneWeightArray", 0)
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
