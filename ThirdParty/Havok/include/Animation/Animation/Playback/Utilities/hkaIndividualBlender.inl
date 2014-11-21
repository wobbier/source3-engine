/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

// Interpolates n hkReal pairs with a single alpha
void hkaBlender::blend( hkReal* HK_RESTRICT dst, const hkReal* HK_RESTRICT srcL, const hkReal* HK_RESTRICT srcR, const hkSimdReal& alpha, int n, BLEND_MODE blendMode )
{
	HK_ASSERT2( 0x1230c277, blendMode == NORMAL || blendMode == ADDITIVE || blendMode == SUBTRACTIVE, "Invalid blend mode" );
	if(n <= 0)
	{
		return;
	}

	const hkSimdReal beta = hkSimdReal_1 - alpha;

	switch ( blendMode )
	{
	case NORMAL:
		{
			{
				hkSimdReal srcLi; srcLi.load<1>(&srcL[0]);
				hkSimdReal srcRi; srcRi.load<1>(&srcR[0]);

				for( int i = 0; i < n-1; ++i )
				{
					hkSimdReal dsti = srcLi * beta + srcRi * alpha;
					srcLi.load<1>(&srcL[i+1]);
					srcRi.load<1>(&srcR[i+1]);
					dsti.store<1>(&dst[i]);
				}
				(srcLi * beta + srcRi * alpha).store<1>(&dst[n-1]);
			}
			break;
		}
	case ADDITIVE:
		{
			hkSimdReal srcLi; srcLi.load<1>(&srcL[0]);
			hkSimdReal srcRi; srcRi.load<1>(&srcR[0]);

			for( int i = 0; i < n-1; ++i )
			{
				hkSimdReal dsti = srcLi + srcRi * alpha;
				srcLi.load<1>(&srcL[i+1]);
				srcRi.load<1>(&srcR[i+1]);
				dsti.store<1>(&dst[i]);
			}
			(srcLi + srcRi * alpha).store<1>(&dst[n-1]);
		}

		break;

	case SUBTRACTIVE:
		{
			hkSimdReal srcLi; srcLi.load<1>(&srcL[0]);
			hkSimdReal srcRi; srcRi.load<1>(&srcR[0]);

			for( int i = 0; i < n-1; ++i )
			{
				hkSimdReal dsti = srcLi - srcRi * alpha;
				srcLi.load<1>(&srcL[i+1]);
				srcRi.load<1>(&srcR[i+1]);
				dsti.store<1>(&dst[i]);
			}
			(srcLi - srcRi * alpha).store<1>(&dst[n-1]);
		}

		break;
	}
}

// Interpolates n hkVector4 pairs with a single alpha
void hkaBlender::blend( hkVector4* HK_RESTRICT dst, const hkVector4* HK_RESTRICT srcL, const hkVector4* HK_RESTRICT srcR, const hkSimdReal& alpha, int n, BLEND_MODE blendMode )
{
	HK_ASSERT2( 0x1c0d4a7b, blendMode == NORMAL || blendMode == ADDITIVE || blendMode == SUBTRACTIVE, "Invalid blend mode" );

	switch ( blendMode )
	{
	case NORMAL:
		for ( int i = 0; i < n; i++ )
		{
			dst[ i ].setInterpolate( srcL[ i ], srcR[ i ], alpha );
		}
		break;

	case ADDITIVE:
		for ( int i = 0; i < n; i++ )
		{
			dst[ i ].setAddMul( srcL[ i ], srcR[ i ], alpha );
		}
		break;

	case SUBTRACTIVE:
		for ( int i = 0; i < n; i++ )
		{
			dst[ i ].setSubMul( srcL[ i ], srcR[ i ], alpha );
		}
		break;
	}
}

