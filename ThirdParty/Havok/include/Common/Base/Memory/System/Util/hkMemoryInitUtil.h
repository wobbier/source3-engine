/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_hkMemoryInitUtil_H
#define HKBASE_hkMemoryInitUtil_H

#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>

#include <Common/Base/Memory/Allocator/FreeList/hkFreeListAllocator.h>
#include <Common/Base/Memory/System/FreeList/hkFreeListMemorySystem.h>

class hkMemoryAllocator;
class hkThreadMemory;
class hkMemoryRouter;
class hkMemorySystem;
struct hkSingletonInitNode;

	/// Helper methods to initialize and quit the memory system.
	/// These methods exist mainly for brevity in our demos; the memory system initialization
	/// may be inlined in your setup code.
	/// The init methods must be passed a base system allocator.
	/// All Havok memory allocations will ultimately come from
	/// this allocator. hkMallocAllocator::m_defaultMallocAllocator
	/// is usually suitable for simple systems
namespace hkMemoryInitUtil
{
		/// Initialize with an hkFreeListMemorySystem + leak detection.
	HK_EXPORT_COMMON hkMemoryRouter* HK_CALL initLeakDetect(hkMemoryAllocator *memoryAllocator, const hkMemorySystem::FrameInfo& info);

		/// Initialize with an hkFreeListMemorySystem using a hkFreeListAllocator for heap allocations, and a hkLargeBlockAllocator for 
		/// larger allocations that the hkFreeListAllocator can't handle. The hkLargeBlockAllocator will allocate memory from the memoryAllocator.
	HK_EXPORT_COMMON hkMemoryRouter* HK_CALL initFreeListLargeBlock(hkMemoryAllocator *memoryAllocator, const hkMemorySystem::FrameInfo& info, const hkFreeListAllocator::Cinfo* cinfo = HK_NULL, hkFreeListMemorySystem::SetupFlags flags = hkFreeListMemorySystem::DEFAULT_SETUP_FLAGS);

		/// Initialize with an hkFreeListMemorySystem using a hkFreeListAllocator for heap allocations, and the memoryAllocator for any allocations that 
		/// the hkFreeListAllocator can't handle.
	HK_EXPORT_COMMON hkMemoryRouter* HK_CALL initFreeList(hkMemoryAllocator *memoryAllocator, hkMemoryAllocator::ExtendedInterface* memoryAllocatorExtended, const hkMemorySystem::FrameInfo& info, const hkFreeListAllocator::Cinfo* cinfo = HK_NULL, hkFreeListMemorySystem::SetupFlags flags = hkFreeListMemorySystem::DEFAULT_SETUP_FLAGS);

		/// Initialize with an hkCheckingMemorySystem.
		/// This checks for leaks and some other common errors and is several orders of magnitude
		/// slower than the free list system.
	HK_EXPORT_COMMON hkMemoryRouter* HK_CALL initChecking(hkMemoryAllocator *memoryAllocator, const hkMemorySystem::FrameInfo& info);

		/// Initialize with an hkSimpleMemorySystem.
		/// This is slower than the free list system and is intended as an example.
	HK_EXPORT_COMMON hkMemoryRouter* HK_CALL initSimple(hkMemoryAllocator *memoryAllocator, const hkMemorySystem::FrameInfo& info);

		/// Initialize with an hkOptimizerMemorySystem.
		/// This is mainly for internal use to detect where the memory system is being used
		/// sub-optimally.
	HK_EXPORT_COMMON hkMemoryRouter* HK_CALL initOptimizer(hkMemoryAllocator *memoryAllocator, const hkMemorySystem::FrameInfo& info);

		/// Initialize using an explicit heap allocator. 
		/// The heapAllocator, and heapInteface provide the direct implementation of the heap (in contrast to other methods
		/// such as initFreeList, which uses a hkFreeListAllocator as the heap allocator). The heapInterface provides
		/// methods for garbageCollection/memoryWalk, etc., on the heapAllocator; it is optional and can be passed as HK_NULL.
		/// The memoryAllocator is the allocator which will be used for non heap allocations; for example
		/// the solver's memory block is allocated from the memoryAllocator.
	HK_EXPORT_COMMON hkMemoryRouter* HK_CALL initHeapAllocator(hkMemoryAllocator *memoryAllocator, hkMemoryAllocator *heapAllocator, hkMemoryAllocator::ExtendedInterface* heapInterface, const hkMemorySystem::FrameInfo& info);

		/// Will destroy the memory allocator, by calling mainQuit() and destroying the allocator.
		/// Should only be called if an init call has been made.
	HK_EXPORT_COMMON hkResult HK_CALL quit();

		/// Initialize with the default system, currently hkFreeListMemorySystem.
	HK_EXPORT_COMMON inline hkMemoryRouter* HK_CALL initDefault(hkMemoryAllocator *memoryAllocator, const hkMemorySystem::FrameInfo& info) { return initFreeListLargeBlock(memoryAllocator, info); }

		/// When using Checking mem, if you load DLLs dynamically you should let the stacktracer know by calling this function
	HK_EXPORT_COMMON void HK_CALL refreshDebugSymbols();

#if defined(HK_MEMORY_TRACKER_ENABLE)
		/// Init the memory tracker.
		/// Call this before the hkMemorySystem has been initialized.
	HK_EXPORT_COMMON void HK_CALL initMemoryTracker();
		/// Quit the memory tracker.
		/// Call this after the hkMemorySystem has been shut down.
	HK_EXPORT_COMMON void HK_CALL quitMemoryTracker();
#endif

	HK_EXPORT_COMMON void HK_CALL outputDebugString(const char* s, void*);

		/// Cross DLL sync info
	struct HK_EXPORT_COMMON SyncInfo
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, SyncInfo);
		hkMemoryRouter* m_memoryRouter;
		hkMemorySystem* m_memorySystem;
		hkSingletonInitNode* m_singletonList;
		void* m_stackTracerImpl; // the stack tracer implementation
		hkCriticalSection* m_mtCheckSection; // the multithreading debug check 
		hkMonitorStream* m_monitors; // montor ptrs as monitors not a normal singleton
		hkStackTracer::CallTree* m_mtCheckStackTree; // the multithreading debug check 
		hkUint32* m_mtRefLockedAllPtr;
	};

	HK_EXPORT_COMMON extern hkMemorySystem* s_system;

	typedef void (HK_CALL *onQuitFunc)( void );
	HK_EXPORT_COMMON extern onQuitFunc s_onQuitFunc;
}

#endif // HKBASE_hkMemoryInitUtil_H

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
