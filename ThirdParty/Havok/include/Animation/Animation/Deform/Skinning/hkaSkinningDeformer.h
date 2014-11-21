/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SKINNING_DEFORMER_H
#define HK_SKINNING_DEFORMER_H

#include <Animation/Animation/Deform/hkaVertexDeformerInput.h>

#include <Common/SceneData/Mesh/hkxVertexBuffer.h>

struct hkaSkinBinding
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_RUNTIME, hkaSkinBinding );

	// Input buffer
	const hkFloat32* m_iPosBase;
	const hkFloat32* m_iNormBase;
	const hkFloat32* m_iBinormBase;
	const hkFloat32* m_iTangentBase;
	const hkUint8* m_iWeightBase;
	const hkUint8* m_iIndexBase;
	hkUint8 m_iPosStride;  // in hkFloat32
	hkUint8 m_iNormStride; // in hkFloat32
	hkUint8 m_iBinormStride; // in hkFloat32
	hkUint8 m_iTangentStride;// in hkFloat32
	hkUint8 m_iWeightStride; // in bytes
	hkUint8 m_iIndexStride;  // in bytes
	hkUint8 m_bonesPerVertex;

	// Output Buffer
	hkFloat32* m_oPosBase;
	hkFloat32* m_oNormBase;
	hkFloat32* m_oBinormBase;
	hkFloat32* m_oTangentBase;
	hkUint8 m_oPosStride; // in hkFloat32
	hkUint8 m_oNormStride; // in hkFloat32
	hkUint8 m_oBinormStride; // in hkFloat32
	hkUint8 m_oTangentStride; // in hkFloat32

	hkUint32 m_numVerts;
	bool m_outputBufferIsAligned;

	void setBoneIndicesDataPtr(const hkxVertexBuffer& vb)
	{
		const hkxVertexDescription& vertDecl = vb.getVertexDesc(); 
		const hkxVertexDescription::ElementDecl* boneDecl = vertDecl.getElementDecl(hkxVertexDescription::HKX_DU_BLENDINDICES, 0);

		m_iIndexBase = (hkUint8*)( vb.getVertexDataPtr(*boneDecl) );
		m_iIndexStride =  hkUint8(boneDecl->m_byteStride);
	}
	hkUint16 getVertexBoneIndex(hkUint32 vertexIdx, hkUint32 influenceIdx)
	{
		const hkUint8* vertexBoneIndices = (const hkUint8*)(m_iIndexBase + vertexIdx*m_iIndexStride);
		hkUint8 boneIndex = vertexBoneIndices[influenceIdx];

		return hkUint16(boneIndex);
	}
};

struct hkaSkinLargeBinding
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_RUNTIME, hkaSkinLargeBinding );

	// Input buffer
	const hkFloat32* m_iPosBase;
	const hkFloat32* m_iNormBase;
	const hkFloat32* m_iBinormBase;
	const hkFloat32* m_iTangentBase;
	const hkUint8* m_iWeightBase;
	const hkUint16* m_iIndexBase;
	hkUint8 m_iPosStride;  // in hkFloat32
	hkUint8 m_iNormStride; // in hkFloat32
	hkUint8 m_iBinormStride; // in hkFloat32
	hkUint8 m_iTangentStride;// in hkFloat32
	hkUint8 m_iWeightStride; // in bytes
	hkUint8 m_iIndexStride;  // in bytes
	hkUint8 m_bonesPerVertex;

	// Output Buffer
	hkFloat32* m_oPosBase;
	hkFloat32* m_oNormBase;
	hkFloat32* m_oBinormBase;
	hkFloat32* m_oTangentBase;
	hkUint8 m_oPosStride; // in hkFloat32
	hkUint8 m_oNormStride; // in hkFloat32
	hkUint8 m_oBinormStride; // in hkFloat32
	hkUint8 m_oTangentStride; // in hkFloat32

	hkUint32 m_numVerts;
	bool m_outputBufferIsAligned;

	void setBoneIndicesDataPtr(const hkxVertexBuffer& vb)
	{
		const hkxVertexDescription& vertDecl = vb.getVertexDesc(); 
		const hkxVertexDescription::ElementDecl* boneDecl = vertDecl.getElementDecl(hkxVertexDescription::HKX_DU_BLENDINDICES, 0);

		m_iIndexBase = (hkUint16*)( vb.getVertexDataPtr(*boneDecl) );
		m_iIndexStride =  hkUint8(boneDecl->m_byteStride/sizeof(hkUint16));
	}
	hkUint16 getVertexBoneIndex(hkUint32 vertexIdx, hkUint32 influenceIdx)
	{
		const hkUint16* vertexBoneIndices = (const hkUint16*)(m_iIndexBase + vertexIdx*m_iIndexStride);
		hkUint16 boneIndex = vertexBoneIndices[influenceIdx];

		return boneIndex;
	}
};


/// The abstract base class for weighted vertex deformation.
/// Applies to both indexed and non indexed skinning.
class HK_EXPORT_ANIMATION hkaSkinningDeformer
{
	//+hk.MemoryTracker(ignore=True)
	public:

		virtual ~hkaSkinningDeformer() { }

			/// Bind this deformer to input and output buffers.
			/// The input format is assumed to have (at least) vertex weights.
			/// The output buffer should be preallocated.
			/// Returns false if the deformer does not support the input or output buffer format.
		virtual hkBool bind( const hkaVertexDeformerInput& input, const hkxVertexBuffer* inputBuffer,  hkxVertexBuffer* outputBuffer ) = 0;

			/// Deform the input buffer into the output buffer using the array of matrices specified.
			/// The deformer must first be bound and the output buffer locked before deforming.
		virtual void deform(  const hkTransform* m_worldCompositeMatrices ) = 0;
				
};

#endif // HK_SKINNING_DEFORMER_H

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