// Interpolates n hkQuaternion pairs with a single alpha
void hkaBlender::blend( hkQuaternion* HK_RESTRICT dst, const hkQuaternion* HK_RESTRICT srcL, const hkQuaternion* HK_RESTRICT srcR, const hkSimdReal& alpha, int n, BLEND_MODE blendMode, ROTATION_MODE rotationMode )
{
	HK_ASSERT2( 0x07d385bf, rotationMode == LERP || rotationMode == SLERP, "Invalid rotation mode" );
	HK_ASSERT2( 0x0f9e68fa, blendMode == NORMAL || blendMode == ADDITIVE || blendMode == SUBTRACTIVE, "Invalid blend mode" );

	
	if ( rotationMode == SLERP )
	{
		// SLERP
		switch ( blendMode )
		{
		case NORMAL:
			for ( int i = 0; i < n; i++ )
			{
				dst[ i ].setSlerp( srcL[ i ], srcR[ i ], alpha );
			}
			break;

		case ADDITIVE:
			for ( int i = 0; i < n; i++ )
			{
				hkQuaternion comp;
				comp.setMul( srcL[ i ], srcR[ i ] );
				dst[ i ].setSlerp( srcL[ i ], comp, alpha );
			}
			break;
		
		case SUBTRACTIVE:
			for ( int i = 0; i < n; i++ )
			{
				hkQuaternion comp;
				comp.setMulInverse( srcL[ i ], srcR[ i ] );
				dst[ i ].setSlerp( srcL[ i ], comp, alpha );
			}
			break;
		}
	}
	else
	{
		// LERP
		switch ( blendMode )
		{
		case NORMAL:
			for ( int i = 0; i < n; i++ )
			{
				hkaIndividualBlenderUtilities::qlerp( dst[ i ], srcL[ i ], srcR[ i ], alpha.getReal() );
			}
			break;

		case ADDITIVE:
			for ( int i = 0; i < n; i++ )
			{
				hkQuaternion comp;
				comp.setMul( srcL[ i ], srcR[ i ] );
				hkaIndividualBlenderUtilities::qlerp( dst[ i ], srcL[ i ], comp, alpha.getReal() );
			}
			break;

		case SUBTRACTIVE:
			for ( int i = 0; i < n; i++ )
			{
				hkQuaternion comp;
				comp.setMulInverse( srcL[ i ], srcR[ i ] );
				hkaIndividualBlenderUtilities::qlerp( dst[ i ], srcL[ i ], comp, alpha.getReal() );
			}
			break;
		}
	}
}

