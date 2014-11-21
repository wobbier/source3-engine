/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

/// Set from direction. Does not modify the origin
HK_FORCE_INLINE	void hkcdRay_setDirection(hkVector4Parameter direction, hkSimdRealParameter fraction, hkcdRay* HK_RESTRICT ray )
{
	hkVector4 directionV;
	directionV.setXYZ_W(direction, fraction);
	directionV.zeroIfTrue( directionV.equalZero() ); // Avoid negative zeros to ensure that the reciprocals of zeros are positive.

	hkVector4 invDirection; invDirection.setReciprocal<HK_ACC_RAYCAST,HK_DIV_SET_MAX>(directionV);
	invDirection.setInt24W(int(directionV.greaterEqualZero().getMask<hkVector4ComparisonMask::MASK_XYZ>()) );
	ray->m_direction    = directionV;
	ray->m_invDirection = invDirection;
}

//
HK_FORCE_INLINE	void hkcdRay::setEndPoints(hkVector4Parameter start, hkVector4Parameter end, hkSimdRealParameter fraction)
{
	hkVector4	direction; direction.setSub(end, start);
	hkcdRay_setDirection(direction, fraction, this);
	m_origin  = start;
}


//
HK_FORCE_INLINE	void hkcdRay::setOriginDirection(hkVector4Parameter origin, hkVector4Parameter direction, hkSimdRealParameter fraction)
{
	hkcdRay_setDirection(direction, fraction, this);
	m_origin	=	origin;
}

//
//	Computes the ray end-point

HK_FORCE_INLINE void hkcdRay::getEndPoint(hkVector4& vEndPoint) const
{
	vEndPoint.setAddMul(m_origin, m_direction, getFraction());
}



/*static*/ HK_FORCE_INLINE void hkcdRayQueryFlags::isFlagSet(hkFlags<hkcdRayQueryFlags::Enum,hkUint32> flags, Enum flag, hkVector4Comparison& out)
{
	HK_ASSERT( 0xf034fe54, hkUint32(flag) < 16 );
	out.set(  hkVector4ComparisonMask::Mask(  ( (0- (flags.get()&flag) )>>4 )  & hkVector4ComparisonMask::MASK_XYZW) );
}

#define HK_STRINGIFY_CASE(x) case x: do { return stream << #x; }while(0)

HK_FORCE_INLINE hkOstream& operator<<(hkOstream& stream, const hkcdRayCastResult result)
{
	switch(result.m_value)
	{
		HK_STRINGIFY_CASE(hkcdRayCastResult::NO_HIT);
		HK_STRINGIFY_CASE(hkcdRayCastResult::BACK_FACE_HIT);
		HK_STRINGIFY_CASE(hkcdRayCastResult::FRONT_FACE_HIT);
		HK_STRINGIFY_CASE(hkcdRayCastResult::INSIDE_HIT);
	default:
		HK_ASSERT2(0x7aa47435, false, "Unknown or bad hkcdRayCastResult.");
		return stream << "Unknown or bad hkcdRayCastResult.";
	}
}

#undef HK_STRINGIFY_CASE

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
