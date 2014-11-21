/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_TRAIT_ARITHMETIC_H
#define HKBASE_TRAIT_ARITHMETIC_H


namespace hkTrait
{
	/// The integral type that corresponds to the size and sign.
	template<int size, bool isSigned> struct MatchingIntType { };
	template<> struct MatchingIntType<1, true> { typedef hkInt8 IntType; };
	template<> struct MatchingIntType<1, false> { typedef hkUint8 IntType; };
	template<> struct MatchingIntType<2, true> { typedef hkInt16 IntType; };
	template<> struct MatchingIntType<2, false> { typedef hkUint16 IntType; };
	template<> struct MatchingIntType<4, true> { typedef hkInt32 IntType; };
	template<> struct MatchingIntType<4, false> { typedef hkUint32 IntType; };
	template<> struct MatchingIntType<8, true> { typedef hkInt64 IntType; };
	template<> struct MatchingIntType<8, false> { typedef hkUint64 IntType; };

		

	/// Obtain the minimum of two integers at compile-time.
	/// Could extend this to generic types.
	template<int VAL1, int VAL2>
	struct IntMin
	{
		enum { Result = If< VAL1 < VAL2
			, Constant<VAL1>
			, Constant<VAL2> >::Type::Result };
	};


	/// Get the highest power of two which evenly divides N
	template<int N>
	struct GreatestPowerOfTwoDivisor;

	template<>
	struct GreatestPowerOfTwoDivisor<0> { enum { Result = 1 }; };

	template<int N>
	struct GreatestPowerOfTwoDivisor
	{
		enum { Result = If< (N>1) && (N%2==0)
			, Constant< 2*GreatestPowerOfTwoDivisor<N/2>::Result >
			, Constant<1> >::Type::Result };
	};
}

#endif // HKBASE_TRAIT_ARITHMETIC_H

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
