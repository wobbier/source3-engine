/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

HK_FORCE_INLINE hkaAnimation::hkaAnimation() : m_type(HK_UNKNOWN_ANIMATION)
{
	m_duration = 0;
	m_numberOfTransformTracks = 0;
	m_numberOfFloatTracks = 0;
	m_extractedMotion = HK_NULL;
}

HK_FORCE_INLINE hkaAnimation::AnimationType hkaAnimation::getType() const
{
	return m_type;
}

HK_FORCE_INLINE void hkaAnimation::getFrameAndDelta( hkReal time, hkUint32& frameOut, hkReal& deltaOut ) const
{
	const hkUint32 maxFrameIndex = getNumOriginalFrames() - 1;
	
	const hkSimdReal t = hkSimdReal::fromFloat(time);

	hkSimdReal frameFloat;
#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	hkSimdReal d; d.load<1>(&m_duration);
	frameFloat.setFromInt32((hkInt32)maxFrameIndex);
	frameFloat.mul(t / d);
	frameFloat.zeroIfFalse(d.greaterZero());
#else
	const hkSimdReal d = hkSimdReal::fromFloat(m_duration);
	if (d.isGreaterZero()) 
	{
		frameFloat = (t / d) * hkSimdReal::fromInt32((hkInt32)maxFrameIndex);
	}
	else
	{
		frameFloat.setZero();
	}
#endif
	hkSimdReal floorFrame;
	floorFrame.setFloor(frameFloat);
	floorFrame.storeSaturateInt32((hkInt32*)&frameOut);

	// Handle any roundoff error: We are always interpolating between pose[frameOut] and pose[frameOut+1]
    if (frameOut > maxFrameIndex - 1)
	{
		frameOut = maxFrameIndex - 1;
		deltaOut = hkReal(1);
		return;
	}

	hkSimdReal clampedDelta;
	clampedDelta.setClampedZeroOne(frameFloat - floorFrame);
	deltaOut = clampedDelta.getReal();
}

HK_FORCE_INLINE hkBool hkaAnimation::hasExtractedMotion() const
{
	return m_extractedMotion != HK_NULL;
}

HK_FORCE_INLINE void hkaAnimation::setExtractedMotion( const hkaAnimatedReferenceFrame* extractedMotion )
{
	m_extractedMotion = extractedMotion;
}

HK_FORCE_INLINE const hkaAnimatedReferenceFrame* hkaAnimation::getExtractedMotion() const
{
	return m_extractedMotion;
}

HK_FORCE_INLINE void hkaAnimation::getExtractedMotionReferenceFrame(hkReal time, hkQsTransform& motionOut) const
{
	return m_extractedMotion->getReferenceFrame( time, motionOut );
}

HK_FORCE_INLINE void hkaAnimation::getExtractedMotionDeltaReferenceFrame( hkReal time, hkReal nextTime, int loops, hkQsTransform& deltaMotionOut, hkReal cropStartAmount, hkReal cropEndAmount ) const
{
	return m_extractedMotion->getDeltaReferenceFrame( time, nextTime, loops, deltaMotionOut, cropStartAmount, cropEndAmount );
}

/// Sample a single animation track
HK_FORCE_INLINE void hkaAnimation::sampleSingleTransformTrack( hkReal time, hkInt16 track, hkQsTransform* transformOut ) const
{
	return sampleIndividualTransformTracks( time, &track, 1, transformOut );
}

/// Sample a single floating track
HK_FORCE_INLINE void hkaAnimation::sampleSingleFloatTrack( hkReal time, hkInt16 track, hkReal* out ) const
{
	return sampleIndividualFloatTracks( time, &track, 1, out );
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
