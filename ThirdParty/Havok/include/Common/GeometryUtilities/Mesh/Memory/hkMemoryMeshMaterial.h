/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MEMORY_MESH_MATERIAL_H
#define HK_MEMORY_MESH_MATERIAL_H

#include <Common/GeometryUtilities/Mesh/hkMeshShape.h>
#include <Common/GeometryUtilities/Mesh/hkMeshTexture.h>

class hkMemoryMeshTexture;

extern HK_EXPORT_COMMON const hkClass hkMemoryMeshMaterialClass;


/// A memory based implementation of an hkMeshMaterial
class HK_EXPORT_COMMON hkMemoryMeshMaterial : public hkMeshMaterial
{
	//+version(2)
	public:
        HK_DECLARE_REFLECTION();

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA);
			/// Ctor
        hkMemoryMeshMaterial(const char* name = HK_NULL);
			/// Serialization Ctor
		hkMemoryMeshMaterial( hkFinishLoadedObjectFlag flag );

		/// Destructor
		virtual ~hkMemoryMeshMaterial();

			// Assignment operator
		hkMemoryMeshMaterial& operator=(const hkMemoryMeshMaterial& other);

			// hkReferencedObject implementation
		virtual const hkClass* getClassType() const { return &hkMemoryMeshMaterialClass; }

            // hkMeshMaterial implementation
        virtual hkResult createCompatibleVertexFormat(const hkVertexFormat& format, hkVertexFormat& compatibleFormat);
            // hkMeshMaterial implementation
        virtual hkMeshVertexBuffer* createCompatibleVertexBuffer(hkMeshVertexBuffer* buffer);
            // hkMeshMaterial implementation
        virtual bool isCompatible(const hkMeshVertexBuffer* buffer);

			/// Tests whether two materials are equal
		virtual bool equals(const hkMeshMaterial* other);

			// hkMeshMaterial implementation
		virtual void setName(const char* name);
			// hkMeshMaterial implementation
		virtual const char* getName() const;
			
			// hkMeshMaterial implementation
		virtual int getNumTextures() const;
			// hkMeshMaterial implementation
		virtual hkMeshTexture* getTexture(int index) const;
			// hkMeshMaterial implementation
		virtual void addTexture(hkMeshTexture* texture);

			// Sets a texture of the given slot
		virtual void setTexture(int index, hkMeshTexture* texture) HK_OVERRIDE;
	
			// hkMeshMaterial implementation
		virtual void getColors( hkVector4& diffuse, hkVector4& ambient, hkVector4& specular, hkVector4& emissive ) const;
			// hkMeshMaterial implementation
		virtual void setColors( const hkVector4& diffuse, const hkVector4& ambient, const hkVector4& specular, const hkVector4& emissive );

		/// Gets user data
		virtual hkUlong getUserData() const HK_OVERRIDE			{	return m_userData;		}

		/// Sets user data
		virtual void setUserData(hkUlong userData) HK_OVERRIDE	{	m_userData = userData;	}

		/// Gets / sets the tesselation factor. Triangles will not be tesselated if the factor is 0.0f, and fully tesselated if the factor is 1.0f
		virtual hkReal getTesselationFactor() const	HK_OVERRIDE		{	return m_tesselationFactor;	}
		virtual void setTesselationFactor(hkReal f) HK_OVERRIDE		{	m_tesselationFactor = f;	}

		/// Gets / sets the displacement amount. This represents the actual distance a vertex gets displaced for a displacement factor of 1.0f
		virtual hkReal getDisplacementAmount() const HK_OVERRIDE	{	return m_displacementAmount;	}
		virtual void setDisplacementAmount(hkReal f) HK_OVERRIDE	{	m_displacementAmount = f;		}

	protected:

		/// Reserves a texture slot for the given texture
		int reserveTextureSlot(hkMeshTexture* newTex);
		
	public:

        hkStringPtr m_materialName;
		hkArray< hkRefPtr<hkMeshTexture> > m_textures;
		hkVector4 m_diffuseColor;
		hkVector4 m_ambientColor;
		hkVector4 m_specularColor;
		hkVector4 m_emissiveColor;
		hkUlong m_userData;
		hkReal m_tesselationFactor;
		hkReal m_displacementAmount;
};


#endif // HK_MEMORY_MESH_MATERIAL_H

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
