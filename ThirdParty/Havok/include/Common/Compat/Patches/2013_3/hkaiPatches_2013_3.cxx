/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Ai specific product patches applied to release 2013_3.
// This file is #included by hkaiPatches_2013_3.cpp
HK_PATCH_BEGIN("hkaiWorld", 32, "hkaiWorld", 33)
	HK_PATCH_MEMBER_RENAMED("numPathRequestsPerJob", "numPathRequestsPerTask")
	HK_PATCH_MEMBER_RENAMED("numBehaviorUpdatesPerJob", "numBehaviorUpdatesPerTask")
	HK_PATCH_MEMBER_RENAMED("numCharactersPerAvoidanceJob", "numCharactersPerAvoidanceTask")
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumePathSearchParameters", 5, "hkaiNavVolumePathSearchParameters", 6)
	HK_PATCH_MEMBER_RENAMED("up", "upOld")
	HK_PATCH_MEMBER_ADDED("up", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkaiNavVolumePathSearchParameters_5_to_6)
	HK_PATCH_MEMBER_REMOVED("upOld", TYPE_TUPLE_INT, HK_NULL, 3)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshPathSearchParameters", 10, "hkaiNavMeshPathSearchParameters", 11)
	HK_PATCH_MEMBER_RENAMED("up", "upOld")
	HK_PATCH_MEMBER_ADDED("up", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkaiNavMeshPathSearchParameters_10_to_11)
	HK_PATCH_MEMBER_REMOVED("upOld", TYPE_TUPLE_INT, HK_NULL, 3)
HK_PATCH_END()

