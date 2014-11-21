/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Physics specific product patches applied to release 2013_1.
// This file is #included by hkpPatches_2013_1.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpVehicleSimulation", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpVehicleDefaultSimulation", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpVehicleSimulation")
	HK_PATCH_MEMBER_ADDED("frictionStatus", TYPE_STRUCT, "hkpVehicleFrictionStatus", 0)
	HK_PATCH_MEMBER_ADDED("frictionDescription", TYPE_OBJECT, "hkpVehicleFrictionDescription", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpVehicleFrictionDescription", 0)
	HK_PATCH_DEPENDS("hkpVehicleSimulation", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkpVehicleFrictionStatus", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpVehiclePerWheelSimulationWheelData", 0)
	HK_PATCH_MEMBER_ADDED("axle", TYPE_STRUCT, "hkpWheelFrictionConstraintAtomAxle", 0)
	HK_PATCH_MEMBER_ADDED("frictionData", TYPE_STRUCT, "hkpWheelFrictionConstraintData", 0)
	HK_PATCH_MEMBER_ADDED("forwardDirectionWs", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("sideDirectionWs", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("contactLocal", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkpConstraintInstance", 1)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpConstraintData", 0)
	HK_PATCH_DEPENDS("hkpWheelFrictionConstraintAtomAxle", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkpWheelFrictionConstraintData", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpVehiclePerWheelSimulation", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpVehicleSimulation")
	HK_PATCH_MEMBER_ADDED("instance", TYPE_OBJECT, "hkpVehicleInstance", 0)
	HK_PATCH_MEMBER_ADDED("slipDamping", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("impulseScaling", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxImpulse", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("takeDynamicVelocity", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("curbDamping", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("wheelData", TYPE_ARRAY_STRUCT, "hkpVehiclePerWheelSimulationWheelData", 0)
	HK_PATCH_DEPENDS("hkpVehiclePerWheelSimulationWheelData", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpVehicleInstance", 2)
	HK_PATCH_DEPENDS("hkpAction", 0)
	HK_PATCH_DEPENDS("hkpVehicleSimulation", 0)
	HK_PATCH_DEPENDS("hkpUnaryAction", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpVehicleSteeringAckerman", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpVehicleSteering")
	HK_PATCH_MEMBER_ADDED("maxSteeringAngle", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxSpeedFullSteeringAngle", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("doesWheelSteer", TYPE_ARRAY_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("trackWidth", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("wheelBaseLength", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkpVehicleSteering", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpVehicleInstance", 1, "hkpVehicleInstance", 2)
	HK_PATCH_MEMBER_REMOVED("frictionStatus", TYPE_STRUCT, "hkpVehicleFrictionStatus", 0)
	HK_PATCH_MEMBER_ADDED_POINTER("vehicleSimulation", "hkpVehicleSimulation", 0)
	HK_PATCH_DEPENDS("hkpVehicleFrictionStatus", 0)
	HK_PATCH_DEPENDS("hkpVehicleSimulation", 0)
	//HK_PATCH_FUNCTION(hkpVehicleInstance_1_to_2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpVehicleData", 1, "hkpVehicleData", 2)
	HK_PATCH_MEMBER_REMOVED("frictionDescription", TYPE_STRUCT, "hkpVehicleFrictionDescription", 0)
	HK_PATCH_DEPENDS("hkpVehicleFrictionDescription", 0)
	//HK_PATCH_FUNCTION(hkpVehicleData_1_to_2)
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
