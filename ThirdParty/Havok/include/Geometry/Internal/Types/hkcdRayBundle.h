/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE
#ifndef	HKCD_TYPES_RAY_BUNDLE
#define HKCD_TYPES_RAY_BUNDLE


#include <Common/Base/hkBase.h>
#include <Common/Base/Types/hkHandle.h>
#include <Common/Base/Math/Vector/hkFourTransposedPoints.h>



/// Represents 4 line segments (rays) bundled together.
/// The start and end position are stored in transposed form
struct HK_EXPORT_COMMON hkcdRayBundle
{
	/// Returns the direction
	HK_FORCE_INLINE void getDirection(hkFourTransposedPoints& directionOut) const
	{
		directionOut.setSub(m_end, m_start);
	}

	/// The start positions of 4 rays transposed
	hkFourTransposedPoints m_start;

	/// The end positions of 4 rays transposed
	hkFourTransposedPoints m_end;

	/// A mask indicating which rays are active
	hkVector4Comparison m_activeRays;
};

#endif // HKCD_TYPES_RAY_BUNDLE

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
