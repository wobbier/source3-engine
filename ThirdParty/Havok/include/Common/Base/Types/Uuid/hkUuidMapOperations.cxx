/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Specialized version of hkMapOperations<> for using hkUuid in a map.
template <>
struct hkMapOperations<hkUuid>
{
	inline static unsigned hash( hkUuid key, unsigned mod ) 
	{ 
		// We take just a part of the Uuid, collisions will be more likely to happen but
		// will work well as a hash.
		return key.getData<0>() & mod; 
	}
	inline static void invalidate( hkUuid& key )
	{
		key = hkUuid::getNil();
	}
	inline static hkBool32 isValid( hkUuid key ) { return key != hkUuid::getNil(); }
	inline static hkBool32 equal( hkUuid key0, hkUuid key1 ) { return key0 == key1; }
};

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
