/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// NewPhysics specific product patches applied to release 2013_1.
// This file is #included by hknpPatches_2013_1.cpp

HK_PATCH_BEGIN("hknpCompressedMeshShape", 0, "hknpCompressedMeshShape", 1)
	// There was a patch to the hkBitField members here, this is no longer required
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hknpCompressedMeshShapeTreeExt", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdSimdTree")
	HK_PATCH_DEPENDS("hkcdSimdTree", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hknpCompressedMeshShape", 1, "hknpCompressedMeshShape", 2)
	HK_PATCH_MEMBER_ADDED("internalsExt", TYPE_OBJECT, "hknpCompressedMeshShapeTreeExt", 0)
	HK_PATCH_DEPENDS("hknpCompressedMeshShapeTreeExt", 0)
	HK_PATCH_DEPENDS("hkcdSimdTree", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hknpCompressedMeshShape", 2, "hknpCompressedMeshShape", 3)
	HK_PATCH_MEMBER_RENAMED("trianglesWithDuplicatedEdges", "triangleIsInternal")
	HK_PATCH_MEMBER_RENAMED("internals", "data")
	HK_PATCH_MEMBER_RENAMED("internalsExt", "extendedData")
HK_PATCH_END()

HK_PATCH_BEGIN("hknpHeightFieldShape", 0, "hknpHeightFieldShape", 1)
	HK_PATCH_MEMBER_REMOVED("smooth", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hknpScaledConvexShapeBase", 0, "hknpScaledConvexShapeBase", 1)
	HK_PATCH_MEMBER_ADDED("childShapeSize", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hknpWorldCinfo", 0, "hknpWorldCinfo", 1)
	HK_PATCH_MEMBER_REMOVED("maxNumBroadPhasePairs", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("processActionsSingleThreaded", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("solverSpinCount", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED_POINTER("collisionFilter", "hknpCollisionFilter", 0)
	HK_PATCH_MEMBER_ADDED_POINTER("collisionQueryFilter", "hknpCollisionFilter", 0)
	HK_PATCH_MEMBER_ADDED_POINTER("shapeTagCodec", "hknpShapeTagCodec", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hknpCollisionFilter", 0)
	HK_PATCH_DEPENDS("hknpShapeTagCodec", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hknpShapeTagCodec", 0, "hknpShapeTagCodec", 1)
	HK_PATCH_MEMBER_ADDED("type", TYPE_BYTE, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hknpBody", 0, "hknpBody", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("spuFlags", 0)
	HK_PATCH_FUNCTION(hknpBody_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hknpBodyCinfo", 0, "hknpBodyCinfo", 1)
	HK_PATCH_MEMBER_ADDED_BYTE("spuFlags", 0)
	HK_PATCH_MEMBER_ADDED("localFrame", TYPE_OBJECT, "hkLocalFrame", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkLocalFrame", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_FUNCTION(hknpBodyCInfo_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hknpMotion", 1, "hknpMotion", 2)
	HK_PATCH_MEMBER_RENAMED("isValid", "spaceSplitterWeight")
HK_PATCH_END()

HK_PATCH_BEGIN("hknpWorkLoad", 0, HK_NULL, HK_CLASS_REMOVED)
HK_PATCH_END()

HK_PATCH_BEGIN("hknpConvexPolytopeShape", 0, "hknpConvexPolytopeShape", 1)
	HK_PATCH_FUNCTION(hknpConvexPolytopeShape_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hknpVehicleLinearCastWheelCollide", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hknpVehicleWheelCollide")
	HK_PATCH_MEMBER_ADDED("wheelStates", TYPE_ARRAY_STRUCT, "hknpVehicleLinearCastWheelCollideWheelState", 0)
	HK_PATCH_MEMBER_ADDED("maxExtraPenetration", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("startPointTolerance", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("chassisBody", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hknpVehicleLinearCastWheelCollideWheelState", 0)
	HK_PATCH_DEPENDS("hknpVehicleWheelCollide", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hknpVehicleLinearCastWheelCollideWheelState", 0)
	HK_PATCH_MEMBER_ADDED("aabb", TYPE_STRUCT, "hkAabb", 0)
	HK_PATCH_MEMBER_ADDED("shape", TYPE_OBJECT, "hknpShape", 0)
	HK_PATCH_MEMBER_ADDED("transform", TYPE_VEC_16, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("to", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkAabb", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hknpShape", 1)
HK_PATCH_END()

HK_PATCH_BEGIN("hknpMotionProperties", 0, "hknpMotionProperties", 1)
	HK_PATCH_MEMBER_RENAMED("solverStabilizationVelocityThreshold", "solverStabilizationSpeedThreshold")
	HK_PATCH_MEMBER_RENAMED("solverStabilizationVelocityReduction", "solverStabilizationSpeedReduction")
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hknpTriangleShape", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hknpConvexPolytopeShape")
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hknpConvexShape", 0)
	HK_PATCH_DEPENDS("hknpConvexPolytopeShape", 1)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hknpShape", 1)
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