#if defined(HK_FEATURE_PRODUCT_AI) && defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
HK_PATCH_BEGIN("hkaiMoppNavMeshQueryMediator", 1, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hkaiNavMeshQueryMediator", HK_NULL)
	HK_PATCH_MEMBER_REMOVED("code", TYPE_OBJECT, "hkpMoppCode", 0)
	HK_PATCH_MEMBER_REMOVED("codeInfoCopy", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("navMesh", TYPE_OBJECT, "hkaiNavMesh", 0)
	HK_PATCH_MEMBER_REMOVED("treeShape", TYPE_OBJECT, "hkpMoppBvTreeShape", 0)
	HK_PATCH_DEPENDS("hkpMoppBvTreeShape", 0)
	HK_PATCH_DEPENDS("hkpBvTreeShape", 1)
	HK_PATCH_DEPENDS("hkaiNavMesh", 14)
	HK_PATCH_DEPENDS("hkpShapeBase", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpShape", 1)
	HK_PATCH_DEPENDS("hkaiNavMeshQueryMediator", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkpMoppCode", 0)
	HK_PATCH_DEPENDS("hkMoppBvTreeShapeBase", 0)
	HK_PATCH_DEPENDS("hkcdShape", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshShapeCollection", 0, HK_NULL, HK_CLASS_REMOVED)
	HK_PATCH_PARENT_SET("hkpShapeCollection", HK_NULL)
	HK_PATCH_MEMBER_REMOVED("navMesh", TYPE_OBJECT, "hkaiNavMesh", 0)
	HK_PATCH_DEPENDS("hkpShapeCollection", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpShape", 1)
	HK_PATCH_DEPENDS("hkpShapeBase", 0)
	HK_PATCH_DEPENDS("hkaiNavMesh", 14)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkcdShape", 0)
HK_PATCH_END()
#endif

HK_PATCH_BEGIN("hkaiSplitGenerationUtilsSettings", 3, "hkaiSplitGenerationUtilsSettings", 4)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("simplificationOptions", 3)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiTraversalAnalysisInputSection", 0)
	HK_PATCH_MEMBER_ADDED("navMeshInstance", TYPE_OBJECT, "hkaiNavMeshInstance", 0)
	HK_PATCH_MEMBER_ADDED("geometry", TYPE_OBJECT, "hkGeometry", 0)
	HK_PATCH_MEMBER_ADDED("walkableBitfield", TYPE_STRUCT, "hkBitField", 0)
	HK_PATCH_MEMBER_ADDED("cuttingBitfield", TYPE_STRUCT, "hkBitField", 0)
	HK_PATCH_DEPENDS("hkBitField", 2)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkGeometry", 1)
	HK_PATCH_DEPENDS("hkaiNavMeshInstance", 5)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkBitFieldBasehkBitFieldStoragehkArrayunsignedinthkContainerHeapAllocator", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiTraversalAnalysisInput", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("sections", TYPE_ARRAY_STRUCT, "hkaiTraversalAnalysisInputSection", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiTraversalAnalysisInputSection", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiTraversalAnalysisOutputSection", 0)
	HK_PATCH_MEMBER_ADDED("uid", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("annotationLibrary", TYPE_OBJECT, "hkaiTraversalAnnotationLibrary", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiTraversalAnnotationLibrary", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiTraversalAnalysisOutput", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("sections", TYPE_ARRAY_STRUCT, "hkaiTraversalAnalysisOutputSection", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiTraversalAnalysisOutputSection", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiTraversalAnalysis", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("settings", TYPE_OBJECT, "hkaiTraversalAnalysisSettings", 0)
	HK_PATCH_MEMBER_ADDED("analyzers", TYPE_ARRAY_OBJECT, "hkaiTraversalAnalyzer", 0)
	HK_PATCH_MEMBER_ADDED("input", TYPE_OBJECT, "hkaiTraversalAnalysisInput", 0)
	HK_PATCH_MEMBER_ADDED("output", TYPE_OBJECT, "hkaiTraversalAnalysisOutput", 0)
	HK_PATCH_DEPENDS("hkaiTraversalAnalysisOutput", 0)
	HK_PATCH_DEPENDS("hkaiTraversalAnalysisSettings", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiTraversalAnalyzer", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkaiTraversalAnalysisInput", 0)
HK_PATCH_END()

#define DEFAULT_LAYER 1

// HK_PATCH_BEGIN("hkaiNavMesh", 14, "hkaiNavMesh", 15)
// 	HK_PATCH_MEMBER_ADDED_INT("layer", DEFAULT_LAYER )
// HK_PATCH_END()
// 
// HK_PATCH_BEGIN("hkaiNavVolume", 10, "hkaiNavVolume", 11)
// 	HK_PATCH_MEMBER_ADDED_INT("layer", DEFAULT_LAYER )
// HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumeInstance", 0, "hkaiNavVolumeInstance", 1)
	HK_PATCH_MEMBER_ADDED_INT("layer", DEFAULT_LAYER)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshInstance", 4, "hkaiNavMeshInstance", 6)
	HK_PATCH_MEMBER_ADDED_INT("layer", DEFAULT_LAYER)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCharacter", 28, "hkaiCharacter", 29)
	HK_PATCH_MEMBER_ADDED_INT("layer", DEFAULT_LAYER )
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 33, "hkaiWorld", 34)
	HK_PATCH_MEMBER_REMOVED("erosionRadius", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiCarver", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("volume", TYPE_OBJECT, "hkaiVolume", 0)
	HK_PATCH_MEMBER_ADDED_INT("flags", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiVolume", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshSimplificationSnapshot", 0, "hkaiNavMeshSimplificationSnapshot", 1)
	HK_PATCH_MEMBER_RENAMED("carvers", "carversOld")
	HK_PATCH_MEMBER_ADDED("carvers", TYPE_ARRAY_OBJECT, "hkaiCarver", 0)
	HK_PATCH_FUNCTION(hkaiNavMeshSimplificationSnapshot_0_to_1)
	HK_PATCH_MEMBER_REMOVED("carversOld", TYPE_ARRAY_OBJECT, "hkaiVolume", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiVolume", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkaiCarver", 1)
	
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 26, "hkaiNavMeshGenerationSettings", 27)
	HK_PATCH_MEMBER_RENAMED("carvers", "carversOld")
	HK_PATCH_MEMBER_ADDED("carvers", TYPE_ARRAY_OBJECT, "hkaiCarver", 0)
	HK_PATCH_FUNCTION(hkaiNavMeshGenerationSettings_26_to_27)
	HK_PATCH_MEMBER_REMOVED("carversOld", TYPE_ARRAY_OBJECT, "hkaiVolume", 0)
	HK_PATCH_DEPENDS("hkaiVolume", 0)
	HK_PATCH_DEPENDS("hkaiCarver", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumeGenerationSettings", 10, "hkaiNavVolumeGenerationSettings", 11)
	HK_PATCH_MEMBER_RENAMED("carvers", "carversOld")
	HK_PATCH_MEMBER_ADDED("carvers", TYPE_ARRAY_OBJECT, "hkaiCarver", 0)
	HK_PATCH_FUNCTION(hkaiNavVolumeGenerationSettings_10_to_11)
	HK_PATCH_MEMBER_REMOVED("carversOld", TYPE_ARRAY_OBJECT, "hkaiVolume", 0)
	HK_PATCH_DEPENDS("hkaiVolume", 0)
	HK_PATCH_DEPENDS("hkaiCarver", 1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiOverlappingTriangles", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiOverlappingTrianglesSettings", 0)
	HK_PATCH_MEMBER_ADDED_REAL("coplanarityTolerance", 0.001000f)
	HK_PATCH_MEMBER_ADDED_REAL("raycastLengthMultiplier", 5.000000f)
	HK_PATCH_MEMBER_ADDED_BYTE("walkableTriangleSettings", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 27, "hkaiNavMeshGenerationSettings", 28)
	HK_PATCH_MEMBER_ADDED_BYTE("fixupOverlappingTriangles", 1)
	HK_PATCH_MEMBER_ADDED("overlappingTrianglesSettings", TYPE_STRUCT, "hkaiOverlappingTrianglesSettings", 0)
	HK_PATCH_DEPENDS("hkaiOverlappingTrianglesSettings", 0)
	//HK_PATCH_FUNCTION(hkaiNavMeshGenerationSettings_27_to_28)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiSilhouetteGenerator", 2, "hkaiSilhouetteGenerator", 3)
	HK_PATCH_FUNCTION(hkaiSilhouetteGenerator_2_to_3)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettingsOverrideSettings", 3, "hkaiNavMeshGenerationSettingsOverrideSettings", 4)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxWalkableSlope", 1.047198f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 28, "hkaiNavMeshGenerationSettings", 29)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("degenerateAreaThreshold", 0.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("convexThreshold", 0.100000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("weldThreshold", 0.010000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("quantizationGridSize", 0.007813f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("degenerateWidthThreshold", 0.005000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiClimbUpAnalyzer", 1, "hkaiClimbUpAnalyzer", 2)
	HK_PATCH_MEMBER_ADDED_REAL("verticalLipHeight", 1.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiDropDownAnalyzer", 1, "hkaiDropDownAnalyzer", 2)
	HK_PATCH_MEMBER_ADDED_REAL("verticalLipHeight", 1.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiSilhouetteGenerator", 3, "hkaiSilhouetteGenerator", 4)
	HK_PATCH_MEMBER_RENAMED("transform", "transformOld")
	HK_PATCH_MEMBER_ADDED("transform", TYPE_STRUCT, "hkQTransform", 0)
	HK_PATCH_FUNCTION(hkaiSilhouetteGenerator_3_to_4)
	HK_PATCH_MEMBER_REMOVED("transformOld", TYPE_STRUCT, "hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransform", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiConvexSilhouetteSet", 1, "hkaiConvexSilhouetteSet", 2)
	HK_PATCH_MEMBER_RENAMED("cachedTransform", "cachedTransformOld")
	HK_PATCH_MEMBER_ADDED("cachedTransform", TYPE_STRUCT, "hkQTransform", 0)
	HK_PATCH_FUNCTION(hkaiConvexSilhouetteSet_1_to_2)
	HK_PATCH_MEMBER_REMOVED("cachedTransformOld", TYPE_STRUCT, "hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransformf", 0)
	HK_PATCH_DEPENDS("hkQTransform", 2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiSilhouetteGeneratorSectionContext", 0, "hkaiSilhouetteGeneratorSectionContext", 1)
	HK_PATCH_MEMBER_RENAMED("lastRelativeTransform", "lastRelativeTransformOld")
	HK_PATCH_MEMBER_ADDED("lastRelativeTransform", TYPE_STRUCT, "hkQTransform", 0)
	HK_PATCH_FUNCTION(hkaiSilhouetteGeneratorSectionContext_0_to_1)
	HK_PATCH_MEMBER_REMOVED("lastRelativeTransformOld", TYPE_STRUCT, "hkQTransformf", 0)
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
