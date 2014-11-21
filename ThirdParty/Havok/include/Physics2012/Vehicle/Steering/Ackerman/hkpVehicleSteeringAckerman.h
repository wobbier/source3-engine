/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKVEHICLE_STEERING_ACKERMAN_hkVehicleSteeringAckerman_XML_H
#define HKVEHICLE_STEERING_ACKERMAN_hkVehicleSteeringAckerman_XML_H

#include <Physics2012/Vehicle/Steering/hkpVehicleSteering.h>

extern const class hkClass hkpVehicleSteeringAckermanClass;


class hkpVehicleSteeringAckerman : public hkpVehicleSteering
{
public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
	HK_DECLARE_REFLECTION();

	/// Default constructor
	hkpVehicleSteeringAckerman();

	//
	// Methods
	//

	/// Calculates information about the effects of steering on the vehicle.
	virtual void calcSteering(const hkReal deltaTime, const hkpVehicleInstance* vehicle, const hkpVehicleDriverInput::FilteredDriverInputOutput& filteredInfoOutput, SteeringAnglesOutput& steeringOutput );

protected:		
	/// Calculates the main steering angle.
	void calcMainSteeringAngle( const hkReal deltaTime, const hkpVehicleInstance* vehicle, const hkpVehicleDriverInput::FilteredDriverInputOutput& filteredInfoOutput, SteeringAnglesOutput& steeringOutput );

	void calcAckermanOuterAngles( const hkpVehicleInstance* vehicle, SteeringAnglesOutput& steeringOutput );

	//
	// Members
	//
public:

	/// The maximum steering angle (valid for velocities less than m_maxSpeedFullSteeringAngle).
	hkReal m_maxSteeringAngle;

	/// The maximum speed the car still can use the m_maxSteeringAngle.
	hkReal m_maxSpeedFullSteeringAngle;

	/// For every wheel, should be true if the wheel is connected to steering.
	hkArray<hkBool> m_doesWheelSteer;

	/// Distance between wheels in the same axle
	hkReal m_trackWidth;

	/// Distance between two axles in meters
	hkReal m_wheelBaseLength; 

public:
	hkpVehicleSteeringAckerman(hkFinishLoadedObjectFlag f) : hkpVehicleSteering(f), m_doesWheelSteer(f) { }
};

#endif // HKVEHICLE_STEERING_DEFAULT_hkVehicleDefaultSteering_XML_H

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
