/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MORPHING_DEFORMER_H
#define HK_MORPHING_DEFORMER_H

#include <Animation/Animation/Deform/hkaVertexDeformerInput.h>

class hkxVertexBuffer;

/// The abstract base class for weighted vertex deformation.
/// Applies to both indexed and non indexed skinning.
class HK_EXPORT_ANIMATION hkaMorphingDeformer
{
	//+hk.MemoryTracker(ignore=True)
	public:
		virtual ~hkaMorphingDeformer() { }

			/// Bind this deformer to input and output buffers.
			/// The output buffer should be preallocated.
			/// Returns false if the deformer does not support the input or output buffer format.
		hkBool bind( const hkaVertexDeformerInput& input, const hkxVertexBuffer* inputBuffer1, const hkxVertexBuffer* inputBuffer2,  hkxVertexBuffer* outputBuffer );

			/// Interpolate the input buffers into the output buffer.
			/// The deformer must first be bound and the output buffer locked before deforming.
		virtual void deform ( hkReal delta ) = 0;

		struct Binding
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_ANIM_RUNTIME, hkaMorphingDeformer::Binding );

			// Input buffer 1
			const hkFloat32* m_i1PosBase;
			const hkFloat32* m_i1NormBase;
			const hkFloat32* m_i1BinormBase;
			const hkFloat32* m_i1TangentBase;
			hkUint8 m_i1Stride;

			// Input Buffer 2
			const hkFloat32* m_i2PosBase;
			const hkFloat32* m_i2NormBase;
			const hkFloat32* m_i2BinormBase;
			const hkFloat32* m_i2TangentBase;
			hkUint8 m_i2Stride;

			// Output Buffer
			hkFloat32* m_oPosBase;
			hkFloat32* m_oNormBase;
			hkFloat32* m_oBinormBase;
			hkFloat32* m_oTangentBase;
			hkUint8 m_oStride;

			hkUint32 m_numVerts;
		};

		struct Binding m_binding;

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
