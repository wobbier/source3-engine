/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE


#ifndef HK_AABB_24_16_24_CODE_H
#define HK_AABB_24_16_24_CODE_H

#include <Common/Base/Types/Geometry/Aabb20/hkAabb20.h>
#include <Common/Base/Types/Geometry/IntSpaceUtil/hkIntSpaceUtil.h>


struct HK_EXPORT_COMMON hkAabb24_16_24_Codec : hkIntSpaceUtil
{
	void set( const hkAabb& aabb );

	HK_FORCE_INLINE void packAabb( const hkAabb& aabbF, hkAabb24_16_24* HK_RESTRICT aabbOut ) const;

	HK_FORCE_INLINE void unpackAabbUnscaled( const hkAabb24_16_24& aabb, hkAabb* HK_RESTRICT aabbFOut ) const;

	HK_FORCE_INLINE void restoreAabb( const hkAabb24_16_24& aabb, hkAabb* HK_RESTRICT aabbFOut ) const;

	int					m_yzReversed;
	hkIntVector			m_packPermuteMask;
	hkIntVector         m_permuteMaskMin;
	hkIntVector         m_permuteMaskMax;
#if HK_ENDIAN_LITTLE
	hkIntVector         m_unpackMask;
#endif
	hkVector4Comparison m_yzIsReversed;
	hkVector4           m_aabb24_16_24_Max;
	hkIntVector			m_aabb24_16_24_iMax;

};


#include <Common/Base/Types/Geometry/Aabb24_16_24_Codec/hkAabb24_16_24_Codec.inl>

#endif // HK_AABB_24_16_24_CODE_H

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
