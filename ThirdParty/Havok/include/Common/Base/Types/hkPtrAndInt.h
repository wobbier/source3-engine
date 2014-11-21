/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_HKPTRANDFLAGS_H
#define HKBASE_HKPTRANDFLAGS_H

/// A simple helper class which encapsulates a pointer and an integer value inside a hkUlong.
template <class PTYPE, class ITYPE = unsigned, ITYPE MASK = 0x3>
class hkPtrAndInt
{
	public:

		HK_DECLARE_PLACEMENT_ALLOCATOR();

		/// Default constructor.
		/// Stored pointer is set to HK_NULL.
		HK_FORCE_INLINE hkPtrAndInt();

		/// Sets pointer and integer.
		HK_FORCE_INLINE hkPtrAndInt(PTYPE* pntr, ITYPE i = 0);

		/// Copy constructor.
		/// Copies pointer and integer.
		HK_FORCE_INLINE hkPtrAndInt(const hkPtrAndInt& p);

		/// Assignment operator.
		/// Copies pointer and integer.
		HK_FORCE_INLINE void operator=(const hkPtrAndInt& p);

		/// Returns the stored pointer.
		HK_FORCE_INLINE PTYPE* operator->() const;

		/// Returns the stored pointer.
		HK_FORCE_INLINE operator PTYPE*() const;
		
		/// Returns the stored pointer.
		HK_FORCE_INLINE PTYPE* getPtr() const;

		/// Returns the integer value.
		HK_FORCE_INLINE ITYPE getInt() const;

		/// Sets the pointer value.
		/// The integer value is not modified.
		HK_FORCE_INLINE void setPtr(PTYPE* p);

		/// Sets the integer value.
		/// The pointer is not modified.
		HK_FORCE_INLINE void setInt(ITYPE p);

	private:

		hkUlong m_ptrAndInt;
};

#include <Common/Base/Types/hkPtrAndInt.inl>

#endif // HKBASE_HKPTRANDFLAGS_H

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
