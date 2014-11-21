/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_PODTYPETRAITS_H
#define HKBASE_PODTYPETRAITS_H

// This can be used to define a type as a pod type.
#define HK_DEFINE_AS_POD_TYPE(T) \
	namespace hkTrait{ template<> struct IsPodType< T > : public TypeIsPod {}; }

namespace hkTrait
{
	typedef TraitBool<true> TypeIsPod;
	typedef TraitBool<false> TypeIsClass;

	template <typename T>
	hkBool::CompileTimeFalseType operator==(const T&, const TypeIsPod&);

	// Default hkIsPodType<T>::type() == hkBoolean<false>.
	template <typename T>
	struct IsPodType : public TraitBool< ( sizeof(*reinterpret_cast<T*>(128) == *reinterpret_cast<const TypeIsPod*>(128)) == sizeof(hkBool::CompileTimeTrueType) ) > {};

	// Pointers are pod types
	template <typename T> struct IsPodType<T*> : public TypeIsPod {};
	// Arrays
	template <typename T, unsigned int N> struct IsPodType<T[N]> : public IsPodType< T > {};
}

//
// Define Havok pod types.
//
HK_DEFINE_AS_POD_TYPE(bool);
HK_DEFINE_AS_POD_TYPE(hkBool);
HK_DEFINE_AS_POD_TYPE(char);
HK_DEFINE_AS_POD_TYPE(hkInt8);
HK_DEFINE_AS_POD_TYPE(hkUint8);
HK_DEFINE_AS_POD_TYPE(hkInt16);
HK_DEFINE_AS_POD_TYPE(hkUint16);
HK_DEFINE_AS_POD_TYPE(hkInt32);
HK_DEFINE_AS_POD_TYPE(hkUint32);
HK_DEFINE_AS_POD_TYPE(hkInt64);
HK_DEFINE_AS_POD_TYPE(hkUint64);
#if HK_POINTER_SIZE != 8
HK_DEFINE_AS_POD_TYPE(hkLong);
HK_DEFINE_AS_POD_TYPE(hkUlong);
#endif
HK_DEFINE_AS_POD_TYPE(hkHalf);
HK_DEFINE_AS_POD_TYPE(hkFloat32);
HK_DEFINE_AS_POD_TYPE(hkDouble64);

// This declaration is required to treat a class or struct as a pod type. Must have public visibility.
#define HK_DECLARE_POD_TYPE() \
	hkBool::CompileTimeTrueType operator== (const hkTrait::TypeIsPod&) const

#define HK_DECLARE_POD_TYPE_IF_POD(TYPE) \
	hkBool::CompileTimeTrueType operator== (const hkTrait::TraitBool< hkTrait::IsPodType< TYPE >::result >&) const

#define HK_DECLARE_CLASS_Pod(N) \
	HK_DECLARE_POD_TYPE();

#endif // HKBASE_PODTYPETRAITS_H

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
