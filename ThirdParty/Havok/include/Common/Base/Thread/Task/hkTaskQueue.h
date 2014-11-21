/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_TASK_QUEUE_H
#define HK_TASK_QUEUE_H

#include <Common/Base/Thread/Task/hkTaskGraph.h>
#include <Common/Base/Thread/Task/hkTaskScheduler.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
#include <Common/Base/Container/MinHeap/hkMinHeap.h>
#include <Common/Base/Container/FreeListArray/hkFreeListArray.h>
#include <Common/Base/Thread/Semaphore/hkSemaphore.h>

// Uncomment this to enable timers
//#define HK_ENABLE_TASK_QUEUE_TIMERS


/// A queue used to process task graphs (hkTaskGraph), by providing tasks from any number of graphs to any number of
/// threads for processing. Tasks are provided only when they have no unfulfilled dependencies, so threads may have to
/// wait for tasks when there are none immediately available.
/// The normal work flow is as follows:
/// -# A thread adds a graph to the queue via addGraph(), becoming the owner of the graph.
/// -# Threads get tasks from the queue via finishTaskAndGetNext(), process them calling hkTask::process() and
/// report them as finished in the queue using finishTask() or finishTaskAndGetNext(). When a task is finished
/// any dependencies of other tasks on it are marked as fulfilled, potentially making them available for processing.
/// -# The owner thread either polls the queue to see if its graph has been finished with isGraphFinished() or joins
/// processing the tasks in the graph with finishTaskAndGetNextInGraph().
/// -# Once the graph is finished, the owner thread calls removeGraph().
class HK_EXPORT_COMMON hkTaskQueue : public hkReferencedObject
{
	public:

		/// Unique identifier for a graph within the queue.
		HK_DECLARE_HANDLE(GraphId, hkUint8, 0xFF);

		/// Unique identifier for a task within a graph.
		typedef hkTaskGraph::TaskId TaskId;

		/// Task multiplicity, i.e. number of times a task must be processed.
		typedef hkTaskScheduler::Multiplicity Multiplicity;

		/// Task priority. The lower the number the higher the priority (0 = maximum priority). Tasks with the same
		/// priority will be ordered by their task ID (lower IDs are executed before higher ones).
		typedef hkUint8 Priority;

		enum
		{
			/// Maximum number of graphs that can be processed simultaneously by the queue.
			MAX_GRAPHS = 8
		};

		/// Controls the behavior of methods that get tasks from the queue, when there are no tasks immediately
		/// available.
		enum WaitingMode
		{
			/// Return when all tasks have been finished, or the queue is closed.
			WAIT_UNTIL_ALL_TASKS_FINISHED,

			/// Return when all tasks have been finished or are being processed by other threads, or the queue is closed.
			/// Note: There may still be tasks being processed by other threads when the method returns.
			WAIT_UNTIL_NO_TASKS_REMAIN,

			/// Return when the queue is closed.
			WAIT_UNTIL_QUEUE_CLOSED,

			/// Return immediately.
			DONT_WAIT
		};

		/// Return value of methods that get tasks from the queue.
		enum GetNextTaskResult
		{
			/// Obtained a task.
			TASK_OBTAINED,

			/// If waiting mode is WAIT_UNTIL_NO_TASKS_REMAIN, this means that there are no more remaining tasks to
			/// obtain although there may still be tasks being processed.
			/// If waiting mode is DONT_WAIT, this indicates that no task is immediately available.
			NO_TASK_AVAILABLE,

			/// All tasks in the specified graph have finished processing.
			GRAPH_FINISHED,

			/// The queue has been closed.
			/// There may still be unprocessed tasks in the queue when the method returns.
			QUEUE_CLOSED
		};

		/// Queue entry.
		/// Contains the information required to sort tasks and obtain the original task pointer (see getTask()).
		struct HK_EXPORT_COMMON PrioritizedTask
		{
			PrioritizedTask() : m_priorityAndTaskId(0), m_graphId(0), m_reaminingMultiplicity(0) {}
			HK_FORCE_INLINE void setPriorityAndTaskId(Priority priority, TaskId taskId)
			{
				m_priorityAndTaskId = (priority << 16) | taskId.value();
			}

