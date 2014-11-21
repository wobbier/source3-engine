/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MATH_Q_TRANSFORM_H
#define HK_MATH_Q_TRANSFORM_H

#include <Common/Base/Math/QTransform/hkQTransformf.h>
#include <Common/Base/Math/QTransform/hkQTransformd.h>

#if defined(HK_REAL_IS_DOUBLE)
	typedef hkQTransformd hkQTransformType;
#else
	typedef hkQTransformf hkQTransformType;
#endif

/// Reflected hkQTransform
struct hkQTransform : public hkQTransformType
{
	//+version(2)
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_MATH, hkQTransform);
	HK_DECLARE_REFLECTION();

	/// Default constructor - all elements are uninitialized.
	HK_FORCE_INLINE hkQTransform();

	/// Creates a new hkQTransformf using the rotation quaternion q and translation t.
#if defined(HK_REAL_IS_DOUBLE)
	HK_FORCE_INLINE hkQTransform(hkQuaterniondParameter q, hkVector4dParameter t);
#else
	HK_FORCE_INLINE hkQTransform(hkQuaternionfParameter q, hkVector4fParameter t);
#endif

	/// Copy constructor
	HK_FORCE_INLINE hkQTransform(const hkQTransformType& qt);

	HK_FORCE_INLINE hkQTransform(class hkFinishLoadedObjectFlag f);

	/// Returns a global identity transform.
	HK_FORCE_INLINE static const hkQTransform& HK_CALL getIdentity();
};

#endif	// HK_MATH_Q_TRANSFORM_H

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
