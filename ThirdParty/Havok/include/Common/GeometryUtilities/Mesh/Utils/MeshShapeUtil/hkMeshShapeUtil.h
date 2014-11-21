/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MESH_SHAPE_UTIL_H
#define HK_MESH_SHAPE_UTIL_H

#include <Common/GeometryUtilities/Mesh/hkMeshShape.h>
#include <Common/GeometryUtilities/Mesh/IndexedTransformSet/hkIndexedTransformSet.h>

class hkMeshSystem;
class hkMeshMaterialRegistry;
class hkAabb;

	/// A simple utility for processing hkMeshShapes
namespace hkMeshShapeUtil
{
    struct HK_EXPORT_COMMON Statistics
    {
        HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_SCENE_DATA, hkMeshShapeUtil::Statistics );

        void clear()
        {
            m_totalNumVertices = 0;
            m_totalNumPrimitives = 0;
            m_numUniqueVertexBuffers = 0;
            m_numUniqueMaterials = 0;
        }

        int m_totalNumVertices;
        int m_totalNumPrimitives;
        int m_numUniqueVertexBuffers;
        int m_numUniqueMaterials;
    };

	struct HK_EXPORT_COMMON SectionInfo
	{
		int m_origSectionIdx;
		bool m_isTransparent;

		static hkBool32 HK_CALL less(const SectionInfo& pA, const SectionInfo& pB)
		{
			return (!pA.m_isTransparent && pB.m_isTransparent) || ((pA.m_isTransparent == pB.m_isTransparent) && (pA.m_origSectionIdx < pB.m_origSectionIdx));
		}
	};

        /// Calculate statistics for a single shape
    HK_EXPORT_COMMON void HK_CALL calculateStatistics(const hkMeshShape* shape, Statistics& statsOut);

        /// Calculate statistics across multiple shapes
    HK_EXPORT_COMMON void HK_CALL calculateStatistics(const hkMeshShape** shape, int numShapes, Statistics& statsOut);

        /// Goes through all of the vertex buffers referenced in the shape, and finds their
        /// unique positions.
    HK_EXPORT_COMMON void HK_CALL findUniqueVertexPositions(hkMeshShape* shape, hkArray<hkVector4>& verticesOut);

        /// Converts a mesh shape constructed in one mesh system to another
    HK_EXPORT_COMMON hkMeshShape* HK_CALL convert(hkMeshMaterialRegistry* srcRegistry, const hkMeshShape* srcShape, hkMeshMaterialRegistry* dstRegistry, hkMeshSystem* dstSystem);

		/// Replace all of the vertex buffers in meshShape with those specified in the buffer map. If not found will just keep the original.
	HK_EXPORT_COMMON hkMeshShape* HK_CALL replaceShapeVertexBuffers(hkMeshSystem* meshSystem, const hkMeshShape* meshShape, hkPointerMap<hkMeshVertexBuffer*, hkMeshVertexBuffer*>& bufferMap);

        /// Transforms the meshShape by the input transform (normalizes normals if normalize is set)
    HK_EXPORT_COMMON hkResult HK_CALL transform(hkMeshShape* meshShape, const hkMatrix4& transformIn, hkBool normalize);

		/// Calc the aabb surrounding a shape
	HK_EXPORT_COMMON void HK_CALL calcAabb(const hkMeshShape* shape, hkAabb& aabbOut);

		/// Reorder the mesh sections to make
	HK_EXPORT_COMMON hkMeshShape* HK_CALL reorderMeshSections(const hkMeshShape* shape, hkMeshSystem* meshSystem, hkArray<SectionInfo>& newSectionOrder);
		
		/// Patches a mesh materials with a given material registery
	HK_EXPORT_COMMON void HK_CALL patchMeshMaterials(hkMeshShape* meshToPatch, hkMeshMaterialRegistry* matRegistry);

		/// Clones the given mesh shape
	HK_EXPORT_COMMON hkMeshShape* HK_CALL cloneMesh(hkMeshSystem* meshSystem, const hkMeshShape* srcShape);

		/// Returns a new mesh shape with at most maxBones in each mesh section. If the mesh has less than the maximum number of bones per section,
		/// the function returns the unchanged original mesh. The function also returns the array of bone mappings, one for each mesh section.
	HK_EXPORT_COMMON const hkMeshShape* HK_CALL createMeshWithLimitedNumBones(hkMeshSystem* meshSystem, const hkMeshShape* srcShape, int maxBonesPerSection, int numTotalMeshBones);

		/// Applies the given transform on the given uv set
	HK_EXPORT_COMMON void HK_CALL transformUvSet(hkMeshShape* meshShape, int uvSet, const hkMatrix4& uvTm);

		/// Converts the given bone indices from section to mesh
	HK_EXPORT_COMMON void HK_CALL mapSectionBoneIndices(const hkMeshSection& section, hkArray<int>& boneIndices);
};

#endif // HK_MESH_SHAPE_UTIL_H

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
