/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKVEHICLE_SIMULATION_hkVehicleSIMULATION_XML_H
#define HKVEHICLE_SIMULATION_hkVehicleSIMULATION_XML_H

#include <Physics2012/Vehicle/Manager/MultithreadedVehicle/hkpVehicleJobs.h>

/// 
class hkpVehicleSimulation : public hkReferencedObject
{
public:

	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_VEHICLE);
	HK_DECLARE_REFLECTION();

	// Input data for simulation
	struct SimulationInput
	{
		SimulationInput( const hkpVehicleAerodynamics::AerodynamicsDragOutput& aerodynamics,
			const hkArray<hkReal>& suspensions, const hkArray<hkReal>& linearForces )
			: aerodynamicsDragInfo(aerodynamics)
			, suspensionForceAtWheel(suspensions), totalLinearForceAtWheel(linearForces)
		{
		}

		const hkpVehicleAerodynamics::AerodynamicsDragOutput& aerodynamicsDragInfo; 
		const hkArray<hkReal>& suspensionForceAtWheel;
		const hkArray<hkReal>& totalLinearForceAtWheel;
	};

	//
	// Methods
	//

	// Initialize simulation-specific data
	virtual void init( hkpVehicleInstance* instance ) = 0;

	// Support vehicle cloning
	virtual hkpVehicleSimulation* clone( hkpVehicleInstance* instance ) = 0;

	// Used by the per-wheel simulation to register/unregister world post-simulation listeners
	virtual void addToWorld( hkpWorld* world ) {}
	virtual void removeFromWorld() {}

	// Calculate and apply forces to the chassis and the rigid bodies the vehicle is riding on.
	virtual void simulateVehicle( hkpVehicleInstance* instance, const hkStepInfo& stepInfo, const SimulationInput& simulInput, hkpVehicleJobResults* vehicleJobResults ) = 0;

	hkpVehicleSimulation(hkFinishLoadedObjectFlag flag) : hkReferencedObject(flag) {}

protected:

	hkpVehicleSimulation() {}
};

#endif // HKVEHICLE_SIMULATION_hkVehicleSIMULATION_XML_H

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
