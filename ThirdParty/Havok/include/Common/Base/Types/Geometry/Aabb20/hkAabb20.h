/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE


#ifndef HK_AABB_20_H
#define HK_AABB_20_H

#include <Common/Base/Math/Vector/hkIntVector.h>	// needed


/// Aabb using 24 16 24 bit for each component.
/// Use the hkAabb24_16_24_Codec to convert hkAabb from and to this class. Note that the hkAabb24_16_24_Codec can 
/// swap y and z with no extra cost, so you are free to choose 16 bit for either the y or the z component.
struct hkAabb24_16_24	
{

		// -------------------------------------------------------------------------------------------------------------
		// Functions
		// -------------------------------------------------------------------------------------------------------------
		//+version(0)
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR( HK_MEMORY_CLASS_CDINFO, hkAabb24_16_24 );
		HK_DECLARE_REFLECTION();


		HK_FORCE_INLINE	void setEmpty();

		HK_FORCE_INLINE	void set( const hkAabb24_16_24& other);


		HK_FORCE_INLINE bool isEqual(const hkAabb24_16_24& testAabb) const;

		HK_FORCE_INLINE	bool isValid() const;

		HK_FORCE_INLINE	hkBoolLL disjoint(const hkAabb24_16_24& testAabb) const;

		static HK_FORCE_INLINE hkBoolLL yzDisjoint( const hkAabb24_16_24& a, const hkAabb24_16_24& b );

		/// returns true if test AABB is fully inside this, touching the border is allowed
		HK_FORCE_INLINE	bool contains( const hkAabb24_16_24& testAabb ) const;

		/// returns true if test AABB is fully inside this and is not touching the border
		HK_FORCE_INLINE	bool containsDontTouch( const hkAabb24_16_24& testAabb ) const;

// 		/// Set this to the extent of all input aabbs.
// 		void setExtents( const hkAabb24_16_24* aabbsIn, int numAabbsIn );
// 
// 		/// Set this to the extent of all input aabb centers, assumes that the bit 16 of the input aabbs is cleared
// 		void setExtentsOfCenters( const hkAabb24_16_24* aabbsIn, int numAabbsIn );
// 
// 		/// Sets this to the intersection of aabb0 and aabb1.
// 		void setIntersection( const hkAabb24_16_24& aabb0, const hkAabb24_16_24& aabb1 );

		// -------------------------------------------------------------------------------------------------------------
		// Internal implementations
		// -------------------------------------------------------------------------------------------------------------

		HK_FORCE_INLINE hkBoolLL disjoint_usingUint64(const hkAabb24_16_24& b) const;
#if defined(HK_INT_VECTOR_NATIVE_ADD64)
		HK_FORCE_INLINE hkBool32 disjoint_usingSimd2(const hkAabb24_16_24& b) const;
		HK_FORCE_INLINE hkBool32 disjoint_usingSimd4(const hkAabb24_16_24& b) const;
#endif

		// -------------------------------------------------------------------------------------------------------------
		// Fields
		// -------------------------------------------------------------------------------------------------------------

		union Coords
		{
			hkUint64 m_u64;
			struct 
			{
				// We use a platform specific byte ordering to allow for a very fast disjoint_usingUint64 implementation.
#if HK_ENDIAN_LITTLE	// intel
				// memory ordering:  lowz, midz, highz, lowy, highy, lowx, midx, highx
				hkUint32 m_lyzzz;
				hkUint32 m_xxxhy;
#else	// ppc
				// memory ordering:  highx, midx, lowx, highy, midy, highz, midz, lowz
				hkUint32 m_xxxhy;
				hkUint32 m_lyzzz;
#endif
			}        m_comp;
			hkUint8  m_u8[8];
		};

		HK_ALIGN16(Coords) m_min; //+overridetype(hkUint64)
		Coords m_max; //+overridetype(hkUint64)
};

struct hkAabb24_16_24_WithKey: public hkAabb24_16_24
{
	HK_FORCE_INLINE void getKey(hkUint16& key) const { key = (hkUint16)m_key; }
	HK_FORCE_INLINE void getKey(hkUint32& key) const { key = m_key; };

	/// compare 2 aabbs using the minXSortKey
	HK_FORCE_INLINE	friend bool operator < (const hkAabb24_16_24& a, const hkAabb24_16_24& b ){ return a.m_min.m_comp.m_xxxhy < b.m_min.m_comp.m_xxxhy; }

	/// set this to be the maximum
	HK_FORCE_INLINE	void setEndMarker();


	HK_FORCE_INLINE bool isEmpty() const;

	HK_FORCE_INLINE bool isEndMarker() const;

	HK_FORCE_INLINE hkUint32 getMinXSortKey() const;
	HK_FORCE_INLINE hkUint32 getMaxXSortKey() const;


	hkUint32 m_key;
};

#include <Common/Base/Types/Geometry/Aabb20/hkAabb20.inl>

#endif // HK_AABB_16_H

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
