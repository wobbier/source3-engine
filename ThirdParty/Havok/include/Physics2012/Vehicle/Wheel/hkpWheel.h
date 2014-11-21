/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_Wheel_H
#define HK_Wheel_H

#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Vehicle/WheelCollide/RejectChassisListener/hkpRejectChassisListener.h>
#include <Physics/Constraint/Atom/hkpConstraintAtom.h>
#include <Physics/Constraint/Data/WheelFriction/hkpWheelFrictionConstraintData.h>

// --------------------------------------------------------------------------------------------------------
// This class performs a basic per-wheel simulation of the friction and other forces in the car
// --------------------------------------------------------------------------------------------------------
class hkpWheel : public hkReferencedObject
{
public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);

	static const int MAX_NUM_SHAPE_KEYS = 8;

	hkpWheel() {}
	hkpWheel( hkFinishLoadedObjectFlag f ) : hkReferencedObject( f ) { }
	~hkpWheel();

	void init(hkpRigidBody* chassis,
			  hkpWheelFrictionConstraintAtom::Axle* axle,
			  hkReal radius, 
			  hkReal width,
			  hkVector4Parameter spinAxisCs, 
			  hkVector4Parameter suspensionHardpointCs, 
			  hkVector4Parameter suspensionDirectionCs, 
			  hkReal suspensionLength);

	//
	// Simulation methods
	//

	// Update the wheel position, steering, and contact point. Call this on each wheel before stepVehicleWheels().
	void update( const hkStepInfo& stepInfo );

	// Call to update the wheel before the physics step
	void preStep( const hkStepInfo& stepInfo );

	// Call to update the wheel after the physics step
	void postStep( const hkStepInfo& stepInfo );

	//
	// Accessors
	//

	// Gets the current position and rotation of the wheel in world space
	void calcCurrentPositionAndRotation( hkVector4& posOut, hkQuaternion& rotOut );

	// Returns the position of the contact point in world space
	const hkVector4& getContactPosition();

	// Returns the normal of the contact point in world space
	const hkVector4& getContactNormal();

	// Returns the wheel's hardpoint in world space
	const hkVector4& getHardPoint();

	// Get or set the wheel's spin velocity
	hkReal getSpinVelocity();
	void setSpinVelocity(hkReal spinVelocity);

protected:

	//
	// Helper methods
	//

	void applySuspension( const hkStepInfo& stepInfo );
	void computeAngularChassisAcceleration( const hkVector4& worldLinearFrictionImpulse, hkVector4& worldAngularVelocityDeltaOut );
	void getAabb( hkAabb& aabb );
	void getContactVelocity( hkVector4& pointVelocityOut, const hkVector4& contactLocal, const hkVector4& linearVelocityCOM, const hkVector4& angularVelocity );
	void removeFrictionConstraint();

public:

	hkpWheelFrictionConstraintData m_frictionData;
	hkpConstraintInstance* m_frictionConstraint;

	//
	// Wheel description
	//

	// Axle that the wheel is on, shared between connected wheels and used to keep them spinning at the same speed.
	// For independent wheels, create a separate axle for each one.
	hkpWheelFrictionConstraintAtom::Axle* m_axle;

	// Damping applied to slipping spin velocity, eg. if the wheel is spinning faster than the contact point's forward
	// linear velocity, the excess spin will be damped by this value.
	hkReal m_slipDamping;

	// Chassis to which this wheel is attached
	hkRefPtr<hkpRigidBody> m_chassis;

	// Axis relative to the chassis that the wheel is spinning around.
	hkVector4 m_spinAxisCs;

	// A point INSIDE the chassis to which the wheel suspension is attached.
	hkVector4 m_suspensionHardpointCs;

	// The suspension direction (in Chassis Space).
	hkVector4 m_suspensionDirectionCs;

	// The suspension length at rest i.e., the maximum distance from the hardpoint to the wheel center.
	hkReal m_suspensionLength;

	// Collision filtering for the wheel raycast / linear cast
	hkUint32 m_collisionFilterInfo;

	/// The wheel's coefficient of friction
	hkReal m_friction;

	// Radius of the wheel
	hkReal m_radius;

	// Width of the wheel
	hkReal m_width;

	/// The strength [N/m] of the suspension
	hkReal m_suspensionStrength;

	/// The damping force [N/(m/sec)] of the suspension
	hkReal m_suspensionDampingCompression;

	/// The damping force [N/(m/sec)] of the suspension
	hkReal m_suspensionDampingRelaxation;

	/// Change this value to clip the normal in suspension force calculations. In
	/// particular, when mounting a curb, the raycast vehicle calculations can produce
	/// large impulses as the rays hit the face of the step, causing the vehicle to
	/// spin around its up-axis. Setting this value to 0.2f produces considerably more
	/// stability.
	hkReal m_normalClippingAngleCos;

	//
	// Wheel state, set by the client each step
	//

	// Total torque applied at the wheel
	hkReal m_torque;

	// Rotation of the wheel about the steering axis
	hkReal m_steeringAngle;