// Interpolates n hkQsTransform pairs with a single alpha
void hkaBlender::blend( hkQsTransform* HK_RESTRICT dst, const hkQsTransform* HK_RESTRICT srcL, const hkQsTransform* HK_RESTRICT srcR, const hkSimdReal& alpha, int n, BLEND_MODE blendMode, ROTATION_MODE rotationMode )
{
	HK_ASSERT2( 0x07d385bf, rotationMode == LERP || rotationMode == SLERP, "Invalid rotation mode" );
	HK_ASSERT2( 0x0f9e68fa, blendMode == NORMAL || blendMode == ADDITIVE || blendMode == SUBTRACTIVE, "Invalid blend mode" );

	hkQsTransform const* HK_RESTRICT srcLPtr = srcL;
	hkQsTransform const* HK_RESTRICT srcRPtr = srcR;
	hkQsTransform* HK_RESTRICT dstPtr = dst;

	if ( rotationMode == SLERP )
	{
		// SLERP
		switch ( blendMode )
		{
		case NORMAL:
			for ( int i = 0; i < n; i++, srcLPtr++, srcRPtr++, dstPtr++ )
			{
				dstPtr->m_translation.setInterpolate( srcLPtr->m_translation, srcRPtr->m_translation, alpha );
				dstPtr->m_rotation.setSlerp( srcLPtr->m_rotation, srcRPtr->m_rotation, alpha );
				dstPtr->m_scale.setInterpolate( srcLPtr->m_scale, srcRPtr->m_scale, alpha );
			}
			break;

		case ADDITIVE:
			for ( int i = 0; i < n; i++, srcLPtr++, srcRPtr++, dstPtr++ )
			{
				hkQsTransform comp;
				comp.setMul( srcL[ i ], srcR[ i ] );
				dstPtr->m_translation.setInterpolate( srcLPtr->m_translation, comp.m_translation, alpha );
				dstPtr->m_rotation.setSlerp( srcLPtr->m_rotation, comp.m_rotation, alpha );
				dstPtr->m_scale.setInterpolate( srcLPtr->m_scale, comp.m_scale, alpha );
			}
			break;

		case SUBTRACTIVE:
			for ( int i = 0; i < n; i++, srcLPtr++, srcRPtr++, dstPtr++ )
			{
				hkQsTransform comp;
				comp.setMulMulInverse( srcL[ i ], srcR[ i ] );
				dstPtr->m_translation.setInterpolate( srcLPtr->m_translation, comp.m_translation, alpha );
				dstPtr->m_rotation.setSlerp( srcLPtr->m_rotation, comp.m_rotation, alpha );
				dstPtr->m_scale.setInterpolate( srcLPtr->m_scale, comp.m_scale, alpha );
			}
			break;
		}
	}
	else
	{
		// LERP
		switch ( blendMode )
		{
		case NORMAL:
			{
				for ( int i = 0; i < n; i++, srcLPtr++, srcRPtr++, dstPtr++ )
				{
					dstPtr->m_translation.setInterpolate( srcLPtr->m_translation, srcRPtr->m_translation, alpha );
					hkaIndividualBlenderUtilities::qlerp( dstPtr->m_rotation, srcLPtr->m_rotation, srcRPtr->m_rotation, alpha.getReal() );
					dstPtr->m_scale.setInterpolate( srcLPtr->m_scale, srcRPtr->m_scale, alpha );
				}
			}
			break;

		case ADDITIVE:
			{
				for ( int i = 0; i < n; i++, srcLPtr++, srcRPtr++, dstPtr++ )
				{
					hkQsTransform comp;
					comp.setMul( *srcLPtr, *srcRPtr );

					dstPtr->m_translation.setInterpolate( srcLPtr->m_translation, comp.m_translation, alpha );
					hkaIndividualBlenderUtilities::qlerp( dstPtr->m_rotation, srcLPtr->m_rotation, comp.m_rotation, alpha.getReal() );
					dstPtr->m_scale.setInterpolate( srcLPtr->m_scale, comp.m_scale, alpha );
				}
			}
			break;

		case SUBTRACTIVE:
			{
				for ( int i = 0; i < n; i++, srcLPtr++, srcRPtr++, dstPtr++ )
				{
					hkQsTransform comp;
					comp.setMulMulInverse( *srcLPtr, *srcRPtr );

					dstPtr->m_translation.setInterpolate( srcLPtr->m_translation, comp.m_translation, alpha );
					hkaIndividualBlenderUtilities::qlerp( dstPtr->m_rotation, srcLPtr->m_rotation, comp.m_rotation, alpha.getReal() );
					dstPtr->m_scale.setInterpolate( srcLPtr->m_scale, comp.m_scale, alpha );
				}
			}
			break;
		}
	}
}


