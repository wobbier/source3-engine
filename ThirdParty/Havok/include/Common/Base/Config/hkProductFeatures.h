/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_PRODUCT_FEATURES_H
#define HK_PRODUCT_FEATURES_H

	/// The initialize function is generated as a side effect of #include <Common/Base/Config/hkProductFeatures.cxx>
class hkProductFeatures
{
	public:

		static void HK_CALL initialize();
};

// You only need to look further if you're doing something specialized.
// Mostly you'll just use the macros in hkProductFeatures.inl to control
// what gets linked or stripped.


//
// Common
//
		/// You'll need this in order to load assets which were generated prior to version 7.0.0.
		/// It's rather large and shouldn't be linked unless you definitely need it.
	extern void HK_CALL hkFeature_serializeDeprecatedPre700();

#endif//HK_PRODUCT_FEATURES_H

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
