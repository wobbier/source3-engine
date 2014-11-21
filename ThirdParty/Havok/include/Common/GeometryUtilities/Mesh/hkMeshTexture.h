/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_MESH_TEXTURE_H
#define HK_MESH_TEXTURE_H

#include <Common/ImageUtilities/Image/hkImage.h>

extern HK_EXPORT_COMMON const class hkClass hkMeshTextureClass;

/// A texture used by a hkMeshMaterial
/// Currently the Havok base framework doesn't provide any interface nor implementation for image loading
/// Texture are represented by this stateless abstract class
/// In the future, when the loading capabilities will be available through hkBase, this class should contains the data pointer and descriptor of the texture

class HK_EXPORT_COMMON hkMeshTexture : public hkReferencedObject
{
	public:
		
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();

	public:

		/// Texture sampler
		class HK_EXPORT_COMMON Sampler : public hkReferencedObject
		{
			public:

				HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);

				/// Samples the texture at the given texel
				virtual void sample(hkVector4Parameter uvIn, hkVector4& texelOut) const = 0;

				/// Returns an image at the specified mip level
				virtual hkImage* getImage(int mipLevel) const = 0;

			protected:

				/// Constructor
				Sampler();

		};

		/// Header for RAW buffer formats. A RAW buffer must start with this descriptor
		struct HK_EXPORT_COMMON RawBufferDescriptor
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkMeshTexture::RawBufferDescriptor);
			HK_DECLARE_REFLECTION();
			HK_DECLARE_POD_TYPE();

			/// Constructor
			HK_FORCE_INLINE RawBufferDescriptor()
			{}

			/// Serialization constructor
			HK_FORCE_INLINE RawBufferDescriptor(hkFinishLoadedObjectFlag flag)
			{}

			hkInt64 m_offset;		///< Offset from the start of the buffer where the payload is stored
			hkUint32 m_stride;		///< The stride between components in the buffer
			hkUint32 m_numElements;	///< The number of elements in the buffer
		};

	public:

			/// Default Ctor
		hkMeshTexture() {}
			/// Serialization Ctor
		hkMeshTexture( hkFinishLoadedObjectFlag flag ): hkReferencedObject(flag) {}

			/// Format of the texture data
		enum Format
		{
			Unknown,
			PNG,
			TGA,
			BMP,
			DDS,
			RAW,
		};	

			/// Filtering mode used by the texture
		enum FilterMode
		{
			POINT,
			LINEAR,
			ANISOTROPIC
		};

		// Has to match 1:1 with HKG_TEXTURE_TYPE_*
		enum TextureUsageType
		{
			UNKNOWN,			
			DIFFUSE,
			REFLECTION,			
			BUMP,		
			NORMAL,			
			DISPLACEMENT,			
			SPECULAR,			// Specular Level map			
			SPECULARANDGLOSS,	// Specular Level map with the Gloss (power) in the Alpha channel			
			OPACITY,			// Opacity (transparency) map. Normally not used, just use the alpha channel in one of the diffuse maps instead.			
			EMISSIVE,			// Emissive (self illumination) map			
			REFRACTION,			
			GLOSS,				// Specular Power map, normally not used (alpha in specmap quicker)	
			DOMINANTS,			// Dominant data for displacement mapping
			NOTEXPORTED
		};

			/// Gets the raw data texture
		virtual void getData(hkUint8*& data, int& size, Format& format) = 0;
			/// Sets the raw data of the texture
		virtual void setData(hkUint8* data, int size, Format format) = 0;

			/// Creates a sampler for this texture
		virtual Sampler* createSampler() const = 0;

			/// Gets the raw data format
		virtual Format getFormat() const = 0;
			
			/// Gets the filename of the texture
		virtual const char* getFilename() const = 0;
			/// Sets the filename of the texture
		virtual void setFilename( const char* filename ) = 0;

			/// Gets if the texture has mip maps
		virtual bool getHasMipMaps() const = 0;
			/// Sets if the texture has mip maps
		virtual void setHasMipMaps(bool hasMipMaps) = 0;
		
			/// Gets the filtering mode of the texture
		virtual FilterMode getFilterMode() const = 0;
			/// Sets the filtering mode of the texture
		virtual void setFilterMode(FilterMode filterMode) = 0;

			/// Gets a usage hint flag for the texture.
		virtual TextureUsageType getUsageHint() const = 0;
			/// Sets a usage hint flag for the texture.
		virtual void setUsageHint( TextureUsageType hint ) = 0;

			/// Gets the index of the texture coordinate this texture should use in the vertex buffer.
		virtual hkInt32 getTextureCoordChannel() const = 0;
			/// Sets the index of the texture coordinate this texture.
		virtual void setTextureCoordChannel( hkInt32 channelIndex ) = 0;

			/// Returns whether or not the texture can be modified.
		virtual bool isReadOnly() const = 0;

			/// Tests whether two textures are equal
		virtual bool equals(const hkMeshTexture* other) const = 0;
};

#endif	//HK_MESH_TEXTURE_H

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
