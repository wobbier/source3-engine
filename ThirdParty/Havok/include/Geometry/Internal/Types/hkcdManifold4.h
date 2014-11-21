/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef	HKCD_TYPES_MANIFOLD_16
#define HKCD_TYPES_MANIFOLD_16

#include <Common/Base/DebugUtil/DeterminismUtil/hkCheckDeterminismUtil.h>

/// A contact manifold between two objects, holding up to 16 points.
/// Note that if the number of contact points > 0, all positions/distances must be initialized,
/// even if the number of contact points < 16 (in this case the first point is replicated in the last points)
struct HK_EXPORT_COMMON hkcdManifold4
{
	enum
	{
		MAX_NUM_CONTACT_POINTS = 4
	};

	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, hkcdManifold4 );

#ifdef HK_WANT_DETERMINISM_CHECKS
	hkcdManifold4()
	{
		hkString::memSet( this, 0xcd, sizeof(hkcdManifold4) ); // deterministically set unused memory
	}
#endif

	/// Get the distance of a given contact.
	HK_FORCE_INLINE hkSimdReal getDistance( int i ) const 
	{
		// we do not use broadcast here, as i is probably not a constant and very likely hkcdManifold4 is in memory
		hkSimdReal res; res.load<1>( &m_distances[i] );	
		return res;
	}

	/// Get the minimum of all distances.
	HK_FORCE_INLINE hkSimdReal getMinimumDistance() const
	{
		return hkSimdReal::fromFloat( m_minimumDistance );
	}

	/// Invert the manifold, so it becomes from A to B instead of B to A.
	HK_FORCE_INLINE void flip()
	{
		for( int i = 0; i < MAX_NUM_CONTACT_POINTS; i += 4 )
		{
			hkVector4 distances; distances.load<4>( &m_distances[i] );
			m_positions[i+0].addMul( m_normal, distances.getComponent<0>() );
			m_positions[i+1].addMul( m_normal, distances.getComponent<1>() );
			m_positions[i+2].addMul( m_normal, distances.getComponent<2>() );
			m_positions[i+3].addMul( m_normal, distances.getComponent<3>() );
		}
		m_normal.setNeg<4>( m_normal );
	}


	HK_ALIGN_REAL(int m_numPoints);	///< The number of valid contact points in m_positions.	

	hkReal m_minimumDistance;		///< The minimum distance between the 2 objects.

	hkVector4 m_normal;				///< The manifold normal, from B to A in world space.
	hkVector4 m_weldNormal;			///< If object B is a quad, this is plane 0 (needed for welding).

	hkReal    m_distances[MAX_NUM_CONTACT_POINTS];	///< The distances of each contact point.
	hkVector4 m_positions[MAX_NUM_CONTACT_POINTS];	///< The positions of each contact point, on B in world space.
};

#endif // HKCD_TYPES_MANIFOLD_16

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
