/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Collide specific product patches applied to release 2013_1.
// This file is #included by hkcdPatches_2013_1.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdFourAabb", 0)
        HK_PATCH_MEMBER_ADDED("lx", TYPE_VEC_4, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("hx", TYPE_VEC_4, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("ly", TYPE_VEC_4, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("hy", TYPE_VEC_4, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("lz", TYPE_VEC_4, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("hz", TYPE_VEC_4, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdAdf", 0)
        HK_PATCH_MEMBER_ADDED("accuracy", TYPE_REAL, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("domain", TYPE_STRUCT, "hkAabb", 0)
        HK_PATCH_MEMBER_ADDED("origin", TYPE_VEC_4, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("scale", TYPE_VEC_4, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("range", TYPE_TUPLE_REAL, HK_NULL, 2)
        HK_PATCH_MEMBER_ADDED("nodes", TYPE_ARRAY_INT, HK_NULL, 0)
        HK_PATCH_MEMBER_ADDED("voxels", TYPE_ARRAY_INT, HK_NULL, 0)
        HK_PATCH_DEPENDS("hkAabb", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdSimdTree", 0)
        HK_PATCH_MEMBER_ADDED("nodes", TYPE_ARRAY_STRUCT, "hkcdSimdTreeNode", 0)
        HK_PATCH_MEMBER_ADDED("domain", TYPE_STRUCT, "hkAabb", 0)
        HK_PATCH_MEMBER_ADDED("root", TYPE_INT, HK_NULL, 0)
        HK_PATCH_DEPENDS("hkcdSimdTreeNode", 0)
        HK_PATCH_DEPENDS("hkAabb", 0)
        HK_PATCH_DEPENDS("hkcdFourAabb", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdSimdTreeNode", 0)
        HK_PATCH_PARENT_SET(HK_NULL, "hkcdFourAabb")
        HK_PATCH_MEMBER_ADDED("data", TYPE_TUPLE_INT, HK_NULL, 4)
        HK_PATCH_DEPENDS("hkcdFourAabb", 0)
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
