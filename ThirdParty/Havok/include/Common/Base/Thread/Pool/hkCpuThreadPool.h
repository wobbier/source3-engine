/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_THREAD_POOL_CPU_H
#define HK_THREAD_POOL_CPU_H

#include <Common/Base/Thread/Pool/hkThreadPool.h>
#include <Common/Base/Thread/Thread/hkThread.h>
#include <Common/Base/Thread/Semaphore/hkSemaphore.h>

class hkWorkerThreadContext;


/// Construction info for hkCpuThreadPool
struct HK_EXPORT_COMMON hkCpuThreadPoolCinfo
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_UTILITIES, hkCpuThreadPoolCinfo );

	hkCpuThreadPoolCinfo();

	/// The number of threads to create.
	/// Defaults to 1.
	int m_numThreads;

	/// The hardware thread IDs to use for each thread, if applicable.
	/// On Windows, SetThreadIdealProcessor is called for each thread. It will use {1,2...,(numProcessors-1),0} by default if this array is empty.
	/// On XBox360, XSetThreadProcessor is called for each thread. It will use {2,4,1,3,5,0} by default if this array is empty.
	/// These defaults assume that you are using core 0 as your main calling thread.
	hkArray<int> m_hardwareThreadIds;

	/// The program stack size to use for each thread, if applicable.
	/// On Windows and Xbox360, this defaults to 0, meaning the thread inherits the executable's stack size.
	/// On PlayStation(R)3, this defaults to 256K.
	/// On PlayStation(R)4, this defaults to 512K in Debug/Dev configurations and 128K in Release.
	/// This has no effect on other platforms (e.g., posix).
	int m_stackSize;

	/// The buffer size to allocate to each thread for collecting timer information.
	/// To view timers in the Visual Debugger, you must set this buffer size to a non zero value.
	/// 2MB is a good recommended size. Smaller buffers are ok, but you may lose some timer info.
	/// Defaults to 0, which means that timers will be disabled.
	int m_timerBufferPerThreadAllocation;

	/// The thread name to be passed to each hkThread::startThread().
	const char* m_threadName;
};


/// A CPU implementation of the hkThreadPool interface. It can be used to process a job or a task queue or to process
/// other types of work loads providing a custom worker function to the processWorkLoad() method.
class HK_EXPORT_COMMON hkCpuThreadPool : public hkThreadPool
{
	public:

		/// Function to be run on each of the worker threads when a work load is processed via a processWorkLoad() call.
		typedef void (HK_CALL *WorkerFunction)(void* workLoad);