			HK_FORCE_INLINE TaskId getTaskId() const { return TaskId(m_priorityAndTaskId & 0xFFFF); }

			HK_FORCE_INLINE hkBool32 operator<(const PrioritizedTask& other) const
			{
				return (this->m_priorityAndTaskId < other.m_priorityAndTaskId);
			}

			hkUint32 m_priorityAndTaskId;
			GraphId m_graphId;

			/// Number of times the task must be obtained before removing it from the queue.
			Multiplicity m_reaminingMultiplicity;
		};

	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE );

		/// Constructor.
		/// The spin count will be used when acquiring the queue's critical section. Optimal values vary depending on
		/// the platform and use case. In case of doubt, use the default.
		hkTaskQueue( int spinCount = 0 );

		/// Add a task graph.
		/// Any of its tasks without unfulfilled dependencies will be immediately available for processing.
		GraphId addGraph(
			const hkTaskGraph* taskGraph, Priority priority,
			hkTaskScheduler::ExecutionPolicy executionPolicy = hkTaskScheduler::EXECUTION_POLICY_DEFAULT );

		/// Remove a task graph.
		/// Must be called by the thread which added the graph, after all tasks in the graph have finished processing.
		void removeGraph( GraphId graphId );

		/// Process tasks from all graphs.
		/// /a waitingMode indicates the desired behavior when there are no tasks immediately available for processing.
		void processTasks( WaitingMode waitingMode );

		/// Process tasks from a single graph.
		/// /a waitingMode indicates the desired behavior when there are no tasks immediately available for processing.
		/// Notes:
		///  - WAIT_UNTIL_QUEUE_CLOSED is not supported.
		///  - Currently this can only be called by the thread that added the given graph.
		void processGraph( GraphId graphId, WaitingMode waitingMode );

		/// Notifies all threads waiting on the queue of its imminent closure and marks the queue as closed so any
		/// subsequent calls to obtain tasks from the queue will fail with QUEUE_CLOSED result.
		void close();

		/// Re-opens the queue after is has been closed with a call to close().
		/// Returns true if the queue is not already open, and returns false if otherwise.
		HK_FORCE_INLINE bool open();

		/// Returns true if the queue is open.
		HK_FORCE_INLINE bool isOpen();

		/// Non-blocking check whether a graph has been finished.
		/// Can only be called by the thread that added the graph.
		HK_FORCE_INLINE hkBool32 isGraphFinished( GraphId graphId ) const;

		/// Access the task referenced by a PrioritizedTask.
		HK_FORCE_INLINE hkTask* getTask( const PrioritizedTask& prioritizedTask ) const;

		/// Replaces an inactive task with an active one in a registered task graph.
		/// The active task will have the same dependencies as the inactive one it replaces.
		void activateTask( GraphId graphId, TaskId taskId, hkTask* task );	

		//
		// Advanced
		//

		/// Marks a processed task as finished if /a finishTask is not NULL and gets the next available task for CPU.
		GetNextTaskResult finishTaskAndGetNext(
			PrioritizedTask* nextTask, WaitingMode waitingMode, const PrioritizedTask* finishedTask = HK_NULL );

		/// Marks a processed task as finished if /a finishTask is not NULL and gets the next available task in the
		/// given graph. Can only be called by the thread that owns the graph.
		/// NOTE: currently the task returned may not be the one with the highest priority as the min-heap where all
		/// available tasks are stored is traversed linearly until a task belonging to the graph is found.
		GetNextTaskResult finishTaskAndGetNextInGraph(
			PrioritizedTask* nextTask, WaitingMode waitingMode, GraphId graphId, const PrioritizedTask* finishedTask = HK_NULL );

		/// Marks a processed task as finished if /a finishTask is not NULL and gets the next available task for SPU.
		/// NOTE: this method is meant to be called from a PPU thread that will take care of processing the task on SPU.
		/// For that reason, tasks with multiplicity larger than 1 will be returned only once and the caller will be
		/// responsible for processing them the required number of times (i.e. PrioritizedTask::m_reaminingMultiplicity
		/// times). SPU tasks still need to be finished as many times as their multiplicity.
		GetNextTaskResult finishTaskAndGetNextForSpu(
			PrioritizedTask* nextTask, WaitingMode waitingMode, const PrioritizedTask* finishedTask = HK_NULL );

		/// Must be called for every task obtained from the queue after it has been processed.
		void finishTask( const PrioritizedTask& finishedTask );

	protected:

		/// Used in some methods to indicate if it is necessary to lock the queue.
		enum LockMode
		{
			DONT_LOCK,
			LOCK
		};

		/// The type of task that finishTaskAndGetNextImpl() should return.
		enum TaskType
		{
			CPU_TASK,
			CPU_TASK_IN_GRAPH,
			SPU_TASK
		};

		/// Information about a queued graph.
		struct HK_EXPORT_COMMON GraphInfo
		{
			public:

				/// Operations for the free list array where graphs are stored.
				struct FreeListArrayOperations
				{
					HK_FORCE_INLINE static void setEmpty(GraphInfo& graphInfo, hkUint32 next);
					HK_FORCE_INLINE static hkUint32 getNext(const GraphInfo& graphInfo);
					HK_FORCE_INLINE static hkBool32 isEmpty(const GraphInfo& graphInfo);
				};

			public:

				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE_CLASS, hkTaskQueue::GraphInfo);

				GraphInfo() : m_numRemainingTasks(0), m_ownerWaitingMode(DONT_WAIT), m_isEmpty(false) {}

				/// Checks that the current thread owns the graph. Debug only.
				HK_FORCE_INLINE void checkThreadOwnership() const;

			public:

				/// Graph scheduler.
				hkTaskScheduler m_scheduler;

				/// Number of tasks that have not been obtained yet.
				int m_numRemainingTasks;

				/// Priority of the tasks in the graph.
				Priority m_priority;

				/// Indicates if the graph owner is waiting on the graph signal.
				WaitingMode m_ownerWaitingMode;

				/// Used by the free list array to keep track of allocated elements.
				hkBool m_isEmpty;

				/// ID of the thread that added the graph to the queue.
				HK_DEBUG_ONLY_MEMBER(int, m_ownerThreadId);
		};

		/// Free list array used to store the graph infos
		typedef hkFreeListArray< GraphInfo, GraphId, MAX_GRAPHS, GraphInfo::FreeListArrayOperations > FreeListArray;

		/// Task used as a placeholder for inactive tasks.
		class EmptyTask : public hkTask
		{
			public:

				HK_DECLARE_CLASS_ALLOCATOR(hkTaskQueue::EmptyTask);
				virtual void process() HK_OVERRIDE {};
		};

	protected:

		/// Read-only access to a graph's information.
		HK_FORCE_INLINE const GraphInfo& getGraphInfo( GraphId graphId ) const;

		/// Read-write access to a graph's information.
		HK_FORCE_INLINE GraphInfo& accessGraphInfo( GraphId graphId );

	protected:

		/// Information about graphs in the queue.
		FreeListArray m_graphInfos;

		/// Signals used by graphs for synchronization with their owner thread.
		
		
		hkSemaphore m_graphSignals[MAX_GRAPHS];

		/// Min heap holding all available CPU tasks.
		hkMinHeap<PrioritizedTask> m_queue;

		/// Min heap holding all available SPU tasks.
		hkMinHeap<PrioritizedTask> m_queueSpu;

		/// Critical section controlling access to the queue.
		hkCriticalSection m_queueLock;

		/// Task returned when a null task is found (representing an inactive task).
		EmptyTask m_emptyTask;

		/// Number of threads currently waiting on the task available semaphore.
		int m_numThreadsWaiting;

		/// Number of tasks that have not been obtained yet.
		int m_numRemainingTasks;

		/// Semaphore used to notify threads of newly available tasks.
		hkSemaphore m_taskAvailableSignal;

		/// Semaphore used to notify the PPU thread that launches SPU ELFs of newly available tasks.
		hkSemaphore m_taskAvailableSignalSpu;

		/// Indicates if the SPUs are waiting for more tasks.
		hkBool m_isWaitingSpu;

		/// Flag to indicate if the task queue has been closed.
		hkBool m_isQueueOpen;

		/// Indicates if there is a thread waiting until there are no more tasks remaining.
		hkBool m_signalWhenNoTasksRemaining;
};

#include <Common/Base/Thread/Task/hkTaskQueue.inl>

#endif // HK_TASK_QUEUE_H

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
