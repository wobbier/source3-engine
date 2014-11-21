/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_FIXED_BLOCK_STREAM_ALLOCATOR_H
#define HK_FIXED_BLOCK_STREAM_ALLOCATOR_H

#	include <Common/Base/Container/BlockStream/Allocator/hkBlockStreamAllocator.h>

/// A simple implementation of block stream allocator using a fixed size buffer asserting when out of memory.
/// This is the only implementation working on PlayStation(R)3.
class HK_EXPORT_COMMON hkFixedBlockStreamAllocator : public hkBlockStreamAllocator
{
	public:

		HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_COLLIDE);

		typedef hkBlockStreamBase::Block Block;

		HK_ON_CPU(virtual) void blockAllocBatch(Block** blocksOut, int nblocks);

		HK_ON_CPU(virtual) void blockFreeBatch(Block** blocks, int nblocks);


		/// get the current bytes used. Note that data in the thread local allocator will
		/// count as bytes used (as they are not available to other threads in a worst case
		/// scenario).
		virtual int getBytesUsed() const;

		/// the peak usage
		virtual int getMaxBytesUsed() const;

		/// Returns the total number of bytes available
		virtual int getCapacity() const;

		void init( int byteSize );

		void init( void* buffer, int byteSize );

		/// free all memory, only necessary if this class allocated the memory
		void clear();

		/// Asserts if any data is allocated.
		void freeAllRemainingAllocations();

		hkFixedBlockStreamAllocator(int allocSize = 0);

		~hkFixedBlockStreamAllocator();

		void getMemoryStatistics( hkMemoryAllocator::MemoryStatistics& statsOut ) const;


	private:

		void rebuildFreelist();

	public:

		/// The critical section, must go before m_storage to avoid DMAing it back and forth SPU
		mutable hkCriticalSection m_criticalSection;

		// Aligned for SPU access.
		HK_ALIGN16(Block* m_blocks);

		hkArray< Block* > m_freeList;

		int		m_capacity;						///< Total number of blocks available
		int		m_minFreeListSize;				///< For tracking peak memory usage
		hkBool	m_dontDeallocate;
		hkBool	m_enableAllocationTimerInfo;	///< Add extra used memory timer infos into the timer stream, debug only
};

#endif

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
