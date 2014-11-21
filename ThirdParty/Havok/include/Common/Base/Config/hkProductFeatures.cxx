/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Config/hkProductFeatures.h>
#include <Common/Serialize/Version/hkVersionPatchManager.h>
#include <Common/Compat/hkHavokVersions.h>
#include <Common/Base/Config/hkOptionalComponent.h>


// HK_SERIALIZE_MIN_COMPATIBLE_VERSION can be used to define which is the oldest
// compatible version of Havok assets. Removing compatibility with older versions
// that will never be used in a given project can cause a significant code size
// reduction. The list of supported versions is given in 
// Common/Compat/Deprecated/Compat/hkCompatVersions.h.
// The minimum compatible version is specified using just the release number:
// to have compatibility at most with version 650b1 the user should use
// #define HK_SERIALIZE_MIN_COMPATIBLE_VERSION 650b1.
#ifndef HK_SERIALIZE_MIN_COMPATIBLE_VERSION
// If HK_SERIALIZE_MIN_COMPATIBLE_VERSION is not defined, use all versions (300 being the first Havok version).
#	if defined(HK_SERIALIZE_LATEST_VERSION_ONLY)
#		define HK_SERIALIZE_MIN_COMPATIBLE_VERSION_INTERNAL_VALUE (HK_HAVOK_VERSION_Current - 1)
#	else
#		define HK_SERIALIZE_MIN_COMPATIBLE_VERSION_INTERNAL_VALUE HK_HAVOK_VERSION_300
#	endif
#else
#define HK_SERIALIZE_MIN_COMPATIBLE_VERSION_INTERNAL_VALUE HK_HAVOK_VERSION(HK_SERIALIZE_MIN_COMPATIBLE_VERSION)
#endif

// Register libraries with the memory tracker, if it is enabled.
// This uses HK_FEATURE_PRODUCT_* and HK_EXCLUDE_LIBRARY_* to decide
// which tracker reflection items are registered.
#if defined(HK_MEMORY_TRACKER_ENABLE) && !defined(HK_EXCLUDE_FEATURE_MemoryTracker)
#include <Common/Base/Memory/Tracker/Registration/hkRegisterTrackedClasses.cxx>
#endif

#if !defined(HK_EXCLUDE_FEATURE_RegisterVersionPatches)
static void registerVersionPatches()
{
	hkVersionPatchManager& man = hkVersionPatchManager::getInstance();
	#include <Common/Compat/Patches/hkRegisterPatches.cxx>
}
#endif

