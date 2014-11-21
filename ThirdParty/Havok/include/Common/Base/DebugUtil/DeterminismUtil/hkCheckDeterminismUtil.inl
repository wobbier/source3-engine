/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE


extern HK_EXPORT_COMMON HK_THREAD_LOCAL(int) hkThreadNumber;

HK_FORCE_INLINE hkBool32 hkCheckDeterminismUtil::Fuid::operator==(const hkCheckDeterminismUtil::Fuid& f)
{
	return m_0 == f.m_0 && m_jobPackedId == f.m_jobPackedId && m_2 == f.m_2 && m_3 == f.m_3 && m_4 == f.m_4;
}

HK_FORCE_INLINE hkBool32 hkCheckDeterminismUtil::Fuid::operator!=(const hkCheckDeterminismUtil::Fuid& f)
{
	return m_0 != f.m_0 || m_jobPackedId != f.m_jobPackedId || m_2 != f.m_2 || m_3 != f.m_3 || m_4 != f.m_4;
}

HK_FORCE_INLINE void hkCheckDeterminismUtil::Fuid::setPackedJobId(const struct hkJob& job)
{
	setPackedJobId(job.m_jobType, job.m_jobSubType);
}

HK_FORCE_INLINE void hkCheckDeterminismUtil::Fuid::setPackedJobId(hkJobType jobType, hkJobSubType jobSubType)
{
	m_jobPackedId = ((hkUint16(jobType) << 8) | hkUint16(jobSubType));
}

HK_FORCE_INLINE hkCheckDeterminismUtil& HK_CALL hkCheckDeterminismUtil::getInstance()
{
	HK_ASSERT2(0xad8655d2, s_instance, "Instance not created.");
	return *s_instance;
}

HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::createInstance()
{
	HK_ASSERT2(0xad8655d3, !s_instance, "Instance already created.");
	s_instance = new hkCheckDeterminismUtil();
}

HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::destroyInstance()
{
	delete s_instance;
	s_instance = HK_NULL;
}


template<typename TYPE>
HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::checkMtCrc( int id, const TYPE* object, int numObjects, int* excluded )
{
#if defined(HK_ENABLE_DETERMINISM_CHECKS) && !defined(HK_PLATFORM_SPU)
	hkCheckDeterminismUtil& instance = getInstance();
	if (instance.m_mode != MODE_IDLE)
	{
		instance.checkCrcImpl( id, object, sizeof(TYPE ) * numObjects, excluded );
		wipeStack();
	}
#endif
}

template<typename TYPE>
HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::checkMt( int id, const TYPE* object, int numObjects, int* excluded )
{
#if defined(HK_ENABLE_DETERMINISM_CHECKS) && !defined(HK_PLATFORM_SPU)
	hkCheckDeterminismUtil& instance = getInstance();
	if (instance.m_mode != MODE_IDLE)
	{
		checkMt(id, numObjects);
		const TYPE* referenceObject;	// if checkImpl halts, this variable points to the object of the previous run, pretty nice for debugging
		instance.checkImpl( id, object, sizeof(TYPE ) * numObjects, excluded, (const void**)&referenceObject );
		wipeStack();
	}
#endif
}

template<typename TYPE>
HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::checkMt( int id, const TYPE& object )
{
#if defined(HK_ENABLE_DETERMINISM_CHECKS) && !defined(HK_PLATFORM_SPU)
	hkCheckDeterminismUtil& instance = getInstance();
	if (instance.m_mode != MODE_IDLE)
	{
		const TYPE* referenceObject;	// if checkImpl halts, this variable points to the object of the previous run, pretty nice for debugging
		instance.checkImpl( id, &object, sizeof(TYPE ), HK_NULL, (const void**)&referenceObject );
		wipeStack();
	}
#endif
}

HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::setMemoryScrubValues(
	hkUint32 heapAllocWrite, hkUint32 heapFreeWrite,
	hkUint32 heapAllocCheck, hkUint32 heapFreeCheck,
	hkUint32 stackWipeWrite, hkUint32 stackWipeCheck )
{
#if defined(HK_ENABLE_DETERMINISM_CHECKS) && !defined(HK_PLATFORM_SPU)
	s_heapAllocScrubValueWrite = heapAllocWrite;
	s_heapFreeScrubValueWrite = heapFreeWrite;
	s_heapAllocScrubValueCheck = heapAllocCheck;
	s_heapFreeScrubValueCheck = heapFreeCheck;
	s_stackScrubValueWrite = stackWipeWrite;
	s_stackScrubValueCheck = stackWipeCheck;
#endif
}

HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::wipeStack()
{
#if defined(HK_ENABLE_DETERMINISM_CHECKS) && !defined(HK_PLATFORM_SPU)
	hkCheckDeterminismUtil& instance = getInstance();
	if(instance.m_mode == MODE_COMPARE)
	{
		wipeStackImpl( s_stackScrubValueCheck );
	}
	else
	{
		wipeStackImpl( s_stackScrubValueWrite );
	}
#endif
}

HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::initThread()
{
#if defined(HK_ENABLE_DETERMINISM_CHECKS) && !defined(HK_PLATFORM_SPU)
	initThreadImpl();
#endif
}

HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::randomizeMemory( void* data, int numBytes )
{
#if defined(HK_ENABLE_DETERMINISM_CHECKS) 
	randomizeMemoryImpl( data, numBytes );
#endif
}


HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::quitThread()
{
#if defined(HK_ENABLE_DETERMINISM_CHECKS) && !defined(HK_PLATFORM_SPU)
	quitThreadImpl();
#endif
}

HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::workerThreadStartFrame(hkBool isPrimaryWorkerThread)
{
#if defined(HK_ENABLE_DETERMINISM_CHECKS) && !defined(HK_PLATFORM_SPU)
	hkCheckDeterminismUtil& instance = getInstance();
	if(instance.m_mode != MODE_IDLE)
	{
		instance.workerThreadStartFrameImpl(isPrimaryWorkerThread);
	}
#endif
}

HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::workerThreadFinishFrame()
{
#if defined(HK_ENABLE_DETERMINISM_CHECKS) && !defined(HK_PLATFORM_SPU)
	hkCheckDeterminismUtil& instance = getInstance();
	if(instance.m_mode != MODE_IDLE)
	{
		instance.workerThreadFinishFrameImpl();
	}
#endif
}

HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::registerAndStartJob(Fuid& jobFuid)
{
#if defined(HK_ENABLE_DETERMINISM_CHECKS) && !defined(HK_PLATFORM_SPU)
	hkCheckDeterminismUtil& instance = getInstance();
	if(instance.m_mode != MODE_IDLE)
	{
		instance.registerAndStartJobImpl(jobFuid);
	}
#endif
}

HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::finishJob(Fuid& jobFuid, hkBool skipCheck)
{
#if defined(HK_ENABLE_DETERMINISM_CHECKS) && !defined(HK_PLATFORM_SPU)
	hkCheckDeterminismUtil& instance = getInstance();
	if(instance.m_mode != MODE_IDLE)
	{
		instance.finishJobImpl(jobFuid, skipCheck);
	}
#endif
}

HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::cancelJob(Fuid& jobFuid)
{
#if defined(HK_ENABLE_DETERMINISM_CHECKS) && !defined(HK_PLATFORM_SPU)
	hkCheckDeterminismUtil& instance = getInstance();
	if(instance.m_mode != MODE_IDLE)
	{
		instance.cancelJobImpl(jobFuid);
	}
#endif
}

HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::combineRegisteredJobs()
{
#if defined(HK_ENABLE_DETERMINISM_CHECKS) && !defined(HK_PLATFORM_SPU)
	hkCheckDeterminismUtil& instance = getInstance();
	if(instance.m_mode != MODE_IDLE)
	{
		instance.combineRegisteredJobsImpl();
	}
#endif
}

HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::extractRegisteredJobs()
{
#if defined(HK_ENABLE_DETERMINISM_CHECKS) && !defined(HK_PLATFORM_SPU)
	hkCheckDeterminismUtil& instance = getInstance();
	if(instance.m_mode != MODE_IDLE)
	{
		instance.extractRegisteredJobsImpl();
	}
#endif
}

HK_FORCE_INLINE void HK_CALL hkCheckDeterminismUtil::clearRegisteredJobs()
{
#if defined(HK_ENABLE_DETERMINISM_CHECKS) && !defined(HK_PLATFORM_SPU)
	hkCheckDeterminismUtil& instance = getInstance();
	if(instance.m_mode != MODE_IDLE)
	{
		instance.clearRegisteredJobsImpl();
	}
#endif
}


HK_FORCE_INLINE void hkCheckDeterminismUtil::setCheckFailMode(CheckFailMode checkFailMode)
{
	m_checkFailMode = checkFailMode;
}

HK_FORCE_INLINE hkBool32 hkCheckDeterminismUtil::didLastCheckFail()
{
	hkBool didFail = false;
	if (m_checkFailMode == CHECK_FAIL_MODE_CONTINUE)
	{
		ThreadData& threadData = getThreadData();
		didFail = threadData.m_didLastCheckFail;
		threadData.m_didLastCheckFail = false;
	}
	return didFail;
}

HK_FORCE_INLINE const hkArray<hkUint8>& hkCheckDeterminismUtil::getLastReferenceData() const
{
	return getThreadData().m_referenceData;
}

HK_FORCE_INLINE hkCheckDeterminismUtil::ThreadData& hkCheckDeterminismUtil::getThreadData()
{
	const int threadNumber = HK_THREAD_LOCAL_GET(hkThreadNumber);
	HK_ASSERT(0x3dbbc60f, threadNumber < HK_MAX_NUM_THREADS);
	return m_threadData[threadNumber];
}

HK_FORCE_INLINE const hkCheckDeterminismUtil::ThreadData& hkCheckDeterminismUtil::getThreadData() const
{
	const int threadNumber = HK_THREAD_LOCAL_GET(hkThreadNumber);
	HK_ASSERT(0x3dbbc60e, threadNumber < HK_MAX_NUM_THREADS);
	return m_threadData[threadNumber];
}

HK_FORCE_INLINE void hkCheckDeterminismUtil::ThreadData::reset()
{
	m_inputStream = HK_NULL;
	m_outputStream = HK_NULL;
	m_jobInfoIdx = HK_NULL;
	m_isPrimaryWorkerThread = HK_NULL;
	m_currentJobFuid0 = HK_NULL;
	m_currentJobFuid1 = HK_NULL;
	m_currentJobFuid2 = HK_NULL;
	m_currentJobFuid3 = HK_NULL;
	m_didLastCheckFail = false;
}

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
