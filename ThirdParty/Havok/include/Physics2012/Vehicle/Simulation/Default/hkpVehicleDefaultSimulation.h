/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKVEHICLE_SIMULATION_DEFAULT_hkVehicleDefaultSimulation_XML_H
#define HKVEHICLE_SIMULATION_DEFAULT_hkVehicleDefaultSimulation_XML_H

#include <Physics2012/Vehicle/Simulation/hkpVehicleSimulation.h>
#include <Physics/ConstraintSolver/VehicleFriction/hkpVehicleFriction.h>

extern const class hkClass hkpVehicleDefaultSimulationClass;

struct hkpVehicleFrictionSolverParams;
struct hkpVehicleFrictionSolverAxleParams;
class hkpVelocityAccumulator;

/// 
class hkpVehicleDefaultSimulation : public hkpVehicleSimulation
{
public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
	HK_DECLARE_REFLECTION();

	/// Default constructor
	hkpVehicleDefaultSimulation();

	//
	// Methods
	//

	virtual void init( hkpVehicleInstance* instance );
	virtual hkpVehicleSimulation* clone( hkpVehicleInstance* instance );
	virtual void simulateVehicle( hkpVehicleInstance* instance, const hkStepInfo& stepInfo, const SimulationInput& simulInput, hkpVehicleJobResults* vehicleJobResults );

	//
	// Members
	//

public: 
	hkpVehicleDefaultSimulation( hkFinishLoadedObjectFlag f )
		: hkpVehicleSimulation(f) 
		, m_frictionStatus(f)
		, m_frictionDescription(f)
	{ }

protected:

	hkpVehicleFrictionStatus m_frictionStatus;

	/// For the friction: const data
	hkRefPtr<class hkpVehicleFrictionDescription> m_frictionDescription;

	//
	// Setup accumulators
	//
	void prepareAxleParams( const hkpVehicleInstance& vehicleInstance, hkReal deltaTime, const hkArray<hkReal>& suspensionForceAtWheel, const hkArray<hkReal>& totalLinearForceAtWheel,hkpRigidBody* groundBody[], hkpVehicleFrictionSolverParams& frictionParams, const hkStepInfo& stepInfo,hkpVelocityAccumulator groundAccum[], hkpVelocityAccumulator groundAccumAtIntegration[] );
	void handleFixedGroundAccum( hkpRigidBody* ground, hkpVelocityAccumulator& accum );
	void getAxleParamsFromWheel( const hkpVehicleInstance& vehicleInstance, int w_it, hkReal linearForceAtWheel, hkReal suspensionForceAtWheel, hkReal estimatedCarSpeed, hkpVehicleFrictionSolverAxleParams& axle_params );
	void prepareChassisParams( const hkpVehicleInstance& vehicleInstance, const hkStepInfo& stepInfo, hkpVehicleFrictionSolverParams& frictionParams );

	//
	// Applying forces to accumulators
	//
	void applyAerodynamicDrag( const hkpVehicleInstance& vehicleInstance, const hkpVehicleAerodynamics::AerodynamicsDragOutput& aerodynamicsDragInfo, hkpVehicleFrictionSolverParams& frictionParams, const hkReal deltaTime );
	void applyVelocityDamping( const hkReal deltaTime, hkpVehicleFrictionSolverParams& frictionParams, const class hkpVehicleVelocityDamper* damper );
	void applySuspensionForces( const hkpVehicleInstance& vehicleInstance, hkReal deltaTime, const hkArray<hkReal>& suspensionForceAtWheel, hkpRigidBody* groundBody[], hkpVehicleFrictionSolverParams& frictionParams, hkVector4* suspensionForcesOnGround );
	void applyDampingToAxleAccumulators( const hkStepInfo& stepInfo, hkpRigidBody** groundBodies, hkpVehicleFrictionSolverParams& frictionParams, hkVector4* originalLinearVels, hkVector4* originalAngularVels );
	void applyDampingToChassisAccumulator( const hkStepInfo& stepInfo, hkpVelocityAccumulator& accumulator, const class hkpMotion* motion );
	void getExtraTorqueFactor( const hkpVehicleInstance& vehicleInstance, hkReal deltaTime, hkpVelocityAccumulator& accumulatorForChassis ) const;

	// 
	// FRICTION SOLVING
	//
	void applyFrictionSolver( const hkpVehicleInstance& vehicleInstance, const hkStepInfo& stepInfo, hkpVehicleFrictionSolverParams& frictionParams, hkpVehicleFrictionStatus& frictionStatus ); 

	// Gathering results
	void calcChassisVelocities( const hkpVehicleInstance& vehicleInstance, hkpVelocityAccumulator& accumulatorForChassis, hkpVehicleJobResults& vehicleResults );
	void calcGroundBodyVelocities( const hkpVehicleInstance& vehicleInstance, hkReal deltaTime, const hkpVehicleFrictionSolverAxleParams axleParams[], hkpRigidBody* groundBody[], hkpVehicleJobResults& vehicleResults, hkVector4* originalLinearVels, hkVector4* originalAngularVels );
};

#endif // HKVEHICLE_SIMULATION_DEFAULT_hkVehicleDefaultSimulation_XML_H

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
