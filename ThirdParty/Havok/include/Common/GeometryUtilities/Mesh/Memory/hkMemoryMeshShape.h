/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MEMORY_MESH_SHAPE_H
#define HK_MEMORY_MESH_SHAPE_H

#include <Common/GeometryUtilities/Mesh/hkMeshShape.h>
#include <Common/GeometryUtilities/Mesh/hkMeshVertexBuffer.h>

extern HK_EXPORT_COMMON const hkClass hkMemoryMeshShapeClass;

	/// A memory based implementation of a hkMeshShape
class HK_EXPORT_COMMON hkMemoryMeshShape : public hkMeshShape
{
	//+version(1)

    public:
		
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA);
		HK_DECLARE_REFLECTION();

	public:

		struct Section
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA, hkMemoryMeshShape::Section);
			HK_DECLARE_REFLECTION();

			/// Constructor
			HK_FORCE_INLINE Section()
			:	m_vertexBuffer(HK_NULL)
			,	m_material(HK_NULL)
			,	m_numPrimitives(0)
			,	m_indexBufferOffset(0)
			{}

			/// Serialization constructor
			Section(hkFinishLoadedObjectFlag f)
			:	m_vertexBuffer(f)
			,	m_material(f)
			,	m_boneMatrixMap(f)
			{}

			/// Vertex buffer that will be used
			hkRefPtr<hkMeshVertexBuffer> m_vertexBuffer;

			/// Material used on this mesh section
			hkRefPtr<hkMeshMaterial> m_material;

			hkMeshBoneIndexMapping m_boneMatrixMap;			///< Map from vertex buffer bone indices to 'global' bone indices

			/// The primitive types
			hkEnum<hkMeshSection::PrimitiveType, hkUint8> m_primitiveType;
			/// Total number of primitives of type m_primitiveType
			int m_numPrimitives;
			/// The index type used (if NONE, then m_indices must be equal to NULL)
			hkEnum<hkMeshSection::MeshSectionIndexType,hkUint8>	m_indexType;

			/// This offset is used if indices aren't specified (ignored if indices are set)
			int m_vertexStartIndex;
			/// Index into transform set used to position this section. -1 if per section transform isn't used.
			int m_transformIndex;

			/// Index buffer offset
			int m_indexBufferOffset;
		};

	public:

		/// Constructor
        hkMemoryMeshShape(const hkMeshSectionCinfo* sections, int numSections);

		/// Serialization Constructor
		hkMemoryMeshShape( hkFinishLoadedObjectFlag flag );

		/// Destructor
        virtual ~hkMemoryMeshShape();

	public:

            // hkMeshShape implementation
        virtual int getNumSections() const HK_OVERRIDE;

            // hkMeshShape implementation
        virtual void lockSection(int sectionIndex, hkUint8 accessFlags, hkMeshSection& sectionOut) const HK_OVERRIDE;

            // hkMeshShape implementation
        virtual void unlockSection(const hkMeshSection& section) const HK_OVERRIDE;

            // hkReferencedObject Implementation
        virtual const hkClass* getClassType() const HK_OVERRIDE { return &hkMemoryMeshShapeClass; }

		virtual const char* getName() const HK_OVERRIDE { return m_name; }
		virtual void setName(const char* n) HK_OVERRIDE { m_name = n; }

    protected:

        mutable hkArray<Section> m_sections;

        hkArray<hkUint16> m_indices16;
        hkArray<hkUint32> m_indices32;

		hkStringPtr m_name;
};



#endif // HK_MEMORY_MESH_SHAPE_H

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
