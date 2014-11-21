/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#	include <intrin.h>
#	define InterlockedCmpXchg _InterlockedCompareExchange
#	pragma intrinsic(InterlockedCmpXchg)

namespace hkAtomic
{
	//
	//	Compare and swap implementation.

	template <int size> struct CasImpl {};
	template <> struct CasImpl<32>
	{
		typedef long Type;

		// 32-bit implementation
		static HK_FORCE_INLINE bool HK_CALL apply(Type volatile* address, const Type& oldValue, const Type& newValue)
		{
			return (InterlockedCmpXchg(address, newValue, oldValue) == oldValue);
		}
	};

	//
	//	Compare and swap.

	template <typename T> HK_FORCE_INLINE bool HK_CALL compareAndSwap(T volatile* address, const T& oldValue, const T& newValue)
	{
		typedef CasImpl<sizeof(T) << 3>	Cas;
		typedef typename Cas::Type		Type;

		return Cas::apply(reinterpret_cast<Type volatile*>(address), reinterpret_cast<const Type&>(oldValue), reinterpret_cast<const Type&>(newValue));
	}
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
