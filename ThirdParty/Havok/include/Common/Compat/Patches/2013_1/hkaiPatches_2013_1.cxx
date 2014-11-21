/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Ai specific product patches applied to release 2013_1.
// This file is #included by hkaiPatches_2013_1.cpp

HK_PATCH_BEGIN("hkaiSilhouetteRecorderSilhouettesSteppedEvent", 2, "hkaiSilhouetteRecorderSilhouettesSteppedEvent", 3)
	// There was a patch to the hkBitField members here, this is no longer required
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiCuttingGeometryInfo", 0, "hkaiCuttingGeometryInfo", 1)
	// There was a patch to the hkBitField members here, this is no longer required
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiSplitGenerationUtils", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettingsEdgeMatchingParameters", 7, "hkaiNavMeshEdgeMatchingParameters", 8)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettingsRegionPruningSettings", 1, "hkaiNavMeshGenerationSettingsRegionPruningSettings", 2)
	HK_PATCH_MEMBER_ADDED_BYTE("pruneBeforeTriangulation", 1)
HK_PATCH_END()


HK_PATCH_BEGIN("hkaiGraphPathSearchParameters", 0, "hkaiGraphPathSearchParameters", 1)
	HK_PATCH_MEMBER_ADDED_REAL("heuristicWeight", 1.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiDirectedGraphExplicitCost", 6, "hkaiDirectedGraphExplicitCost", 7)
	HK_PATCH_MEMBER_ADDED("nodeData", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("edgeData", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_INT("nodeDataStriding", 0)
	HK_PATCH_MEMBER_ADDED_INT("edgeDataStriding", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiAstarOutputParameters", 1, "hkaiAstarOutputParameters", 2)
	HK_PATCH_MEMBER_ADDED_REAL("pathLength", 340282001837565600000000000000000000000.000000f) //HK_REAL_MAX
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiSearchParametersSearchBuffers", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiSearchParameters", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiSearchParametersBufferSizes", 0)
	HK_PATCH_MEMBER_ADDED_INT("maxOpenSetSizeBytes", 0)
	HK_PATCH_MEMBER_ADDED_INT("maxSearchStateSizeBytes", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshPathSearchParameters", 9, "hkaiNavMeshPathSearchParameters", 10)
	HK_PATCH_MEMBER_ADDED("bufferSizes", TYPE_STRUCT, "hkaiSearchParametersBufferSizes", 0)
	HK_PATCH_MEMBER_ADDED("hierarchyBufferSizes", TYPE_STRUCT, "hkaiSearchParametersBufferSizes", 0)
	HK_PATCH_FUNCTION(hkaiNavMeshPathSearchParameters_9_to_10)
	HK_PATCH_MEMBER_REMOVED("maxOpenSetSizeBytes", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("maxSearchStateSizeBytes", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("maxHierarchyOpenSetSizeBytes", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("maxHierarchySearchStateSizeBytes", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkaiSearchParametersBufferSizes", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumePathSearchParameters", 3, "hkaiNavVolumePathSearchParameters", 4)
	HK_PATCH_MEMBER_ADDED("bufferSizes", TYPE_STRUCT, "hkaiSearchParametersBufferSizes", 0)
	HK_PATCH_FUNCTION(hkaiNavVolumePathSearchParameters_3_to_4)
	HK_PATCH_MEMBER_REMOVED("maxOpenSetSizeBytes", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("maxSearchStateSizeBytes", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkaiSearchParametersBufferSizes", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiGraphPathSearchParameters", 1, "hkaiGraphPathSearchParameters", 2)
	HK_PATCH_MEMBER_ADDED("bufferSizes", TYPE_STRUCT, "hkaiSearchParametersBufferSizes", 0)
	HK_PATCH_MEMBER_ADDED("hierarchyBufferSizes", TYPE_STRUCT, "hkaiSearchParametersBufferSizes", 0)
	HK_PATCH_FUNCTION(hkaiGraphPathSearchParameters_1_to_2)
	HK_PATCH_MEMBER_REMOVED("maxOpenSetSizeBytes", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("maxSearchStateSizeBytes", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_BYTE("useHierarchicalHeuristic", 1)
	HK_PATCH_DEPENDS("hkaiSearchParametersBufferSizes", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiStreamingSetGraphConnection", 0, "hkaiStreamingSetGraphConnection", 1)
	
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiDirectedGraphInstance", 0, "hkaiDirectedGraphInstance", 1)
	HK_PATCH_MEMBER_ADDED("ownedEdgeData", TYPE_ARRAY_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiStreamingSetGraphConnection", 1, "hkaiStreamingSetGraphConnection", 2)
	HK_PATCH_MEMBER_ADDED_INT("edgeData", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathfindingUtilFindGraphPathInput", 0, "hkaiPathfindingUtilFindGraphPathInput", 1)
	HK_PATCH_MEMBER_ADDED("agentInfo", TYPE_STRUCT, "hkaiAgentTraversalInfo", 0)
	HK_PATCH_DEPENDS("hkaiAgentTraversalInfo", 1)
	//HK_PATCH_FUNCTION(hkaiPathfindingUtilFindGraphPathInput_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiPathfindingUtilFindGraphPathInput", 1, "hkaiPathfindingUtilFindGraphPathInput", 2)
	HK_PATCH_MEMBER_REMOVED("startNodeKey", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("goalNodeKey", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("startNodeKeys", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("initialCosts", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("goalNodeKeys", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("finalCosts", TYPE_ARRAY_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiStreamingSetGraphConnection", 2, "hkaiStreamingSetGraphConnection", 3)
	HK_PATCH_MEMBER_ADDED("edgeCost", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkaiStreamingSetGraphConnection_2_to_3)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshEdgeMatchingParameters", 8, "hkaiNavMeshEdgeMatchingParameters", 9)
	HK_PATCH_MEMBER_ADDED_BYTE("useSafeEdgeTraversibilityHorizontalEpsilon", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiSplitGenerationUtilsSettings", 1, "hkaiSplitGenerationUtilsSettings", 2)
	HK_PATCH_MEMBER_DEFAULT_SET_BYTE("splitMethod", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshSimplificationUtilsExtraVertexSettings", 3, "hkaiNavMeshSimplificationUtilsExtraVertexSettings", 4)
	HK_PATCH_MEMBER_ADDED_BYTE("addVerticesOnPartitionBorders", 1)
	HK_PATCH_MEMBER_ADDED_REAL("partitionBordersSplitLength", 50.000000f)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiHierarchyUtilsClusterSettings", 0, "hkaiHierarchyUtilsClusterSettings", 1)
	HK_PATCH_MEMBER_REMOVED("costModifier", TYPE_OBJECT, "hkaiAstarCostModifier", 0)
	HK_PATCH_MEMBER_REMOVED("edgeFilter", TYPE_OBJECT, "hkaiAstarEdgeFilter", 0)
	HK_PATCH_MEMBER_ADDED("searchParameters", TYPE_STRUCT, "hkaiNavMeshPathSearchParameters", 0)
	HK_PATCH_MEMBER_ADDED("agentInfo", TYPE_STRUCT, "hkaiAgentTraversalInfo", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkaiAstarCostModifier", 3)
	HK_PATCH_DEPENDS("hkaiAstarEdgeFilter", 0)
	HK_PATCH_DEPENDS("hkaiNavMeshPathSearchParameters", 10)
	HK_PATCH_DEPENDS("hkaiAgentTraversalInfo", 1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiNavMeshSimplificationSnapshot", 0)
	HK_PATCH_MEMBER_ADDED("geometry", TYPE_OBJECT, "hkGeometry", 0)
	HK_PATCH_MEMBER_ADDED("carvers", TYPE_ARRAY_OBJECT, "hkaiVolume", 0)
	HK_PATCH_MEMBER_ADDED("cuttingTriangles", TYPE_STRUCT, "hkBitField", 0)
	HK_PATCH_MEMBER_ADDED("settings", TYPE_STRUCT, "hkaiNavMeshGenerationSettings", 0)
	HK_PATCH_MEMBER_ADDED("unsimplifiedNavMesh", TYPE_OBJECT, "hkaiNavMesh", 0)
	HK_PATCH_DEPENDS("hkBitField", 2)
	HK_PATCH_DEPENDS("hkaiNavMeshGenerationSettings", 24)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkGeometry", 1)
	HK_PATCH_DEPENDS("hkaiVolume", 0)
	HK_PATCH_DEPENDS("hkaiNavMesh", 14)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshSimplificationUtilsSettings", 12, "hkaiNavMeshSimplificationUtilsSettings", 13)
	HK_PATCH_MEMBER_ADDED("saveInputSnapshot", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("snapshotFilename", TYPE_CSTRING, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshCutter", 11, "hkaiNavMeshCutter", 12)
	HK_PATCH_MEMBER_ADDED_BYTE("useNewCutter", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiMovementProperties", 7, "hkaiMovementProperties", 8)
	HK_PATCH_MEMBER_REMOVED("maxAngularAcceleration", TYPE_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavVolumeGenerationSettings", 8, "hkaiNavVolumeGenerationSettings", 9)
	HK_PATCH_MEMBER_REMOVED("validateInputGeometry", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

#if defined(HK_FEATURE_PRODUCT_PHYSICS)

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiPhysicsBodySilhouetteGenerator", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaiPhysicsBodySilhouetteGeneratorBase")
	HK_PATCH_DEPENDS("hkaiSilhouetteGenerator", 2)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiPointCloudSilhouetteGenerator", 1)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkaiPhysicsBodySilhouetteGeneratorBase", 1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkaiPhysicsBodyObstacleGenerator", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkaiObstacleGenerator")
	HK_PATCH_MEMBER_ADDED("velocityThreshold", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkaiObstacleGenerator", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()
#endif // HK_FEATURE_PRODUCT_PHYSICS

HK_PATCH_BEGIN("hkaiNavMeshCutter", 12, "hkaiNavMeshCutter", 13)
        HK_PATCH_MEMBER_ADDED("forceClearanceCalcFaceKeys", TYPE_ARRAY_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED_BYTE("recomputeClearanceAfterCutting", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiWorld", 31, "hkaiWorld", 32)
        HK_PATCH_MEMBER_ADDED("precomputeNavMeshClearance", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkaiNavMeshGenerationSettings", 24, "hkaiNavMeshGenerationSettings", 25)
	HK_PATCH_MEMBER_ADDED_BYTE("triangleWinding", 0)
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