protected:

	//
	// Collision detection phantom
	//

	// Phantom for collision queries
	class hkpAabbPhantom* m_phantom;

	// This hkpPhantomOverlapListener is added to the phantom to ignore the chassis.
	hkpRejectChassisListener m_rejectChassisListener;

	//
	// Cached state, including collision detection input, updated by the wheel each step before collide()
	//

	// Location of the wheel hardPoint in world space
	hkVector4 m_hardPointWs;

	// Farthest point on the wheel from the vehicle in the direction of the suspension.
	hkVector4 m_rayEndPointWs;

	// Current direction of the suspension (in world space).
	hkVector4 m_suspensionDirectionWs;

	// Axis in world space that the wheel is spinning around.
	hkVector4 m_spinAxisWs;

	// The current rotation of the steering wheel.
	hkQuaternion m_steeringOrientationCs;

	// Force applied to the wheel in the suspension direction
	hkReal m_suspensionForce;

	//
	// Cached state updated after collide()
	//

	// (contact normal) x (spin axis)
	hkVector4 m_forwardDirectionWs;

	// (m_forwardDirectionWs) x (contact normal)
	hkVector4 m_sideDirectionWs;

	// Position of the contact in local space. Used for calculating chassis velocity
	// at the contact point, and also necessary for updateVelocityError(), which is
	// called after the physics step but needs to make a calculation using the chassis'
	// center of mass from before the step. This is updated after calling collide()
	hkVector4 m_contactLocal;

	//
	// Collision detection output, updated by collide()
	//

	class hkContactPoint m_contactPoint;

	// The friction coefficient at the point of contact.
	hkReal m_contactFriction;

	// The ground body the vehicle is in contact. This value is HK_NULL if none of the wheels are in contact with the ground.
	hkpRigidBody* m_contactBody; //+nosave

	// The shapeKey hierarchy of the object at the point of contact.
	hkpShapeKey m_contactShapeKey[MAX_NUM_SHAPE_KEYS];

	// Current length of the suspension.
	hkReal m_currentSuspensionLength;

	/// The relative speed along the suspension normal.
	hkReal m_suspensionClosingSpeed;

	/// Scaling factor used to handle curb interaction.
	/// Forces along the contact normal are scaled by this factor.
	/// This ensures that the suspension force component is unscaled.
	/// Clipping is affected by hkpVehicleData::m_normalClippingAngle.
	hkReal m_suspensionScalingFactor;

public:

	//
	// Simulation output
	//

	// Final wheel angle [rad]
	hkReal m_spinAngle;

	// Assuming no slipping [rad/sec]
	hkReal m_noSlipIdealSpinVelocity;

	// Wheel Slipping linear velocity in forward direction [m/sec]
	hkReal m_forwardSlipVelocity;

	// Translational+Rotational energy lost by the wheel [Kilo Joules]
	hkReal m_skidEnergyDensity;

	// Total side force applied by the wheel [N]
	hkReal m_sideForce;

	// Total impulse applied to the chassis at m_hardPoint by this wheel's friction
	hkVector4 m_frictionImpulse;

	// Total impulse applied to the chassis at m_hardPoint by this wheel's suspension
	hkVector4 m_suspensionImpulse;

protected:

	//
	// Collision methods implemented by raycast / linear cast / custom subclasses
	//

	// Updates contact point and other collision info
	virtual void collide() = 0;
};

#endif // HK_Wheel_H

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
