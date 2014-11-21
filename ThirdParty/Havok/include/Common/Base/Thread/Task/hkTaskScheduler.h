/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_TASK_SCHEDULER_H
#define HK_TASK_SCHEDULER_H

#include <Common/Base/Thread/Task/hkTaskGraph.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>

class hkTask;


/// Class for handling the orderly execution of the tasks in a graph making sure dependencies are respected.
/// This class is not thread-safe, concurrent use must be synchronized externally.
class HK_EXPORT_COMMON hkTaskScheduler
{
	public:

		typedef hkTaskGraph::TaskId TaskId;

		typedef hkUint8 Multiplicity;

		/// Task ID and multiplicity encoded in a single 32-bit value in the following way:
		/// (multiplicity << 16) | taskId
		typedef hkUint32 TaskIdAndMultiplicity;

		/// Controls the relative priorities of tasks within a task graph.
		/// Execution modes different from EXECUTION_POLICY_DEFAULT will change the original task IDs.
		enum ExecutionPolicy
		{
			/// Tasks with lowest task ID are executed first.
			EXECUTION_POLICY_DEFAULT,

			/// Tasks with the lowest depth are executed first.
			EXECUTION_POLICY_BREADTH_FIRST,

			/// Tasks with the highest depth are executed first.
			EXECUTION_POLICY_DEPTH_FIRST,
		};

	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE_CLASS, hkTaskScheduler);

		/// Initializes the scheduler for processing of the given task graph.
		void init(const hkTaskGraph* taskGraph, ExecutionPolicy executionPolicy = EXECUTION_POLICY_DEFAULT);

		/// Returns the next available task.
		TaskIdAndMultiplicity getNextTask();

		/// Activate an inactive task (originally added to the graph with a NULL task pointer).
		void activateTask(TaskId taskId, hkTask* task);

		/// Translates a task ID into a task.
		HK_FORCE_INLINE hkTask* getTask(TaskId taskId) const
		{
			return m_taskInfos[taskId.value()].m_task;
		}

		/// Mark a task as processed.
		hkBool32 finishTask(TaskId taskId);

		///////////////
		// Accessors

		HK_FORCE_INLINE int getNumAvailableTasks() const { return m_numAvailableTasks; }
		HK_FORCE_INLINE hkUint32 getNumUnfinishedTasks() const { return m_numUnfinishedTasks; }

	protected:

		// Make sure that TaskId and Multiplicity fit in an TaskIdAndMultiplicity
		HK_COMPILE_TIME_ASSERT(sizeof(TaskId) <= 2 && sizeof(Multiplicity) <= 2);

		enum
		{
			MAX_DEPENDENCIES = 0xFFFF,
			MAX_MULTIPLICITY = (1 << (8 * sizeof(Multiplicity))) - 1
		};

		/// Information about a task's dependencies and state of completion.
		struct TaskInfo
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, TaskInfo );

			HK_FORCE_INLINE void set(const hkTaskGraph::TaskInfo& taskInfo)
			{
				HK_ASSERT2(0x4223fb44, taskInfo.m_multiplicity <= MAX_MULTIPLICITY, "Multiplicity is too large");
				m_task = taskInfo.m_task;
				m_numUnfinishedParents = 0;
				m_numChildren = 0;
				m_reaminingMultiplicity = (Multiplicity) taskInfo.m_multiplicity;
			}

			hkTask* m_task;
			int m_firstChildIndex;
			TaskId::Type m_numUnfinishedParents;
			TaskId::Type m_numChildren;
			Multiplicity m_reaminingMultiplicity;
		};

		struct HK_EXPORT_COMMON TaskDepth
		{
			static HK_FORCE_INLINE bool HK_CALL lessDepthFirst(const TaskDepth& a, const TaskDepth& b)
			{ return b.m_depth < a.m_depth; }
			static HK_FORCE_INLINE bool HK_CALL lessBreadthFirst(const TaskDepth& a, const TaskDepth& b)
			{ return a.m_depth < b.m_depth; }

			TaskId m_taskId;
			int m_depth;
		};

	protected:

		void calculateTaskDepths(hkArrayBase<TaskDepth>& taskDepths);
		int calculateTaskDepthsRec(TaskDepth& node, hkArrayBase<TaskDepth>& taskDepths);
		void setDepthFirstExecOrderRec(
			TaskId taskId, int& newId, const hkArrayBase<int>& taskIdToDepthId, hkArrayBase<TaskDepth>& taskDepths,
			hkArrayBase<int>& remapTable);
		void reorderTasksForExecutionPolicy(ExecutionPolicy executionPolicy);
		void reshuffleTasks(hkArrayBase<int>& remapTable);

	protected:

		/// Tasks information.
		hkArray<TaskInfo> m_taskInfos;

		/// List of all task's children sorted by parent.
		hkArray<TaskId> m_children;

		/// Circular buffer with the tasks currently available to be obtained via getNextTask().
		hkArray<TaskId> m_availableTasks;

		/// Position in the available tasks buffer of the first available task.
		int m_nextTask;

		/// Number of available tasks.
		int m_numAvailableTasks;

		/// Number of tasks that have not been finished yet as many times as their multiplicity.
		hkUint32 m_numUnfinishedTasks;
};

#endif // HK_TASK_SCHEDULER_H

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