// Interpolates n hkReal pairs with a single alpha
void hkaBlender::blend( hkReal* HK_RESTRICT dst, hkReal* HK_RESTRICT weightsOut, const hkReal* HK_RESTRICT srcL, const hkReal* HK_RESTRICT weightsL, const hkReal* HK_RESTRICT srcR, const hkReal* HK_RESTRICT weightsR, const hkSimdReal& alphaIn, int n, BLEND_MODE blendMode )
{
	HK_ASSERT2( 0x1230c277, blendMode == NORMAL || blendMode == ADDITIVE || blendMode == SUBTRACTIVE, "Invalid blend mode" );

	hkReal alpha;

	switch ( blendMode )
	{
	case NORMAL:
		for ( int i = 0; i < n; i++ )
		{
			hkaIndividualBlenderUtilities::computeBlendFactorAndWeights1( alpha, weightsOut[ i ], alphaIn.getReal(), weightsL[ i ], weightsR[ i ] );
			hkSimdReal srcLi; srcLi.load<1>(&srcL[i]);
			hkSimdReal srcRi; srcRi.load<1>(&srcR[i]);
			hkSimdReal a; a.setFromFloat(alpha);
			hkSimdReal dsti; dsti.setInterpolate(srcLi, srcRi, a);
			dsti.store<1>(&dst[ i ]);
		}
		break;

	case ADDITIVE:
		for ( int i = 0; i < n; i++ )
		{
			hkaIndividualBlenderUtilities::computeBlendFactorAndWeightsAdditive1( alpha, weightsOut[ i ], alphaIn.getReal(), weightsL[ i ], weightsR[ i ] );
			hkSimdReal srcLi; srcLi.load<1>(&srcL[i]);
			hkSimdReal srcRi; srcRi.load<1>(&srcR[i]);
			hkSimdReal a; a.setFromFloat(alpha);
			hkSimdReal dsti = srcLi + srcRi * a;
			dsti.store<1>(&dst[ i ]);
		}
		break;

	case SUBTRACTIVE:
		for ( int i = 0; i < n; i++ )
		{
			hkaIndividualBlenderUtilities::computeBlendFactorAndWeightsAdditive1( alpha, weightsOut[ i ], alphaIn.getReal(), weightsL[ i ], weightsR[ i ] );
			hkSimdReal srcLi; srcLi.load<1>(&srcL[i]);
			hkSimdReal srcRi; srcRi.load<1>(&srcR[i]);
			hkSimdReal a; a.setFromFloat(alpha);
			hkSimdReal dsti = srcLi - srcRi * a;
			dsti.store<1>(&dst[ i ]);
		}
		break;
	}
}

// Interpolates n hkVector4 pairs with a single alpha
void hkaBlender::blend( hkVector4* HK_RESTRICT dst, hkReal* weightsOut,const hkVector4* HK_RESTRICT srcL, const hkReal* weightsL, const hkVector4* HK_RESTRICT srcR, const hkReal* weightsR, const hkSimdReal& alphaIn, int n, BLEND_MODE blendMode )
{
	HK_ASSERT2( 0x1c0d4a7b, blendMode == NORMAL || blendMode == ADDITIVE || blendMode == SUBTRACTIVE, "Invalid blend mode" );

	hkReal alpha;

	switch ( blendMode )
	{
	case NORMAL:
		for ( int i = 0; i < n; i++ )
		{
			hkaIndividualBlenderUtilities::computeBlendFactorAndWeights1( alpha, weightsOut[ i ], alphaIn.getReal(), weightsL[ i ], weightsR[ i ] );
			hkSimdReal a; a.setFromFloat(alpha);
			dst[ i ].setInterpolate( srcL[ i ], srcR[ i ], a );
		}
		break;

	case ADDITIVE:
		for ( int i = 0; i < n; i++ )
		{
			hkaIndividualBlenderUtilities::computeBlendFactorAndWeightsAdditive1( alpha, weightsOut[ i ], alphaIn.getReal(), weightsL[ i ], weightsR[ i ] );
			hkSimdReal a; a.setFromFloat(alpha);
			dst[ i ].setAddMul( srcL[ i ], srcR[ i ], a );
		}
		break;

	case SUBTRACTIVE:
		for ( int i = 0; i < n; i++ )
		{
			hkaIndividualBlenderUtilities::computeBlendFactorAndWeightsAdditive1( alpha, weightsOut[ i ], alphaIn.getReal(), weightsL[ i ], weightsR[ i ] );
			hkSimdReal a; a.setFromFloat(alpha);
			dst[ i ].setSubMul( srcL[ i ], srcR[ i ], a );
		}
		break;
	}
}

