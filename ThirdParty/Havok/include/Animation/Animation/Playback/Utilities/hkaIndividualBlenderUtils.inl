/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

namespace hkaIndividualBlenderUtilities
{
	//
	// The following base functions blend and interpolate vectors,
	// quaternions and transforms.  These base functions provide the
	// building blocks for more complex actions.  Each function
	// provides the appropriate analogue of the interpolation
	// function: dst = ( 1 - alpha ) * src0 + ( alpha ) * src1.
	//

	// Linearly interpolates four hkVector4 pairs with four unique blend amounts alpha
	HK_FORCE_INLINE void HK_CALL lerp1( hkVector4& dst, const hkVector4& srcL, const hkVector4& srcR, hkReal alpha );
	
	// Spherically linearly interpolates four quaternion pairs (as hkVector4's) with four unique blend amounts alpha
	HK_FORCE_INLINE void HK_CALL slerp1( hkQuaternion& dst0, const hkQuaternion& srcL0, const hkQuaternion& srcR0, hkReal alpha );
	
	// Linearly interpolates four quaternion pairs (as hkVector4's) with four unique blend amounts alpha (must be renormalized later)
	HK_FORCE_INLINE void HK_CALL qlerp1( hkQuaternion& dst0, const hkQuaternion& srcL0, const hkQuaternion& srcR0, hkReal alpha );
	
	// Blends four hkQsTransform pairs with four unique alphas, slerping rotations
	HK_FORCE_INLINE void HK_CALL blendSlerp1( hkQsTransform& dst0, const hkQsTransform& srcL0, const hkQsTransform& srcR0, hkReal alpha );

	// Blends four hkQsTransform pairs with four unique alphas, lerping rotations (requires normalize)
	HK_FORCE_INLINE void HK_CALL blendQLerp1( hkQsTransform& dst0, const hkQsTransform& srcL0, const hkQsTransform& srcR0, hkReal alpha );

	// Additive blends four hkQsTransform pairs with four unique alphas, slerping rotations
	// Equivalent to blendSlerp4( srcL, mul( srcL, SrcR ) )
	HK_FORCE_INLINE void HK_CALL blendAdditiveSlerp1( hkQsTransform& dst0, const hkQsTransform& srcL0, const hkQsTransform& srcR0, hkReal alpha );

	// Additive blends four hkQsTransform pairs with four unique alphas, lerping rotations (requires normalize)
	// Equivalent to blendQLerp4( srcL, mul( srcL, SrcR ) )
	HK_FORCE_INLINE void HK_CALL blendAdditiveQLerp1( hkQsTransform& dst0, const hkQsTransform& srcL0, const hkQsTransform& srcR0, hkReal alpha );

	// Subtractive blends four hkQsTransform pairs with four unique alphas, slerping rotations
	// Equivalent to blendSlerp4( srcL, mul( srcL, inv( SrcR ) ) )
	HK_FORCE_INLINE void HK_CALL blendSubtractiveSlerp1( hkQsTransform& dst0, const hkQsTransform& srcL0, const hkQsTransform& srcR0, hkReal alpha );

	// Subtractive blends four hkQsTransform pairs with four unique alphas, lerping rotations (requires normalize)
	// Equivalent to blendQLerp4( srcL, mul( srcL, inv( SrcR ) ) )
	HK_FORCE_INLINE void HK_CALL blendSubtractiveQLerp1( hkQsTransform& dst0, const hkQsTransform& srcL0, const hkQsTransform& srcR0, hkReal alpha );

	// Computes new blend amount alphaOut from four given alphas and four weights
	HK_FORCE_INLINE void HK_CALL computeBlendFactorAndWeights1(
		hkReal& alphaOut, hkReal& weightsOut,
		hkReal alpha, hkReal weightL, hkReal weightR );

	// Computes new blend amount alphaOut from four given alphas and four weights
	HK_FORCE_INLINE void HK_CALL computeBlendFactorAndWeightsAdditive1(
		hkReal& alphaOut, hkReal& weightOut,
		hkReal alpha, hkReal weightL, hkReal weightR );

