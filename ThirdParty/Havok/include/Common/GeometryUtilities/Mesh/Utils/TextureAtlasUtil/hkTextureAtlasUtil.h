/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_TEXTURE_ATLAS_UTIL_H
#define HK_TEXTURE_ATLAS_UTIL_H

/// Arranges a set of textures in an atlas
class hkTextureAtlasUtil
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA, hkTextureAtlasUtil);

	public:

		/// Texture
		struct Texture
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA, hkTextureAtlasUtil::Texture);

			/// Sets the texture sizes
			HK_FORCE_INLINE void set(int w, int h)
			{
				m_width = w;
				m_height = h;
			}

			int m_width;	///< Texture width in pixels
			int m_height;	///< Texture height in pixels
		};

		/// Texture placement
		struct Placement
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA, hkTextureAtlasUtil::Placement);

			int m_textureId;	///< Index of the texture in the input textures array
			int m_x, m_y;		///< The (x, y) top left pixel in the atlas where the texture should be placed.
			hkUint8 m_rotation;	///< The texture rotation angle. Can only be 0 or 90 degrees CCW.	
			hkUint16 m_atlasId;	///< The atlas where the texture was placed
		};

	public:

		/// Estimates the size of the atlas map that could fit the given textures
		static void HK_CALL estimateAtlasSize(const Texture* texturesIn, int numTextures, int& atlasWidthOut, int& atlasHeightOut);

		/// Arranges the given textures in an atlas
		static hkResult HK_CALL arrangeTextures(
			const Texture* texturesIn, int numTextures,
			Placement* placementsOut,
			int& atlasWidthOut, int& atlasHeightOut,
			int maxAtlasWidth = 2048, int maxAtlasHeight = 2048);

	public:

		/// Debug self-test.
		static hkResult HK_CALL selfTest();
};

#endif	// HK_TEXTURE_ATLAS_UTIL_H

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
