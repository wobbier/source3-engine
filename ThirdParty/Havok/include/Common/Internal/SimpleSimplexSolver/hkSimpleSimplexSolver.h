/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_SIMPLE_SIMPLEX_SOLVER_H
#define HK_SIMPLE_SIMPLEX_SOLVER_H


/// The input structure for the simplex solver
struct HK_EXPORT_COMMON hkSimpleSimplexSolverInput
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT_SOLVER, hkSimpleSimplexSolverInput );

	inline hkSimpleSimplexSolverInput();

		/// The position of the particle
	hkVector4 m_position;

		/// The velocity of the particle
	hkVector4 m_velocity;

		/// The timeslice
	hkReal	  m_deltaTime;

		/// The minimum time we should walk before exiting
	hkReal	  m_minDeltaTime;

		/// The input array of surface constraints
	const hkVector4* m_constraints;

		/// The number of constraints in the array
	int	m_numConstraints;
};


/// Contains the simplex results for each surface constraint
struct HK_EXPORT_COMMON hkSimpleSimplexPlaneInteraction
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT_SOLVER, hkSimpleSimplexPlaneInteraction );

	/// The status of the internal solving. Note: this list is order dependent
	enum hkStatus
	{
			/// OK.
		HK_STATUS_OK = 0,
			/// 3D Failure.
		HK_STATUS_3D_FAILURE = 1,
			/// 2D Failure.
		HK_STATUS_2D_FAILURE = 2
	};

	hkStatus  m_status;

		/// If m_touched is set to true, then the characterController touched this plane
	hkUint8      m_touched;

		/// The time spent in contact with this surface
	hkReal    m_surfaceTime;

	hkReal    m_penaltyDistance;	// for internal use only, needed to avoid endless loops

};

/// Output structure for the simplex solver.
struct HK_EXPORT_COMMON hkSimpleSimplexSolverOutput
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CONSTRAINT_SOLVER, hkSimpleSimplexSolverOutput );

		/// Position.
	hkVector4		  m_position;

		/// Velocity.
	hkVector4		  m_velocity;

		/// The time solved to if the output m_deltaTime is < the input m_deltaTime then the simplex hit a surface.
		/// Continue to iterate to complete the timestep
	hkReal			  m_deltaTime;

		/// The output interaction array - this should be the same size as the input constraints array
	hkSimpleSimplexPlaneInteraction* m_planeInteractions;
};

extern "C"
{
		// Solves for the motion of a particle in a set on dynamic plane constraints
	HK_EXPORT_COMMON void HK_CALL hkSimpleSimplexSolverSolve( const hkSimpleSimplexSolverInput& input, hkSimpleSimplexSolverOutput& output );

}

hkSimpleSimplexSolverInput::hkSimpleSimplexSolverInput()
{
	m_position.setZero();
	m_velocity.setZero();
}

#endif //HK_SIMPLE_SIMPLEX_SOLVER_H

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
