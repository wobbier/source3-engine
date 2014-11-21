/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HKBASE_UUID_H
#define HKBASE_UUID_H

extern HK_EXPORT_COMMON const hkClass hkUuidClass; 

/// Havok UUID class.
/// A Universally Unique IDentifier (UUID) guarantees uniqueness across space and time and can be used to identify
/// different entities. There are several variants of UUIDs defined by different standards:
/// - NCS backward compatibility
/// - RFC-4122
/// - Microsoft Corporation backward compatibility (used for COM)
/// Havok UUIDs adhere to the RFC-4122 standard in terms of generation algorithms.
/// A generic UUID obtained from a different source can still be stored in an hkUuid.
class HK_EXPORT_COMMON hkUuid
{
	//+version(1)
	
	public:
		
		// This class is a C++ aggregate.
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkUuid);
		HK_DECLARE_POD_TYPE();
		HK_DECLARE_REFLECTION();

		/// Constructor
		hkUuid(hkUint32 d0 = 0, hkUint32 d1 = 0, hkUint32 d2 = 0, hkUint32 d3 = 0);

		/// Serialization constructor
		hkUuid(hkFinishLoadedObjectFlag flag);
		
		/// Returns the Nil UUID according to RFC-4122 (a UUID whose all bits are zero).
		static const hkUuid& getNil();

		/// Returns true if the string passed in represents a valid UUID string.
		static bool isValidUuidString(const char* uuidString);

		// Implicit default constructor is available for usage.
		// Implicit copy constructor is available for usage.
		// Implicit copy assignment operator is available for usage.

		/// Sets the value as a new, random Uuid. This random generation ensures that
		/// the probability of a collision is basically too low to be considered possible.
		/// In other words, the generated hkUuid value can be considered unique.
		void setRandom();

		/// Sets the value of the hkUuid from a given string in the standard format:
		/// XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX.
		/// This function ignores the casing of hexadecimal digits in the string.
		/// If the given string is invalid, HK_FAILURE is returned and this UUID is not changed.
		hkResult setFromString(const char* uuidString);

		/// Sets the UUID as a combination of a few different UUIDs passed in. If the arguments are exactly
		/// the same, the result is guaranteed to be the same, it is a deterministic process.
		void setCombination(const hkUuid& uuid1, const hkUuid& uuid2);

		/// Set to a deterministic combination of the input UUID and the given null terminated text string.
		void setCombination(const hkUuid& uuid, const char* combineString);

		/// Comparison operator (equality).
		inline bool operator==(const hkUuid& rhs) const;

		/// Comparison operator (inequality).
		inline bool operator!=(const hkUuid& rhs) const;

		/// Prints a human readable representation of the UUID in the given string buffer, 
		/// the returned string will be in the standard format XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX.
		/// The returned pointer references the contents of the string buffer.
		const char* toString(hkStringBuf& sbuf) const;

		/// Gets the data
		template <int I> HK_FORCE_INLINE hkUint32 getData() const;
		HK_FORCE_INLINE hkUint32 getData(int I) const;

		/// Sets the data
		template <int I> HK_FORCE_INLINE void setData(hkUint32 v);
		HK_FORCE_INLINE void setData(int I, hkUint32 v);

	protected:

		hkUint32 m_data[4];
};

// Make sure that the size of an hkUuid is 128 bits (16 bytes).
HK_COMPILE_TIME_ASSERT(sizeof(hkUuid) == 16);

#include <Common/Base/Types/Uuid/hkUuid.inl>

#endif // HKBASE_UUID_H

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
