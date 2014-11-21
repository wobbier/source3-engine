/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Destruction specific product patches applied to release 2013_3.
// This file is #included by hkdPatches_2013_3.cpp

HK_PATCH_BEGIN("hkdShape", 5, "hkdShape", 6)
	HK_PATCH_MEMBER_ADDED_BYTE("lockDeformation", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdAction", 0, "hkdAction", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("priority", 100)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdConvexHullAction", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkdAction")
	HK_PATCH_MEMBER_ADDED_BYTE("method", 0)
	HK_PATCH_MEMBER_ADDED_BYTE("self", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("recurse", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkdAction", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdRemoveWeakConnectionsAction", 0, "hkdRemoveWeakConnectionsAction", 1)
	HK_PATCH_FUNCTION(hkdRemoveWeakConnectionsAction_0_to_1)
	HK_PATCH_DEPENDS("hkdAction", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdConvexDecompositionAction", 3, "hkdConvexDecompositionAction", 4)
	HK_PATCH_FUNCTION(hkdConvexDecompositionAction_3_to_4)
	HK_PATCH_DEPENDS("hkdAction", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdSplitByPhysicsIslandsAction", 0, "hkdSplitByPhysicsIslandsAction", 1)
	HK_PATCH_FUNCTION(hkdSplitByPhysicsIslandsAction_0_to_1)
	HK_PATCH_DEPENDS("hkdAction", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdGlueFixedPiecesAction", 0, "hkdGlueFixedPiecesAction", 1)
	HK_PATCH_FUNCTION(hkdGlueFixedPiecesAction_0_to_1)
	HK_PATCH_DEPENDS("hkdAction", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecorateFractureFaceAction", 8, "hkdDecorateFractureFaceAction", 9)
	HK_PATCH_FUNCTION(hkdDecorateFractureFaceAction_8_to_9)
	HK_PATCH_DEPENDS("hkdAction", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdMeshSimplifierAction", 6, "hkdMeshSimplifierAction", 7)
	HK_PATCH_FUNCTION(hkdMeshSimplifierAction_6_to_7)
	HK_PATCH_DEPENDS("hkdAction", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdFlattenHierarchyAction", 0, "hkdFlattenHierarchyAction", 1)
	HK_PATCH_FUNCTION(hkdFlattenHierarchyAction_0_to_1)
	HK_PATCH_DEPENDS("hkdAction", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecalMapAction", 0, "hkdDecalMapAction", 1)
	HK_PATCH_FUNCTION(hkdDecalMapAction_0_to_1)
	HK_PATCH_DEPENDS("hkdAction", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdShareVerticesAction", 0, "hkdShareVerticesAction", 1)
	HK_PATCH_FUNCTION(hkdShareVerticesAction_0_to_1)
	HK_PATCH_DEPENDS("hkdAction", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdMeshOptimizerInfo", 0, "hkdMeshOptimizerInfo", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("limitNumSectionBones", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdPrepareForDynamicFractureAction", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkdAction")
	HK_PATCH_MEMBER_ADDED_BYTE("createAccelerationMeshes", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkdAction", 1)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdImageBasedFracture", 0, "hkdImageBasedFracture", 1)
	HK_PATCH_MEMBER_ADDED_REAL("cutoutSideExpansion", 0.100000f)
	HK_PATCH_MEMBER_ADDED_BYTE("setFrameShapeFixed", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdImageBasedFracture", 1, "hkdImageBasedFracture", 2)
	HK_PATCH_MEMBER_ADDED_BYTE("outputDebugFiles", 0)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("normalAngleThreshold", 0.010000f)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkdFxDebrisFracture", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkdFracture")
	HK_PATCH_MEMBER_ADDED("templateDebris", TYPE_OBJECT, "hkdBreakableShape", 0)
	HK_PATCH_MEMBER_ADDED("templateDebrisUuid", TYPE_STRUCT, "hkUuid", 0)
	HK_PATCH_MEMBER_ADDED_INT("maxNumPieces", 100)
	HK_PATCH_MEMBER_ADDED_REAL("minLifeTime", 1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("maxLifeTime", 1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("minScale", 1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("maxScale", 1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("density", 1.000000f)
	HK_PATCH_MEMBER_ADDED_INT("userData", 0)
	HK_PATCH_DEPENDS("hkdFracture", 4)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpBreakableShape", 1)
	HK_PATCH_DEPENDS("hkdBreakableShape", 6)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkUuid", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdFlattenHierarchyAction", 1, "hkdFlattenHierarchyAction", 2)
	HK_PATCH_MEMBER_ADDED_BYTE("createGraphicsCompound", 0)
	HK_PATCH_MEMBER_ADDED_BYTE("createPhysicsCompound", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdFracture", 4, "hkdFracture", 5)
	HK_PATCH_MEMBER_REMOVED("allowOpenMeshes", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDecorateFractureFaceActionGlobalDecorationData", 3, "hkdDecorateFractureFaceActionGlobalDecorationData", 4)
	HK_PATCH_MEMBER_RENAMED("rawTransforms", "rawTransformsOld")
	HK_PATCH_MEMBER_ADDED("rawTransforms", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkdDecorateFractureFaceActionGlobalDecorationData_3_to_4)
	HK_PATCH_MEMBER_REMOVED("rawTransformsOld", TYPE_ARRAY_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDeformableBreakableShapeBoneInfo", 1, "hkdDeformableBreakableShapeBoneInfo", 2)
	HK_PATCH_MEMBER_RENAMED("modelSpaceBindPoseTransform", "modelSpaceBindPoseTransformOld")
	HK_PATCH_MEMBER_ADDED("modelSpaceBindPoseTransform", TYPE_STRUCT, "hkQTransform", 0)
	HK_PATCH_FUNCTION(hkdDeformableBreakableShapeBoneInfo_1_to_2)
	HK_PATCH_MEMBER_REMOVED("modelSpaceBindPoseTransformOld", TYPE_STRUCT, "hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransform", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdShapeInstanceInfo", 4, "hkdShapeInstanceInfo", 5)
	HK_PATCH_MEMBER_RENAMED("transform", "transformOld")
	HK_PATCH_MEMBER_ADDED("transform", TYPE_STRUCT, "hkQTransform", 0)
	HK_PATCH_FUNCTION(hkdShapeInstanceInfo_4_to_5)
	HK_PATCH_MEMBER_REMOVED("transformOld", TYPE_STRUCT, "hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransform", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDeformableBreakableShapePhysicsSkinInstance", 2, "hkdDeformableBreakableShapePhysicsSkinInstance", 3)
	HK_PATCH_MEMBER_RENAMED("modelSpaceBoneTransforms", "modelSpaceBoneTransformsOld")
	HK_PATCH_MEMBER_ADDED("modelSpaceBoneTransforms", TYPE_ARRAY_STRUCT, "hkQTransform", 0)
	HK_PATCH_FUNCTION(hkdDeformableBreakableShapePhysicsSkinInstance_2_to_3)
	HK_PATCH_MEMBER_REMOVED("modelSpaceBoneTransformsOld", TYPE_ARRAY_STRUCT, "hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransform", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkdDeformableBreakableBodyMemento", 1, "hkdDeformableBreakableBodyMemento", 2)
	HK_PATCH_MEMBER_RENAMED("transforms", "transformsOld")
	HK_PATCH_MEMBER_ADDED("transforms", TYPE_ARRAY_STRUCT, "hkQTransform", 0)
	HK_PATCH_FUNCTION(hkdDeformableBreakableBodyMemento_1_to_2)
	HK_PATCH_MEMBER_REMOVED("transformsOld", TYPE_ARRAY_STRUCT, "hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransform", 2)
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