	// Linearly interpolates two quaternions, keeping polarity into account
	HK_FORCE_INLINE void HK_CALL qlerp( hkQuaternion& dstOut, const hkQuaternion& srcL, const hkQuaternion& srcR, hkReal alpha );
}

HK_FORCE_INLINE void HK_CALL hkaIndividualBlenderUtilities::blendSlerp1( hkQsTransform& dst, const hkQsTransform& srcL, const hkQsTransform& srcR, hkReal alpha )
{
	hkSimdReal a; a.setFromFloat(alpha);
	dst.m_translation.setInterpolate( srcL.m_translation, srcR.m_translation, a );
	dst.m_rotation.setSlerp( srcL.m_rotation, srcR.m_rotation, a );
	dst.m_scale.setInterpolate( srcL.m_scale, srcR.m_scale, a );
}

HK_FORCE_INLINE void HK_CALL hkaIndividualBlenderUtilities::blendQLerp1( hkQsTransform& dst, const hkQsTransform& srcL, const hkQsTransform& srcR, hkReal alphaR )
{
	hkSimdReal alpha; alpha.setFromFloat(alphaR);
	dst.m_translation.setInterpolate( srcL.m_translation, srcR.m_translation, alpha );
	const hkSimdReal dot = srcL.m_rotation.m_vec.dot<4>( srcR.m_rotation.m_vec );
	hkSimdReal beta; beta.setSelect(dot.greaterEqualZero(), hkSimdReal_1 - alpha, alpha - hkSimdReal_1);
	hkVector4 tmp;
	tmp.setMul( alpha, srcR.m_rotation.m_vec );
	tmp.addMul( beta,  srcL.m_rotation.m_vec );
	dst.m_rotation.m_vec = tmp;
	dst.m_scale.setInterpolate( srcL.m_scale, srcR.m_scale, alpha );
}


HK_FORCE_INLINE void HK_CALL hkaIndividualBlenderUtilities::blendAdditiveSlerp1( hkQsTransform& dst, const hkQsTransform& srcL, const hkQsTransform& srcR, hkReal alpha )
{
	hkQsTransform tmp;
	tmp.setMul( srcL, srcR );
	blendSlerp1( dst, srcL, tmp, alpha );
}

HK_FORCE_INLINE void HK_CALL hkaIndividualBlenderUtilities::blendAdditiveQLerp1( hkQsTransform& dst, const hkQsTransform& srcL, const hkQsTransform& srcR, hkReal alpha )
{
	hkQsTransform tmp;
	tmp.setMul( srcL, srcR );
	blendQLerp1( dst, srcL, tmp, alpha  );
}

HK_FORCE_INLINE void HK_CALL hkaIndividualBlenderUtilities::blendSubtractiveSlerp1( hkQsTransform& dst, const hkQsTransform& srcL, const hkQsTransform& srcR, hkReal alpha )
{
	hkQsTransform tmp;
	tmp.setMulMulInverse( srcL, srcR );
	blendSlerp1( dst, srcL, tmp, alpha  );
}

HK_FORCE_INLINE void HK_CALL hkaIndividualBlenderUtilities::blendSubtractiveQLerp1( hkQsTransform& dst, const hkQsTransform& srcL, const hkQsTransform& srcR, hkReal alpha )
{
	hkQsTransform tmp;
	tmp.setMulMulInverse( srcL, srcR );
	blendQLerp1( dst, srcL, tmp, alpha  );
}

