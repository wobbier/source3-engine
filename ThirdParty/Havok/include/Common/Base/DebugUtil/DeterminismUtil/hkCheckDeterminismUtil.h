/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_CHECK_DETERMINISM_UTIL_H
#define HK_CHECK_DETERMINISM_UTIL_H

#include <Common/Base/Config/hkConfigThread.h>
#include <Common/Base/Thread/JobQueue/hkJobQueue.h>

// Uncomment the next line if you want to check the engine for determinism
//#define HK_WANT_DETERMINISM_CHECKS

#if defined(HK_WANT_DETERMINISM_CHECKS)
	#define HK_ON_DETERMINISM_CHECKS_WANTED(CODE) CODE
		#define	HK_ENABLE_DETERMINISM_CHECKS
#else
	#define HK_ON_DETERMINISM_CHECKS_WANTED(CODE)
#endif

#if defined(HK_ENABLE_DETERMINISM_CHECKS)
	#include <Common/Base/Thread/Thread/hkThreadLocalData.h>
	#include <Common/Base/System/Io/IStream/hkIStream.h>
	#include <Common/Base/System/Io/OStream/hkOStream.h>

	#define HK_ON_DETERMINISM_CHECKS_ENABLED(CODE) CODE

	// Uncomment the following define to get a report of the total size of the data checked aggregated by ID at then end
	// of the first run of each demo.
	//#define HK_DETERMINISM_CHECK_SIZES
	#if defined HK_DETERMINISM_CHECK_SIZES
		#include <Common/Base/Container/PointerMap/hkPointerMap.h>
	#endif
#else
	#define HK_ON_DETERMINISM_CHECKS_ENABLED(CODE)
#endif


class hkIstream;
class hkOstream;
class hkCriticalSection;
class hkMemoryTrack;


/// This is a small helper class allowing to check the determinism of
/// a system. Basically it works by running an application twice:
/// First a binary logfile is created and the second time the system
/// checks against this binary logfile.
///
/// Usage quick start:
///
/// You activate writing or reading+checking with startWriteMode() or startCheckMode() functions from anywhere in your app.
/// Similarly you call finish() when you're done with writing or reading+checking.
///
/// Then for every single thread that you're intending to use the utility in, you must call workerThreadStartFrame() before
/// and workerThreadFinishFrame() after any use of the utility.
///
/// The workerThreadStartFrame() function takes a parameter isPrimaryWorkerThread. This can be true for only one thread.
/// That 'marked' thread is allowed to used the utility immediately. This is used when the primary thread performs special
/// operations besides the jobs taken off of the job queue.
///
/// Other threads must register a job first. The primary thread can also register jobs, when it starts working
/// in parallel to other threads.
///
/// Why do we need to register jobs? When multithreading, before the utility is used, you must tell it what that thread
/// is about to start doing -- you must do that, as the same thread may be given different jobs on each consecutive run.
/// You do that by calling registerAndStartJob() and finishJob(). Those functions take a job ID which must be unique
/// across all jobs performed during that one frame.
///
/// Soo, only now after starting, and before finishing a job. You can use the hkCheckDeterminismUtil::checkMt() function.
struct HK_EXPORT_COMMON hkCheckDeterminismUtil
{
	public:

		// Frame-unique ID
		//
		// This id has to be unique for a job in the scope of a single frame.
		// It is made up of the hkpSimulationIslands's unite tag, job type, job task's sequential id, and one another counter (hmm).
		// See hkCheckDeterminismUtil::Fuid hkpDynamicsJob::getFuid().
		struct Fuid
		{
			public:
				HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkCheckDeterminismUtil::Fuid );

				static Fuid& getZeroFuid();
				static Fuid& getCanceledFuid();

				HK_FORCE_INLINE hkBool32 operator==(const Fuid& f);
				HK_FORCE_INLINE hkBool32 operator!=(const Fuid& f);
				HK_FORCE_INLINE void setPackedJobId(const struct hkJob& job);
				HK_FORCE_INLINE void setPackedJobId(hkJobType jobType, hkJobSubType jobSubType);
				HK_FORCE_INLINE hkUint16 getPackedJobId() const { return m_jobPackedId; }

