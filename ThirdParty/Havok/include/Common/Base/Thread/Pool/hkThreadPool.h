/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_THREAD_POOL_H
#define HK_THREAD_POOL_H

#include <Common/Base/Thread/JobQueue/hkJobQueue.h>
#include <Common/Base/Thread/Task/hkTaskQueue.h>

struct hkTimerData;


/// Interface for managing a set of worker threads.
class HK_EXPORT_COMMON hkThreadPool : public hkReferencedObject
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE );

		virtual ~hkThreadPool() {}

		/// Begin processing jobs in the queue using the thread pool and return immediately (non-blocking call).
		virtual void processJobQueue( hkJobQueue* jobQueue, hkJobType firstJobType = HK_JOB_TYPE_MAX ) = 0;

		/// Begin processing tasks in the queue using the thread pool and return immediately (non-blocking call).
		/// /a waitingMode will be used by the worker threads when processing tasks from the task queue.
		/// Note: If the waiting mode is WAIT_UNTIL_QUEUE_CLOSED the queue must be closed before calling
		/// waitForCompletion() to prevent a deadlock.
		virtual void processTaskQueue(
			hkTaskQueue* taskQueue, hkTaskQueue::WaitingMode waitingMode = hkTaskQueue::WAIT_UNTIL_QUEUE_CLOSED ) = 0;

		/// Return true if any of the worker threads is currently processing a work load.
		virtual bool isProcessing() const = 0;

		/// Wait until all worker threads have finished processing the last work load.
		virtual void waitForCompletion() = 0;

		/// Get the number of threads in use.
		virtual int getNumThreads() const = 0;

		/// Set the number of threads in use.
		virtual void setNumThreads( int numThreads ) = 0;

		/// Get the timer data collected while processing.
		virtual void appendTimerData( hkArrayBase<hkTimerData>& timerDataOut, hkMemoryAllocator& alloc ) = 0;

		/// Clear the timer data. This must be done every frame or the timers will overrun.
		virtual void clearTimerData() = 0;

		/// Cause threads to garbage collect their memory immediately before signaling completion.
		/// Call this method before the processX() ones. Note this only applies to the next completion, it is reset to
		/// false when waitForCompletion() returns. This allows a subsequent garbage collection of the main heap
		/// (hkMemorySystem::garbageCollect) to recover more memory. This operation should only be called when needed
		/// since repopulating the thread local caches can be expensive.
		virtual void gcThreadMemoryOnNextCompletion() = 0;
};


#endif // HK_THREAD_POOL_H

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
