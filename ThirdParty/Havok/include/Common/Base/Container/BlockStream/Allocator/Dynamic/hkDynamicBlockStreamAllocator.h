/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_DYNAMIC_BLOCK_STREAM_ALLOCATOR_H
#define HK_DYNAMIC_BLOCK_STREAM_ALLOCATOR_H

#include <Common/Base/Container/BlockStream/Allocator/hkBlockStreamAllocator.h>

/// A block stream allocator which dynamically allocates more blocks when its initial capacity is exceeded.
/// It "shrinks" (i.e. returns the blocks to the base allocator) only when it is destroyed or when you call
/// releaseUnusedBlocks().
class HK_EXPORT_COMMON hkDynamicBlockStreamAllocator : public hkBlockStreamAllocator
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE );

		/// Create an allocator with the given initial capacity.
		hkDynamicBlockStreamAllocator( int initialSize = 0 );

		/// Destructor. Frees all the blocks.
		~hkDynamicBlockStreamAllocator();

		/// Allocate the requested number of blocks.
		virtual void blockAllocBatch( Block** blocksOut, int nblocks );

		/// Free the given blocks.
		virtual void blockFreeBatch( Block** blocks, int nblocks );

		/// Return the number of bytes given out by this allocator.
		/// Note: The blocks in the thread-local allocator's cache will count as used from this allocator's point of view.
		virtual int getBytesUsed() const;

		/// Get the peak byte usage.
		virtual int getMaxBytesUsed() const;

		/// Return the current total bytes used and available through this allocator without expanding it.
		virtual int getCapacity() const;

		/// Free all memory. The allocator will be completely empty. Asserts if any data has not been deallocated.
		virtual void freeAllRemainingAllocations();

		/// Return the memory statistics.
		virtual void getMemoryStatistics( hkMemoryAllocator::MemoryStatistics& statsOut ) const;

		/// Attempt to free reserved blocks if they are not used.
		void releaseUnusedBlocks();

	protected:

		// Reserve more blocks to allocate at least the given size in bytes.
		void expand( int numBytes );

	protected:

		/// A critical section to protect allocations and deallocations.
		hkCriticalSection m_criticalSection;

		/// This array contains all blocks.
		hkArray<Block*> m_blocks;

		/// This array contains all blocks available for allocation.
		hkArray<Block*> m_freeList;

		/// The maximum number of bytes ever allocated through this allocator.
		int m_maxBytesUsed;
};

#endif	// !HK_DYNAMIC_BLOCK_STREAM_ALLOCATOR_H

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
