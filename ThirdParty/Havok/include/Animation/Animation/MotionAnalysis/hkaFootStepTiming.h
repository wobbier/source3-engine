/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_FOOTSTEP_TIMING_H
#define HK_FOOTSTEP_TIMING_H

class hkaExpandAnimationUtility;
#include <Animation/Internal/hkaExport.h>
class HK_EXPORT_ANIMATION hkaFootStepTiming
{
public:

	/// Default initialization
	hkaFootStepTiming();

	/// Initialize from an expanded animation
	hkaFootStepTiming( const hkArrayBase< hkBool >& isDown, hkSimdRealParameter duration );

	/// Initialize
	void init( const hkArrayBase< hkBool >& isDown, hkSimdRealParameter duration );

	/// \return The time that the foot first contacts the ground
	hkSimdReal getDownTime() const;
	
	/// \return The time that the foot first lifts from the ground
	hkSimdReal getUpTime() const;

	/// \return The midpoint for the foot down
	hkSimdReal getMidDownTime() const;

	/// \return The midpoint for the foot down
	hkSimdReal getMidUpTime() const;

	/// \return The length of time that the foot is down
	hkSimdReal getDownDuration() const;

	/// \return The length of time that the foot is up
	hkSimdReal getUpDuration() const;

	/// \return True if the foot is down at the specified time
	bool isDown( hkSimdRealParameter time ) const;

	/// \return True if the foot is up at the specified time
	bool isUp( hkSimdRealParameter time ) const;

	/// \return The midpoint in time between two events, takes wrapping into account
	hkSimdReal getMidpoint( hkSimdRealParameter first, hkSimdRealParameter last ) const;


	/// Set the time that the foot strikes the ground
	inline void setDownTime( hkSimdRealParameter time ) { m_downTime = time; }

	/// Set the time that the foot releases from the ground
	inline void setUpTime( hkSimdRealParameter time ) { m_upTime = time; }

	/// Set the total duration of the cycle
	inline void setDuration( hkSimdRealParameter time ) { m_duration = time; }

private:

	hkSimdReal m_downTime;
	hkSimdReal m_upTime;
	hkSimdReal m_duration;
};

#endif // HK_FOOTSTEP_TIMING_H

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
