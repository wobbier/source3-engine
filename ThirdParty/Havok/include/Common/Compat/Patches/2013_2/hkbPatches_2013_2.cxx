/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Behavior specific product patches applied to release 2013_2.
// This file is #included by hkbPatches_2013_2.cpp

HK_PATCH_BEGIN("hkbCharacter", 3, "hkbCharacter", 4)
        HK_PATCH_MEMBER_ADDED("capabilities", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("effectiveCapabilities", TYPE_INT, HK_NULL, 0)
		HK_PATCH_FUNCTION(hkbCharacter_3_to_4)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbCustomIdSelector", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbTestIdSelector", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hkbCustomIdSelector")
        HK_PATCH_MEMBER_ADDED("int", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("real", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("string", TYPE_CSTRING, HK_NULL, 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hkbCustomIdSelector", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbStateChooserWrapper", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hkbCustomIdSelector")
		HK_PATCH_MEMBER_ADDED("wrappedChooser", TYPE_OBJECT, "hkbStateChooser", 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hkbCustomIdSelector", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbStateMachine", 4, "hkbStateMachine", 5)
		HK_PATCH_MEMBER_ADDED("startStateIdSelector", TYPE_OBJECT, "hkbCustomIdSelector", 0)
		HK_PATCH_FUNCTION(hkbStateMachine_4_to_5)
        HK_PATCH_MEMBER_REMOVED("startStateChooser", TYPE_OBJECT, "hkbStateChooser", 0)
        HK_PATCH_DEPENDS("hkbStateChooser", 0)
		HK_PATCH_DEPENDS("hkbStateChooserWrapper", 0)
        HK_PATCH_DEPENDS("hkbCustomIdSelector", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbTestStateChooser", 0, HK_NULL, HK_CLASS_REMOVED)
        HK_PATCH_PARENT_SET("hkbStateChooser", HK_NULL)
        HK_PATCH_MEMBER_REMOVED("int", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_REMOVED("real", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_REMOVED("string", TYPE_CSTRING, HK_NULL, 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hkbStateChooser", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbCustomTestGenerator", 2, "hkbCustomTestGenerator", 3)
        HK_PATCH_MEMBER_ADDED("idSelector", TYPE_OBJECT, "hkbCustomIdSelector", 0)
        HK_PATCH_DEPENDS("hkbCustomIdSelector", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbManualSelectorTransitionEffect", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hkbTransitionEffect")
        HK_PATCH_MEMBER_ADDED("transitionEffects", TYPE_ARRAY_OBJECT, "hkbTransitionEffect", 0)
        HK_PATCH_MEMBER_ADDED_BYTE("selectedIndex", 0)
        HK_PATCH_MEMBER_ADDED("indexSelector", TYPE_OBJECT, "hkbCustomIdSelector", 0)
        HK_PATCH_DEPENDS("hkbNode", 1)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hkbGenerator", 0)
        HK_PATCH_DEPENDS("hkbTransitionEffect", 0)
        HK_PATCH_DEPENDS("hkbBindable", 0)
        HK_PATCH_DEPENDS("hkbCustomIdSelector", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkbManualSelectorTransitionEffectInternalState", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
        HK_PATCH_MEMBER_ADDED("currentTransitionEffectIndex", TYPE_BYTE, HK_NULL, 0)
        HK_PATCH_DEPENDS("hkBaseObject", 0)
        HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbDockingGenerator", 0, "hkbDockingGenerator", 1)
        HK_PATCH_MEMBER_REMOVED("previousLocalTime", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_REMOVED("intervalStartLocalTime", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_REMOVED("intervalEndLocalTime", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbManualSelectorGenerator", 2, "hkbManualSelectorGenerator", 3)
        HK_PATCH_MEMBER_REMOVED("currentGeneratorIndex", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_REMOVED("generatorIndexAtActivate", TYPE_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("indexSelector", TYPE_OBJECT, "hkbCustomIdSelector", 0)
        HK_PATCH_DEPENDS("hkbCustomIdSelector", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbFootIkDriverInfoLeg", 0, "hkbFootIkDriverInfoLeg", 1)
        HK_PATCH_MEMBER_ADDED_INT("hipSiblingIndex", -1)
        HK_PATCH_MEMBER_ADDED_INT("kneeSiblingIndex", -1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkbBlendingTransitionEffectInternalState", 1, "hkbBlendingTransitionEffectInternalState", 2)
        HK_PATCH_MEMBER_REMOVED("resetToGenerator", TYPE_BYTE, HK_NULL, 0)
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
