/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_THREAD_LOCAL_BLOCK_STREAM_ALLOCATOR_H
#define HK_THREAD_LOCAL_BLOCK_STREAM_ALLOCATOR_H

#include <Common/Base/Container/BlockStream/Allocator/hkBlockStreamAllocator.h>

/// Thread local allocator, acts as a cache over a Block Stream allocator.
/// There is one for each thread, which caches a number of blocks.
class HK_EXPORT_COMMON hkThreadLocalBlockStreamAllocator
{
	public:

		enum
		{
			BATCH_ALLOC_SIZE	= 6,	///< The number of blocks freed/allocated in one go in the m_blockStreamManager
			MAX_FREE_LIST_SIZE	= 8,	///< The maximum number of elements cached locally
		};

	public:

		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_BASE, hkThreadLocalBlockStreamAllocator );

		/// Constructor.
		/// Note that on SPU, bsAllocator must be a PPU pointer
		hkThreadLocalBlockStreamAllocator( hkBlockStreamAllocator* bsAllocator, int threadId )
			: m_blockStreamAllocator( bsAllocator ), m_numFreeBlocks(0)
		{
			HK_ON_CPU( m_threadId = threadId );
		}

		~hkThreadLocalBlockStreamAllocator()
		{
			clear();
		}

		/// Allocate a block
		hkBlockStreamAllocator::Block* blockAlloc();

		/// Deallocate a block
		void blockFree( hkBlockStreamAllocator::Block* blockPpu );

		/// Free a batch
		void blockFreeBatch( hkBlockStreamAllocator::Block** blocks, int nblocks );

		/// Clear all locally cached blocks
		void clear();

	protected:

		void checkConsistency( );

	public:

		HK_ON_CPU( int m_threadId );	///< For debugging. Set to -1 to skip debug checks.
		hkPadSpu<hkBlockStreamAllocator*> m_blockStreamAllocator;

		hkPadSpu<int> m_numFreeBlocks;
		hkBlockStreamAllocator::Block* m_freeBlocks[MAX_FREE_LIST_SIZE];
};

#endif	// HK_THREAD_LOCAL_BLOCK_STREAM_ALLOCATOR_H

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
