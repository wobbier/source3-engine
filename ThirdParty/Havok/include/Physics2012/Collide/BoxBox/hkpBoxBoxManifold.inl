/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


HK_FORCE_INLINE int hkpBoxBoxManifold::getNumPoints() const
{
	return m_numPoints;
}

HK_FORCE_INLINE hkpFeatureContactPoint& hkpBoxBoxManifold::operator[]( int index )
{
	return m_contactPoints[index];
}

HK_FORCE_INLINE bool hkpBoxBoxManifold::findInManifold( const hkpFeatureContactPoint& fcp ) const
{
	for (int i = m_numPoints-1; i>=0; i--)
	{
		if ( m_contactPoints[i].m_featureIdA == fcp.m_featureIdA && m_contactPoints[i].m_featureIdB == fcp.m_featureIdB )
		{
			return true;
		}
	}
	return false;
}

HK_FORCE_INLINE bool hkpBoxBoxManifold::isComplete() const
{
	return m_isComplete; 
}

HK_FORCE_INLINE void hkpBoxBoxManifold::setComplete( bool complete )
{
	m_isComplete = complete;	
}

HK_FORCE_INLINE bool hkpBoxBoxManifold::hasNoPointsLeft() const
{
	return (m_numPoints >= HK_BOXBOX_MANIFOLD_MAX_POINTS); 
}

HK_FORCE_INLINE hkBool32 hkpBoxBoxManifold::isNormalInitialized() const
{
	return m_manifoldNormalA.getW().isLessZero();
}

HK_FORCE_INLINE void hkpBoxBoxManifold::setNormalInitialized()
{
	m_manifoldNormalA.setW(hkSimdReal_Minus1);
}

HK_FORCE_INLINE void hkpBoxBoxManifold::clearNormalInitialized()
{
	m_manifoldNormalA.zeroComponent<3>();
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
