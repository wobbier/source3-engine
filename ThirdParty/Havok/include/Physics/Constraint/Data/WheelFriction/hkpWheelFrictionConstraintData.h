/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_WheelFrictionConstraintData_H
#define HK_WheelFrictionConstraintData_H

#include <Physics/Constraint/Data/hkpConstraintData.h>

class hkpWheelFrictionConstraintData : public hkpConstraintData
{
public:

	struct Runtime
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpWheelFrictionConstraintData::Runtime );
		HK_DECLARE_REFLECTION();
		// No solver results, they're stored in the atom
	};

	struct Atoms
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_DYNAMICS, hkpWheelFrictionConstraintData::Atoms );
		HK_DECLARE_REFLECTION();

		Atoms() {}
		Atoms(hkFinishLoadedObjectFlag f) : m_transforms(f), m_friction(f) {}

		const hkpConstraintAtom* getAtoms() const
		{
			return &m_transforms;
		}

		int getSizeOfAllAtoms() const
		{
			return hkGetByteOffsetInt(getAtoms(), &m_friction+1);
		}

		struct hkpSetLocalTransformsConstraintAtom	m_transforms;
		struct hkpWheelFrictionConstraintAtom		m_friction;
	};

	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
	HK_DECLARE_REFLECTION();

	hkpWheelFrictionConstraintData() { m_atoms.m_friction.m_axle = HK_NULL; }
	hkpWheelFrictionConstraintData(hkFinishLoadedObjectFlag f) : hkpConstraintData(f), m_atoms(f) {}

	void init( hkpWheelFrictionConstraintAtom::Axle* axle, hkReal radius );

	hkBool isValid() const;
	int getType() const;
	static inline Runtime* HK_CALL getRuntime( hkpConstraintRuntime* runtime );
	void getRuntimeInfo( hkBool wantRuntime, hkpConstraintData::RuntimeInfo& infoOut ) const;
	void getConstraintInfo( hkpConstraintData::ConstraintInfo& infoOut ) const;

	void setInWorldSpace( const hkTransform& bodyATransform, const hkTransform& bodyBTransform, const hkVector4& contact, const hkVector4& forward, const hkVector4& side );
	void setMaxFrictionForce(hkReal maxFrictionForce);
	void setTorque(hkReal torque);
	void setInvInertia(hkReal invInertia);
	void setImpulseScaling(hkReal impulseScaling, hkReal impulseMax);

	// Get or set the spin velocity of the wheel from the wheel friction atom
	hkReal getSpinVelocity();
	void setSpinVelocity(hkReal spinVelocity);

	// Call after the physics step and before resetSolverData() to get the impulse applied by the solver
	hkReal getForwardFrictionImpulse();
	hkReal getSideFrictionImpulse();
	hkReal getForwardSlipImpulse();
	hkReal getSideSlipImpulse();

	// Reset solver outputs before each physics step
	void resetSolverData();

	//Create an Atoms structure and align it on a 16 byte boundary
	HK_ALIGN_REAL( struct Atoms m_atoms );
};

#endif // HK_WheelFrictionConstraintData_H

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
