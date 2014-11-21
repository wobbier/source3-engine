/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_CONSTTYPETRAITS_H
#define HKBASE_CONSTTYPETRAITS_H

namespace hkTrait
{
	typedef TraitBool<true> TypeIsConst;
	typedef TraitBool<false> TypeIsNonConst;

	// Type with one level of const removed: hkRemoveConst<int>::type is int, so is hkRemoveConst<const int>::type
	template <typename T>
	struct RemoveConst{ typedef T type; };

	template <typename T>
	struct RemoveConst<const T>{ typedef T type; };

	template <typename T>
	struct RemoveConst<T const*>{ typedef T* type; };

	template <typename T>
	struct RemoveConst<T const&>{ typedef T& type; };

	template <typename T>
	struct RemoveConst<T const*const>{ typedef T* type; };

	template <typename T>
	struct RemoveConst<T *const>{ typedef T* type; };


	template <typename T>
	struct RemoveRef { typedef T Type; };

	template <typename T>
	struct RemoveRef<T&>{ typedef T Type; };

	template <typename T>
	struct RemoveConstRef { typedef typename RemoveRef< typename RemoveConst<T>::type >::Type Type; };

	// Adds a const to the type if it isn't already const (const int => const int ; int => const int).
	template <typename T>
	struct AddConst { typedef const T type; };

	template <typename T>
	struct AddConst<const T> { typedef const T type; };

	template <typename T>
	struct AddConst<T*> { typedef const T* type; };

	template <typename T>
	struct AddConst<const T*> { typedef const T* type; };

	template <typename T>
	struct AddConst<T* const> { typedef const T*const type; };

	// Checking for "const"
	template <typename T>
	struct IsConstType : public FalseType {};
	template <typename T>
	struct IsConstType<T* const> : public FalseType {};
	template <typename T>
	struct IsConstType<const T> : public TrueType {};
	template <typename T>
	struct IsConstType<const T*> : public TrueType {};
	template <typename T>
	struct IsConstType<const T*const> : public TrueType {};


	// Adds const if the boolean parameter is true
	template <bool Add, typename Output>
	struct ConstIfTrue { typedef typename AddConst<Output>::type type; };

	template <typename Output>
	struct ConstIfTrue<false, Output> { typedef Output type; };

	// Adds const to the second parameter if the first one is const
	template <typename Input, typename Output>
	struct ConstIfConst { typedef typename ConstIfTrue<IsConstType<Input>::result, Output>::type type; };

	// Erases type while preserving constness
	template <typename T>
	struct ToVoid { typedef typename ConstIfConst<T, void*>::type type; };
}

#endif // HKBASE_CONSTTYPETRAITS_H

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
