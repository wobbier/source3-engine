/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

/// Copies dynamic and static values into their respective components, based on a mask
/// \param statmask Mask describing the static components of the data
/// \param dynmask Mask describing the dynamic components of the data
/// \param S Static values
/// \param I identity values
/// \param inOut Output with static/identity values overwritten
HK_FORCE_INLINE /*static*/ void hkaSplineCompressedAnimation::recompose( hkVector4ComparisonParameter statmask, hkVector4ComparisonParameter dynmask, hkVector4Parameter S, hkVector4Parameter I, hkVector4& inOut )
{
	inOut.setSelect( statmask, S, inOut );
	inOut.setSelect( dynmask, I, inOut );
}

/// Reads 8 bits from an internal buffer
/// \param dataInOut Buffer which is incremented
HK_FORCE_INLINE hkUint8 hkaSplineCompressedAnimation::read8( const hkUint8* HK_RESTRICT & dataInOut )
{
	return *dataInOut++;
}

/// Reads 16 bits from an internal buffer
/// \param dataInOut Buffer which is incremented
HK_FORCE_INLINE hkUint16 hkaSplineCompressedAnimation::read16( const hkUint8* HK_RESTRICT & dataInOut )
{
	return *reinterpret_cast< const hkUint16* HK_RESTRICT &  >( dataInOut )++;
}

/// Reads a real value from an internal buffer
/// \param dataInOut Buffer which is incremented
HK_FORCE_INLINE hkReal hkaSplineCompressedAnimation::readReal( const hkUint8* HK_RESTRICT & dataInOut )
{
	hkFloat32 f = *reinterpret_cast< const hkFloat32* HK_RESTRICT &  >( dataInOut )++;
	return hkReal(f);
}

template <int align>
HK_FORCE_INLINE void hkaSplineCompressedAnimation::readAlign( const hkUint8* HK_RESTRICT & dataInOut )
{
	dataInOut = reinterpret_cast< const hkUint8 * HK_RESTRICT > ( HK_NEXT_MULTIPLE_OF( align, reinterpret_cast< hk_size_t >( dataInOut ) ) );
}

/// \return A packed floating point value expanded
/// \param minp Minimum expected value
/// \param maxp Maximum expected value
/// \param Packed value to expand
HK_FORCE_INLINE hkSimdReal hkaSplineCompressedAnimation::unpack16( hkSimdRealParameter minp, hkSimdRealParameter maxp, hkUint16 val )
{
	const hkSimdReal v  = hkSimdReal::fromUint16(val);

	hkSimdReal d = ( v * hkSimdReal::fromFloat(hkReal(1)/hkReal(65535)) ) * ( maxp - minp ) + minp;

	return d;
}

HK_FORCE_INLINE void hkaSplineCompressedAnimation::unpack16vec( hkVector4Parameter minp, hkVector4Parameter maxp, const hkUint16* HK_RESTRICT vals, hkVector4& out )
{
	hkIntVector ivals; 
	ivals.load<2>((const hkUint32*)vals);
	ivals.setConvertLowerU16ToU32(ivals);

	hkVector4 v;
	ivals.convertS32ToF32(v);

	const hkSimdReal scale = hkSimdReal::fromFloat(hkReal(1)/hkReal(65535));
	v.mul(scale);
	hkVector4 span;
	span.setSub(maxp, minp);

	out.setAddMul(minp, span, v);
}



