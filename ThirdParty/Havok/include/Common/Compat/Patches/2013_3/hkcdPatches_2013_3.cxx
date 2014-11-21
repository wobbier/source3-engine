/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Collide specific product patches applied to release 2013_3.
// This file is #included by hkcdPatches_2013_3.cpp

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdPlanarEntity", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdPlanarGeometryPrimitivesPlane", 0)
	HK_PATCH_MEMBER_ADDED("iEqn", TYPE_TUPLE_INT, HK_NULL, 4)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdPlanarSolid", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdPlanarEntity")
	HK_PATCH_MEMBER_ADDED("nodes", TYPE_OBJECT, "hkcdPlanarSolidNodeStorage", 0)
	HK_PATCH_MEMBER_ADDED("planes", TYPE_OBJECT, "hkcdPlanarGeometryPlanesCollection", 0)
	HK_PATCH_MEMBER_ADDED("rootNodeId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkcdPlanarEntity", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkcdPlanarGeometryPlanesCollection", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkcdPlanarSolidNodeStorage", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdPlanarGeometryPlanesCollection", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("offsetAndScale", TYPE_VEC_4, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("planes", TYPE_ARRAY_STRUCT, "hkcdPlanarGeometryPrimitivesPlane", 0)
	HK_PATCH_DEPENDS("hkcdPlanarGeometryPrimitivesPlane", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdPlanarSolidNodeStorage", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("storage", TYPE_ARRAY_STRUCT, "hkcdPlanarSolidNode", 0)
	HK_PATCH_MEMBER_ADDED("firstFreeNodeId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkcdPlanarSolidNode", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdPlanarGeometry", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdPlanarEntity")
	HK_PATCH_MEMBER_ADDED("planes", TYPE_OBJECT, "hkcdPlanarGeometryPlanesCollection", 0)
	HK_PATCH_MEMBER_ADDED("polys", TYPE_OBJECT, "hkcdPlanarGeometryPolygonCollection", 0)
	HK_PATCH_DEPENDS("hkcdPlanarGeometryPrimitivesCollection28", 0)
	HK_PATCH_DEPENDS("hkcdPlanarEntity", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkcdPlanarGeometryPlanesCollection", 0)
	HK_PATCH_DEPENDS("hkcdPlanarGeometryPolygonCollection", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdPlanarGeometryPrimitivesCollection28", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("storage", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("primaryBitmap", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("secondaryBitmaps", TYPE_TUPLE_INT, HK_NULL, 26)
	HK_PATCH_MEMBER_ADDED("freeBlocks", TYPE_TUPLE_INT, HK_NULL, 832)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdPlanarSolidNode", 0)
	HK_PATCH_MEMBER_ADDED("parent", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("left", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("right", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("nextFreeNodeId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("planeId", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("data", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("typeAndFlags", TYPE_INT, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdPlanarGeometryPolygonCollection", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkcdPlanarGeometryPrimitivesCollection28")
	HK_PATCH_DEPENDS("hkcdPlanarGeometryPrimitivesCollection28", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdPlanarCsgOperand", 0)
	HK_PATCH_PARENT_SET(HK_NULL, "hkReferencedObject")
	HK_PATCH_MEMBER_ADDED("geometry", TYPE_OBJECT, "hkcdPlanarGeometry", 0)
	HK_PATCH_MEMBER_ADDED("danglingGeometry", TYPE_OBJECT, "hkcdPlanarGeometry", 0)
	HK_PATCH_MEMBER_ADDED("solid", TYPE_OBJECT, "hkcdPlanarSolid", 0)
	HK_PATCH_MEMBER_ADDED("geomSources", TYPE_ARRAY_STRUCT, "hkcdPlanarCsgOperandGeomSource", 0)
	HK_PATCH_DEPENDS("hkcdPlanarGeometry", 0)
	HK_PATCH_DEPENDS("hkcdPlanarEntity", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkcdPlanarCsgOperandGeomSource", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
	HK_PATCH_DEPENDS("hkcdPlanarSolid", 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkcdPlanarCsgOperandGeomSource", 0)
	HK_PATCH_MEMBER_ADDED("geometry", TYPE_OBJECT, "hkcdPlanarGeometry", 0)
	HK_PATCH_MEMBER_ADDED("materialOffset", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numMaterialIds", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("flipPolygons", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkcdPlanarGeometry", 0)
	HK_PATCH_DEPENDS("hkcdPlanarEntity", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkcdSimdTree", 0, "hkcdSimdTree", 1)
        HK_PATCH_PARENT_SET(HK_NULL, "hkBaseObject")
        HK_PATCH_MEMBER_REMOVED("domain", TYPE_STRUCT, "hkAabb", 0)
        HK_PATCH_MEMBER_REMOVED("root", TYPE_INT, HK_NULL, 0)
        HK_PATCH_DEPENDS("hkAabb", 0)        
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