// Interpolates n hkQuaternion pairs with a single alpha
void hkaBlender::blend( hkQuaternion* HK_RESTRICT dst, hkReal* weightsOut,const hkQuaternion* HK_RESTRICT srcL, const hkReal* weightsL, const hkQuaternion* HK_RESTRICT srcR, const hkReal* weightsR, const hkSimdReal& alphaIn, int n, BLEND_MODE blendMode, ROTATION_MODE rotationMode )
{
	HK_ASSERT2( 0x07d385bf, rotationMode == LERP || rotationMode == SLERP, "Invalid rotation mode" );
	HK_ASSERT2( 0x0f9e68fa, blendMode == NORMAL || blendMode == ADDITIVE || blendMode == SUBTRACTIVE, "Invalid blend mode" );

	hkReal alpha;
	
	if ( rotationMode == SLERP )
	{
		// SLERP
		switch ( blendMode )
		{
		case NORMAL:
			for ( int i = 0; i < n; i++ )
			{
				hkaIndividualBlenderUtilities::computeBlendFactorAndWeights1( alpha, weightsOut[ i ], alphaIn.getReal(), weightsL[ i ], weightsR[ i ] );
				hkSimdReal a; a.setFromFloat(alpha);
				dst[ i ].setSlerp( srcL[ i ], srcR[ i ], a );
			}
			break;

		case ADDITIVE:
			for ( int i = 0; i < n; i++ )
			{
				hkQuaternion comp;
				comp.setMul( srcL[ i ], srcR[ i ] );
				hkaIndividualBlenderUtilities::computeBlendFactorAndWeightsAdditive1( alpha, weightsOut[ i ], alphaIn.getReal(), weightsL[ i ], weightsR[ i ] );
				hkSimdReal a; a.setFromFloat(alpha);
				dst[ i ].setSlerp( srcL[ i ], comp, a );
			}
			break;
		
		case SUBTRACTIVE:
			for ( int i = 0; i < n; i++ )
			{
				hkQuaternion comp;
				comp.setMulInverse( srcL[ i ], srcR[ i ] );
				hkaIndividualBlenderUtilities::computeBlendFactorAndWeightsAdditive1( alpha, weightsOut[ i ], alphaIn.getReal(), weightsL[ i ], weightsR[ i ] );
				hkSimdReal a; a.setFromFloat(alpha);
				dst[ i ].setSlerp( srcL[ i ], comp, a );
			}
			break;
		}
	}
	else
	{
		// LERP
		switch ( blendMode )
		{
		case NORMAL:
			for ( int i = 0; i < n; i++ )
			{
				hkaIndividualBlenderUtilities::computeBlendFactorAndWeights1( alpha, weightsOut[ i ], alphaIn.getReal(), weightsL[ i ], weightsR[ i ] );
				hkaIndividualBlenderUtilities::qlerp( dst[ i ], srcL[ i ], srcR[ i ], alpha );
			}
			break;

		case ADDITIVE:
			for ( int i = 0; i < n; i++ )
			{
				hkQuaternion comp;
				comp.setMul( srcL[ i ], srcR[ i ] );
				hkaIndividualBlenderUtilities::computeBlendFactorAndWeightsAdditive1( alpha, weightsOut[ i ], alphaIn.getReal(), weightsL[ i ], weightsR[ i ] );
				hkaIndividualBlenderUtilities::qlerp( dst[ i ], srcL[ i ], comp, alpha );
			}
			break;

		case SUBTRACTIVE:
			for ( int i = 0; i < n; i++ )
			{
				hkQuaternion comp;
				hkaIndividualBlenderUtilities::computeBlendFactorAndWeightsAdditive1( alpha, weightsOut[ i ], alphaIn.getReal(), weightsL[ i ], weightsR[ i ] );
				comp.setMulInverse( srcL[ i ], srcR[ i ] );
				hkaIndividualBlenderUtilities::qlerp( dst[ i ], srcL[ i ], comp, alpha );
			}
			break;
		}
	}
}

