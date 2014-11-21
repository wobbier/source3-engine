/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKGP_JOB_QUEUE_H
#define HKGP_JOB_QUEUE_H

//
// Bare-bone job queue
//
struct HK_EXPORT_COMMON hkgpJobQueue
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,hkgpJobQueue);
private:

	struct IJob
	{
		//+hk.MemoryTracker(ignore=True)

		HK_FORCE_INLINE IJob(int multiplicity) : m_id(-1), m_multiplicity(multiplicity) {}
		virtual			~IJob() {}
		virtual void	run() const = 0;

		int						m_id;
		int						m_multiplicity;
		hkInplaceArray<int,8>	m_dependencies;
	};

	template <typename T>
	struct PointerWrapper
	{
		HK_FORCE_INLINE PointerWrapper(T* ptr) : m_ptr(ptr) {}
		HK_FORCE_INLINE T* operator->() { return m_ptr; }
		T* m_ptr;
	};

	template <typename T>
	struct ReferenceWrapper
	{
		HK_FORCE_INLINE ReferenceWrapper(T& ref) : m_ref(ref) {}
		HK_FORCE_INLINE T* operator->() { return &m_ref; }
		T& m_ref;
	};

	template <typename T> struct WrapType { typedef ReferenceWrapper<T> Wrapper; };
	template <typename T> struct WrapType<T*> { typedef PointerWrapper<T> Wrapper; };

	template <typename T>
	struct Box : public IJob
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,Box);
		inline			Box(const T& job, int multiplicity) : IJob(multiplicity), m_job(job) {}
		void		    run() const HK_OVERRIDE { typename WrapType<T>::Wrapper(m_job)->run(); }
		mutable T		m_job;
	};

	template <typename T>
	struct BoxWithDependencies : public Box<T>
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE,BoxWithDependencies);
		inline			BoxWithDependencies(const T& job, int multiplicity) : Box<T>( job, multiplicity )
		{
			Box<T>::m_id = WrapType<T>::Wrapper(Box<T>::m_job).getIdAndFillDependencies(Box<T>::m_dependencies);
		}
	};

public:
							hkgpJobQueue(int numThreads=-1);
							~hkgpJobQueue();
	void					waitForCompletion();
	int						getNumThreads() const { return(m_threads.getSize()); }

	template <typename T>
	void					appendJob(const T& job, int multiplicity = 1) { push( new Box<T>(job, multiplicity) ); }

	template <typename T>
	void					appendJobWithDependencies(const T& job, int multiplicity = 1) { push( new BoxWithDependencies<T>(job,multiplicity) ); }

private:
	void					push(IJob* job);
	void					threadMain();
	static void* HK_CALL	threadStart(void* arg);
private:
	hkInplaceArray<class hkThread*,8>	m_threads;
	class hkCriticalSection*			m_jobsLock;
	class hkSemaphore*					m_newJobEvent;
	class hkSemaphore*					m_endJobEvent;
	class hkSemaphore*					m_endThreadEvent;
	hkArray<IJob*>						m_jobs;
	hkArray<IJob*>						m_jobsToDelete;
	hkArray<int>						m_pendingJobIds;
	int									m_numPendings;
};


#endif // HKGP_JOB_QUEUE_H

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
