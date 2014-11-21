/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_FPU_MORPHING_DEFORMER_H
#define HK_FPU_MORPHING_DEFORMER_H

#include <Animation/Animation/Deform/Morphing/hkaMorphingDeformer.h>

/// The derived reference counted class for weighted vertex deformation.
/// Applies to both indexed and non indexed skinning.
/// By FPU it really means that it will not enforce any alignment on the input
/// or output data, but if your math configuration uses SIMD, it will use the SIMD ops
/// where it can. If you have data that has its deformable members (pos, normals, etc)
/// properly aligned, then use the SIMD version of this deformer
/// as it will be more streamlined.
/// Note this deformer only processes 3-component vectors.
/// N.B. It is important to note that these deformers are here to be used by Havok's demos but are not production quality.
/// It is assumed that deforming will be done most commonly by your graphics engine, usually in hardware on GPUs or VUs.
/// That hardware deformation is usually performed at the same time as per vertex lighting operations, so Havok cannot
/// provide optimized deformers for all such game specific usage.
class HK_EXPORT_ANIMATION hkaFPUMorphingDeformer : public hkReferencedObject, public hkaMorphingDeformer
{
	public:
	
		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ANIM_RUNTIME);

			/// Initializes to an unbound deformer
		hkaFPUMorphingDeformer();

			/// Bind the buffers.
			/// The output buffer should be preallocated.
			/// Returns false if the deformer does not support the input or output buffer format.
		hkBool bind( const hkaVertexDeformerInput& input, const hkxVertexBuffer* inputBuffer1, const hkxVertexBuffer* inputBuffer2,  hkxVertexBuffer* outputBuffer );

			/// Interpolate the input buffers into the output buffer.
			/// The deformer must first be bound and the output buffer locked before deforming.
		virtual void deform ( hkReal delta ) HK_OVERRIDE;

};

#endif // HK_FPU_MORPHING_DEFORMER_H

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
