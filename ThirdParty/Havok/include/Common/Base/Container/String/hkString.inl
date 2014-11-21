/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

void HK_CALL hkString::memCpy4( void* dst, const void* src, int numWords)
{
	const hkUint32* src32 = reinterpret_cast<const hkUint32*>(src);
	hkUint32* dst32       = reinterpret_cast<      hkUint32*>(dst);
	{
		for (int i = 0; i < numWords; i++)
		{
			*(dst32++) = *(src32++);
		}
	}
}

void HK_CALL hkString::memCpy16( void* dst, const void* src, int numQuads)
{
	HK_ASSERT2( 0xf021d445, (hkUlong(dst) & HK_NATIVE_ALIGN_CHECK ) == 0, "Unaligned address" );
	HK_ASSERT2( 0xf021d446, (hkUlong(src) & HK_NATIVE_ALIGN_CHECK ) == 0, "Unaligned address" );
	
	const hkQuadFloat32* srcQuad = reinterpret_cast<const hkQuadFloat32*>(src);
	hkQuadFloat32* dstQuad = reinterpret_cast<hkQuadFloat32*>(dst);
	{
		if ( numQuads )
		{
			do
			{
				*(dstQuad++) = *(srcQuad++);
			}
			while(--numQuads);
		}
// 		for (int i = numQuads-1; i>=0; i--)	// this loop will be detected by the compiler and replaced by a slow ooo call to ::memcpy
// 		{
// 			*(dstQuad++) = *(srcQuad++);
// 		}
	}
}

void HK_CALL hkString::memCpy16NonEmpty( void* dst, const void* src, int numQuads)
{
	HK_ASSERT2( 0xf022d444, numQuads > 0, "Size 0 not allowed" );
#if ( HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && ( defined(HK_PLATFORM_WIN32) || defined(HK_PLATFORM_X64) || defined (HK_PLATFORM_PS3_PPU) || defined (HK_PLATFORM_PS3_SPU) || defined( HK_PLATFORM_XBOX360 ) || defined( HK_PLATFORM_PS4 ) )
	
	HK_ASSERT2( 0xf022d445, (hkUlong(dst) & HK_NATIVE_ALIGN_CHECK) == 0, "Unaligned address" );
	HK_ASSERT2( 0xf022d446, (hkUlong(src) & HK_NATIVE_ALIGN_CHECK) == 0, "Unaligned address" );
	const hkQuadFloat32* srcQuad = reinterpret_cast<const hkQuadFloat32*>(src);
	hkQuadFloat32* dstQuad = reinterpret_cast<hkQuadFloat32*>(dst);
	{
		do
		{
			*(dstQuad++) = *(srcQuad++);
		}
		while ( --numQuads > 0 );
	}
	
#else

	#if defined(HK_ALIGN_RELAX_CHECKS)  // stack allocated vars not aligned to 16 etc, yet a lot of code uses this call to init the vars. As it is only using uint32, it only has to be 4 byte aligned anyway.
	    HK_ASSERT2( 0xf022d445, (hkUlong(dst) & 0x03) == 0, "Unaligned address" );
	    HK_ASSERT2( 0xf022d446, (hkUlong(src) & 0x03) == 0, "Unaligned address" );
	#else
	    HK_ASSERT2( 0xf022d445, (hkUlong(dst) & 0xf) == 0, "Unaligned address" );
	    HK_ASSERT2( 0xf022d446, (hkUlong(src) & 0xf) == 0, "Unaligned address" );
	#endif
	const hkUint32* src32 = reinterpret_cast<const hkUint32*>(src);
	hkUint32* dst32 = reinterpret_cast<      hkUint32*>(dst);
	{
		do
		{
			hkUint32 a = src32[0];
			hkUint32 b = src32[1];
			hkUint32 c = src32[2];
			hkUint32 d = src32[3];
			dst32[0] = a;
			dst32[1] = b;
			dst32[2] = c;
			dst32[3] = d;
			dst32+= 4;
			src32+= 4;
		}
		while ( --numQuads > 0 );
	}
#endif
}

