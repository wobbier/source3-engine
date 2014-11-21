/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// NewDestruction specific product patches applied to release 2013_3.
// This file is #included by hkndPatches_2013_3.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkndConvexHullAction", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkndAction")
	HK_PATCH_MEMBER_ADDED_BYTE("method", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("self", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("recurse", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkndAssetProcessingUnit", 0)
	HK_PATCH_DEPENDS("hkndAction", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndMeshOptimizerInfo", 0, "hkndMeshOptimizerInfo", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("limitNumSectionBones", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkndPrepareForDynamicFractureAction", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkndAction")
	HK_PATCH_MEMBER_ADDED_BYTE("createAccelerationMeshes", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkndAssetProcessingUnit", 0)
	HK_PATCH_DEPENDS("hkndAction", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkndFxDebrisFracture", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkndFracture")
	HK_PATCH_MEMBER_ADDED("debrisTemplateUuid", TYPE_STRUCT, "hkUuid", 0)
	HK_PATCH_MEMBER_ADDED_INT("maxNumPieces", 100)
	HK_PATCH_MEMBER_ADDED_REAL("minLifeTime", 1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("maxLifeTime", 1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("minScale", 1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("maxScale", 1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("density", 1.000000f)
	HK_PATCH_MEMBER_ADDED_INT("userData", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkndFracture", 1)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkndAssetProcessingUnit", 0)
	HK_PATCH_DEPENDS("hkUuid", 1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkndDynamicFractureContextDataBlock", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkndFractureDataBlock")
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkndFractureDataBlock", 0)
	HK_PATCH_DEPENDS("hkndAssetProcessingDataBlock", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndFlexibleJointProcessor", 0, "hkndFlexibleJointProcessor", 1)
	HK_PATCH_MEMBER_ADDED_REAL("activationStrength", 0.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndFlattenHierarchyAction", 0, "hkndFlattenHierarchyAction", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("createGraphicsCompound", 0)
	HK_PATCH_MEMBER_ADDED_BYTE("createPhysicsCompound", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkndImageBasedFracture", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkndFracture")
	HK_PATCH_MEMBER_ADDED("textureImage", TYPE_OBJECT, "hkMeshTexture", 0)
	HK_PATCH_MEMBER_ADDED_BYTE("binarizationThreshold", 40)
	HK_PATCH_MEMBER_ADDED_REAL("cornerMaxAngle", 15.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("lineSimplification", 0.100000f)
	HK_PATCH_MEMBER_ADDED_REAL("mergePointThreshold", 0.100000f)
	HK_PATCH_MEMBER_ADDED_INT("uvChannel", 0)
	HK_PATCH_MEMBER_ADDED_REAL("extrusionDepth", 1.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("normalAngleThreshold", 0.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("cutoutSideExpansion", 0.100000f)
	HK_PATCH_MEMBER_ADDED_BYTE("setFrameShapeFixed", 1)
	HK_PATCH_MEMBER_ADDED("splitPlaneGeometry", TYPE_OBJECT, "hkndSplittingPlane", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkndFracture", 1)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkMeshTexture", 0)
	HK_PATCH_DEPENDS("hkndAssetProcessingUnit", 0)
	HK_PATCH_DEPENDS("hkndSplittingPlane", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndFracture", 1, "hkndFracture", 2)
	HK_PATCH_MEMBER_REMOVED("allowOpenMeshes", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndImageBasedFracture", 0, "hkndImageBasedFracture", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("outputDebugFiles", 0)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("normalAngleThreshold", 0.010000f)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkndCompoundShape", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkndShape")
	HK_PATCH_MEMBER_ADDED("compoundPieceId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("physicsShape", TYPE_OBJECT, "hknpShape", 0)
	HK_PATCH_MEMBER_ADDED("childPieceIds", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("childShapeInstances", TYPE_ARRAY_OBJECT, "hkndShapeInstance", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkndShape", 0)
	HK_PATCH_DEPENDS("hknpShape", 2)
	HK_PATCH_DEPENDS("hkndShapeInstance", 1)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDeformationProcessor", 0, "hkndDeformationProcessor", 1)
	HK_PATCH_MEMBER_REMOVED("constraintStrength", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("constraintBreakingLimit", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("softness", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("deformationTau", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndWoodProcessor", 0, "hkndWoodProcessor", 1)
	HK_PATCH_MEMBER_REMOVED("deformationFriction", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndFractureEngine", 0, "hkndFractureEngine", 1)
	HK_PATCH_MEMBER_ADDED_REAL("minShapeExtentAfterSplit", 0.0f)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkndSphereGun", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hknpProjectileGun")
	HK_PATCH_DEPENDS("hknpFirstPersonGun", 0)
	HK_PATCH_DEPENDS("hknpProjectileGun", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkndStickyGun", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hknpProjectileGun")
	HK_PATCH_DEPENDS("hknpFirstPersonGun", 0)
	HK_PATCH_DEPENDS("hknpProjectileGun", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkndRaycastGun", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hknpFirstPersonGun")
	HK_PATCH_MEMBER_ADDED_REAL("destructionRadius", 0.600000f)
	HK_PATCH_MEMBER_ADDED_REAL("beamRadius", 0.100000f)
	HK_PATCH_MEMBER_ADDED_REAL("mass", 1000.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("velocity", 20.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("angImpulseFactor", 0.400000f)
	HK_PATCH_MEMBER_ADDED_INT("shockwaveEnabled", 1)
	HK_PATCH_DEPENDS("hknpFirstPersonGun", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkndMissileGun", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hknpProjectileGun")
	HK_PATCH_DEPENDS("hknpFirstPersonGun", 0)
	HK_PATCH_DEPENDS("hknpProjectileGun", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkndGrenadeGun", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hknpProjectileGun")
	HK_PATCH_DEPENDS("hknpFirstPersonGun", 0)
	HK_PATCH_DEPENDS("hknpProjectileGun", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDeformableShape", 0, "hkndDeformableShape", 1)
	HK_PATCH_MEMBER_RENAMED("invBindPose", "invBindPoseOld")
	HK_PATCH_MEMBER_ADDED("invBindPose", TYPE_ARRAY_STRUCT, "hkQTransform", 0)
	HK_PATCH_FUNCTION(hkndDeformableShape_0_to_1)
	HK_PATCH_MEMBER_REMOVED("invBindPoseOld", TYPE_ARRAY_STRUCT, "hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransform", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndHierarchyInstance", 0, "hkndHierarchyInstance", 1)
	HK_PATCH_MEMBER_RENAMED("hierarchyFromPieceTransforms", "hierarchyFromPieceTransformsOld")
	HK_PATCH_MEMBER_ADDED("hierarchyFromPieceTransforms", TYPE_ARRAY_STRUCT, "hkQTransform", 0)
	HK_PATCH_FUNCTION(hkndHierarchyInstance_0_to_1)
	HK_PATCH_MEMBER_REMOVED("hierarchyFromPieceTransformsOld", TYPE_ARRAY_STRUCT, "hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransform", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDecalMapActionDecalMapData", 0, "hkndDecalMapActionDecalMapData", 1)
	HK_PATCH_MEMBER_RENAMED("bodyFromDecoration", "bodyFromDecorationOld")
	HK_PATCH_MEMBER_ADDED("bodyFromDecoration", TYPE_STRUCT, "hkQTransform", 0)
	HK_PATCH_FUNCTION(hkndDecalMapActionDecalMapData_0_to_1)
	HK_PATCH_MEMBER_REMOVED("bodyFromDecorationOld", TYPE_STRUCT, "hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransform", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDecorateFractureFaceRuntimeGlobalDecorationData", 1, "hkndDecorateFractureFaceRuntimeGlobalDecorationData", 2)
	HK_PATCH_MEMBER_RENAMED("rawTransforms", "rawTransformsOld")
	HK_PATCH_MEMBER_ADDED("rawTransforms", TYPE_ARRAY_STRUCT, "hkQTransform", 0)
	HK_PATCH_FUNCTION(hkndDecorateFractureFaceRuntimeGlobalDecorationData_1_to_2)
	HK_PATCH_MEMBER_REMOVED("rawTransformsOld", TYPE_ARRAY_STRUCT, "hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransform", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDeformableBodySnapshot", 0, "hkndDeformableBodySnapshot", 1)
	HK_PATCH_MEMBER_RENAMED("hierarchyFromPieceTransforms", "hierarchyFromPieceTransformsOld")
	HK_PATCH_MEMBER_ADDED("hierarchyFromPieceTransforms", TYPE_ARRAY_STRUCT, "hkQTransform", 0)
	HK_PATCH_FUNCTION(hkndDeformableBodySnapshot_0_to_1)
	HK_PATCH_MEMBER_REMOVED("hierarchyFromPieceTransformsOld", TYPE_ARRAY_STRUCT, "hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransform", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndBreakableBodySnapshot", 1, "hkndBreakableBodySnapshot", 2)
	HK_PATCH_MEMBER_RENAMED("worldFromBody", "worldFromBodyOld")
	HK_PATCH_MEMBER_ADDED("worldFromBody", TYPE_STRUCT, "hkQTransform", 0)
	HK_PATCH_FUNCTION(hkndBreakableBodySnapshot_1_to_2)
	HK_PATCH_MEMBER_REMOVED("worldFromBodyOld", TYPE_STRUCT, "hkQTransformf", 0)
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