/// Unpack the representation of the given quantization types
/// \param translation The type of translation quantization given
/// \param rotation The type of rotation quantization given
/// \param scale The type of scale quantization given
HK_FORCE_INLINE void hkaSplineCompressedAnimation::unpackQuantizationTypes( hkUint8 packedQuatizationTypes, TrackCompressionParams::ScalarQuantization& translation, TrackCompressionParams::RotationQuantization& rotation, TrackCompressionParams::ScalarQuantization& scale )
{
	translation = static_cast< TrackCompressionParams::ScalarQuantization >( ( packedQuatizationTypes >> 0 ) & 0x03 );
	rotation = static_cast< TrackCompressionParams::RotationQuantization >( ( packedQuatizationTypes >> 2 ) & 0x0F );
	scale = static_cast< TrackCompressionParams::ScalarQuantization >( ( packedQuatizationTypes >> 6 ) & 0x03 );

	HK_ASSERT2( 0x3aa3eb74, TrackCompressionParams::validQuantization( translation ), "Spline data corrupt." );
	HK_ASSERT2( 0x3aa3eb74, TrackCompressionParams::validQuantization( rotation ), "Spline data corrupt." );
	HK_ASSERT2( 0x3aa3eb74, TrackCompressionParams::validQuantization( scale ), "Spline data corrupt." );
}


HK_FORCE_INLINE void hkaSplineCompressedAnimation::unpackMaskAndQuantizationType( hkUint8 packedMaskAndQuatizationType, hkUint8& mask, TrackCompressionParams::ScalarQuantization& floatQuantization )
{
	// Read in the floatQuantization from the 1st (not 0th) bit
	floatQuantization = static_cast< TrackCompressionParams::ScalarQuantization >( ( packedMaskAndQuatizationType >> 1 ) & 0x03 );
	mask = packedMaskAndQuatizationType & ~0x06;

	HK_ASSERT2( 0x3aa3eb74, TrackCompressionParams::validQuantization( floatQuantization ), "Spline data corrupt." );
	HK_ASSERT2( 0x3aa3eb74,  ( mask & 0x06 ) == 0, "Spline data corrupt." );
}


/// \return A packed floating point value expanded
/// \param minp Minimum expected value
/// \param maxp Maximum expected value
/// \param Packed value to expand
HK_FORCE_INLINE hkSimdReal hkaSplineCompressedAnimation::unpack8( hkSimdRealParameter minp, hkSimdRealParameter maxp, hkUint8 val )
{
	const hkSimdReal v  = hkSimdReal::fromUint8(val);

	hkSimdReal d = ( v * hkSimdReal_Inv_255 ) * ( maxp - minp ) + minp;

	return d;
}

HK_FORCE_INLINE void hkaSplineCompressedAnimation::unpack8vec( hkVector4Parameter minp, hkVector4Parameter maxp, const hkUint8* HK_RESTRICT vals, hkVector4& out )
{
	hkIntVector ivals; 
	ivals.load<1>((const hkUint32*)vals);
	ivals.setSplit8To32(ivals);

	hkVector4 v;
	ivals.convertS32ToF32(v);

	v.mul(hkSimdReal_Inv_255);
	hkVector4 span;
	span.setSub(maxp, minp);

	out.setAddMul(minp, span, v);
}

/// Evaluate the spline at a given time.  Chooses from several optimized function implementations
/// \param u Time to evaluate at
/// \param p Degree of the curve
/// \param U Array of knot values for the given time
/// \param P Array of control point values for the given time
/// \param out Output value
HK_FORCE_INLINE void hkaSplineCompressedAnimation::evaluate( hkReal u, int p, const hkReal* HK_RESTRICT U, const hkVector4* HK_RESTRICT P, hkVector4& out )
{
	HK_ASSERT2( 0x3aa3eb74,  p >= 1 && p <= 3, "Spline data corrupt." );

	switch (p)
	{
	case 1: evaluateSimple1( u, p, U, P, out ); break;
	case 2: evaluateSimple2( u, p, U, P, out ); break;
	case 3: evaluateSimple3( u, p, U, P, out ); break;
	default: HK_ASSERT2(0x3aa3eb74,false,"unknown compression type");
	}
}


