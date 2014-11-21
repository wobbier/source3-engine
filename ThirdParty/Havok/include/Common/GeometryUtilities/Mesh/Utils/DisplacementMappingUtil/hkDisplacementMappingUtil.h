/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_DISPLACEMENT_MAPPING_UTIL_H
#define HK_DISPLACEMENT_MAPPING_UTIL_H

#include <Common/GeometryUtilities/Mesh/hkMeshTexture.h>

/// Utility class that computes per-vertex dominant displacements to be used in displacement mapping.
class hkDisplacementMappingUtil
{
	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA, hkDisplacementMappingUtil);

		typedef hkMeshTexture::RawBufferDescriptor Descriptor;

	public:

		/// Per-vertex dominant info
		class DominantInfo
		{
			public:

				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA, hkDisplacementMappingUtil::DominantInfo);

			public:

				/// Constructor
				HK_FORCE_INLINE DominantInfo();

				/// Retrieves the normal
				HK_FORCE_INLINE void getNormal(hkVector4& nrmOut) const;

				/// Sets the displacement normal. The normal is assumed normalized and will be encoded to just 2 components, .xy
				HK_FORCE_INLINE void setNormal(hkVector4Parameter n);

				/// Gets / sets the displacement amount, i.e. a factor in [0, 1] used to scale the displacement normal
				HK_FORCE_INLINE const hkSimdReal getDisplacement() const;
				HK_FORCE_INLINE void setDisplacement(hkSimdRealParameter d);

				/// Gets / sets the interpolation factor between the two displacement maps
				HK_FORCE_INLINE const hkSimdReal getBlendFactor() const;
				HK_FORCE_INLINE void setBlendFactor(hkSimdRealParameter f);

				/// Returns the uv for the i-th map
				HK_FORCE_INLINE void getUv(int mapIdx, hkVector4& uvOut) const;

				/// Sets the displacement map uv
				template <int I>
				HK_FORCE_INLINE void setUv(hkVector4Parameter uv);

				/// Sets the displacement map uv
				HK_FORCE_INLINE void setUv(int mapIdx, hkVector4Parameter uv);

				/// Gets the displacement vector
				HK_FORCE_INLINE void getDisplacementVector(hkVector4& dOut) const;

				/// Sets the displacement vector (i.e. n = normalize(vD), d = length(vD)). The normal is considered null if its length is under the given tol.
				HK_FORCE_INLINE void setDisplacementVector(hkVector4Parameter vD, hkSimdRealParameter tol);

				/// Permutes the displacement maps
				HK_FORCE_INLINE void permuteDisplacementMaps();

				/// Loads the values from a buffer
				HK_FORCE_INLINE void load(const void* buffer);

			protected:

				/// Displacement map uv.
				hkVector4f m_data0;	///< [uv0.x, uv0.y, uv1.x, uv1.y]

				/// Normalized displacement direction in .xyz.
				hkVector4f m_data1;	///< [normal.x, normal.y, mapBlendFactor, displacementAmount]
		};

		/// Dominants buffer
		class DominantsBuffer
		{
			public:

				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_SCENE_DATA, hkDisplacementMappingUtil::DominantsBuffer);

			public:

				/// Constructor
				DominantsBuffer();

				/// Destructor
				virtual ~DominantsBuffer();

			public:

				/// Allocates a buffer for N dominants
				void alloc(int numDominants);

				/// Creates and returns the texture
				hkMeshTexture* realize(hkMeshSystem* meshSystem);

				/// Returns the I-th element
				HK_FORCE_INLINE DominantInfo& operator[](int i);
				HK_FORCE_INLINE const DominantInfo& operator[](int i) const;

			protected:

				hkUint8* m_data;					///< Buffer data
				hkRefPtr<hkMeshTexture> m_texture;	///< The texture
		};

	public:

		/// Returns the displacement map set on the given material
		static hkMeshTexture* HK_CALL getDisplacementMap(const hkMeshMaterial* mtl);

		/// Returns the dominants map set on the given material
		static hkMeshTexture* HK_CALL getDominantsMap(const hkMeshMaterial* mtl);

		/// Sets the given dominants map on the given material
		static void HK_CALL setDominantsMap(hkMeshMaterial* mtl, hkMeshTexture* dominantsMap);

		/// Sets the I-th displacement map on the given material to the given texture
		static void HK_CALL setDisplacementMap(int i, hkMeshMaterial* mtl, hkMeshTexture* displacementMap);

		/// Clones a material without preserving the name
		static hkMeshMaterial* HK_CALL duplicateMaterial(hkMeshSystem* meshSystem, const hkMeshMaterial* src);
};

#include <Common/GeometryUtilities/Mesh/Utils/DisplacementMappingUtil/hkDisplacementMappingUtil.inl>

#endif	// HK_DISPLACEMENT_MAPPING_UTIL_H

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
