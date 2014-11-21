/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE void hkAabb24_16_24_Codec::packAabb( const hkAabb& aabbF, hkAabb24_16_24* HK_RESTRICT aabbOut ) const
{
	HK_ASSERT2( 0xf03ddfe5, 0 == (0xf & hkUlong(aabbOut)), "Your output aabb is not aligned.");

	hkVector4 mi;  mi.setAdd( m_bitOffsetLow,  aabbF.m_min );
	hkVector4 ma;  ma.setAdd( m_bitOffsetHigh, aabbF.m_max );
	mi.mul( m_bitScale );
	ma.mul( m_bitScale );

#if !defined(HK_INT_VECTOR_NATIVE_PERMUTE8) 
	hkVector4 minVal; minVal.setZero();
	mi.setMax( minVal, mi );
	ma.setMax( minVal, ma );
	mi.setMin( m_aabb24_16_24_Max, mi );
	ma.setMin( m_aabb24_16_24_Max, ma );

	hkIntVector imi; imi.setConvertF32toS32( mi );
	hkIntVector ima; ima.setConvertF32toS32( ma );

	{
		hkUint32 x = (hkUint32)imi.getComponent<0>();
		hkUint32 y = (hkUint32)imi.getComponent( 1+m_yzReversed );
		hkUint32 z = (hkUint32)imi.getComponent( 2-m_yzReversed );
		aabbOut->m_min.m_comp.m_xxxhy = (x<<8)  |  (y>>8);
		aabbOut->m_min.m_comp.m_lyzzz = (y<<24) |  (z);
	}
	{
		int x = ima.getComponent<0>();
		int y = ima.getComponent( 1+m_yzReversed );
		int z = ima.getComponent( 2-m_yzReversed );
		aabbOut->m_max.m_comp.m_xxxhy = (x<<8)  |  (y>>8);
		aabbOut->m_max.m_comp.m_lyzzz = (y<<24) |  (z);
	}
#else
	hkIntVector imi; imi.setConvertF32toS32( mi );
	hkIntVector ima; ima.setConvertF32toS32( ma );

	// do the min/max using integer since faster than using floating point
	hkIntVector minVal; minVal.setZero();
	imi.setMaxS32( minVal, imi );
	ima.setMaxS32( minVal, ima );
	imi.setMinS32( m_aabb24_16_24_iMax, imi );
	ima.setMinS32( m_aabb24_16_24_iMax, ima );

	imi.setPermuteU8(imi, m_packPermuteMask );
	ima.setPermuteU8(ima, m_packPermuteMask );
	((hkIntVector*)aabbOut)->setSelect<hkVector4ComparisonMask::MASK_XY>( imi, ima );

#endif	//HK_USING_GENERIC_INT_VECTOR_IMPLEMENTATION
}

HK_FORCE_INLINE void hkAabb24_16_24_Codec::unpackAabbUnscaled( const hkAabb24_16_24& aabb, hkAabb* HK_RESTRICT aabbFOut ) const
{
#if defined(HK_USING_GENERIC_INT_VECTOR_IMPLEMENTATION)
	aabbFOut->m_min(0) = hkReal(aabb.m_min.m_comp.m_xxxhy>>8);
	aabbFOut->m_max(0) = hkReal(aabb.m_max.m_comp.m_xxxhy>>8);

	aabbFOut->m_min(1+m_yzReversed) = hkReal(*(const hkUint16*)&aabb.m_min.m_u8[3]);
	aabbFOut->m_max(1+m_yzReversed) = hkReal(*(const hkUint16*)&aabb.m_max.m_u8[3]);

	aabbFOut->m_min(2-m_yzReversed) = hkReal(aabb.m_min.m_comp.m_lyzzz & 0xffffff);
	aabbFOut->m_max(2-m_yzReversed) = hkReal(aabb.m_max.m_comp.m_lyzzz & 0xffffff);
	aabbFOut->m_min(3) = hkReal(0);
	aabbFOut->m_max(3) = hkReal(0);
#elif defined(HK_INT_VECTOR_NATIVE_PERMUTE8)
#	if HK_ENDIAN_BIG
	hkIntVector zero; zero.setZero();
	hkIntVector imi; imi.setPermuteU8( (const hkIntVector&)aabb, zero, m_permuteMaskMin );
	hkIntVector ima; ima.setPermuteU8( (const hkIntVector&)aabb, zero, m_permuteMaskMax );
#	else
	// intel, does not have a full native setPermuteU8 with 2 input vectors, use single version with and
	hkIntVector imi; imi.setPermuteU8( (const hkIntVector&)aabb, m_permuteMaskMin );
	hkIntVector ima; ima.setPermuteU8( (const hkIntVector&)aabb, m_permuteMaskMax );
	imi.setAnd( imi, m_unpackMask );
	ima.setAnd( ima, m_unpackMask );
#endif
	imi.convertS32ToF32(aabbFOut->m_min);
	ima.convertS32ToF32(aabbFOut->m_max);
#else
	static const HK_ALIGN16( hkUint32 m_unpackMaskXCst[4] ) = { 0xffffff, 0, 0xffffff, 0 };
	static const HK_ALIGN16( hkUint32 m_unpackMaskYCst[4] ) = { 0xffff, 0, 0xffff, 0 };
	static const HK_ALIGN16( hkUint32 m_unpackMaskZCst[4] ) = { 0, 0xffffff, 0, 0xffffff };
	hkIntVector m_unpackMaskX; m_unpackMaskX.load<4>(m_unpackMaskXCst);
	hkIntVector m_unpackMaskY; m_unpackMaskY.load<4>(m_unpackMaskYCst);
	hkIntVector m_unpackMaskZ; m_unpackMaskZ.load<4>(m_unpackMaskZCst);
	{
		hkIntVector a; a.load<4>( (hkUint32*)(&aabb) );
#if HK_ENDIAN_LITTLE
		hkIntVector x; x.setShiftLeft128<5>( a );
		hkIntVector y; y.setShiftLeft128<3>( a );
		hkIntVector z; z.setPermutation<hkVectorPermutation::XXZZ>(a); // now we have minz minz maxz maxz
#else
		hkIntVector x; x.setPermutation<hkVectorPermutation::YXWZ>(a);
		hkIntVector y; y.setShiftRight128<3>( a );
		hkIntVector z; z.setShiftRight128<5>( a );	// now we have - minz - maxz
#endif

		y.setAnd( y, m_unpackMaskY );	// now we have miny - maxy -
		z.setAnd( z, m_unpackMaskZ );	// now we have - minz - maxz
		x.setAnd( x, m_unpackMaskX );	// now we have minx - maxx -

		x.setOr( x, z );								// now we have minx minz maxx maxz
		hkIntVector imi; imi.setMergeHead32( x,y );
		hkIntVector ima; ima.setMergeTail32( x,y );
		if ( m_yzReversed )
		{
			imi.setPermutation<hkVectorPermutation::XZYW>(imi);
			ima.setPermutation<hkVectorPermutation::XZYW>(ima);
		}
		imi.convertS32ToF32(aabbFOut->m_min);
		ima.convertS32ToF32(aabbFOut->m_max);
	}
#endif
}

HK_FORCE_INLINE void hkAabb24_16_24_Codec::restoreAabb( const hkAabb24_16_24& aabb, hkAabb* HK_RESTRICT aabbFOut ) const
{
	hkAabb unscaled;	unpackAabbUnscaled( aabb, &unscaled );
	convertIntToWorldSpace( unscaled, *aabbFOut );
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