// Interpolates n hkQsTransform pairs with a single alpha
void hkaBlender::blend( hkQsTransform* HK_RESTRICT dst, hkReal* weightsOut,const hkQsTransform* HK_RESTRICT srcL, const hkReal* weightsL, const hkQsTransform* HK_RESTRICT srcR, const hkReal* weightsR, const hkSimdReal& alphaIn, int n, BLEND_MODE blendMode, ROTATION_MODE rotationMode )
{
	HK_ASSERT2( 0x07d385bf, rotationMode == LERP || rotationMode == SLERP, "Invalid rotation mode" );
	HK_ASSERT2( 0x0f9e68fa, blendMode == NORMAL || blendMode == ADDITIVE || blendMode == SUBTRACTIVE, "Invalid blend mode" );

	hkReal alpha;
	hkQsTransform const* HK_RESTRICT srcLPtr = srcL;
	hkQsTransform const* HK_RESTRICT srcRPtr = srcR;
	hkQsTransform* HK_RESTRICT dstPtr = dst;
	hkReal const* weightsLPtr = weightsL;
	hkReal const* weightsRPtr = weightsR;
	hkReal* weightsOutPtr = weightsOut;

	if ( rotationMode == SLERP )
	{
		// SLERP
		switch ( blendMode )
		{
		case NORMAL:
			for( int i = 0; i < n; i++, srcLPtr++, srcRPtr++, dstPtr++, weightsLPtr++, weightsRPtr++, weightsOutPtr++ )
			{
				hkaIndividualBlenderUtilities::computeBlendFactorAndWeights1( alpha, *weightsOutPtr, alphaIn.getReal(), *weightsLPtr, *weightsRPtr );
				hkSimdReal a; a.setFromFloat(alpha);
				dstPtr->m_translation.setInterpolate(srcLPtr->m_translation, srcRPtr->m_translation, a);
				dstPtr->m_rotation.setSlerp( srcLPtr->m_rotation, srcRPtr->m_rotation, a );
				dstPtr->m_scale.setInterpolate( srcLPtr->m_scale, srcRPtr->m_scale, a );
			}
			break;

		case ADDITIVE:
			for( int i = 0; i < n; i++, srcLPtr++, srcRPtr++, dstPtr++, weightsLPtr++, weightsRPtr++, weightsOutPtr++ )
			{
				hkQsTransform comp;
				hkaAdditiveAnimationUtility::applyAdditiveTransform<hkaAnimationBinding::ADDITIVE>( *srcLPtr, *srcRPtr, comp );
				hkaIndividualBlenderUtilities::computeBlendFactorAndWeightsAdditive1( alpha, *weightsOutPtr, alphaIn.getReal(), *weightsLPtr, *weightsRPtr );
				hkSimdReal a; a.setFromFloat(alpha);
				dstPtr->m_translation.setInterpolate(srcLPtr->m_translation, comp.m_translation, a);
				dstPtr->m_rotation.setSlerp( srcLPtr->m_rotation, comp.m_rotation, a );
				dstPtr->m_scale.setInterpolate( srcLPtr->m_scale, comp.m_scale, a );
			}
			break;

		case SUBTRACTIVE:
			for( int i = 0; i < n; i++, srcLPtr++, srcRPtr++, dstPtr++, weightsLPtr++, weightsRPtr++, weightsOutPtr++ )
			{
				hkQsTransform comp;
				comp.setMulMulInverse( *srcLPtr, *srcRPtr );
				hkaIndividualBlenderUtilities::computeBlendFactorAndWeightsAdditive1( alpha, *weightsOutPtr, alphaIn.getReal(), *weightsLPtr, *weightsRPtr );
				hkSimdReal a; a.setFromFloat(alpha);
				dstPtr->m_translation.setInterpolate(srcLPtr->m_translation, comp.m_translation, a);
				dstPtr->m_rotation.setSlerp( srcLPtr->m_rotation, comp.m_rotation, a );
				dstPtr->m_scale.setInterpolate( srcLPtr->m_scale, comp.m_scale, a );
			}
			break;
		}
	}
	else
	{
		// LERP
		switch ( blendMode )
		{
		case NORMAL:
			for( int i = 0; i < n; i++, srcLPtr++, srcRPtr++, dstPtr++, weightsLPtr++, weightsRPtr++, weightsOutPtr++ )
			{
				hkaIndividualBlenderUtilities::computeBlendFactorAndWeights1( alpha, *weightsOutPtr, alphaIn.getReal(), *weightsLPtr, *weightsRPtr );
				hkSimdReal a; a.setFromFloat(alpha);
				dstPtr->m_translation.setInterpolate(srcLPtr->m_translation, srcRPtr->m_translation, a);
				hkaIndividualBlenderUtilities::qlerp( dstPtr->m_rotation, srcLPtr->m_rotation, srcRPtr->m_rotation, alpha );
				dstPtr->m_scale.setInterpolate( srcLPtr->m_scale, srcRPtr->m_scale, a );
			}
			break;

		case ADDITIVE:
			for( int i = 0; i < n; i++, srcLPtr++, srcRPtr++, dstPtr++, weightsLPtr++, weightsRPtr++, weightsOutPtr++ )
			{
				hkQsTransform comp;
				hkaAdditiveAnimationUtility::applyAdditiveTransform<hkaAnimationBinding::ADDITIVE>( *srcLPtr, *srcRPtr, comp );
				hkaIndividualBlenderUtilities::computeBlendFactorAndWeightsAdditive1( alpha, *weightsOutPtr, alphaIn.getReal(), *weightsLPtr, *weightsRPtr );
				hkSimdReal a; a.setFromFloat(alpha);
				dstPtr->m_translation.setInterpolate(srcLPtr->m_translation, comp.m_translation, a);
				hkaIndividualBlenderUtilities::qlerp( dstPtr->m_rotation, srcLPtr->m_rotation, comp.m_rotation, alpha );
				dstPtr->m_scale.setInterpolate( srcLPtr->m_scale, comp.m_scale, a );
			}
			break;

		case SUBTRACTIVE:
			for( int i = 0; i < n; i++, srcLPtr++, srcRPtr++, dstPtr++, weightsLPtr++, weightsRPtr++, weightsOutPtr++ )
			{
				hkQsTransform comp;
				comp.setMulMulInverse( *srcLPtr, *srcRPtr );
				hkaIndividualBlenderUtilities::computeBlendFactorAndWeightsAdditive1( alpha, *weightsOutPtr, alphaIn.getReal(), *weightsLPtr, *weightsRPtr );
				hkSimdReal a; a.setFromFloat(alpha);
				dstPtr->m_translation.setInterpolate(srcLPtr->m_translation, comp.m_translation, a);
				hkaIndividualBlenderUtilities::qlerp( dstPtr->m_rotation, srcLPtr->m_rotation, comp.m_rotation, alpha );
				dstPtr->m_scale.setInterpolate( srcLPtr->m_scale, comp.m_scale, a );
			}
			break;
		}
	}
}