void HK_CALL hkProductFeatures::initialize()
{
//
// Common
//
#if 1
	#if !defined(HK_EXCLUDE_FEATURE_SerializeDeprecatedPre700)
		HK_OPTIONAL_COMPONENT_REQUEST(hkSerializeDeprecated);
	#endif

	#if defined(HK_MEMORY_TRACKER_ENABLE) && !defined(HK_EXCLUDE_FEATURE_MemoryTracker)
		hkRegisterMemoryTracker();
	#endif

	#if !defined(HK_EXCLUDE_FEATURE_RegisterVersionPatches)
		if ( hkVersionPatchManager::getInstance().getNumPatches() > 0 )
		{
			hkVersionPatchManager::getInstance().clearPatches();
		}

		registerVersionPatches();

		hkVersionPatchManager::getInstance().recomputePatchDependencies();
	#endif
#endif

//
// Physics
//
#ifdef HK_FEATURE_PRODUCT_PHYSICS_2012
	#if !defined(HK_EXCLUDE_FEATURE_hkpHeightField)
		HK_OPTIONAL_COMPONENT_REQUEST(hkpHeightFieldAgent);
	#endif

	#if !defined(HK_EXCLUDE_FEATURE_hkpSimulation)
		HK_OPTIONAL_COMPONENT_REQUEST(hkpSimulation);
	#endif

	#if !defined(HK_EXCLUDE_FEATURE_hkpContinuousSimulation)
		HK_OPTIONAL_COMPONENT_REQUEST(hkpContinuousSimulation);
	#endif

	#if (HK_CONFIG_THREAD != HK_CONFIG_SINGLE_THREADED)
		#if !defined(HK_EXCLUDE_FEATURE_hkpMultiThreadedSimulation)
			HK_OPTIONAL_COMPONENT_REQUEST(hkpMultiThreadedSimulation);
		#endif
	#endif

	#if !defined(HK_EXCLUDE_FEATURE_hkpAccurateInertiaTensorComputer)
		HK_OPTIONAL_COMPONENT_REQUEST(hkpAccurateInertiaTensorComputer);
	#endif

	#if !defined(HK_EXCLUDE_FEATURE_hkp3AxisSweep)
		HK_OPTIONAL_COMPONENT_REQUEST(hkp3AxisSweep);
	#endif

	#if !defined(HK_EXCLUDE_FEATURE_hkpTreeBroadPhase)
		HK_OPTIONAL_COMPONENT_REQUEST(hkpTreeBroadPhase);
	#endif

	#if !defined(HK_EXCLUDE_FEATURE_hkpTreeBroadPhase32)
		HK_OPTIONAL_COMPONENT_REQUEST(hkpTreeBroadPhase32);
	#endif

	#if defined(HK_EXCLUDE_FEATURE_hkpSampledHeightFieldDdaRayCast) && defined (HK_EXCLUDE_FEATURE_hkpSampledHeightFieldCoarseTreeRayCast)
		// Do nothing, the function pointers are set to null.	
	#elif defined(HK_EXCLUDE_FEATURE_hkpSampledHeightFieldDdaRayCast)
		HK_OPTIONAL_COMPONENT_REQUEST(hkpSampledHeightFieldShape_CoarseCast);
	#elif defined(HK_EXCLUDE_FEATURE_hkpSampledHeightFieldCoarseTreeRayCast)
		HK_OPTIONAL_COMPONENT_REQUEST(hkpSampledHeightFieldShape_DdaCast);	
	#else
		HK_OPTIONAL_COMPONENT_REQUEST(hkpSampledHeightField_AllCasts);
	#endif
#endif // HK_FEATURE_PRODUCT_PHYSICS_2012

//
// Destruction2012
//
#if defined(HK_FEATURE_PRODUCT_DESTRUCTION_2012) && !defined(HK_EXCLUDE_FEATURE_DestructionRuntime)
	extern void HK_CALL registerDestructionRuntime();
	registerDestructionRuntime();
#endif

//
// Destruction
//

#if defined(HK_FEATURE_PRODUCT_DESTRUCTION)
#	if defined(HK_EXCLUDE_FEATURE_hkndAssetProcessing)
#		define HK_EXCLUDE_FEATURE_hkndConvexDecompositionAction_execute
#		define HK_EXCLUDE_FEATURE_hkndConvexHullAction_execute
#		define HK_EXCLUDE_FEATURE_hkndDecalMapAction_execute
#		define HK_EXCLUDE_FEATURE_hkndDecorateFractureFaceAction_execute
#		define HK_EXCLUDE_FEATURE_hkndDecorateFractureFaceAction_syncDecorationData
#		define HK_EXCLUDE_FEATURE_hkndExplosionForceAction_execute
#		define HK_EXCLUDE_FEATURE_hkndFlattenHierarchyAction_execute
#		define HK_EXCLUDE_FEATURE_hkndGlueFixedPiecesAction_execute
#		define HK_EXCLUDE_FEATURE_hkndIntegrityAnalyzerAction_execute
#		define HK_EXCLUDE_FEATURE_hkndMeshSimplifierAction_execute
#		define HK_EXCLUDE_FEATURE_hkndPrepareForDynamicFractureAction_execute
#		define HK_EXCLUDE_FEATURE_hkndRemoveDebrisAction_execute
#		define HK_EXCLUDE_FEATURE_hkndRemoveWeakConnectionsAction_execute
#		define HK_EXCLUDE_FEATURE_hkndSetRigidBodyPropertiesAction_execute
#		define HK_EXCLUDE_FEATURE_hkndShareVerticesAction_execute
#		define HK_EXCLUDE_FEATURE_hkndShockWaveAction_execute
#		define HK_EXCLUDE_FEATURE_hkndSplitByPhysicsIslandsAction_execute
#		define HK_EXCLUDE_FEATURE_hkndDebrisFractureInfo_execute
#		define HK_EXCLUDE_FEATURE_hkndDecorateCornerInfo_execute
#		define HK_EXCLUDE_FEATURE_hkndDecorateFractureFaceInfo_execute
#		define HK_EXCLUDE_FEATURE_hkndMeshOptimizerInfo_execute
#		define HK_EXCLUDE_FEATURE_hkndBuildingProcessor_execute
#		define HK_EXCLUDE_FEATURE_hkndDeformationProcessor_execute
#		define HK_EXCLUDE_FEATURE_hkndFlexibleJointProcessor_execute
#		define HK_EXCLUDE_FEATURE_hkndWoodProcessor_execute
#		define HK_EXCLUDE_FEATURE_hkndCutOutFracture_execute
#		define HK_EXCLUDE_FEATURE_hkndDecomposeFracture_execute
#		define HK_EXCLUDE_FEATURE_hkndImageBasedFracture_execute
#		define HK_EXCLUDE_FEATURE_hkndPieFracture_execute
#		define HK_EXCLUDE_FEATURE_hkndRandomSplitFracture_execute
#		define HK_EXCLUDE_FEATURE_hkndSliceFracture_execute
#		define HK_EXCLUDE_FEATURE_hkndSplitInHalfFracture_execute
#		define HK_EXCLUDE_FEATURE_hkndVoronoiFracture_execute
#		define HK_EXCLUDE_FEATURE_hkndVoronoiFracture_getCutouts
#		define HK_EXCLUDE_FEATURE_hkndWoodFracture_execute
#	endif

	// Actions
#	if !defined(HK_EXCLUDE_FEATURE_hkndConvexDecompositionAction_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndConvexDecompositionAction_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndConvexHullAction_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndConvexHullAction_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndDecalMapAction_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndDecalMapAction_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndDecorateFractureFaceAction_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndDecorateFractureFaceAction_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndDecorateFractureFaceAction_syncDecorationData)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndDecorateFractureFaceAction_syncDecorationData);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndExplosionForceAction_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndExplosionForceAction_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndFlattenHierarchyAction_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndFlattenHierarchyAction_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndGlueFixedPiecesAction_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndGlueFixedPiecesAction_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndIntegrityAnalyzerAction_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndIntegrityAnalyzerAction_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndMeshSimplifierAction_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndMeshSimplifierAction_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndPrepareForDynamicFractureAction_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndPrepareForDynamicFractureAction_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndRemoveDebrisAction_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndRemoveDebrisAction_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndRemoveWeakConnectionsAction_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndRemoveWeakConnectionsAction_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndSetRigidBodyPropertiesAction_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndSetRigidBodyPropertiesAction_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndShareVerticesAction_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndShareVerticesAction_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndShockWaveAction_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndShockWaveAction_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndSplitByPhysicsIslandsAction_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndSplitByPhysicsIslandsAction_execute);
#	endif

	// Infos
#	if !defined(HK_EXCLUDE_FEATURE_hkndDebrisFractureInfo_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndDebrisFractureInfo_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndDecorateCornerInfo_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndDecorateCornerInfo_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndDecorateFractureFaceInfo_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndDecorateFractureFaceInfo_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndMeshOptimizerInfo_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndMeshOptimizerInfo_execute);
#	endif

	// Controllers
#	if !defined(HK_EXCLUDE_FEATURE_hkndBuildingProcessor_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndBuildingProcessor_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndFlexibleJointProcessor_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndFlexibleJointProcessor_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndDeformationProcessor_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndDeformationProcessor_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndWoodProcessor_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndWoodProcessor_execute);
#	endif

	// Fractures
#	if !defined(HK_EXCLUDE_FEATURE_hkndCutOutFracture_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndCutOutFracture_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndDebrisFracture_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndDebrisFracture_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndDecomposeFracture_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndDecomposeFracture_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndFxDebrisFracture_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndFxDebrisFracture_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndImageBasedFracture_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndImageBasedFracture_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndPieFracture_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndPieFracture_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndRandomSplitFracture_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndRandomSplitFracture_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndSliceFracture_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndSliceFracture_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndSplitInHalfFracture_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndSplitInHalfFracture_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndVoronoiFracture_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndVoronoiFracture_execute);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndVoronoiFracture_getCutouts)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndVoronoiFracture_getCutouts);
#	endif
#	if !defined(HK_EXCLUDE_FEATURE_hkndWoodFracture_execute)
		HK_OPTIONAL_COMPONENT_REQUEST(hkndWoodFracture_execute);
#	endif
#endif
}

// Generate class registration. Use default classes file if no custom class file is provided
#if !defined(HK_EXCLUDE_FEATURE_RegisterReflectedClasses)
	#if !defined(HK_CLASSES_FILE)
		#define HK_CLASSES_FILE <Common/Serialize/Classlist/hkKeyCodeClasses.h>
	#endif
	#include <Common/Serialize/Util/hkBuiltinTypeRegistry.cxx>
#endif

// Set up the deprecated serialization and versioning system.
// You can replace HK_COMPAT_FILE with your own file that contains
// only the versioning steps you need.
#if !defined(HK_EXCLUDE_FEATURE_SerializeDeprecatedPre700)
	#ifndef HK_COMPAT_FILE
		#define HK_COMPAT_FILE <Common/Compat/Deprecated/Compat/hkCompatVersions.h>
	#endif
	#include <Common/Compat/Deprecated/Compat/hkCompat_All.cxx>
#else
	// Codewarrior cannot deadstrip this correctly, so declare empty updaters list and class list
	#if defined( HK_COMPILER_MWERKS ) && !defined(HK_EXCLUDE_LIBRARY_hkCompat)
		#include <Common/Compat/Deprecated/Compat/hkCompat_None.cxx>
	#endif
#endif

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
