/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

//
//	Returns the given plane

HK_FORCE_INLINE void hkcdPlanarGeometryPlanesCollection::getPlane(PlaneId planeId, Plane& planeOut) const
{
	const int idx = planeId.value() & (~hkcdPlanarGeometryPrimitives::FLIPPED_PLANE_FLAG);
	const Plane& p = m_planes[idx];

	if ( planeId.value() & hkcdPlanarGeometryPrimitives::FLIPPED_PLANE_FLAG )
	{
		planeOut.setOpposite(p);
	}
	else
	{
		planeOut = p;
	}
}

//
//	Advanced use. Accesses the plane having the given Id.

HK_FORCE_INLINE hkcdPlanarGeometryPlanesCollection::Plane& hkcdPlanarGeometryPlanesCollection::accessPlane(PlaneId planeId)
{
	HK_ASSERT(0x3296464, !(planeId.value() & hkcdPlanarGeometryPrimitives::FLIPPED_PLANE_FLAG));
	const int idx = planeId.value() & (~hkcdPlanarGeometryPrimitives::FLIPPED_PLANE_FLAG);
	return m_planes[idx];
}

//
//	Gets the requested world boundary plane

HK_FORCE_INLINE const hkcdPlanarGeometryPrimitives::Plane& hkcdPlanarGeometryPlanesCollection::getBoundaryPlane(Bounds b) const
{
	return m_planes[b];
}

//
//	Allocates a new plane

HK_FORCE_INLINE hkcdPlanarGeometryPlanesCollection::PlaneId hkcdPlanarGeometryPlanesCollection::allocPlane()
{
	const PlaneId planeId(m_planes.getSize());
	m_planes.expandOne();
	return planeId;
}

//
//	Adds a new plane

HK_FORCE_INLINE hkcdPlanarGeometryPlanesCollection::PlaneId hkcdPlanarGeometryPlanesCollection::addPlane(const Plane& plane)
{
	const PlaneId planeId(m_planes.getSize());
	m_planes.pushBack(plane);
	return planeId;
}

//
//	Returns the number of planes stored in the collection

HK_FORCE_INLINE int hkcdPlanarGeometryPlanesCollection::getNumPlanes() const
{
	return m_planes.getSize();
}

//
//	Removes all planes from the collection

HK_FORCE_INLINE void hkcdPlanarGeometryPlanesCollection::clear()
{
	HK_ASSERT(0x3296463, m_planes.getSize() >= NUM_BOUNDS);
	m_planes.setSize(NUM_BOUNDS);
	clearCaches();
}

//
//	Gets / sets the offset / scale that has been applied to all coordinates

HK_FORCE_INLINE const hkVector4& hkcdPlanarGeometryPlanesCollection::getPositionOffset() const			{	return m_offsetAndScale;	}
HK_FORCE_INLINE const hkSimdReal hkcdPlanarGeometryPlanesCollection::getPositionScale() const			{	return m_offsetAndScale.getComponent<3>();	}
HK_FORCE_INLINE void hkcdPlanarGeometryPlanesCollection::setPositionOffset(hkVector4Parameter v)		{	const hkSimdReal s = getPositionScale(); m_offsetAndScale = v; setPositionScale(s);	}
HK_FORCE_INLINE void hkcdPlanarGeometryPlanesCollection::setPositionScale(hkSimdRealParameter scale)	{	m_offsetAndScale.setComponent<3>(scale);	}

//
//	Converts a vertex from / to float to / from fixed-precision

HK_FORCE_INLINE void hkcdPlanarGeometryPlanesCollection::convertWorldPosition(hkVector4Parameter vSrc, hkIntVector& vDst) const
{
	hkVector4 v;	v.setSub(vSrc, m_offsetAndScale);
	v.mul(m_offsetAndScale.getComponent<3>());
	v.setMax(v,hkVector4::getZero());	// We shouldn't have negative numbers at this stage!
	vDst.setConvertF32toS32(v);
}

HK_FORCE_INLINE void hkcdPlanarGeometryPlanesCollection::convertFixedPosition(hkIntVectorParameter vSrc, hkVector4& vDst) const
{
	hkSimdReal invScale;	invScale.setReciprocal<HK_ACC_FULL, HK_DIV_IGNORE>(m_offsetAndScale.getComponent<3>());
	hkVector4 v;			vSrc.convertS32ToF32(v);
	v.mul(invScale);
	vDst.setAdd(v, m_offsetAndScale);
}

//
//	Converts a direction from world to fixed-precision

HK_FORCE_INLINE void hkcdPlanarGeometryPlanesCollection::convertWorldDirection(hkVector4Parameter vSrc, hkIntVector& vDst) const
{
	hkVector4 v;
	v.setMul(m_offsetAndScale.getComponent<3>(), vSrc);
	vDst.setConvertF32toS32(v);
}

//
//	Returns a valid orientation cache for this plane collection
HK_FORCE_INLINE hkcdPlanarGeometryPlanesCollection::OrientationCache* hkcdPlanarGeometryPlanesCollection::getOrientationCache() const
{
	if ( !m_cache )
	{
		m_cache = new OrientationCache();
	}

	return m_cache;
}

//
//	Resets the orientation cache

HK_FORCE_INLINE void hkcdPlanarGeometryPlanesCollection::clearCaches()
{
	if ( m_cache )
	{
		delete m_cache;
		m_cache = HK_NULL;
	}
}

//
//	Locks the plane collection for thread safe access

HK_FORCE_INLINE void hkcdPlanarGeometryPlanesCollection::lock() const
{
	m_criticalAccess->enter();
}

//
//	Unlocks the plane collection

HK_FORCE_INLINE void hkcdPlanarGeometryPlanesCollection::unlock() const
{
	m_criticalAccess->leave();
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
