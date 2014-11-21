/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// NewDestruction specific product patches applied to release 2013_2.
// This file is #included by hkndPatches_2013_2.cpp

HK_PATCH_BEGIN("hkndDecalMapActionDecalMap", 0, "hkndDecalMapActionDecalMap", 1)
	HK_PATCH_MEMBER_ADDED_INT("uvChannel", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkndBreakableBodyMergeUtilPropertyBag", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("properties", TYPE_STRUCT, "hkRefCountedProperties", 0)
	HK_PATCH_DEPENDS("hkRefCountedProperties", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndConnection", 0, "hkndConnection", 1)
	HK_PATCH_MEMBER_ADDED("inertiaXx", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("inertiaYy", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("userData", TYPE_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkndConnection_0_to_1)
	HK_PATCH_MEMBER_REMOVED("inertia", TYPE_TUPLE_INT, HK_NULL, 4)	
HK_PATCH_END()

HK_PATCH_BEGIN("hkndFracturePiece", 0, "hkndFracturePiece", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("lodMask", 0)
	HK_PATCH_FUNCTION(hkndFracturePiece_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDestructionDemoConfig", 0, "hkndDestructionDemoConfig", 1)
	HK_PATCH_MEMBER_ADDED_REAL("distanceLodFine", 10.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("distanceLodCoarse", 20.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkFreeListArrayhkndMaterialhkHandleunsignedint4294967295hkndMaterialUniqueId8hkndMaterialLibraryStorageOps", 0)
	HK_PATCH_MEMBER_ADDED("elements", TYPE_ARRAY_STRUCT, "hkndMaterial", 0)
	HK_PATCH_MEMBER_ADDED("firstFree", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkndMaterial", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkndMaterialLibrary", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("materials", TYPE_STRUCT, "hkFreeListArrayhkndMaterialhkHandleunsignedint4294967295hkndMaterialUniqueId8hkndMaterialLibraryStorageOps", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkFreeListArrayhkndMaterialhkHandleunsignedint4294967295hkndMaterialUniqueId8hkndMaterialLibraryStorageOps", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndHierarchy", 0, "hkndHierarchy", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("numLods", 3)
	HK_PATCH_MEMBER_ADDED("mtlLibrary", TYPE_OBJECT, "hkndMaterialLibrary", 0)
	HK_PATCH_DEPENDS("hkndMaterialLibrary", 0)
	HK_PATCH_FUNCTION(hkndHierarchy_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndMaterial", 0, "hkndMaterial", 1)
	HK_PATCH_MEMBER_ADDED_INT("flags", 1)
	HK_PATCH_MEMBER_ADDED("userData", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndBodyCinfo", 0, "hkndBodyCinfo", 1)
	HK_PATCH_MEMBER_ADDED("uuid", TYPE_STRUCT, "hkUuid", 0)
	HK_PATCH_MEMBER_ADDED("userData", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkUuid", 1)
	HK_PATCH_DEPENDS("hkndDebrisFracture", 0) 
	HK_PATCH_FUNCTION(hkndBodyCinfo_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDestructionSystemDataBodyClone", 0, "hkndDestructionSystemDataBodyClone", 1)
	HK_PATCH_MEMBER_ADDED("userData", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDebrisFractureInfoTemplateInfo", 0, "hkndDebrisFractureInfoTemplateInfo", 1)
	HK_PATCH_MEMBER_ADDED("debrisTemplateUuid", TYPE_STRUCT, "hkUuid", 0)
	HK_PATCH_DEPENDS("hkUuid", 1)
	HK_PATCH_FUNCTION(hkndDebrisFractureInfoTemplateInfo_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDebrisFracture", 0, "hkndDebrisFracture", 1)
	HK_PATCH_MEMBER_ADDED("debrisTemplateUuid", TYPE_STRUCT, "hkUuid", 0)
	HK_PATCH_MEMBER_ADDED("controlShapesUuid", TYPE_STRUCT, "hkUuid", 0)
	HK_PATCH_DEPENDS("hkUuid", 1)
	HK_PATCH_FUNCTION(hkndDebrisFracture_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDestructionSystemData", 0, "hkndDestructionSystemData", 1)
	HK_PATCH_MEMBER_ADDED("mtlLibrary", TYPE_OBJECT, "hkndMaterialLibrary", 0)
	HK_PATCH_DEPENDS("hkndMaterial", 0)
	HK_PATCH_DEPENDS("hkndMaterialLibrary", 0)
	HK_PATCH_DEPENDS("hkndHierarchy", 1)
	HK_PATCH_DEPENDS("hkndBodyCinfo", 1)
	HK_PATCH_DEPENDS("hkndDebrisFractureInfoTemplateInfo", 1)
	HK_PATCH_DEPENDS("hkndDebrisFracture", 1)
	HK_PATCH_DEPENDS("hkndDecorateFractureFaceRuntimeGlobalDecorationData", 1)
	HK_PATCH_FUNCTION(hkndDestructionSystemData_0_to_1)
	HK_PATCH_MEMBER_REMOVED("materials", TYPE_ARRAY_STRUCT, "hkndMaterial", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDebrisFractureInfoTemplateInfo", 1, "hkndDebrisFractureInfoTemplateInfo", 2)
	HK_PATCH_MEMBER_REMOVED("debrisTemplateProviderId", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDebrisFracture", 1, "hkndDebrisFracture", 2)
	HK_PATCH_MEMBER_REMOVED("debrisTemplateProviderId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("controlShapesProviderId", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDecorateFractureFaceActionCornerDecorationInfo", 0, "hkndDecorateFractureFaceActionCornerDecorationInfo", 1)
	HK_PATCH_MEMBER_ADDED("decorationsUuid", TYPE_STRUCT, "hkUuid", 0)
	HK_PATCH_MEMBER_REMOVED("decorationsProviderId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkUuid", 1)
	HK_PATCH_FUNCTION(hkndDecorateFractureFaceActionCornerDecorationInfo_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDecorateFractureFaceActionFractureFaceInfo", 0, "hkndDecorateFractureFaceActionFractureFaceInfo", 1)
	HK_PATCH_MEMBER_ADDED("decorationsUuid", TYPE_STRUCT, "hkUuid", 0)
	HK_PATCH_MEMBER_REMOVED("decorationsProviderId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkUuid", 1)
	HK_PATCH_FUNCTION(hkndDecorateFractureFaceActionFractureFaceInfo_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDecorateFractureFaceRuntimeDecorationId", 0, "hkndDecorateFractureFaceRuntimeDecorationId", 1)
	HK_PATCH_MEMBER_ADDED("providerId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkndHierarchy", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDecorateFractureFaceRuntimeGlobalDecorationData", 0, "hkndDecorateFractureFaceRuntimeGlobalDecorationData", 1)
	HK_PATCH_MEMBER_ADDED("providerUuids", TYPE_ARRAY_STRUCT, "hkUuid", 0)
	HK_PATCH_DEPENDS("hkUuid", 1)
	HK_PATCH_DEPENDS("hkndDecorateFractureFaceRuntimeDecorationId", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDecorateFractureFaceRuntimeDecorationId", 1, "hkndDecorateFractureFaceRuntimeDecorationId", 2)
	HK_PATCH_MEMBER_REMOVED("hierarchy", TYPE_OBJECT, "hkndHierarchy", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkndHierarchy", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDecorateFractureFaceActionGeomSource", 0, "hkndDecorateFractureFaceActionGeomSource", 1)
	HK_PATCH_PARENT_SET("hknpExternMeshShapeMesh", "hknpExternMeshShapeGeometry")
	HK_PATCH_DEPENDS("hknpExternMeshShapeMesh", 0)
	HK_PATCH_DEPENDS("hknpExternMeshShapeGeometry", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndSetRigidBodyPropertiesModifierData", 0, "hkndSetRigidBodyPropertiesModifierData", 1)
	HK_PATCH_MEMBER_REMOVED("materialId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("motionPropertiesId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("material", TYPE_STRUCT, "hknpMaterial", 0)
	HK_PATCH_MEMBER_ADDED("motionProperties", TYPE_STRUCT, "hknpMotionProperties", 0)
	HK_PATCH_DEPENDS("hknpMaterial", 0)
	HK_PATCH_DEPENDS("hknpMotionProperties", 1)
	//HK_PATCH_FUNCTION(hkndSetRigidBodyPropertiesModifierData_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndGeometryTriangleSource", 0, "hkndGeometryTriangleSource", 1)
	HK_PATCH_MEMBER_ADDED("uuid", TYPE_STRUCT, "hkUuid", 0)
	HK_PATCH_DEPENDS("hkUuid", 1)
	HK_PATCH_FUNCTION(hkndGeometryTriangleSource_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndDestructionSystemData", 1, "hkndDestructionSystemData", 2)
	HK_PATCH_MEMBER_REMOVED("rbMaterials", TYPE_ARRAY_STRUCT, "hknpMaterial", 0)
	HK_PATCH_MEMBER_REMOVED("rbMotionProperties", TYPE_ARRAY_STRUCT, "hknpMotionProperties", 0)
	HK_PATCH_DEPENDS("hknpMaterial", 1)
	HK_PATCH_DEPENDS("hknpMotionProperties", 2)
	//HK_PATCH_FUNCTION(hkndDestructionSystemData_1_to_2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndFracture", 0, "hkndFracture", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("splitDisjointPieces", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkndFracturePiece", 1, "hkndFracturePiece", 2)
	HK_PATCH_FUNCTION(hkndFracturePiece_1_to_2)
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