template<int size>
void HK_CALL hkString::memCpy16(void* dst, const void* src)
{
	HK_ASSERT( 0xf0dedf34, ((size & 0xf) == 0) && (size <= 192) && (size > 0));
#if HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED

	const int maxSize = 64;
	
	if ( size <= maxSize )
	{
		const hkQuadFloat32* srcQuad = reinterpret_cast<const hkQuadFloat32*>(src);
		hkQuadFloat32*       dstQuad = reinterpret_cast<hkQuadFloat32*>(dst);
		hkQuadFloat32 a,b,c,d;
		if ( size >  0) a = srcQuad[0];
		if ( size > 16) b = srcQuad[1];
		if ( size > 32) c = srcQuad[2];
		if ( size > 48) d = srcQuad[3];
		if ( size >  0) dstQuad[0] = a;
		if ( size > 64) a = srcQuad[4];
		if ( size > 16) dstQuad[1] = b;
		if ( size > 80) b = srcQuad[5];
		if ( size > 32) dstQuad[2] = c;
		if ( size > 96) c = srcQuad[6];
		if ( size > 48) dstQuad[3] = d;
		if ( size > 112) d = srcQuad[7];
		if ( size > 64) dstQuad[4] = a;
		if ( size > 128) a = srcQuad[8];
		if ( size > 80) dstQuad[5] = b;
		if ( size > 144) b = srcQuad[9];
		if ( size > 96) dstQuad[6] = c;
		if ( size > 160) c = srcQuad[10];
		if ( size > 112) dstQuad[7] = d;
		if ( size > 176) d = srcQuad[11];
		if ( size > 128) dstQuad[8] = a;
		if ( size > 144) dstQuad[9] = b;
		if ( size > 160) dstQuad[10] = c;
		if ( size > 176) dstQuad[11] = d;
	}
	else
#endif // config simd
	{
		hkString::memCpy16NonEmpty(dst, src, size/16);
	}
}

void HK_CALL hkString::memCpy256(void* dst, const void* src)
{
	hkString::memCpy16NonEmpty(dst, src, 16);
}

void HK_CALL hkString::memSet4(void* dst, const int value, int numWords)
{
	hkUint32* dst32 = reinterpret_cast<      hkUint32*>(dst);
	for (int i = numWords-1; i>=0; i--)
	{
		*dst32 = value;
		dst32++;
	}
}

void HK_CALL hkString::memClear16(void* dst, int numQuads)
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	HK_ASSERT2( 0xf021d445, (hkUlong(dst) & HK_NATIVE_ALIGN_CHECK ) == 0, "Unaligned address" );
	hkVector4f zero;
	zero = hkVector4f::getZero();	// using zero.setZero(); does not work, as the compiler will replace this loop with on out of line call to memset
	hkVector4f* dstQuad = (hkVector4f*)dst;
	for (int i = numQuads-1; i>=0; i--)
	{
		*(dstQuad++) = zero;
	}
#else

#if defined(HK_ALIGN_RELAX_CHECKS) // stack allocated vars not aligned to 16 etc, yet a lot of code uses this call to init the vars. As it is only using uint32, it only has to be 4 byte aligned anyway.
	HK_ASSERT2( 0xf021d445, (hkUlong(dst)   & 0x03) == 0, "Unaligned address" );
#else
	HK_ASSERT2( 0xf021d445, (hkUlong(dst)   & 0xf) == 0, "Unaligned address" );
#endif
	hkUint32* dst32 = reinterpret_cast<      hkUint32*>(dst);
	{
		for (int i = 0; i < numQuads; i++)
		{
			dst32[0] = 0;
			dst32[1] = 0;
			dst32[2] = 0;
			dst32[3] = 0;
			dst32+= 4;
		}
	}
#endif
}


// For size up to 512 bytes, on PlayStation(R)3, this will compile down to a sequence of store instructions
// For larger copies or other platforms, it reverts to the looped version.
template<int size>
void HK_CALL hkString::memSet16(void* dst, const void* HK_RESTRICT src)
{
	HK_ASSERT( 0xf0dedf34, ((size & 0xf) == 0) && (size > 0) );

	{
		hkString::memSet16(dst, src, size/16);
	}
}

void HK_CALL hkString::memSet16(void* dst, const void* value, int numQuads)
{
	const hkQuadFloat32* valueQuad = reinterpret_cast<const hkQuadFloat32*>(value);
	hkQuadFloat32* dstQuad = reinterpret_cast<hkQuadFloat32*>(dst);
	{
		hkQuadFloat32 v = *(valueQuad);
		for (int i = numQuads-1; i>=0; i--)
		{
			*(dstQuad++) = v;
		}
	}
}

HK_FORCE_INLINE int HK_CALL hkString::memCmpUint32(const hkUint32* buf1, const hkUint32* buf2, int n)
{
	for (int i =0; i < n; i++)
	{
		if ( buf1[i] == buf2[i] )
		{
			continue;
		}
		if ( buf1[i] < buf2[i] )
		{
			return -1;
		}
		return 1;
	}
	return 0;
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