/// Algorithm A2.1 The NURBS Book p68 - Determine the knot span index
/// \return The index i such that U[i] <= u < U[i+1]
/// \param n Max control point index
/// \param p Degree
/// \param u Knot value to find span for as byte
/// \param U Array of knots as bytes
HK_FORCE_INLINE int hkaSplineCompressedAnimation::findSpan( int n, int p, hkUint8 u, const hkUint8* U )
{
	// Bounds protect
	// Splines can extrapolate, so times (slightly) outside the range are OK.
	if ( u >= U[ n+1 ] ) return n;
	if ( u <= U[0] ) return p;

	// Search
	int low = p;
	int high = n + 1;
	int mid = ( low + high ) / 2;
	while ( u < U[mid] || u >= U[mid+1] )
	{
		if ( u < U[mid] ) high = mid;
		else low = mid;
		mid = ( low + high ) / 2;
	}
	return mid;
}

/// Find the local time within a block
/// Provides an unambiguous result for the blockOut when
/// multithreading on processors with different numeric precision.
/// The blockTimeOut may be subject to differences in precision.
/// This avoids discrepancies in boundary cases where the block
/// index is computed differently on different processors.
/// \param time Time to query the animation
/// \param blockOut Which block the local time lies within
/// \param blockTimeOut Local time within the block
/// \param quantizedTimeOut Time expressed as integer within the block
HK_FORCE_INLINE void hkaSplineCompressedAnimation::getBlockAndTime( hkUint32 frame, hkReal delta, int& blockOut, hkReal& blockTimeOut, hkUint8& quantizedTimeOut ) const
{
	// Find the appropriate block
	blockOut = frame / ( m_maxFramesPerBlock - 1 );

	// Clamp the block
	blockOut = hkMath::max2( blockOut, 0 );
	blockOut = hkMath::min2( blockOut, m_numBlocks-1 );

	// Find the local time
	const hkUint32 firstFrameOfBlock = blockOut * ( m_maxFramesPerBlock - 1 );
	const hkReal realFrame = hkReal( frame - firstFrameOfBlock ) + delta;
	blockTimeOut = realFrame * m_frameDuration;

	// Find the truncated time
	quantizedTimeOut = static_cast< hkUint8 >( ( blockTimeOut * m_blockInverseDuration ) * ( m_maxFramesPerBlock - 1 ) );
}

HK_FORCE_INLINE void hkaSplineCompressedAnimation::readAlignQuaternion( hkaSplineCompressedAnimation::TrackCompressionParams::RotationQuantization Q, const hkUint8* HK_RESTRICT & dataInOut )
{
	HK_ASSERT2( 0x3aa3eb74, TrackCompressionParams::validQuantization( Q ), "Spline data corrupt." );

	// Bit mask for byte alignment
	// Each type has it's own unique byte alignment

	switch (Q)
	{
	case TrackCompressionParams::POLAR32:		readAlign<4>( dataInOut ); break;
	case TrackCompressionParams::THREECOMP40:	readAlign<1>( dataInOut ); break;
	case TrackCompressionParams::THREECOMP48:	readAlign<2>( dataInOut ); break;
	case TrackCompressionParams::THREECOMP24:	readAlign<1>( dataInOut ); break;
	case TrackCompressionParams::STRAIGHT16:	readAlign<2>( dataInOut ); break;
	case TrackCompressionParams::UNCOMPRESSED:	readAlign<4>( dataInOut ); break;
	default: HK_ASSERT2(0x3aa3eb74,false,"unknown compression type");
	}
}

HK_FORCE_INLINE int hkaSplineCompressedAnimation::bytesPerQuaternion( hkaSplineCompressedAnimation::TrackCompressionParams::RotationQuantization Q )
{
	HK_ASSERT2( 0x3aa3eb74, TrackCompressionParams::validQuantization( Q ), "Spline data corrupt." );

	switch (Q)
	{
	case TrackCompressionParams::POLAR32:		return 4;
	case TrackCompressionParams::THREECOMP40:	return 5;
	case TrackCompressionParams::THREECOMP48:	return 6;
	case TrackCompressionParams::THREECOMP24:	return 3;
	case TrackCompressionParams::STRAIGHT16:	return 2;
	case TrackCompressionParams::UNCOMPRESSED:	return 16;
	default: HK_ASSERT2(0x3aa3eb74,false,"unknown compression type"); return 0;
	}
}

#if defined(HKA_USE_TEMPLATES)

