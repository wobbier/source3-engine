/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKP_WRAPPED_CONSTRAINT_DATA_H
#define HKP_WRAPPED_CONSTRAINT_DATA_H

#include <Physics/Constraint/hkpConstraint.h>
#include <Physics/Constraint/Data/hkpConstraintData.h>


/// This abstract class is the base class for wrappers that add properties to a constraint data (e.g. breakable, malleable).
/// This class only implements a few methods of constraint data, and the default behavior is to forward the calls to the
/// wrapped data.
class hkpWrappedConstraintData : public hkpConstraintData
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);
		HK_DECLARE_REFLECTION();

		/// Creates a wrapped constraint data around the given constraint data
		hkpWrappedConstraintData( hkpConstraintData* constraintData );

		/// Serialization constructor
		hkpWrappedConstraintData( hkFinishLoadedObjectFlag f );

		/// Accessor to the wrapped constraint data.
		virtual const hkpConstraintData* getWrappedConstraintData() const;

		/// Accessor to the wrapped constraint data.
		virtual hkpConstraintData* accessWrappedConstraintData();

		//
		// hkpConstraintData interface
		//

		/// Get the atoms structure of the wrapped constraint.
		virtual void getConstraintInfo( ConstraintInfo& infoOut ) const HK_OVERRIDE;

		/// Return whether the wrapped constraint is valid.
		virtual hkBool isValid() const HK_OVERRIDE;

		/// Get information about the size of the runtime data needed.
		/// This calls the underlying data's getRuntimeInfo() method.
		virtual void getRuntimeInfo( hkBool wantRuntime, RuntimeInfo& infoOut )const HK_OVERRIDE;

		/// Access to the solver results in a generic way. Use getRuntimeInfo() to get the number of solver results.
		/// This calls the underlying data's getSolverResults() method.
		virtual hkpSolverResults* getSolverResults( hkpConstraintRuntime* runtime ) const HK_OVERRIDE;

		/// Deep clone the constraint.
		virtual hkpWrappedConstraintData* deepClone() const = 0;

	protected:

		/// Wrapped constraint data. Automatically reference counted.
		hkRefPtr<hkpConstraintData> m_constraintData;
};

#endif // HKP_WRAPPED_CONSTRAINT_DATA_H

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
