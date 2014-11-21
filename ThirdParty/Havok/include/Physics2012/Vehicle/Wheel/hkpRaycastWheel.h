/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_RaycastWheel_H
#define HK_RaycastWheel_H

#include <Physics2012/Vehicle/Wheel/hkpWheel.h>
#include "Physics2012/Collide/Query/Collector/RayCollector/hkpClosestRayHitCollector.h"

// --------------------------------------------------------------------------------------------------------
// This class performs a basic per-wheel simulation of the friction and other forces in the car
// --------------------------------------------------------------------------------------------------------
class hkpRaycastWheel : public hkpWheel
{
public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);

	hkpRaycastWheel( hkpClosestRayHitCollector* collector = HK_NULL );
	hkpRaycastWheel( hkFinishLoadedObjectFlag f ) : hkpWheel(f) { }	
	~hkpRaycastWheel();

protected:
	void collide();

	hkpClosestRayHitCollector* m_collector;
	hkBool m_ownCollector;	//True if the collector was allocated by the hkpRayCastWheel
};

#endif // HK_RaycastWheel_H

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
