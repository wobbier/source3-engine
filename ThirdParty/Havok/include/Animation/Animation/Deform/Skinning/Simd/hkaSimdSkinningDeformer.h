/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKA_SIMD_SKINNING_DEFORMER_H
#define HKA_SIMD_SKINNING_DEFORMER_H

/// The class for a SIMD based implementation of weighted vertex deformation.
/// Applies to both indexed and non indexed skinning.
/// This deformer requires that the input buffers' deformable
/// members (pos, normals) be aligned for SIMD processing
/// and for faster operation make sure that the outputs are aligned as well.
/// Note this deformer only processes 3-component vectors.
/// N.B. It is important to note that these deformers are here to be used by Havok's demos but are not production quality.
/// It is assumed that deforming will be done most commonly by your graphics engine, usually in hardware on GPUs or VUs.
/// That hardware deformation is usually performed at the same time as per vertex lighting operations, so Havok cannot
/// provide optimized deformers for all such game specific usage.
class HK_EXPORT_ANIMATION hkaSimdSkinningDeformer
{
	public:
			/// Will call either one of the aligned static funcs, depending on m_outputBufferIsAligned in binding.
		template <class SimdSkinBinding>
		static void HK_CALL deform( const hkTransform* worldCompositeMatrices, int numWorldCompositeMatrices, SimdSkinBinding& binding  );

			/// Input must be SIMD aligned, if Output is aligned set OUTPUTMODE to HK_IO_SIMD_ALIGNED
		template <class SimdSkinBinding, hkMathIoMode OUTPUTMODE>
		static void HK_CALL deformAlignedInput( const hkTransform* worldCompositeMatrices, int numWorldCompositeMatrices, SimdSkinBinding& binding );
};

#endif // HKA_SIMD_SKINNING_DEFORMER_H

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
