/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Physics specific product patches applied to release 2013_1.
// This file is #included by hkpConstraintPatches_2013_1.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpWheelFrictionConstraintAtomAxle", 0)
	HK_PATCH_MEMBER_ADDED("spinVelocity", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("sumVelocity", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numWheels", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("wheelsSolved", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("stepsSolved", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("invInertia", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("inertia", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("impulseScaling", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("impulseMax", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("isFixed", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numWheelsOnGround", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpWheelFrictionConstraintAtom", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpConstraintAtom")
	HK_PATCH_MEMBER_ADDED("isEnabled", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("forwardAxis", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("sideAxis", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("maxFrictionForce", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("torque", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("radius", TYPE_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("frictionImpulse", TYPE_TUPLE_REAL, HK_NULL, 2)
	HK_PATCH_MEMBER_ADDED("slipImpulse", TYPE_TUPLE_REAL, HK_NULL, 2)
	HK_PATCH_MEMBER_ADDED("axle", TYPE_OBJECT, "hkpWheelFrictionConstraintAtomAxle", 0)
	HK_PATCH_DEPENDS("hkpWheelFrictionConstraintAtomAxle", 0)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpWheelFrictionConstraintDataAtoms", 0)
	HK_PATCH_MEMBER_ADDED("transforms", TYPE_STRUCT, "hkpSetLocalTransformsConstraintAtom", 0)
	HK_PATCH_MEMBER_ADDED("friction", TYPE_STRUCT, "hkpWheelFrictionConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpWheelFrictionConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpSetLocalTransformsConstraintAtom", 0)
	HK_PATCH_DEPENDS("hkpConstraintAtom", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpWheelFrictionConstraintData", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkpConstraintData")
	HK_PATCH_MEMBER_ADDED("atoms", TYPE_STRUCT, "hkpWheelFrictionConstraintDataAtoms", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkpConstraintData", 0)
	HK_PATCH_DEPENDS("hkpWheelFrictionConstraintDataAtoms", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkpWheelFrictionConstraintDataRuntime", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpVehicleFrictionDescription", 0, "hkpVehicleFrictionDescription", 1)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	//HK_PATCH_FUNCTION(hkpVehicleFrictionDescription_0_to_1)
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
