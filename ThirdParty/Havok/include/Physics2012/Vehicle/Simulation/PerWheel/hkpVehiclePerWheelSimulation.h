/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKVEHICLE_SIMULATION_SIMPLEPERWHEEL_hkpVehiclePerWheelSimulation_XML_H
#define HKVEHICLE_SIMULATION_SIMPLEPERWHEEL_hkpVehiclePerWheelSimulation_XML_H

#include <Physics2012/Vehicle/Simulation/hkpVehicleSimulation.h>
#include <Physics/Constraint/Data/WheelFriction/hkpWheelFrictionConstraintData.h>
#include <Physics2012/Dynamics/World/Listener/hkpWorldPostSimulationListener.h>

extern const class hkClass hkpVehiclePerWheelSimulationClass;

// forward internal structs declarations
struct PerWheelSimParams;

// --------------------------------------------------------------------------------------------------------
/// This class performs a basic per-wheel simulation of the friction and other forces in the car
// --------------------------------------------------------------------------------------------------------
class hkpVehiclePerWheelSimulation : public hkpVehicleSimulation, public hkpWorldPostSimulationListener
{
public:
	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
	HK_DECLARE_REFLECTION();

	hkpVehiclePerWheelSimulation();
	hkpVehiclePerWheelSimulation( hkFinishLoadedObjectFlag f )
	: hkpVehicleSimulation(f) 
	, m_wheelData(f)
	{ }
	
	~hkpVehiclePerWheelSimulation();

	virtual void init( hkpVehicleInstance* instance );
	virtual hkpVehicleSimulation* clone( hkpVehicleInstance* instance );
	virtual void addToWorld( hkpWorld* world );
	virtual void removeFromWorld();
	virtual void simulateVehicle( hkpVehicleInstance* instance, const hkStepInfo& stepInfo, const SimulationInput& simulInput, hkpVehicleJobResults* vehicleJobResults );

	virtual void postSimulationCallback( hkpWorld* world );

protected:
	void applySuspensionForces( const hkStepInfo& stepInfo, const SimulationInput& simulInput );
	void applyAerodynamicForces( const hkStepInfo& stepInfo, const SimulationInput& simulInput );
	void setupFriction( const hkStepInfo& stepInfo, const SimulationInput& simulInput );
	void computeAngularChassisAcceleration( const hkVector4& worldLinearFrictionImpulse, const hkVector4& contactLocal, hkVector4& worldAngularVelocityDeltaOut );
	void removeFrictionConstraint(int w_it);

public:

	// Vehicle instance that this simulation belongs to (weak reference)
	hkpVehicleInstance* m_instance;	

	// World that the vehicle has been added to
	hkpWorld* m_world; //+nosave

	// Reduce the spin velocity of slipping wheels
	hkReal m_slipDamping;

	// Scale impulses applied by wheels to objects that they're in contact with
	hkReal m_impulseScaling;

	// The maximum impulse that can be applied by a wheel to the body it's in contact with per step
	hkReal m_maxImpulse;

	// Whether to use the velocity of dynamic objects that the wheels are in contact with for friction calculations.
	// Setting it true gives more accurate behavior when the car is on a large dynamic platform, or driving over debris
	// resting on a keyframed surface. Setting it false improves stability when driving over fast-moving debris.
	hkReal m_takeDynamicVelocity;

	// Scaling factor for resistance force when climbing curbs
	hkReal m_curbDamping;

	// Internal information about the wheel
	struct WheelData
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT, WheelData );
		HK_DECLARE_REFLECTION();

		hkpWheelFrictionConstraintAtom::Axle m_axle;	// One "axle" per wheel, no support for shared axle
		hkpWheelFrictionConstraintData m_frictionData;
		hkpConstraintInstance* m_frictionConstraint; //+nosave

		// Temporary data used in the post sim callback
		hkVector4 m_forwardDirectionWs;
		hkVector4 m_sideDirectionWs;
		hkVector4 m_contactLocal;

		WheelData()
		{
			m_frictionConstraint = HK_NULL;
		}

		WheelData(hkFinishLoadedObjectFlag f)
		: m_axle(f)
		, m_frictionData(f)
		{
		}
	};
	hkArray<WheelData> m_wheelData;
};

#endif // HKVEHICLE_SIMULATION_SIMPLEPERWHEEL_hkpVehiclePerWheelSimulation_XML_H

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
