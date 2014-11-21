/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Destruction specific product patches applied to release 2013_2.
// This file is #included by hkdPatches_2013_2.cpp

HK_PATCH_BEGIN("hkdShape", 4, "hkdShape", 5)
	HK_PATCH_MEMBER_ADDED_REAL("yieldStrength", 0.000000f)
	HK_PATCH_FUNCTION(hkdShape_4_to_5)	
HK_PATCH_END()

HK_PATCH_BEGIN("hkdBody", 3, "hkdBody", 4)
	HK_PATCH_MEMBER_ADDED_BYTE("numSimulationLods", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDestructionDemoConfig", 6, "hkdDestructionDemoConfig", 7)
	HK_PATCH_MEMBER_ADDED_REAL("distanceLodFine", 10.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("distanceLodCoarse", 20.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdBody", 4, "hkdBody", 5)
	HK_PATCH_MEMBER_ADDED("uuid", TYPE_STRUCT, "hkUuid", 0)
	HK_PATCH_DEPENDS("hkUuid", 1)
	HK_PATCH_FUNCTION(hkdBody_4_to_5)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDebrisFractureInfoTemplateInfo", 0, "hkdDebrisFractureInfoTemplateInfo", 1)
	HK_PATCH_MEMBER_ADDED("templateDebrisUuid", TYPE_STRUCT, "hkUuid", 0)
	HK_PATCH_DEPENDS("hkUuid", 1)
	HK_PATCH_FUNCTION(hkdDebrisFractureInfoTemplateInfo_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDebrisFracture", 3, "hkdDebrisFracture", 4)
	HK_PATCH_MEMBER_ADDED("templateDebrisUuid", TYPE_STRUCT, "hkUuid", 0)
	HK_PATCH_MEMBER_ADDED("controlShapesUuid", TYPE_STRUCT, "hkUuid", 0)
	HK_PATCH_DEPENDS("hkUuid", 1)
	HK_PATCH_FUNCTION(hkdDebrisFracture_3_to_4)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecorateFractureFaceActionCornerDecorationInfo", 0, "hkdDecorateFractureFaceActionCornerDecorationInfo", 1)
	HK_PATCH_MEMBER_ADDED("decorationsUuid", TYPE_STRUCT, "hkUuid", 0)
	HK_PATCH_DEPENDS("hkUuid", 1)
	HK_PATCH_FUNCTION(hkdDecorateFractureFaceActionCornerDecorationInfo_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecorateFractureFaceActionFractureFaceInfo", 3, "hkdDecorateFractureFaceActionFractureFaceInfo", 4)
	HK_PATCH_MEMBER_ADDED("decorationsUuid", TYPE_STRUCT, "hkUuid", 0)
	HK_PATCH_DEPENDS("hkUuid", 1)
	HK_PATCH_FUNCTION(hkdDecorateFractureFaceActionFractureFaceInfo_3_to_4)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdFracture", 3, "hkdFracture", 4)
	HK_PATCH_MEMBER_ADDED_BYTE("splitDisjointPieces", 1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdImageBasedFracture", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkdFracture")
	HK_PATCH_MEMBER_ADDED("textureImage", TYPE_CSTRING, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BYTE("binarizationThreshold", 40)
	HK_PATCH_MEMBER_ADDED_REAL("cornerMaxAngle", 130.0f)
	HK_PATCH_MEMBER_ADDED_REAL("lineSimplification", 0.100000f)
	HK_PATCH_MEMBER_ADDED_REAL("mergePointThreshold", 0.100000f)
	HK_PATCH_MEMBER_ADDED_INT("uvChannel", 0)
	HK_PATCH_MEMBER_ADDED_REAL("extrusionDepth", 1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("normalAngleThreshold", 0.000000f)
	HK_PATCH_MEMBER_ADDED("splitPlaneGeometry", TYPE_OBJECT, "hkdGeometry", 0)
	HK_PATCH_DEPENDS("hkdFracture", 3)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkdGeometry", 1)
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
