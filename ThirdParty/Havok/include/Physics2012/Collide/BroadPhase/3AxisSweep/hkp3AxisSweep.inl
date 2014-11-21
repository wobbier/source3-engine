/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */


/*static*/ HK_FORCE_INLINE void HK_CALL hkp3AxisSweep::_convertAabbToInt( const hkAabb& aabb, hkVector4Parameter offsetLow, hkVector4Parameter offsetHigh, hkVector4Parameter scale, hkAabbUint32& aabbOut )
{
	HK_ASSERT3(0x4868f302,  aabb.isValid(), "AABB at " << &aabb << " was invalid. (Contains a NaN or min > max)");

	HK_COMPILE_TIME_ASSERT( HK_OFFSET_EQUALS( hkAabbUint32, m_min, 0 ) );
	HK_COMPILE_TIME_ASSERT( HK_OFFSET_EQUALS( hkAabbUint32, m_max, 0x10 ) );

#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkVector4 clipMin; clipMin.setZero();
	hkVector4 clipMax; clipMax.m_quad = hkp3AxisSweep::s_MaxVal;

#if !defined(HK_BROADPHASE_32BIT)
	// there is no need to saturate if the clip max fits in bitwidth
	HK_COMPILE_TIME_ASSERT( hkp3AxisSweep::AABB_MAX_FVALUE <= 0xffff );
#endif
	{
		hkVector4 x;
		x.setAdd(aabb.m_min, offsetLow);
		x.mul(scale);
		x.setMin(x,clipMax);
		x.setMax(x,clipMin);
		hkIntVector i;
		i.setConvertF32toS32(x); // signed conversion is ok because min = 0
		i.setShiftRight32<1>(i);
		i.setShiftLeft32<1>(i); // clear LSB
		i.store<3>(&aabbOut.m_min[0]); // the aabb class is aligned
	}
	{
		hkVector4 x;
		x.setAdd(aabb.m_max, offsetHigh);
		x.mul(scale);
		x.setMin(x,clipMax);
		x.setMax(x,clipMin);
		hkIntVector i;
		i.setConvertF32toS32(x); // signed conversion is ok because min = 0
		i.setOr(i, hkIntVector::getConstant<HK_QUADINT_1>());
		i.store<3>(&aabbOut.m_max[0]); // the aabb class is aligned
	}

#else // FPU

#if !defined(HK_BROADPHASE_32BIT)
	hkVector4 clipMin; clipMin.setZero();
	hkVector4 clipMax; clipMax.m_quad = hkp3AxisSweep::s_MaxVal;

	HK_ALIGN16(hkIntUnion64 mi);
	HK_ALIGN16(hkIntUnion64 ma);

	hkVector4Util::convertToUint16WithClip( aabb.m_min, offsetLow, scale,	clipMin, clipMax, mi );
	hkVector4Util::convertToUint16WithClip( aabb.m_max, offsetHigh, scale,	clipMin, clipMax, ma );

	aabbOut.m_min[0] = mi.u16[0] & 0xfffe;
	aabbOut.m_min[1] = mi.u16[1] & 0xfffe;
	aabbOut.m_min[2] = mi.u16[2] & 0xfffe;
	aabbOut.m_max[0] = ma.u16[0] | 1;
	aabbOut.m_max[1] = ma.u16[1] | 1;
	aabbOut.m_max[2] = ma.u16[2] | 1;
#else
	hkAabbUtil::convertAabbToUint32(aabb, offsetLow, offsetHigh, scale, aabbOut);

	aabbOut.m_min[0] &= 0xfffffffe;
	aabbOut.m_min[1] &= 0xfffffffe;
	aabbOut.m_min[2] &= 0xfffffffe;
	aabbOut.m_max[0] |= 1;
	aabbOut.m_max[1] |= 1;
	aabbOut.m_max[2] |= 1;
#endif

#endif // simd
}

