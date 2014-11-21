/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Physics specific product patches applied to release 2013_2.
// This file is #included by hkpPatches_2013_2.cpp
HK_PATCH_BEGIN("hkpVehicleLinearCastWheelCollide", 0, "hkpVehicleLinearCastWheelCollide", 1)
	HK_PATCH_MEMBER_DEFAULT_SET_INT("wheelCollisionFilterInfo", 0)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("maxExtraPenetration", HK_REAL_EPSILON)
	HK_PATCH_MEMBER_DEFAULT_SET_REAL("startPointTolerance", HK_REAL_EPSILON)
	HK_PATCH_MEMBER_ADDED_BYTE("collectStartPointHits", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpBreakableConstraintData", 0, "hkpBreakableConstraintData", 1)
	HK_PATCH_DEPENDS("hkpWrappedConstraintData", 0)
	HK_PATCH_PARENT_SET("hkpConstraintData", "hkpWrappedConstraintData")
	HK_PATCH_MEMBER_RENAMED("constraintData", "constraintDataOld")
	HK_PATCH_FUNCTION(hkpBreakableConstraintData_0_to_1)
	HK_PATCH_MEMBER_REMOVED("constraintDataOld", TYPE_OBJECT, "hkpConstraintData", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkpMalleableConstraintData", 0, "hkpMalleableConstraintData", 1)
	HK_PATCH_DEPENDS("hkpWrappedConstraintData", 0)
	HK_PATCH_PARENT_SET("hkpConstraintData", "hkpWrappedConstraintData")
	HK_PATCH_MEMBER_RENAMED("constraintData", "constraintDataOld")
	HK_PATCH_FUNCTION(hkpMalleableConstraintData_0_to_1)
	HK_PATCH_MEMBER_REMOVED("constraintDataOld", TYPE_OBJECT, "hkpConstraintData", 0)
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
