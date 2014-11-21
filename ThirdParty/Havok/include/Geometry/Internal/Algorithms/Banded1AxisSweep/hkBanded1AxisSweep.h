/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


#ifndef HK_BANDED_1_AXIS_SWEEP_H
#define HK_BANDED_1_AXIS_SWEEP_H


struct hkAabb16;

/// Old broadphase which Havokd used in HavokFx 2005, improved 1-axis sweep for lots of objects.
/// Performance is potentially better than 1-axis sweep, but slower compared to hknpHybridBroadphase
namespace hkBanded1AxisSweep
{

	struct KeyPair
	{
		int m_a;
		int m_b;
	};

	/// some constansts
	enum 
	{
		AXIS_SWEEP_BATCH_SIZE = 4,	///< internal batch size
		SweepNumBandsTotal = 64,	///< total number of 1-axis sweep lists

		SweepNumBandsPerAxis = 16,	///< Size 
		SweepBandsMask = SweepNumBandsPerAxis-1,
	};


	/// calculates the buffer size needed by collide()
	int calcBufferSize( int numBodies );

	/// returns the number of collision pairs, input aabbs can be unsorted, no padding needed
	int collide( int widthOfBand[3], int sweepAxisIndex, 
		const hkAabb16* aabbs, int numAabbs,
		void* buffer,  
		KeyPair* HK_RESTRICT pairsOut,	int maxNumPairs, hkPadSpu<int>& numPairsSkippedOut );

}
#endif // HK_BANDED_1_AXIS_SWEEP_H

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