			public:
				hkUint32 m_0;
				hkUint16 m_jobPackedId; // use getJobFuid() to initialize for this value
				hkUint16 m_2;
				hkUint32 m_3, m_4;
		};

		/// Controls the behavior when a determinism check fails.
		enum CheckFailMode
		{
			/// Break with an error. Default mode.
			CHECK_FAIL_MODE_BREAK,

			/// Store a copy of the current reference data and return. Calling didLastCheckFail() will return true.
			/// Useful if you want to add some code to visualize the data.
			CHECK_FAIL_MODE_CONTINUE
		};

	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkCheckDeterminismUtil );

		 hkCheckDeterminismUtil();
		~hkCheckDeterminismUtil();

		static HK_FORCE_INLINE hkCheckDeterminismUtil& HK_CALL getInstance();
		static HK_FORCE_INLINE void HK_CALL createInstance();
		static HK_FORCE_INLINE void HK_CALL destroyInstance();

		/// Sets this utility to write mode. Call at startup of your test.
		/// Make sure to call finish() at the end.
		void startWriteMode(bool stampFilename = false, const char* filename = "hkDeterminismCheckfile.bin");

		/// Sets this utility to check mode. Call at startup of your test.
		/// Make sure to call finish() at the end.
		void startCheckMode(const char* filename = HK_NULL);

		/// Call this function at the end of your write/check run. This closes the open files
		void finish();

		/// Check an array, but only check the crc number of the whole array. The excluded array must have the same
		/// format as described in checkMt().
		template<typename TYPE>
		static HK_ALWAYS_INLINE void HK_CALL checkMtCrc(
			int id, const TYPE* object, int numObjects = 1, int* excluded = HK_NULL );

		/// The excluded array excludes specific bytes of the data from checking. 
		/// It is an array of (offset, sizeBytes) pairs, ordered by offset, with -1 as the last element.
		/// Per example, to exclude 2 bytes at offset 12 and 1 byte at offset 15, one would pass: { 12, 2, 15, 1, -1 } 
		/// as the excluded array.
		template<typename TYPE>
		static HK_FORCE_INLINE void HK_CALL checkMt(
			int id, const TYPE* object, int numObjects = 1, int* excluded = HK_NULL );

		/// Check a simple type object
		template<typename TYPE>
		static HK_FORCE_INLINE void HK_CALL checkMt( int id, const TYPE& object );

		static HK_FORCE_INLINE void HK_CALL randomizeMemory( void* data, int numBytes );

		/// Sets the values used when writing or checking the determinism log.
		/// The user may set the values used when allocating and deallocating,
		/// both when writing and when checking the determinism log. Moreover,
		/// the user can change the value used for wiping the stack memory every time
		/// one of the check functions is called in case of write and check.
		static HK_FORCE_INLINE void HK_CALL setMemoryScrubValues(
			hkUint32 heapAllocWrite, hkUint32 heapFreeWrite, hkUint32 heapAllocCheck, hkUint32 heapFreeCheck,
			hkUint32 stackWipeWrite, hkUint32 stackWipeCheck );

		/// Automatically called to wipe the stack (128 4 bytes words, 512 bytes) at the end
		/// of checkMt() and checkMtCrc(). May also be called explicitly.
		static HK_FORCE_INLINE void HK_CALL wipeStack();

		static HK_FORCE_INLINE void HK_CALL initThread();
		static HK_FORCE_INLINE void HK_CALL quitThread();

		static HK_FORCE_INLINE void HK_CALL workerThreadStartFrame(hkBool isPrimaryWorkerThread);
		static HK_FORCE_INLINE void HK_CALL workerThreadFinishFrame();

		static HK_FORCE_INLINE void HK_CALL registerAndStartJob(Fuid& jobFuid);
		static HK_FORCE_INLINE void HK_CALL finishJob(Fuid& jobFuid, hkBool skipCheck);
		static HK_FORCE_INLINE void HK_CALL cancelJob(Fuid& jobFuid);

		void flushWrite();
		void setCurrentJobFuid(Fuid jobFuid);
		static void setCurrentCheckIndex(hkUint32 checkIndex);
		static void bumpCurrentCheckIndex();
		static hkUint32 getCurrentCheckIndex();
		static Fuid getCurrentJobFuid();

		bool isNearBreakpoint(hkUint64 offset);

		/// Set the current check fail mode. See CheckFailMode.
		HK_FORCE_INLINE void setCheckFailMode(CheckFailMode checkFailMode);

		/// Returns true if the last check failed and the check fail mode is CHECK_FAIL_MODE_CONTINUE, otherwise it
		/// returns false. Calling this method clears the failure flag.
		HK_FORCE_INLINE hkBool32 didLastCheckFail();

		/// Returns an array with the last reference data that failed a check if check fail mode is
		/// CHECK_FAIL_MODE_CONTINUE.
		HK_FORCE_INLINE const hkArray<hkUint8>& getLastReferenceData() const;

	protected:

		enum Mode
		{
			MODE_IDLE,
			MODE_WRITE,
			MODE_COMPARE
		};

		/// Per thread data
		struct ThreadData
		{
			public:

				HK_FORCE_INLINE void reset();

			public:

				/// Contains the last read reference data if a check fails and the check fail mode is set to continue.
				hkArray<hkUint8> m_referenceData;

				hkIstream* m_inputStream;
				hkOstream* m_outputStream;
				void* m_jobInfoIdx;
				void* m_isPrimaryWorkerThread;
				hkUint32 m_currentJobFuid0;
				hkUint32 m_currentJobFuid1;
				hkUint32 m_currentJobFuid2;
				hkUint32 m_currentJobFuid3;
				hkUint32 m_currentCheckIndex;

				/// True if the check fail mode is set to continue and the last determinism check failed.
				hkBool m_didLastCheckFail;
		};

		struct JobInfo
		{
			HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE_CLASS, hkCheckDeterminismUtil::JobInfo );
			Fuid		m_jobFuid;

			// This is the data. In multi threaded mode, the thread-local m_input/outputStreams connect to the corresponding hkArray.
			// This array is resizable, therefore it has to point to the data array.
			hkMemoryTrack* m_data; // for write

			hkBool			m_isOpen;
		};

	protected:

		/// Returns the thread data corresponding to the current hkThreadNumber.
		HK_FORCE_INLINE ThreadData& getThreadData();
		HK_FORCE_INLINE const ThreadData& getThreadData() const;

		static HK_FORCE_INLINE void HK_CALL combineRegisteredJobs();
		static HK_FORCE_INLINE void HK_CALL extractRegisteredJobs();
		static HK_FORCE_INLINE void HK_CALL clearRegisteredJobs();

		static void HK_CALL initThreadImpl();
		static void HK_CALL quitThreadImpl();

		void workerThreadStartFrameImpl(hkBool isPrimaryWorkerThread);
		void workerThreadFinishFrameImpl();

		static HK_NEVER_INLINE void HK_CALL wipeStackImpl( hkUint32 value );

		void  registerAndStartJobImpl(Fuid& jobFuid);
		//There is an MT check in finish job; If the job was defered due to running out of memory, skipCheck must be true
		void  finishJobImpl(Fuid& jobFuid, hkBool skipCheck);
		void  cancelJobImpl(Fuid& jobFuid);
		void  combineRegisteredJobsImpl();
		void  extractRegisteredJobsImpl();
		void  clearRegisteredJobsImpl();
		void  delayJob(const Fuid& id, bool start) const;

		// check the object of size of the object.
		// Note: the referenceObject pointer will be set to the object of the previous run, this pointer is only valid
		// if you get a breakpoint in this function call, it is pointing to garbage once this function has finished.
		// This sounds useless, but it is really handy for debugging, see checkMt.
		void checkImpl( int id, const void* object, int size, int* excluded = HK_NULL, const void** referenceObject = HK_NULL );
		void checkCrcImpl( int id, const void* object, int numBytes, int* excluded = HK_NULL);
		static void HK_CALL randomizeMemoryImpl( void* data, int numBytes );

	protected:

		ThreadData m_threadData[HK_MAX_NUM_THREADS];
		Mode m_mode;
		hkEnum<CheckFailMode, hkUint8> m_checkFailMode;
		hkUint64 m_frame;
		static hkUint32 s_randomSeed;

		hkBool m_inSingleThreadedCode;

		hkMemoryTrack* m_memoryTrack;	///< This will be created when this utility works in memory ( no file name given in the startXXX() functions)

		hkStringPtr	m_filename;
		hkIstream*	m_sharedInputStream;
		hkOstream*	m_sharedOutputStream;

		hkIstream* m_primaryWorkerThreadInputStream;
		hkOstream* m_primaryWorkerThreadOutputStream;
		int m_primaryWorkerThreadJobInfoIdx;

		hkCriticalSection* m_shared;

		hkArray<JobInfo> m_registeredJobs;

		hkBool m_delayJobs;
		hkUint32 m_delayCounter;
		hkArray<unsigned char> m_delayJobSeed;

		bool m_enableThreadTracker;
		int m_maxTheadId;
		hkArray<Fuid> m_threadTracker;

