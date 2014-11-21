/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_TASK_GRAPH_H
#define HK_TASK_GRAPH_H

#include <Common/Base/Thread/Task/hkTask.h>
#include <Common/Base/Types/hkHandle.h>


/// A set of tasks to be processed, with optional dependencies between them.
/// To process a task graph, you can add it to a hkTaskQueue and have your threads call the methods there,
/// or you could convert it to a form that suits your own scheduling system.
struct HK_EXPORT_COMMON hkTaskGraph
{
	public:

		/// Task identifier.
		HK_DECLARE_HANDLE( TaskId, hkUint16, 0xFFFF );

		/// A node in the graph, describing a task and its multiplicity.
		struct HK_EXPORT_COMMON TaskInfo
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, TaskInfo );

			hkRefPtr<hkTask> m_task;	///< The task to be processed. Can be HK_NULL.
			int m_multiplicity;			///< The number of times that the task must be processed.
		};

		/// An edge in the graph, describing a dependency between two tasks.
		struct HK_EXPORT_COMMON Dependency
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, Dependency );

			TaskId m_parentId;	///< The task that must be processed first.
			TaskId m_childId;	///< The task that must be processed after the parent is finished.
		};

	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, hkTaskGraph );

		/// Add a task to the graph with the given multiplicity.
		/// A placeholder can be added by passing in a HK_NULL task pointer and overriding it later.
		/// The multiplicity is the number of times that the task must be processed before it is considered
		/// to be finished and its dependent tasks are made available.
		HK_FORCE_INLINE TaskId addTask( hkTask* task, int multiplicity = 1 );

		/// Same as addTask but does not increment the reference count on the task.
		/// However the reference count will be removed once the task is finished.
		HK_FORCE_INLINE TaskId addTaskAndDontIncrementReference( hkTask* task, int multiplicity = 1 );

		/// Add a parent-child dependency between two tasks.
		HK_FORCE_INLINE void addDependency( TaskId parentId, TaskId childId );

		/// Clear all tasks and dependencies from the graph.
		HK_FORCE_INLINE void clear();

		/// Get read only access to the tasks array.
		HK_FORCE_INLINE const hkArray<TaskInfo>& getTasks() const { return m_tasks; }

		/// Get read only access to the dependencies array.
		HK_FORCE_INLINE const hkArray<Dependency>& getDependencies() const { return m_dependencies; }

		/// Allocate space for the specified number of tasks and dependencies (calls hkArray::reserve)
		HK_FORCE_INLINE void reserve( int numTasks, int numDependencies = 0);

	protected:

		/// The nodes of the graph.
		/// Any available nodes (those with no unfinished parents) are expected to be processed in ascending order.
		hkArray<TaskInfo> m_tasks;

		/// The edges of the graph.
		hkArray<Dependency> m_dependencies;
};

#include <Common/Base/Thread/Task/hkTaskGraph.inl>

#endif // HK_TASK_GRAPH_H

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
