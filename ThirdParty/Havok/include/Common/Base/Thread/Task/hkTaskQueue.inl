/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


#if !defined(HK_ENABLE_TASK_QUEUE_TIMERS)
	#define HK_TQ_TIMER_GET_MONITOR_STREAM()
	#define HK_TQ_TIMER_BEGIN(X)
	#define HK_TQ_TIMER_END()
	#define HK_TQ_TIMER_BEGIN_LIST(X, Y)
	#define HK_TQ_TIMER_SPLIT_LIST(X)
	#define HK_TQ_TIMER_END_LIST()
	#define HK_TQ_MONITOR_ADD_VALUE(X, Y, Z)
	#define HK_TQ_TIMER_BEGIN_RELEASE_SEMAPHORE(COUNT)
#else
	#define HK_TQ_TIMER_GET_MONITOR_STREAM()	hkMonitorStream& monitorStream = hkMonitorStream::getInstance()
	#define HK_TQ_TIMER_BEGIN(X)				HK_TIMER_BEGIN2(monitorStream, X, HK_NULL)
	#define HK_TQ_TIMER_END()					HK_TIMER_END2(monitorStream)
	#define HK_TQ_TIMER_BEGIN_LIST(X, Y)		HK_TIMER_BEGIN_LIST2(monitorStream, X, Y)
	#define HK_TQ_TIMER_SPLIT_LIST(X)			HK_TIMER_SPLIT_LIST2(monitorStream, X)
	#define HK_TQ_TIMER_END_LIST()				HK_TIMER_END_LIST2(monitorStream)
	#define HK_TQ_MONITOR_ADD_VALUE(X, Y, Z)	HK_MONITOR_ADD_VALUE2(monitorStream, X, Y, Z)
	#define HK_TQ_TIMER_BEGIN_RELEASE_SEMAPHORE(COUNT)	\
	switch (COUNT) \
	{ \
		case 1: \
			HK_TQ_TIMER_BEGIN("ReleaseSemaphore_1"); \
			break; \
		case 2: \
			HK_TQ_TIMER_BEGIN("ReleaseSemaphore_2"); \
			break; \
		case 3: \
			HK_TQ_TIMER_BEGIN("ReleaseSemaphore_3"); \
			break; \
		case 4: \
			HK_TQ_TIMER_BEGIN("ReleaseSemaphore_4"); \
			break; \
		default: \
			HK_TQ_TIMER_BEGIN("ReleaseSemaphore_5+"); \
	}
#endif


// On debug we keep track of the thread ID that owns each group
HK_ON_DEBUG(extern HK_EXPORT_COMMON HK_THREAD_LOCAL(int) hkThreadNumber);

HK_FORCE_INLINE hkTask* hkTaskQueue::getTask(const hkTaskQueue::PrioritizedTask& prioritizedTask) const
{
	hkTask* task = m_graphInfos[prioritizedTask.m_graphId].m_scheduler.getTask(prioritizedTask.getTaskId());

	// If the task is inactive return the empty task.
	return task ? task : (hkTask*) &m_emptyTask;
}

HK_FORCE_INLINE const hkTaskQueue::GraphInfo& hkTaskQueue::getGraphInfo(hkTaskQueue::GraphId groupId) const
{
	HK_ASSERT(0x6f5e6a6e, m_graphInfos.isAllocated(groupId));
	return m_graphInfos[groupId];
}

HK_FORCE_INLINE hkTaskQueue::GraphInfo& hkTaskQueue::accessGraphInfo(GraphId groupId)
{
	HK_ASSERT(0x6f5e6a6e, m_graphInfos.isAllocated(groupId));
	return m_graphInfos[groupId];
}

HK_FORCE_INLINE hkBool32 hkTaskQueue::isGraphFinished(GraphId graphId) const
{
	HK_ON_DEBUG(getGraphInfo(graphId).checkThreadOwnership());
	return !getGraphInfo(graphId).m_scheduler.getNumUnfinishedTasks();
}

HK_FORCE_INLINE bool hkTaskQueue::open()
{
	m_queueLock.enter();
	bool res = !m_isQueueOpen;
	if (!m_isQueueOpen)
	{
		m_isQueueOpen = true;
	}
	m_queueLock.leave();
	return res;
}

HK_FORCE_INLINE bool hkTaskQueue::isOpen()
{
	return m_isQueueOpen;
}

HK_FORCE_INLINE void hkTaskQueue::GraphInfo::FreeListArrayOperations::setEmpty(
	hkTaskQueue::GraphInfo& groupInfo, hkUint32 next)
{
	*((hkUint32*) &groupInfo) = next;
	groupInfo.m_isEmpty = true;
}

HK_FORCE_INLINE hkUint32 hkTaskQueue::GraphInfo::FreeListArrayOperations::getNext(
	const hkTaskQueue::GraphInfo& groupInfo)
{
	return *((hkUint32*) &groupInfo);
}

HK_FORCE_INLINE hkBool32 hkTaskQueue::GraphInfo::FreeListArrayOperations::isEmpty(
	const hkTaskQueue::GraphInfo& groupInfo)
{
	return groupInfo.m_isEmpty;
}


HK_FORCE_INLINE void hkTaskQueue::GraphInfo::checkThreadOwnership() const
{
#if defined(HK_DEBUG)
	HK_ASSERT2(0x68da411a, m_ownerThreadId == HK_THREAD_LOCAL_GET(hkThreadNumber), "This operation is allowed only in the thread that owns the group");
#endif
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