template <>
HK_FORCE_INLINE void hkaSplineCompressedAnimation::readAlignQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::POLAR32>( const hkUint8* HK_RESTRICT & dataInOut ) const
{
	readAlign<4>( dataInOut );
}
template <>
HK_FORCE_INLINE void hkaSplineCompressedAnimation::readAlignQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::THREECOMP40>( const hkUint8* HK_RESTRICT & dataInOut ) const
{
	readAlign<1>( dataInOut );
}
template <>
HK_FORCE_INLINE void hkaSplineCompressedAnimation::readAlignQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::THREECOMP48>( const hkUint8* HK_RESTRICT & dataInOut ) const
{
	readAlign<2>( dataInOut );
}
template <>
HK_FORCE_INLINE void hkaSplineCompressedAnimation::readAlignQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::THREECOMP24>( const hkUint8* HK_RESTRICT & dataInOut ) const
{
	readAlign<1>( dataInOut );
}
template <>
HK_FORCE_INLINE void hkaSplineCompressedAnimation::readAlignQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::STRAIGHT16>( const hkUint8* HK_RESTRICT & dataInOut ) const
{
	readAlign<2>( dataInOut );
}
template <>
HK_FORCE_INLINE void hkaSplineCompressedAnimation::readAlignQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::UNCOMPRESSED>( const hkUint8* HK_RESTRICT & dataInOut ) const
{
	readAlign<4>( dataInOut );
}
template <hkaSplineCompressedAnimation::TrackCompressionParams::RotationQuantization Q>
HK_FORCE_INLINE void hkaSplineCompressedAnimation::readAlignQuaternion( const hkUint8* HK_RESTRICT & dataInOut ) const
{
	HK_ASSERT2(0x3aa3eb74,false,"unknown compression type");
}


template <>
HK_FORCE_INLINE int hkaSplineCompressedAnimation::bytesPerQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::POLAR32>() const
{
	return 4;
}
template <>
HK_FORCE_INLINE int hkaSplineCompressedAnimation::bytesPerQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::THREECOMP40>() const
{
	return 5;
}
template <>
HK_FORCE_INLINE int hkaSplineCompressedAnimation::bytesPerQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::THREECOMP48>() const
{
	return 6;
}
template <>
HK_FORCE_INLINE int hkaSplineCompressedAnimation::bytesPerQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::THREECOMP24>() const
{
	return 3;
}
template <>
HK_FORCE_INLINE int hkaSplineCompressedAnimation::bytesPerQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::STRAIGHT16>() const
{
	return 2;
}
template <>
HK_FORCE_INLINE int hkaSplineCompressedAnimation::bytesPerQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::UNCOMPRESSED>() const
{
	return 16;
}
template <hkaSplineCompressedAnimation::TrackCompressionParams::RotationQuantization Q>
HK_FORCE_INLINE int hkaSplineCompressedAnimation::bytesPerQuaternion() const
{
	HK_ASSERT2(0x3aa3eb74,false,"unknown compression type"); return 0;
}