HK_FORCE_INLINE void hkp3AxisSweep::convertAabbToInt( const hkAabb& aabb, hkAabbUint32& aabbOut ) const
{
	HK_ASSERT2(0xaf542fe1, m_scale.lengthSquared<4>().isNotEqualZero(), "Make sure to call set32BitOffsetAndScale() after creating the broadphase.");

	_convertAabbToInt( aabb, m_offsetLow, m_offsetHigh, m_scale, aabbOut );
}

HK_FORCE_INLINE void hkp3AxisSweep::convertVectorToInt( hkVector4Parameter vec, hkUint32* intsOut) const
{
	HK_ASSERT2(0xaf542fe7, m_scale.lengthSquared<4>().isNotEqualZero(), "Make sure to call set32BitOffsetAndScale() after creating the broadphase.");

	hkVector4 clipMin; clipMin.setZero();
	hkVector4 clipMax; clipMax.m_quad = hkp3AxisSweep::s_MaxVal;

	hkVector4 x;
	x.setAdd(vec, m_offsetLow);
	x.mul(m_scale);
	x.setMin(x,clipMax);
	x.setMax(x,clipMin);
	hkIntVector i;
	i.setConvertF32toS32(x); // signed conversion is ok because min = 0
	i.store<4>(intsOut);
}

#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_DISABLED) && !defined(HK_BROADPHASE_32BIT)

// adapted from http://www.hackersdelight.org/corres.txt (search for usaddv8qi)
// adds 1 to x, makes sure that the result is <= 0xFFFFF, and sets the low bit.
// So calling this on 0xFFFD, 0xFFFE, and 0xFFFF will all return 0xFFFF
static HK_FORCE_INLINE hkUint32 add1SaturateAndSetLowBit(hkUint32 x)
{
	//hkUint32 y = 1;
	//hkUint32 t0, t1;
	//const hkUint32 signMask = 0x8000;

	//t0 = (y ^ x) & signMask;
	//t1 = (y & x) & signMask;

	//x &= ~signMask;
	//y &= ~signMask;
	//x += y;

	//t1 |= t0 & x;
	// // The original code shifted right by 7, but they were dealing with bytes
	//t1 = (t1 << 1) - (t1 >> 15);
	// // We also need to OR with 1 here
	//return ( (x ^ t0) | t1 ) | 1;

	HK_ASSERT2(0xDE115E10, x <= 0xFFFF, "Bad AABB value.  Check that the hkpWorldObject's transform doesn't contain INFINITY or NAN");

	x = (x == 0xFFFF) ? x : x+1;
	return x | 1;
}
#endif

HK_FORCE_INLINE void hkp3AxisSweep::convertAabbToBroadPhaseResolution(const hkAabbUint32& aabbIn, hkAabbUint32& aabbOut) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)

	const hkIntVector one = hkIntVector::getConstant<HK_QUADINT_1>();
	hkIntVector mins; mins.load<4>(&aabbIn.m_min[0]);
	hkIntVector maxs; maxs.load<4>(&aabbIn.m_max[0]);

#if !defined(HK_BROADPHASE_32BIT)
	mins.setShiftRight32<15>(mins);
	maxs.setShiftRight32<15>(maxs);
	maxs.setAddSaturateU16(maxs, one); // note 'one' is setup S32
#endif

	mins.setShiftRight32<1>(mins);
	mins.setShiftLeft32<1>(mins); // clear LSB
	mins.store<3>(&aabbOut.m_min[0]);
	maxs.setOr(maxs, one);
	maxs.store<3>(&aabbOut.m_max[0]);

#else // FPU

#if !defined(HK_BROADPHASE_32BIT)
	aabbOut.m_min[0] = aabbIn.m_min[0] >> 15;
	aabbOut.m_min[1] = aabbIn.m_min[1] >> 15;
	aabbOut.m_min[2] = aabbIn.m_min[2] >> 15;
	aabbOut.m_max[0] = add1SaturateAndSetLowBit(aabbIn.m_max[0] >> 15);
	aabbOut.m_max[1] = add1SaturateAndSetLowBit(aabbIn.m_max[1] >> 15);
	aabbOut.m_max[2] = add1SaturateAndSetLowBit(aabbIn.m_max[2] >> 15);

	aabbOut.m_min[0] &= 0xfffe;
	aabbOut.m_min[1] &= 0xfffe;
	aabbOut.m_min[2] &= 0xfffe;
