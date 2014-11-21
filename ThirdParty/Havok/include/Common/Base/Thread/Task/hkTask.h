/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_TASK_H
#define HK_TASK_H

#include <Common/Base/Object/hkReferencedObject.h>


/// Value used to indicate that there is no appropriate elf to process a given task.
#	define HK_INVALID_SPU_ELF	HK_NULL


/// A task is a self-contained unit of work that may be executed in any thread (worker or main).
/// Dependencies between tasks can be defined using a task graph (hkTaskGraph).
HK_CLASSALIGN16(class) HK_EXPORT_COMMON hkTask : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS );

		hkTask() {}

		/// Process the task. When this method returns the task is considered as finished and the dependencies of 
		/// other tasks on it fulfilled.
		virtual void process() = 0;

		/// Return the address of the SPU ELF that should process this task on PlayStation(R)3,
		/// or HK_INVALID_SPU_ELF if this task is not supported on SPU (default).
		/// Note: In the SPU simulator the task type (see hkTaskType) must be returned instead of the ELF address.
		virtual void* getSpuElf()
		{
			return HK_INVALID_SPU_ELF;
		}

		/// Get a name for the task. This is only used for debugging.
		/// Optionally also get some node attributes using the DOT language (e.g. "shape=diamond,style=rounded"),
		/// for use with hkTaskGraphUtil::printGraph().
		virtual void getName( hkStringBuf& nameOut, hkStringBuf* nodeAttributesOut = HK_NULL ) const
		{
			nameOut = "Unnamed";
			if( nodeAttributesOut ) { *nodeAttributesOut = ""; }
		}
};


/// This task type enum is used in the SPU simulator to dispatch tasks to the appropriate elf (see threadMain() in 
/// hkSpuSimulatorMain.cpp). It may be used as well to create unique frame IDs for the check determinism util (see 
/// hkCheckDeterminismUtil::Fuid). If your task does not require any of these things then it does not need to have
/// a task type here.
struct hkTaskType
{
	enum
	{
		// We start assigning values from 100 on to avoid overlapping with the values defined in hkJobType
		JOB_TYPE_MAX = 99,

		//
		// Physics tasks
		//
		HKNP_NARROW_PHASE_TASK,
		HKNP_SOLVER_TASK,
		HKNP_COLLISION_QUERY_TASK,
		HKNP_RAYCAST_TASK,

		//
		// Destruction tasks
		//
		HKND_CONTROLLER_TASK,
		HKND_PROJECT_MANIFOLD_TASK,

		//
		// AI tasks
		//
		HKAI_PATHFINDING_TASK,
		HKAI_VOLUME_PATHFINDING_TASK,
		HKAI_LOCAL_STEERING_TASK,
		HKAI_DYNAMIC_NAVMESH_TASK,

		// No ELFs associated with these, just for determinism fuids
		HKAI_NAVMESH_GENERATION_TASK,
		HKAI_NAVMESH_CLUSTERING_TASK,
		HKAI_NAVVOLUME_GENERATION_TASK,
		
	};
};


#endif // HK_TASK_H

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