template <>
HK_FORCE_INLINE void hkaSplineCompressedAnimation::unpackQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::POLAR32>( const hkUint8* HK_RESTRICT in, hkQuaternion* HK_RESTRICT out ) const
{
	hkaSignedQuaternion::unpackSignedQuaternion32(in,out);
}
template <>
HK_FORCE_INLINE void hkaSplineCompressedAnimation::unpackQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::THREECOMP40>( const hkUint8* HK_RESTRICT in, hkQuaternion* HK_RESTRICT out ) const
{
	hkaSignedQuaternion::unpackSignedQuaternion40(in,out);
}
template <>
HK_FORCE_INLINE void hkaSplineCompressedAnimation::unpackQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::THREECOMP48>( const hkUint8* HK_RESTRICT in, hkQuaternion* HK_RESTRICT out ) const
{
	hkaSignedQuaternion::unpackSignedQuaternion48(in,out);
}
template <>
HK_FORCE_INLINE void hkaSplineCompressedAnimation::unpackQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::THREECOMP24>( const hkUint8* HK_RESTRICT in, hkQuaternion* HK_RESTRICT out ) const
{
	hkaSignedQuaternion::unpackSignedQuaternion24(in,out);
}
template <>
HK_FORCE_INLINE void hkaSplineCompressedAnimation::unpackQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::STRAIGHT16>( const hkUint8* HK_RESTRICT in, hkQuaternion* HK_RESTRICT out ) const
{
	hkaSignedQuaternion::unpackSignedQuaternion16(in,out);
}
template <>
HK_FORCE_INLINE void hkaSplineCompressedAnimation::unpackQuaternion<hkaSplineCompressedAnimation::TrackCompressionParams::UNCOMPRESSED>( const hkUint8* HK_RESTRICT in, hkQuaternion* HK_RESTRICT out ) const
{
	hkaSignedQuaternion::unpackSignedQuaternion128(in,out);
}
template <hkaSplineCompressedAnimation::TrackCompressionParams::RotationQuantization Q>
HK_FORCE_INLINE void hkaSplineCompressedAnimation::unpackQuaternion( const hkUint8* HK_RESTRICT in, hkQuaternion* HK_RESTRICT out ) const
{
	HK_ASSERT2(0x3aa3eb74,false,"unknown compression type");
}

template <>
HK_FORCE_INLINE int hkaSplineCompressedAnimation::bytesPerComponent<hkaSplineCompressedAnimation::TrackCompressionParams::BITS8>() const
{
	return 1;
}
template <>
HK_FORCE_INLINE int hkaSplineCompressedAnimation::bytesPerComponent<hkaSplineCompressedAnimation::TrackCompressionParams::BITS16>() const
{
	return 2;
}
template <hkaSplineCompressedAnimation::TrackCompressionParams::ScalarQuantization Q>
HK_FORCE_INLINE int hkaSplineCompressedAnimation::bytesPerComponent() const
{
	HK_ASSERT2(0x3aa3eb74,false,"unknown compression type"); return 0;
}

#else

HK_FORCE_INLINE void hkaSplineCompressedAnimation::unpackQuaternion( hkaSplineCompressedAnimation::TrackCompressionParams::RotationQuantization Q, const hkUint8* HK_RESTRICT in, hkQuaternion* HK_RESTRICT out ) const
{
	HK_ASSERT2( 0x3aa3eb74, TrackCompressionParams::validQuantization(Q), "Spline data corrupt." );

	switch (Q)
	{
	case TrackCompressionParams::POLAR32:		hkaSignedQuaternion::unpackSignedQuaternion32(in,out); break;
	case TrackCompressionParams::THREECOMP40:	hkaSignedQuaternion::unpackSignedQuaternion40(in,out); break;
	case TrackCompressionParams::THREECOMP48:	hkaSignedQuaternion::unpackSignedQuaternion48(in,out); break;
	case TrackCompressionParams::THREECOMP24:	hkaSignedQuaternion::unpackSignedQuaternion24(in,out); break;
	case TrackCompressionParams::STRAIGHT16:	hkaSignedQuaternion::unpackSignedQuaternion16(in,out); break;
	case TrackCompressionParams::UNCOMPRESSED:	hkaSignedQuaternion::unpackSignedQuaternion128(in,out); break;
	default: HK_ASSERT2(0x3aa3eb74,false,"unknown compression type");
	}
}

HK_FORCE_INLINE int hkaSplineCompressedAnimation::bytesPerComponent( hkaSplineCompressedAnimation::TrackCompressionParams::ScalarQuantization Q ) const
{
	HK_ASSERT2( 0x3aa3eb74, TrackCompressionParams::validQuantization(Q), "Spline data corrupt." );

	switch (Q)
	{
	case TrackCompressionParams::BITS8:  return 1;
	case TrackCompressionParams::BITS16: return 2;
	default: HK_ASSERT2(0x3aa3eb74,false,"unknown compression type"); return 0;
	}
}

#endif

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
