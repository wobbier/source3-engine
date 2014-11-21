/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE hkTaskGraph::TaskId hkTaskGraph::addTask( hkTask* task, int multiplicity )
{
	HK_ASSERT2( 0x6ca69f2d, m_tasks.getSize() + 1 <= TaskId::Type(-1), "Graph is full" );
	HK_CHECK_ALIGN16(task);
	TaskId taskId( m_tasks.getSize() );
	TaskInfo& taskInfo = m_tasks.expandOne();
	taskInfo.m_task = task;
	taskInfo.m_multiplicity = multiplicity;
	return taskId;
}

HK_FORCE_INLINE hkTaskGraph::TaskId hkTaskGraph::addTaskAndDontIncrementReference( hkTask* task, int multiplicity )
{
	HK_ASSERT2( 0x6ca69f2d, m_tasks.getSize() + 1 <= TaskId::Type(-1), "Graph is full" );
	HK_CHECK_ALIGN16(task);
	TaskId taskId( m_tasks.getSize() );
	TaskInfo& taskInfo = m_tasks.expandOne();
	taskInfo.m_task.setAndDontIncrementRefCount(task);
	taskInfo.m_multiplicity = multiplicity;
	return taskId;
}

HK_FORCE_INLINE void hkTaskGraph::addDependency( TaskId parentId, TaskId childId )
{
	HK_ASSERT2( 0x386b8d39, (parentId.value() < m_tasks.getSize()) && (childId.value() < m_tasks.getSize()), "Invalid task ID(s)" );
	HK_ASSERT2( 0x4211a96d, parentId != childId, "A task cannot depend on itself" );
	Dependency& dependency = m_dependencies.expandOne();
	dependency.m_parentId = parentId;
	dependency.m_childId = childId;
}


HK_FORCE_INLINE void hkTaskGraph::reserve( int numTasks, int numDependencies /*= 0*/ )
{
	m_tasks.reserve(numTasks);
	m_dependencies.reserve(numDependencies);
}

HK_FORCE_INLINE void hkTaskGraph::clear()
{
	m_tasks.clear();
	m_dependencies.clear();
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