#else
	aabbOut.m_min[0] = aabbIn.m_min[0] & 0xfffffffe;
	aabbOut.m_min[1] = aabbIn.m_min[1] & 0xfffffffe;
	aabbOut.m_min[2] = aabbIn.m_min[2] & 0xfffffffe;
	aabbOut.m_max[0] = aabbIn.m_max[0] | 1;
	aabbOut.m_max[1] = aabbIn.m_max[1] | 1;
	aabbOut.m_max[2] = aabbIn.m_max[2] | 1;
#endif

#endif // simd
}


HK_FORCE_INLINE void hkp3AxisSweep::getOffsetLowHigh32bit(hkVector4& offsetLow32bit, hkVector4& offsetHigh32bit) const
{
	offsetLow32bit  = m_offsetLow32bit;
	offsetHigh32bit = m_offsetHigh32bit;
}


HK_FORCE_INLINE int hkp3AxisSweep::getNumMarkers() const
{
	return m_numMarkers;
}


HK_FORCE_INLINE hkBool32 hkp3AxisSweep::hkpBpNode::yzDisjoint( const hkpBpNode& other ) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_PLATFORM_XBOX360) && !defined(HK_PLATFORM_PS3_PPU)

	hkIntVector A,B;
#ifndef HK_BROADPHASE_32BIT
	A.loadNotAligned<2>((const hkUint32*)&min_y);       // miny minz maxy maxz as U16
	B.loadNotAligned<2>((const hkUint32*)&other.min_y);

	A.setConvertLowerU16ToU32(A);  // miny minz maxy maxz as U32
	B.setConvertLowerU16ToU32(B);
#else
	A.loadNotAligned<4>(&min_y);       // miny minz maxy maxz as U32
	B.loadNotAligned<4>(&other.min_y);
#endif

	hkIntVector Aperm; Aperm.setPermutation2<2,3,6,7>(A,B);
	hkIntVector Bperm; Bperm.setPermutation2<0,1,4,5>(B,A);

	hkIntVector s; s.setSubS32(Aperm, Bperm);

	return s.lessZeroS32().anyIsSet();

#else // FPU

#ifndef HK_BROADPHASE_32BIT
	hkUint32 minA = *reinterpret_cast<const hkUint32*>(&min_y);
	hkUint32 minB = *reinterpret_cast<const hkUint32*>(&other.min_y);
	hkUint32 maxA = *reinterpret_cast<const hkUint32*>(&max_y);
	hkUint32 maxB = *reinterpret_cast<const hkUint32*>(&other.max_y);
	maxA -= minB;
	maxB -= minA;
	maxA |= maxB;		// or the sign bits
	maxA &= 0x80008000;	// get the sign bits
	return maxA;
#else
	hkUint32 a = hkUint32(max_y) - other.min_y;
	hkUint32 b = hkUint32(max_z) - other.min_z;
	hkUint32 c = hkUint32(other.max_y) - min_y;
	hkUint32 d = hkUint32(other.max_z) - min_z;
	a |= b;
	c |= d;
	c |= a;
	return c & 0x80000000;
#endif

#endif
}

HK_FORCE_INLINE hkBool32 hkp3AxisSweep::hkpBpNode::xyDisjoint( const hkpBpNode& other ) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_PLATFORM_XBOX360) && !defined(HK_PLATFORM_PS3_PPU)

	hkIntVector A,B,A1,B1;

#ifndef HK_BROADPHASE_32BIT
	A.loadNotAligned<4>((const hkUint32*)&min_y);       // miny minz maxy maxz minx maxx as U16
	B.loadNotAligned<4>((const hkUint32*)&other.min_y);

	A1.setPermutation<hkVectorPermutation::YZZW>(A); // maxy maxz minx maxx as U16
	B1.setPermutation<hkVectorPermutation::YZZW>(B);

	A.setConvertLowerU16ToU32(A);  // miny minz maxy maxz as U32
	B.setConvertLowerU16ToU32(B);

	A1.setConvertLowerU16ToU32(A1);  // maxy maxz minx maxx as U32
	B1.setConvertLowerU16ToU32(B1);
