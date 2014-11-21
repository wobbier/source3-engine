/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

template <hkaAnimationBinding::BlendHint B>
void HK_FORCE_INLINE HK_CALL hkaAdditiveAnimationUtility::computeAdditiveTransform( const hkQsTransform& origTransform, const hkQsTransform& baseTransform, hkQsTransform& resultOut )
{
	switch (B)
	{
	case hkaAnimationBinding::ADDITIVE:
		{
			resultOut.setMulInverseMul( baseTransform, origTransform );
			break;
		}
	case hkaAnimationBinding::ADDITIVE_DEPRECATED:
		{
			resultOut.setMulMulInverse( origTransform, baseTransform );
			break;
		}
	default:
		{
			HK_ASSERT2( false, 0x22440347, "Only additive blend hints are supported" );
		}
	}
}

template <hkaAnimationBinding::BlendHint B>
void HK_FORCE_INLINE HK_CALL hkaAdditiveAnimationUtility::applyAdditiveTransform( const hkQsTransform& poseTransform, const hkQsTransform& additiveTransform, hkQsTransform& resultOut )
{
	switch (B)
	{
	case hkaAnimationBinding::ADDITIVE:
		{
			resultOut.setMul( poseTransform, additiveTransform );
			break;
		}
	case hkaAnimationBinding::ADDITIVE_DEPRECATED:
		{
			resultOut.setMul( additiveTransform, poseTransform );
			break;
		}
	default:
		{
			HK_ASSERT2( false, 0x22440348, "Only additive blend hints are supported" );
		}
	}
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
