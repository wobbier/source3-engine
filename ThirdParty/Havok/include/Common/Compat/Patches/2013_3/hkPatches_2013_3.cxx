/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Common specific product patches applied to release 2013_3.
// This file is #included by hkPatches_2013_3.cpp

HK_PATCH_BEGIN("hkxVertexDescriptionElementDecl", 3, "hkxVertexDescriptionElementDecl", 4)
	HK_PATCH_MEMBER_REMOVED("hint", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("channelID", TYPE_CSTRING, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkxMeshSection", 4, "hkxMeshSection", 5)
	HK_PATCH_MEMBER_ADDED("boneMatrixMap", TYPE_ARRAY_STRUCT, "hkMeshBoneIndexMapping", 0)
	HK_PATCH_DEPENDS("hkMeshBoneIndexMapping", 0)
	//HK_PATCH_FUNCTION(hkxMeshSection_4_to_5)
HK_PATCH_END()

HK_PATCH_BEGIN("hkMeshSectionCinfo", 1, "hkMeshSectionCinfo", 2)
	HK_PATCH_MEMBER_ADDED("boneMatrixMap", TYPE_STRUCT, "hkMeshBoneIndexMapping", 0)
	HK_PATCH_DEPENDS("hkMeshBoneIndexMapping", 0)
	//HK_PATCH_FUNCTION(hkMeshSectionCinfo_1_to_2)
HK_PATCH_END()

HK_PATCH_BEGIN("hkMeshSection", 1, "hkMeshSection", 2)
	HK_PATCH_MEMBER_ADDED("boneMatrixMap", TYPE_OBJECT, "hkMeshBoneIndexMapping", 0)
	HK_PATCH_DEPENDS("hkMeshBoneIndexMapping", 0)
	//HK_PATCH_FUNCTION(hkMeshSection_1_to_2)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkMemoryMeshShapeSection", 0)
	HK_PATCH_MEMBER_ADDED("vertexBuffer", TYPE_OBJECT, "hkMeshVertexBuffer", 0)
	HK_PATCH_MEMBER_ADDED("material", TYPE_OBJECT, "hkMeshMaterial", 0)
	HK_PATCH_MEMBER_ADDED("boneMatrixMap", TYPE_STRUCT, "hkMeshBoneIndexMapping", 0)
	HK_PATCH_MEMBER_ADDED("primitiveType", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("numPrimitives", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("indexType", TYPE_BYTE, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("vertexStartIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("transformIndex", TYPE_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("indexBufferOffset", TYPE_INT, HK_NULL, 0)
	HK_PATCH_DEPENDS("hkMeshBoneIndexMapping", 0)
	HK_PATCH_DEPENDS("hkBaseObject", 0)
	HK_PATCH_DEPENDS("hkMeshVertexBuffer", 0)
	HK_PATCH_DEPENDS("hkMeshMaterial", 0)
	HK_PATCH_DEPENDS("hkReferencedObject", 0)
HK_PATCH_END()

HK_PATCH_BEGIN("hkMemoryMeshShape", 0, "hkMemoryMeshShape", 1)
	HK_PATCH_MEMBER_REMOVED("sections", TYPE_ARRAY_STRUCT, "hkMeshSectionCinfo", 0)
	HK_PATCH_MEMBER_ADDED("sections", TYPE_ARRAY_STRUCT, "hkMemoryMeshShapeSection", 0)
	HK_PATCH_DEPENDS("hkMeshSectionCinfo", 2)
	HK_PATCH_DEPENDS("hkMemoryMeshShapeSection", 0)
	//HK_PATCH_FUNCTION(hkMemoryMeshShape_0_to_1)
HK_PATCH_END()

HK_PATCH_BEGIN("hkUiAttribute", 3, "hkUiAttribute", 4)
	HK_PATCH_MEMBER_RENAMED("hideInModeler", "hideCriteria")
HK_PATCH_END()

HK_PATCH_BEGIN("hkxVertexBufferVertexData", 1, "hkxVertexBufferVertexData", 2)
	HK_PATCH_MEMBER_RENAMED("floatData", "floatDataOld")
	HK_PATCH_MEMBER_RENAMED("vectorData", "vectorDataOld")
	HK_PATCH_MEMBER_ADDED("floatData", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_MEMBER_ADDED("vectorData", TYPE_ARRAY_INT, HK_NULL, 0)
	HK_PATCH_FUNCTION(hkxVertexBufferVertexData_1_to_2)
	HK_PATCH_MEMBER_REMOVED("floatDataOld", TYPE_ARRAY_REAL, HK_NULL, 0)
	HK_PATCH_MEMBER_REMOVED("vectorDataOld", TYPE_ARRAY_REAL, HK_NULL, 0)
HK_PATCH_END()

HK_PATCH_BEGIN(HK_NULL, HK_CLASS_ADDED, "hkQTransform", 2)
	HK_PATCH_PARENT_SET(HK_NULL, "hkQTransformf")
	HK_PATCH_DEPENDS("hkQTransformf", 0)
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