#else
	A.loadNotAligned<4>(&min_y);       // miny minz maxy maxz as U32
	B.loadNotAligned<4>(&other.min_y);

	A1.loadNotAligned<4>(&max_y);       // maxy maxz minx maxx as U32
	B1.loadNotAligned<4>(&other.max_y);
#endif
	hkIntVector A2; A2.setSelect<hkVector4ComparisonMask::MASK_XY>(A,A1); // miny minz minx maxx as U32
	hkIntVector B2; B2.setSelect<hkVector4ComparisonMask::MASK_XY>(B,B1);

	hkIntVector Aperm; Aperm.setPermutation2<0,3,4,7>(A1,B1); //       maxy       maxx other.maxy other.maxx
	hkIntVector Bperm; Bperm.setPermutation2<0,2,4,6>(B2,A2); // other.miny other.minx       miny       minx

	hkIntVector s; s.setSubS32(Aperm, Bperm);

	return s.lessZeroS32().anyIsSet();

#else // FPU

	BpInt a = max_y - other.min_y;
	BpInt b = max_x - other.min_x;
	BpInt c = other.max_y - min_y;
	BpInt d = other.max_x - min_x;
	a |= b;
	c |= d;
	c |= a;
#ifndef HK_BROADPHASE_32BIT
	return c & 0x8000;
#else
	return c & 0x80000000;
#endif

#endif
}

HK_FORCE_INLINE hkBool32 hkp3AxisSweep::hkpBpNode::xzDisjoint( const hkpBpNode& other ) const
{
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED) && !defined(HK_PLATFORM_XBOX360) && !defined(HK_PLATFORM_PS3_PPU)

	hkIntVector A,B,A1,B1;

#ifndef HK_BROADPHASE_32BIT
	A.loadNotAligned<2>((const hkUint32*)&min_z);       // minz maxy maxz minx as U16
	B.loadNotAligned<2>((const hkUint32*)&other.min_z);

	A.setConvertLowerU16ToU32(A);  // minz maxy maxz minx as U32
	B.setConvertLowerU16ToU32(B);

	A1.loadNotAligned<2>((const hkUint32*)&max_y);       // maxy maxz minx maxx as U16
	B1.loadNotAligned<2>((const hkUint32*)&other.max_y);

	A1.setConvertLowerU16ToU32(A1);  // maxy maxz minx maxx as U32
	B1.setConvertLowerU16ToU32(B1);
#else
	A.loadNotAligned<4>(&min_z);       // minz maxy maxz minx as U32
	B.loadNotAligned<4>(&other.min_z);

	A1.loadNotAligned<4>(&max_y);       // maxy maxz minx maxx as U32
	B1.loadNotAligned<4>(&other.max_y);
#endif

	hkIntVector Aperm; Aperm.setPermutation2<3,1,7,5>(A1,B1);
	hkIntVector Bperm; Bperm.setPermutation2<3,0,7,4>(B,A);

	hkIntVector s; s.setSubS32(Aperm, Bperm);

	return s.lessZeroS32().anyIsSet();

#else // FPU

#ifndef HK_BROADPHASE_32BIT
	hkInt16 a = max_x - other.min_x;
	hkInt16 b = max_z - other.min_z;
	hkInt16 c = other.max_x - min_x;
	hkInt16 d = other.max_z - min_z;
	a |= b;
	c |= d;
	c |= a;
	return c & 0x8000;
#else
	hkUint32 a = max_x - other.min_x;
	hkUint32 b = max_z - other.min_z;
	hkUint32 c = other.max_x - min_x;
	hkUint32 d = other.max_z - min_z;
	a |= b;
	c |= d;
	c |= a;
	return c & 0x80000000;
#endif

#endif
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