void hkaBlender::mul( hkReal* HK_RESTRICT dst, const hkReal* HK_RESTRICT srcL, const hkReal* HK_RESTRICT srcR, int n )
{
	for ( int i = 0; i < n; i++ )
	{
		dst[ i ] = srcL[ i ] * srcR[ i ];
	}
}

void hkaBlender::mul( hkVector4* HK_RESTRICT dst, const hkVector4* HK_RESTRICT srcL, const hkVector4* HK_RESTRICT srcR, int n )
{
	for ( int i = 0; i < n; i++ )
	{
		dst[ i ].setMul( srcL[ i ], srcR[ i ] );
	}
}

void hkaBlender::mul( hkQuaternion* HK_RESTRICT dst, const hkQuaternion* HK_RESTRICT srcL, const hkQuaternion* HK_RESTRICT srcR, int n )
{
	for ( int i = 0; i < n; i++ )
	{
		dst[ i ].setMul( srcL[ i ], srcR[ i ] );
	}
}

void hkaBlender::mul( hkQsTransform* HK_RESTRICT dst, const hkQsTransform* HK_RESTRICT srcL, const hkQsTransform* HK_RESTRICT srcR, int n )
{
	for ( int i = 0; i < n; i++ )
	{
		dst[ i ].setMul( srcL[ i ], srcR[ i ] );
	}
}