		/// Determines whether to start the worker threads on construction of the thread pool or manually via a
		/// startTreads() call. The later option is usefull when deriving from hkCpuThreadPool to prevent threads from
		/// starting before the derived class constructor finishes.
		enum ThreadStartMode
		{
			START_THREADS_ON_CONSTRUCTION,
			START_THREADS_MANUALLY
		};

	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE);

		/// Constructor.
		/// This method calls hkReferencedObject::setLockMode( hkReferencedObject::LOCK_MODE_MANUAL);
		hkCpuThreadPool(
			const hkCpuThreadPoolCinfo& cinfo, ThreadStartMode threadStartMode = START_THREADS_ON_CONSTRUCTION);

		/// Destructor.
		/// This method calls hkReferencedObject::setLockMode( hkReferencedObject::LOCK_MODE_NONE);
		~hkCpuThreadPool();

		/// Starts the worker threads. Call only if the thread pool has been constructed with
		/// START_THREADS_MANUALLY thread start mode.
		void startThreads(const hkCpuThreadPoolCinfo& cinfo);

		/// Sets the worker function and work load and wakes up all worker threads, returning immediately.
		void processWorkLoad( WorkerFunction workerFunction, void* workLoad );

		//
		// hkThreadPool interface
		//

		virtual void processJobQueue( hkJobQueue* jobQueue, hkJobType notUsed = HK_JOB_TYPE_MAX ) HK_OVERRIDE;
		virtual void processTaskQueue(
			hkTaskQueue* taskQueue, hkTaskQueue::WaitingMode waitingMode = hkTaskQueue::WAIT_UNTIL_QUEUE_CLOSED )
			HK_OVERRIDE;
		virtual void waitForCompletion() HK_OVERRIDE;
		virtual bool isProcessing() const HK_OVERRIDE;
		virtual void appendTimerData( hkArrayBase<hkTimerData>& timerDataOut, hkMemoryAllocator& alloc ) HK_OVERRIDE;
		virtual void clearTimerData() HK_OVERRIDE;
		virtual int getNumThreads() const HK_OVERRIDE;
		virtual void setNumThreads( int numThreads ) HK_OVERRIDE;
		virtual void gcThreadMemoryOnNextCompletion() HK_OVERRIDE;

		static void HK_CALL setThreadAffinity(int hardwareThreadId);

	protected:

		/// Used internally to pass in a task queue and the waiting mode to the processWorkLoad() method.
		struct TaskQueueWorkLoad
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, TaskQueueWorkLoad );

			hkTaskQueue* m_taskQueue;
			hkTaskQueue::WaitingMode m_waitingMode;
		};

		/// State data per worker thread
		struct ThreadData
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ENTITY, ThreadData);

			ThreadData();

			/// Pointer to the data shared between threads.
			hkCpuThreadPool* m_threadPool;

			/// System handle to the thread.
			hkThread m_thread;

			/// Thread Id from 0 - N
			int m_threadId;

			int m_hardwareThreadId;

			/// Flag is set to true when the thread is requested to close.
			bool m_killThread;

			bool m_clearTimers;

			/// Semaphore used to pause a physics thread after it's done its calculations.
			/// This semaphore is released by the main thread on every simulation step.
			hkSemaphore m_semaphore;

			// Internal buffer used for collecting timer information
			char* m_monitorStreamBegin;
			char* m_monitorStreamEnd;
		};

	protected:

		void addThread();
		void removeThread();

		/// Simple forwarder to the member function.
		static void* HK_CALL threadMainForwarder(void* workerThreadData);

		/// Worker thread main function. May be overridden in derived classes to customize thread setup and shutdown.
		virtual void threadMain(int threadIndex);

		/// Worker thread processing loop. Must be called from the thread's main function to process work loads.
		void threadProcessingLoop(int threadIndex, hkMemoryRouter* memoryRouter);

		/// Worker function for processing a job queue.
		static void HK_CALL jobQueueWorkerFunction(void* jobQueue);

		/// Worker function for processing a task queue.
		static void HK_CALL taskQueueWorkerFunction(void* taskQueue);

	protected:

		/// Data local to each thread.
		ThreadData m_workerThreads[ HK_MAX_NUM_THREADS ];

		/// Function run by worker threads to process a work load.
		WorkerFunction m_workerFunction;

		/// Pointer to a generic work load to be processed by worker threads calling m_workerFunction.
		void* m_workLoad;

		/// Task queue and waiting mode passed in in the last processTaskQueue() call.
		TaskQueueWorkLoad m_taskQueueWorkLoad;

		/// Semaphore used to pause the main thread when it waits for threads
		/// to finish their calculations.
		hkSemaphore m_workerThreadFinished;

		/// Number of threads.
		int m_numThreads;

		/// Monitor buffer size per thread.
		int m_timerBufferAllocation;

		/// True if garbage collection must be performed after the next work load is processed.
		hkBool m_gcThreadMemoryOnCompletion;

		/// Debugging flag set to true when worker threads are stepping
		hkBool m_isRunning;

		/// String for thread names (depending on platform support)
		const char* m_threadName;

		/// See comments for hkCpuThreadPoolCinfo::m_stackSize
		int m_stackSize;
};


#endif // HK_THREAD_POOL_CPU_H

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
