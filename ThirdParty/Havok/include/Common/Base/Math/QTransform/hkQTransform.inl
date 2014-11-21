/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Math/QTransform/hkQTransformf.inl>
#include <Common/Base/Math/QTransform/hkQTransformd.inl>

HK_FORCE_INLINE hkQTransform::hkQTransform()
:	hkQTransformType()
{}

#if defined(HK_REAL_IS_DOUBLE)
HK_FORCE_INLINE hkQTransform::hkQTransform(hkQuaterniondParameter q, hkVector4dParameter t)
#else
HK_FORCE_INLINE hkQTransform::hkQTransform(hkQuaternionfParameter q, hkVector4fParameter t)
#endif
:	hkQTransformType(q, t)
{}

HK_FORCE_INLINE hkQTransform::hkQTransform(const hkQTransformType& qt)
:	hkQTransformType(qt)
{}

HK_FORCE_INLINE hkQTransform::hkQTransform(hkFinishLoadedObjectFlag f)
:	hkQTransformType(f)
{}

HK_FORCE_INLINE const hkQTransform& HK_CALL hkQTransform::getIdentity()
{
	// This is to prevent the copy constructor of hkQTransform to be called
	// every time hkQTransform::getIdentity is called
	return reinterpret_cast<const hkQTransform&>(hkQTransformType::getIdentity());
}

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
