/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_HARDWARE_INFO_H
#define HKBASE_HARDWARE_INFO_H


/// Run-time hardware information.
/// This is a strict superset of compile-time information.
class HK_EXPORT_COMMON hkHardwareInfo : public hkReferencedObject, public hkSingleton<hkHardwareInfo>
{
	public:

		/// Supported features.
		enum CpuFeature
		{
			CMPXCHG8,
			CMPXCHG16B,
			CMOV,
			CLFLUSH,
			PCLMULDQ,
			MOVBE,

			/// Most relevant intrinsics (not a complete list):
			/// - int _mm_popcnt__u32 (unsigned int v)
			/// - __int64 _mm_popcnt__u64 (unsigned __int64 v)
			POPCNT,

			LZCNT,
			F16C,
			FMA,
			AES,
			MMX,
			AVX,
			AVX2,
			SSE,
			SSE2,
			SSE3,

			/// Most relevant intrinsics (not a complete list):
			/// __m128i _mm_shuffle_epi8 (__m128i a, __m128i b)
			/// __m128i _mm_hadd_epi32 (__m128i a, __m128i b)
			SSSE3,

			SSE41,
			SSE42,
			FP16C,
			BMI1,
			BMI2,

			/// Dummy feature, always set.
			DUMMY,

			NUM_CPU_FEATURES
		};

	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);

		/// Constructor.
		hkHardwareInfo();

		/// Return true if the feature is supported, false otherwise.
		template <CpuFeature FEATURE>
		static HK_FORCE_INLINE bool hasFeature()
		{
			return hkHardwareInfo::getInstance().m_cpuFeatures & ( 1 << FEATURE ) || false;
		}

		/// Return true if the feature set is supported, false otherwise.
		static HK_FORCE_INLINE bool hasFeatureSet( CpuFeature f0, CpuFeature f1 = DUMMY, CpuFeature f2 = DUMMY, CpuFeature f3 = DUMMY)
		{
			const hkUint32 featureSet = hkUint32( (1 << f0) | (1 << f1) | (1 << f2) | (1 << f3) );
			return (hkHardwareInfo::getInstance().m_cpuFeatures & featureSet) == featureSet;
		}

		/// Return the number of hardware threads.
		static HK_FORCE_INLINE int getNumHardwareThreads()
		{
			return hkHardwareInfo::getInstance().m_numHardwareThreads;
		}

		/// Calculate the number of hardware threads.
		/// This method does not require the singleton to be initialized.
		static int calcNumHardwareThreads();

	protected:

		int			m_numHardwareThreads;	///< Number of hardware threads.
		hkUint32	m_cpuFeatures;			///< Feature set.
};


#endif // HKBASE_HARDWARE_INFO_H

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
