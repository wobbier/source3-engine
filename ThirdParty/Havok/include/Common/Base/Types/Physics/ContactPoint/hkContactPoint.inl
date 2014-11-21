/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

inline const hkVector4& hkContactPoint::getPosition() const
{ 
	return m_position; 
}

inline const hkVector4& hkContactPoint::getNormal() const
{ 
	return m_separatingNormal; 
}

#if defined(HK_CONTACT_POINT_NAN_CHECKS)
static void hkContactPoint_infassert(hkVector4Parameter v)
{
	HK_ASSERT(0x99999999,v.isOk<3>());
//	HK_REPORT("v "<<v(0)<<" "<<v(1)<<" "<<v(2));
}
#else
#define hkContactPoint_infassert(x)
#endif

inline void hkContactPoint::setPosition( const hkVector4& position )
{
	hkContactPoint_infassert(position);
	m_position = position; 
}


inline const hkVector4& hkContactPoint::getSeparatingNormal() const
{ 
	return m_separatingNormal; 
}

inline void hkContactPoint::setSeparatingNormal( const hkVector4& normal, hkReal dist )
{
	hkContactPoint_infassert(normal);
	m_separatingNormal = normal;
	m_separatingNormal(3) = dist;
}

inline void hkContactPoint::setSeparatingNormal( hkVector4Parameter normal, hkSimdRealParameter dist )
{
	hkContactPoint_infassert(normal);
	m_separatingNormal.setXYZ_W(normal,dist);
}

inline void hkContactPoint::setSeparatingNormal( const hkVector4& separatingNormal )
{
	hkContactPoint_infassert(separatingNormal);
	m_separatingNormal = separatingNormal;
}


inline hkReal hkContactPoint::getDistance() const
{
	return m_separatingNormal(3); 
}

inline hkSimdReal hkContactPoint::getDistanceSimdReal() const
{
	return m_separatingNormal.getComponent<3>(); 
}

inline void hkContactPoint::setDistance( hkReal d )
{ 
	m_separatingNormal(3) = d; 
}

//
//	Set the distance

inline void hkContactPoint::setDistanceSimdReal(hkSimdRealParameter newValue)
{
	m_separatingNormal.setW(newValue);
}

inline void hkContactPoint::set( const hkVector4& position, const hkVector4& normal, hkReal dist )
{ 
	hkContactPoint_infassert(position);
	hkContactPoint_infassert(normal);
	m_position = position; 
	m_separatingNormal = normal;
	m_separatingNormal(3) = dist; 
}

//
//	Set the position, normal and distance

inline void hkContactPoint::setPositionNormalAndDistance(hkVector4Parameter position, hkVector4Parameter normal, hkSimdRealParameter dist)
{
	hkContactPoint_infassert(position);
	hkContactPoint_infassert(normal);
	m_position = position; 
	m_separatingNormal.setXYZ_W(normal, dist);
}

inline void hkContactPoint::setNormalOnly( const hkVector4& normal )
{ 
	hkContactPoint_infassert(normal);
	m_separatingNormal.setXYZ( normal );
}

inline void hkContactPoint::setFlipped( const hkContactPoint& point )
{
	m_position.setAddMul( point.m_position, point.m_separatingNormal, point.m_separatingNormal.getComponent<3>() );
	hkContactPoint_infassert(m_position);
	m_separatingNormal.setNeg<3>( point.m_separatingNormal );
	hkContactPoint_infassert(m_separatingNormal);
}

inline void hkContactPoint::flip()
{
	setFlipped(*this);
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