#if defined(HK_DETERMINISM_CHECK_SIZES)
		hkPointerMap<int,int> m_sizePerId;
#endif
		hkBool m_writingStFromWorker;

		friend class hkNetworkedDeterminismUtil;

		static hkUint32 s_heapAllocScrubValueWrite; // used in write mode
		static hkUint32 s_heapFreeScrubValueWrite; // used in write mode
		static hkUint32 s_heapAllocScrubValueCheck; // used in check mode
		static hkUint32 s_heapFreeScrubValueCheck; // used in check mode
		static hkUint32 s_stackScrubValueWrite; // used in write or idle mode
		static hkUint32 s_stackScrubValueCheck; // used in check mode

		static hkCheckDeterminismUtil* s_instance;
};

#if defined (HK_ENABLE_DETERMINISM_CHECKS)
	// Global variables filled in with relevant data on determinism check fails
	extern int hkCheckDeterminismUtil_id;
	extern hkReal* hkCheckDeterminismUtil_reference;
	extern hkReal* hkCheckDeterminismUtil_object;
	extern int hkCheckDeterminismUtil_size;
	extern hkReal* hkCheckDeterminismUtil_crcObject;
#endif

#include <Common/Base/DebugUtil/DeterminismUtil/hkCheckDeterminismUtil.inl>

#endif // HK_CHECK_DETERMINISM_UTIL_H

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
