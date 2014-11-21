/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Ai specific product patches applied to release 2013_2.
// This file is #included by hkaiPatches_2013_2.cpp

HK_PATCH_BEGIN("hkaiNavVolumePathSearchParameters", 4, "hkaiNavVolumePathSearchParameters", 5)
	HK_PATCH_MEMBER_ADDED_REAL("maximumPathLength", 340282001837565600000000000000000000000.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshCutter", 13, "hkaiNavMeshCutter", 14)
	HK_PATCH_MEMBER_ADDED_REAL("domainQuantum", 0.000000f)
HK_PATCH_END()

#if defined(HK_FEATURE_PRODUCT_AI) && defined(HK_FEATURE_PRODUCT_PHYSICS_2012)
HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavMeshShapeCollection", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpShapeCollection")
	HK_PATCH_MEMBER_ADDED("navMesh", TYPE_OBJECT, "hkaiNavMesh", 0)
	HK_PATCH_DEPENDS("hkpShapeCollection", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpShape", 1)
	HK_PATCH_DEPENDS("hkpShapeBase", 0)
	HK_PATCH_DEPENDS("hkaiNavMesh", 14)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkcdShape", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiMoppNavMeshQueryMediator", 0, "hkaiMoppNavMeshQueryMediator", 1)
	HK_PATCH_MEMBER_ADDED("treeShape", TYPE_OBJECT, "hkpMoppBvTreeShape", 0)
	HK_PATCH_DEPENDS("hkpMoppBvTreeShape", 0)
	HK_PATCH_DEPENDS("hkpBvTreeShape", 1)
	HK_PATCH_DEPENDS("hkpShape", 1)
	HK_PATCH_DEPENDS("hkpShapeBase", 0)
	HK_PATCH_DEPENDS("hkMoppBvTreeShapeBase", 0)
	HK_PATCH_DEPENDS("hkcdShape", 0)
	//HK_PATCH_FUNCTION(hkaiMoppNavMeshQueryMediator_0_to_1)
HK_PATCH_END()
#endif

HK_PATCH_BEGIN("hkaiLineOfSightUtilInputBase", 2, "hkaiLineOfSightUtilInputBase", 3)
	HK_PATCH_MEMBER_ADDED_BYTE("ignoreBackfacingEdges", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiHierarchyUtilsClusterSettings", 1, "hkaiHierarchyUtilsClusterSettings", 2)
	HK_PATCH_MEMBER_REMOVED("ensureClusterPerRegion", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshCutter", 14, "hkaiNavMeshCutter", 15)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("minEdgeMatchingLength", 0.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("smallGapFixupTolerance", 0.001000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiSplitGenerationUtilsSettings", 2, "hkaiSplitGenerationUtilsSettings", 3)
	HK_PATCH_MEMBER_ADDED_REAL("streamingEdgeMatchTolerance", 0.100000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 25, "hkaiNavMeshGenerationSettings", 26)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumeGenerationSettings", 9, "hkaiNavVolumeGenerationSettings", 10)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiLineOfSightUtilInputBase", 3, "hkaiLineOfSightUtilInputBase", 4)
	HK_PATCH_MEMBER_ADDED_BYTE("userEdgeHandling", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiClimbUpAnalyzer", 0, "hkaiClimbUpAnalyzer", 1)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxUnderhang", 1.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("minUpHeight", 0.500000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxUpHeight", 3.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("grabAngle", 1.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("grabScanDepth", 1.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiDuckUnderAnalyzer", 0, "hkaiDuckUnderAnalyzer", 1)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxHorizontalDistance", 0.500000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("minClearance", 0.500000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxClearance", 3.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxHeightDifference", 0.500000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiVaultAnalyzer", 0, "hkaiVaultAnalyzer", 1)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("minWallWidth", 0.007813f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxWallWidth", 0.500000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("minWallHeight", 0.500000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxWallHeight", 1.500000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxUpHeight", 0.500000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxDownHeight", 1.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("verticalApex", 1.500000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("handPlantAngle", 0.500000f)
	HK_PATCH_MEMBER_ADDED_REAL("handPlantLeftExtent", 0.000000f)
	HK_PATCH_MEMBER_ADDED_REAL("handPlantRightExtent", 0.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiDropDownAnalyzer", 0, "hkaiDropDownAnalyzer", 1)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("minDropDistance", 0.500000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxDropDistance", 3.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxUnderhang", 1.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiJumpAnalyzer", 0, "hkaiJumpAnalyzer", 1)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxHorizontalDistance", 2.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxUpHeight", 0.500000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxDownHeight", 1.000000f)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("verticalApex", 0.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiAvoidanceProperties", 12, "hkaiAvoidanceProperties", 13)
	HK_PATCH_MEMBER_REMOVED("avoidanceSolverType", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("agentLimitTime", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("obstacleLimitTime", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("boundaryLimitTime", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("limitObstacleDistance", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("limitObstacleVelocity", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("limitBoundaryDistance", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiLocalSteeringInput", 6, "hkaiLocalSteeringInput", 7)
	HK_PATCH_MEMBER_REMOVED("desiredFutureDir", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("timeToLocalGoal", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("isLocalGoalLast", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

#if defined(HK_FEATURE_PRODUCT_PHYSICS)

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiPhysicsShapeVolume", 3)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaiVolume")
	HK_PATCH_MEMBER_ADDED("shape", TYPE_OBJECT, "hknpShape", 0)
	HK_PATCH_MEMBER_ADDED("shapeTransform", TYPE_VEC_16, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("geometry", TYPE_STRUCT, "hkGeometry", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiVolume", 0)
	HK_PATCH_DEPENDS("hkGeometry", 1)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hknpShape", 1)
HK_PATCH_END()
#endif

HK_PATCH_BEGIN("hkaiNavVolumeGenerationSettingsChunkSettings", 0, "hkaiNavVolumeGenerationSettingsChunkSettings", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("doGreedyMergeAfterCombine", 1)
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