void hkaBlender::mulInv( hkQsTransform* HK_RESTRICT dst, const hkQsTransform* HK_RESTRICT srcL, const hkQsTransform* HK_RESTRICT srcR, int n )
{
	for ( int i = 0; i < n; i++ )
	{
		dst[ i ].setMulMulInverse( srcL[ i ], srcR[ i ] );
	}
}

void hkaBlender::mulInv( hkQuaternion* HK_RESTRICT dst, const hkQuaternion* HK_RESTRICT srcL, const hkQuaternion* HK_RESTRICT srcR, int n )
{
	for ( int i = 0; i < n; i++ )
	{
		dst[ i ].setMulInverse( srcL[ i ], srcR[ i ] );
	}
}

void HK_CALL hkaBlender::normalize( hkQuaternion* quaternionsInOut, int n )
{
	for ( int i = 0; i < n; i++ )
	{
		quaternionsInOut[ i ].normalize();
	}
}

void HK_CALL hkaBlender::normalize( hkQsTransform* transformsInOut, int n )
{
	for ( int i = 0; i < n; i++ )
	{
		transformsInOut[ i ].m_rotation.normalize();
	}
}



void hkaBlender::rotate( hkVector4* HK_RESTRICT dst, const hkQuaternion* HK_RESTRICT srcL, const hkVector4* HK_RESTRICT srcR, int n )
{
	for ( int i = 0; i < n; i++ )
	{
		dst[ i ]._setRotatedDir( srcL[ i ], srcR[ i ] );
	}
}

void hkaBlender::rotateInv( hkVector4* HK_RESTRICT dst, const hkQuaternion* HK_RESTRICT srcL, const hkVector4* HK_RESTRICT srcR, int n )
{
	for ( int i = 0; i < n; i++ )
	{
		dst[ i ]._setRotatedInverseDir( srcL[ i ], srcR[ i ] );
	}
}

void hkaBlender::transform( hkVector4* HK_RESTRICT dst, const hkQsTransform* HK_RESTRICT srcL, const hkVector4* HK_RESTRICT srcR, int n )
{
	for ( int i = 0; i < n; i++ )
	{
		dst[ i ]._setTransformedPos( srcL[ i ], srcR[ i ] );
	}
}

void hkaBlender::transformInv( hkVector4* HK_RESTRICT dst, const hkQsTransform* HK_RESTRICT srcL, const hkVector4* HK_RESTRICT srcR, int n )
{
	for ( int i = 0; i < n; i++ )
	{
		dst[ i ]._setTransformedInversePos( srcL[ i ], srcR[ i ] );
	}
}

void HK_CALL hkaBlender::localFromModel( hkQsTransform* poseLocalOut, hkQsTransform* poseModelIn, const hkInt16* parentIndices, int numBones, const hkQsTransform& worldFromModel )
{
	for ( int i = numBones; i--; )
	{
		int p = parentIndices[ i ];

		const hkQsTransform modelFromBone = poseModelIn[ i ];
		const hkQsTransform modelFromParent = p >= 0 ? poseModelIn[ p ] : worldFromModel;
		
		poseLocalOut[ i ].setMulInverseMul( modelFromParent, modelFromBone );
	}
}

void HK_CALL hkaBlender::modelFromLocal( hkQsTransform* poseModelOut, hkQsTransform* poseLocalIn, const hkInt16* parentIndices, int numBones, const hkQsTransform& worldFromModel )
{
	for ( int i = 0; i < numBones; i++ )
	{
		int p = parentIndices[ i ];

		const hkQsTransform parentFromBone = poseLocalIn[ i ];
		const hkQsTransform modelFromParent = p >= 0 ? poseModelOut[ p ] : worldFromModel;
		
		poseModelOut[ i ].setMul( modelFromParent, parentFromBone );
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