HK_FORCE_INLINE void HK_CALL hkaIndividualBlenderUtilities::computeBlendFactorAndWeights1(
	hkReal& alphaOut, hkReal& weightOut,
	const hkReal alpha,
	const hkReal weightL, const hkReal weightR )
{
	// Compute a new alpha factor based on the given weights
	// If weightL > weightR then want beta < alpha.  Let beta = alpha * weightR / weightL
	// If weightR > weightL then want (1-beta) < (1-alpha).  Let (1-beta) = (1-alpha) * weightL / weightR

	//               |  weightL > 0                      |  weightL == 0       
	// ------------------------------------------------------------------------
	// weightR > 0   |  beta = (see logic above)         |  w = weightR        
	//               |  w = blend(weightL,weightR,beta)  |  beta = 1           
	// ------------------------------------------------------------------------
	// weightR == 0  |  w = weightL                      |  w = 0              
    //               |  beta = 0                         |  beta = alpha  

#if (HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED)
	const hkSimdReal alphaS = hkSimdReal::fromFloat(alpha);
	const hkSimdReal weightLS = hkSimdReal::fromFloat(weightL);
	const hkSimdReal weightRS = hkSimdReal::fromFloat(weightR);

	const hkVector4Comparison wR_gt0 = weightRS.greaterZero();

	hkSimdReal alphaOutS1, weightOutS1;
	{
		// first col
		const hkVector4Comparison L_gt_R = weightLS.greater(weightRS);
		hkSimdReal alphaTmp; alphaTmp.setSelect(L_gt_R, alphaS * ( weightRS / weightLS ), hkSimdReal_1 - ( hkSimdReal_1 - alphaS ) * ( weightLS / weightRS ));
		hkSimdReal weightTmp = ( hkSimdReal_1 - alphaTmp ) * weightLS + alphaTmp * weightRS;

		alphaOutS1.setSelect(wR_gt0, alphaTmp, hkSimdReal_0);
		weightOutS1.setSelect(wR_gt0, weightTmp, weightLS);
	}

	hkSimdReal alphaOutS2, weightOutS2;
	{
		// second col
		weightOutS2.setSelect(wR_gt0, weightRS, hkSimdReal_0);
		alphaOutS2.setSelect(wR_gt0, hkSimdReal_1, alphaS);
	}

	hkSimdReal alphaOutS, weightOutS;
	{
		const hkVector4Comparison wL_gt0 = weightLS.greaterZero();
		alphaOutS.setSelect(wL_gt0, alphaOutS1, alphaOutS2);
		weightOutS.setSelect(wL_gt0, weightOutS1, weightOutS2);
	}

	alphaOutS.store<1>(&alphaOut);
	weightOutS.store<1>(&weightOut);
#else
	if ( weightL > hkReal(0) )
	{
		// first col
		if ( weightR > hkReal(0) )
		{
			alphaOut = weightL > weightR ?
				alpha * ( weightR / weightL ) :
				hkReal(1) - ( hkReal(1) - alpha ) * ( weightL / weightR );

			weightOut = ( hkReal(1) - alphaOut ) * weightL + alphaOut * weightR;
		}
		else
		{
			weightOut = weightL;
			alphaOut = hkReal(0);
		}
	}
	else
	{
		// second col
		if ( weightR > hkReal(0) )
		{
			weightOut = weightR;
			alphaOut = hkReal(1);
		}
		else
		{
			weightOut = hkReal(0);
			alphaOut = alpha;
		}
	}
#endif
}


HK_FORCE_INLINE void HK_CALL hkaIndividualBlenderUtilities::computeBlendFactorAndWeightsAdditive1(
	hkReal& alphaOut, hkReal& weightOut,
	hkReal alpha, hkReal weightL, hkReal weightR )
{
	// Output alpha is input alpha * right weights
	alphaOut = alpha * weightR;

	// Output weights are the same as the left weights
	weightOut = weightL;
}

HK_FORCE_INLINE void HK_CALL hkaIndividualBlenderUtilities::qlerp( hkQuaternion& dst, const hkQuaternion& srcL, const hkQuaternion& srcR, hkReal alphaR )
{
	const hkSimdReal dot = srcL.m_vec.dot<4>( srcR.m_vec );
	const hkSimdReal alpha = hkSimdReal::fromFloat(alphaR);
	hkSimdReal beta; beta.setFlipSign(hkSimdReal_1 - alpha, dot.lessZero());
	hkQuaternion tmp;
	tmp.m_vec.setMul( alpha, srcR.m_vec );
	tmp.m_vec.addMul( beta, srcL.m_vec );
	dst = tmp;
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
