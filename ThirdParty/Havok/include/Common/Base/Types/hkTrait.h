/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_TRAITS_H
#define HKBASE_TRAITS_H


namespace hkTrait
{
	// Boolean trait

	template <bool N> 
	struct TraitBool 
	{ 
		typedef TraitBool<N> type; 
		typedef type Type; 
		enum { result = N }; 
	};

	typedef TraitBool<true> TrueType;
	typedef TraitBool<false> FalseType;

	typedef char Yes;
	typedef long No;


	// Types are equal

	template <typename T, typename U>
	struct TypesAreEqual : public FalseType { };

	template <typename T>
	struct TypesAreEqual<T, T> : public TrueType { };


	// Type signedness

	template<typename T> 
	struct IsSigned : public TraitBool<T(-1) < 0> { };


	// If

	template<bool COND, typename IF_TRUE, typename IF_FALSE>
	struct If;

	template<typename IF_TRUE, typename IF_FALSE>
	struct If<true, IF_TRUE, IF_FALSE>
	{
		typedef IF_TRUE Type;
	};

	template<typename IF_TRUE, typename IF_FALSE>
	struct If<false, IF_TRUE, IF_FALSE>
	{
		typedef IF_FALSE Type;
	};

	// Wraps a constant integer value

	template<int N>
	struct Constant
	{
		enum { Result = N };
	};


	/// Returns true if Source can be converted to Destination (ie. if you can create a Destination from a Source)
	/// This means typically that either:
	/// * Source inherits publicly from Destination
	/// * Source has a public non-explicit constructor such as: Source(const Destination&)
	/// * Source can be coerced into Destination (int to double, ...)
	template< typename Source, typename Destination >
	struct IsConvertibleTo
	{
		static hkTrait::Yes isConvertible(const Destination&);
		static hkTrait::No isConvertible(...);

		enum
		{
			#ifndef __HAVOK_PARSER__
				result = (sizeof(isConvertible(*static_cast<const Source*>(0))) == sizeof(Yes)),
			#else
				result = 0
			#endif
		};
	};
}

#include <Common/Base/Types/Traits/hkTraitModifier.h>
#include <Common/Base/Types/Traits/hkTraitIsPod.h>
#include <Common/Base/Types/Traits/hkTraitArithmetic.h>

#endif // HKBASE_TRAITS_H

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
