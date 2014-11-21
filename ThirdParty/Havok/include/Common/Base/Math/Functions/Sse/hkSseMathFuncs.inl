/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#include <Common/Base/Fwd/hkcmath.h>

namespace hkMath
{
	// import the constants
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_sinCoeff0[4])  ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_sinCoeff1[4])  ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_sinCoeff2[4])  ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_cosCoeff0[4])  ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_cosCoeff1[4])  ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_cosCoeff2[4])  ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_signMask[4])   ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_pi[4])         ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_twoPi[4])      ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_piOver2[4])    ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_fourOverPi[4]) ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_DP1[4])        ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_DP2[4])        ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_DP3[4])        ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_floatOne[4])   ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_floatTwo[4])   ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_floatThree[4]) ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_floatHalf[4])  ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt32 hkSse_intOne[4])     ;

	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_sinCoeff0[2]);
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_sinCoeff1[2]);
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_sinCoeff2[2]);
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_sinCoeff3[2]);
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_sinCoeff4[2]);
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_sinCoeff5[2]);
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_cosCoeff0[2]);
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_cosCoeff1[2]);
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_cosCoeff2[2]);
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_cosCoeff3[2]);
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_cosCoeff4[2]);
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_cosCoeff5[2]);
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_atanP0[2])   ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_atanP1[2])   ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_atanP2[2])   ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_atanP3[2])   ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_atanP4[2])   ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_atanQ1[2])   ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_atanQ2[2])   ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_atanQ3[2])   ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_atanQ4[2])   ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_atanQ5[2])   ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_twoPi[2] )   ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_pi[2] )      ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_piOver2[2])  ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_piOver4[2])  ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_fourOverPi[2]);
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_DP1[2])      ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_DP2[2])      ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_DP3[2])      ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_doubleHalf[2]) ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_doubleOne[2])  ;
	extern HK_EXPORT_COMMON HK_ALIGN16(const hkInt64 hkSse_D_signMask[2]) ;


	//
	// need to implement
	//
#	define HK_MATH_quadReciprocal
	HK_FORCE_INLINE static hkQuadFloat32 HK_CALL quadReciprocal( const hkQuadFloat32& r )
	{
		const hkQuadFloat32 rb = _mm_rcp_ps(r);
		// One Newton-Raphson refinement iteration
		const hkQuadFloat32 rbr = _mm_mul_ps(r, rb);
		const hkQuadFloat32 d = _mm_sub_ps(*(__m128*)hkSse_floatTwo, rbr);
		return _mm_mul_ps(rb, d);
	}

	HK_FORCE_INLINE static hkQuadDouble64 HK_CALL quadReciprocal( const hkQuadDouble64& r )
	{
#if HK_SSE_VERSION >= 0x50
		return _mm256_div_pd(_mm256_set1_pd(1.0), r);
#else
		const __m128 xy = _mm_cvtpd_ps(r.xy);
		const __m128 zw = _mm_cvtpd_ps(r.zw);
		const __m128 xyzw = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
		const __m128 rb = _mm_rcp_ps(xyzw);
		// One Newton-Raphson refinement iteration
		const __m128 rbr = _mm_mul_ps(xyzw, rb);
		const __m128 d = _mm_sub_ps(*(__m128*)hkSse_floatTwo, rbr);
		const __m128 re = _mm_mul_ps(rb, d);
		hkQuadDouble64 result;
		result.xy = _mm_cvtps_pd(re);
		result.zw = _mm_cvtps_pd(_mm_shuffle_ps(re,re,_MM_SHUFFLE(1,0,3,2)));
		return result;
#endif
	}

#	define HK_MATH_quadReciprocalSquareRoot
	HK_FORCE_INLINE static hkQuadFloat32 HK_CALL quadReciprocalSquareRoot( const hkQuadFloat32& r )
	{
		const hkQuadFloat32 e = _mm_rsqrt_ps(r);
		// One Newton-Raphson refinement iteration
		const hkQuadFloat32 he = _mm_mul_ps(*(__m128*)hkSse_floatHalf,e);
		const hkQuadFloat32 ree = _mm_mul_ps(_mm_mul_ps(r,e),e);
		return _mm_mul_ps(he, _mm_sub_ps(*(__m128*)hkSse_floatThree, ree) );
	}

	HK_FORCE_INLINE static hkQuadDouble64 HK_CALL quadReciprocalSquareRoot( const hkQuadDouble64& r )
	{
#if HK_SSE_VERSION >= 0x50
		return _mm256_div_pd(_mm256_set1_pd(1.0), _mm256_sqrt_pd(r));
#else
		const __m128 xy = _mm_cvtpd_ps(r.xy);
		const __m128 zw = _mm_cvtpd_ps(r.zw);
		const __m128 xyzw = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
		const __m128 e = _mm_rsqrt_ps(xyzw);
		// One Newton-Raphson refinement iteration
		const __m128 he = _mm_mul_ps(*(__m128*)hkSse_floatHalf,e);
		const __m128 ree = _mm_mul_ps(_mm_mul_ps(xyzw,e),e);
		const __m128 re = _mm_mul_ps(he, _mm_sub_ps(*(__m128*)hkSse_floatThree, ree) );
		hkQuadDouble64 result;
		result.xy = _mm_cvtps_pd(re);
		result.zw = _mm_cvtps_pd(_mm_shuffle_ps(re,re,_MM_SHUFFLE(1,0,3,2)));
		return result;
#endif
	}

#	define HK_MATH_quadReciprocalTwoIter
	HK_FORCE_INLINE static hkQuadFloat32 HK_CALL quadReciprocalTwoIter( const hkQuadFloat32& r )
	{
		const __m128 two = *(__m128*)hkSse_floatTwo;
		const hkQuadFloat32 rb = _mm_rcp_ps(r);
		//One round of Newton-Raphson refinement
		const hkQuadFloat32 rbr = _mm_mul_ps(r, rb);
		const hkQuadFloat32 d = _mm_sub_ps(two, rbr);
		const hkQuadFloat32 rb1 = _mm_mul_ps(rb, d);
		//Another round
		const hkQuadFloat32 rbr2 = _mm_mul_ps(r, rb1);
		const hkQuadFloat32 d2 = _mm_sub_ps(two, rbr2);
		return _mm_mul_ps(rb1, d2);
	}

	HK_FORCE_INLINE static hkQuadDouble64 HK_CALL quadReciprocalTwoIter( const hkQuadDouble64& r )
	{
#if HK_SSE_VERSION >= 0x50
		return _mm256_div_pd(_mm256_set1_pd(1.0), r);
#else
		const __m128 two = *(__m128*)hkSse_floatTwo;
		const __m128 xy = _mm_cvtpd_ps(r.xy);
		const __m128 zw = _mm_cvtpd_ps(r.zw);
		const __m128 xyzw = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
		const __m128 rb = _mm_rcp_ps(xyzw);
		//One round of Newton-Raphson refinement
		const __m128 rbr = _mm_mul_ps(xyzw, rb);
		const __m128 d = _mm_sub_ps(two, rbr);
		const __m128 rb1 = _mm_mul_ps(rb, d);
		//Another round
		const __m128 rbr2 = _mm_mul_ps(xyzw, rb1);
		const __m128 d2 = _mm_sub_ps(two, rbr2);
		const __m128 re = _mm_mul_ps(rb1, d2);
		hkQuadDouble64 result;
		result.xy = _mm_cvtps_pd(re);
		result.zw = _mm_cvtps_pd(_mm_shuffle_ps(re,re,_MM_SHUFFLE(1,0,3,2)));
		return result;
#endif
	}

#	define HK_MATH_quadReciprocalSquareRootTwoIter
	HK_FORCE_INLINE static hkQuadFloat32 HK_CALL quadReciprocalSquareRootTwoIter( const hkQuadFloat32& r )
	{
		const __m128 half = *(__m128*)hkSse_floatHalf;
		const __m128 three = *(__m128*)hkSse_floatThree;
		const hkQuadFloat32 e = _mm_rsqrt_ps(r);
		// One Newton-Raphson refinement iteration
		const hkQuadFloat32 he = _mm_mul_ps(half,e);
		const hkQuadFloat32 ree = _mm_mul_ps(_mm_mul_ps(r,e),e);
		const hkQuadFloat32 e1 = _mm_mul_ps(he, _mm_sub_ps(three, ree) );
		//Another round
		const hkQuadFloat32 he2 = _mm_mul_ps(half,e1);
		const hkQuadFloat32 ree2 = _mm_mul_ps(_mm_mul_ps(r,e1),e1);
		return _mm_mul_ps(he2, _mm_sub_ps(three, ree2) );
	}

	HK_FORCE_INLINE static hkQuadDouble64 HK_CALL quadReciprocalSquareRootTwoIter( const hkQuadDouble64& r )
	{
#if HK_SSE_VERSION >= 0x50
		return _mm256_div_pd(_mm256_set1_pd(1.0), _mm256_sqrt_pd(r));
#else
		const __m128 half = *(__m128*)hkSse_floatHalf;
		const __m128 three = *(__m128*)hkSse_floatThree;
		const __m128 xy = _mm_cvtpd_ps(r.xy);
		const __m128 zw = _mm_cvtpd_ps(r.zw);
		const __m128 xyzw = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
		const __m128 e = _mm_rsqrt_ps(xyzw);
		// One Newton-Raphson refinement iteration
		const __m128 he = _mm_mul_ps(half,e);
		const __m128 ree = _mm_mul_ps(_mm_mul_ps(xyzw,e),e);
		const __m128 e1 = _mm_mul_ps(he, _mm_sub_ps(three, ree) );
		//Another round
		const __m128 he2 = _mm_mul_ps(half,e1);
		const __m128 ree2 = _mm_mul_ps(_mm_mul_ps(xyzw,e1),e1);
		const __m128 re = _mm_mul_ps(he2, _mm_sub_ps(three, ree2) );
		hkQuadDouble64 result;
		result.xy = _mm_cvtps_pd(re);
		result.zw = _mm_cvtps_pd(_mm_shuffle_ps(re,re,_MM_SHUFFLE(1,0,3,2)));
		return result;
#endif
	}

	//
	// SSE optimized implementations
	//

#	define HK_MATH_sqrt
	HK_FORCE_INLINE static hkFloat32 HK_CALL sqrt(const hkFloat32 r)
	{
		const __m128 s = _mm_sqrt_ss(_mm_load_ss(&r));
		return _mm_cvtss_f32(s);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL sqrt(const hkDouble64 r)
	{
		const __m128d s = _mm_sqrt_sd(_mm_setzero_pd(),_mm_load_sd(&r));
		return _mm_cvtsd_f64(s);
	}

#	define HK_MATH_sqrtInverse
	HK_FORCE_INLINE static hkFloat32 HK_CALL sqrtInverse(const hkFloat32 r)
	{
		const __m128 s = _mm_sqrt_ss(_mm_load_ss(&r));
		return _mm_cvtss_f32(_mm_div_ss(*(__m128*)hkSse_floatOne,s));
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL sqrtInverse(const hkDouble64 r)
	{
		const __m128d s = _mm_sqrt_sd(_mm_setzero_pd(),_mm_load_sd(&r));
		const __m128d q = _mm_div_sd(*(__m128d*)hkSse_doubleOne,s);
		return _mm_cvtsd_f64(q);
	}

	namespace
	{
		HK_FORCE_INLINE static void HK_CALL quadLogHelper(__m128& x)
		{
			static HK_ALIGN16(const unsigned int minNormalizedPosNumber[4])	= {  0x00800000,  0x00800000,  0x00800000,  0x00800000 }; // 1.1754943508222875E-38 (smallest normalized positive number)
			static HK_ALIGN16(const			 int invMantissaMask[4])		= { ~0x7f800000, ~0x7f800000, ~0x7f800000, ~0x7f800000 };
			static HK_ALIGN16(const unsigned int int0x7f[4])				= {  0x0000007f,  0x0000007f,  0x0000007f,  0x0000007f };
			static HK_ALIGN16(const unsigned int logP0[4])					= {  0xBF4A21EF,  0xBF4A21EF,  0xBF4A21EF,  0xBF4A21EF }; // -7.89580278884799154124e-1
			static HK_ALIGN16(const unsigned int logQ0[4])					= {  0xC20EB06A,  0xC20EB06A,  0xC20EB06A,  0xC20EB06A }; // -3.56722798256324312549e1
			static HK_ALIGN16(const unsigned int logP1[4])					= {  0x418317E4,  0x418317E4,  0x418317E4,  0x418317E4 }; // 1.63866645699558079767e1
			static HK_ALIGN16(const unsigned int logQ1[4])					= {  0x439C0C01,  0x439C0C01,  0x439C0C01,  0x439C0C01 }; // 3.12093766372244180303e2
			static HK_ALIGN16(const unsigned int logP2[4])					= {  0xC2804831,  0xC2804831,  0xC2804831,  0xC2804831 }; // -6.41409952958715622951e1
			static HK_ALIGN16(const unsigned int logQ2[4])					= {  0xC4406C49,  0xC4406C49,  0xC4406C49,  0xC4406C49 }; // -7.69691943550460008604e2
			static HK_ALIGN16(const unsigned int logC0[4])					= {  0x3F317218,  0x3F317218,  0x3F317218,  0x3F317218 }; // 0.693147180559945

			// cut off denormalized stuff
			x = _mm_max_ps(x, *(__m128*)minNormalizedPosNumber);

			__m128i emm0 = _mm_srli_epi32(_mm_castps_si128(x), 23);

			// keep only the fractional part
			x = _mm_or_ps(_mm_and_ps(x, *(__m128*)invMantissaMask), *(__m128*)hkSse_floatOne);

			x = _mm_mul_ps(_mm_sub_ps(x, *(__m128*)hkSse_floatOne), _mm_rcp_ps(_mm_add_ps(x, *(__m128*)hkSse_floatOne)));
			x = _mm_add_ps(x, x);
			__m128 bs = x;

			x = _mm_mul_ps(x, x);

			__m128 x4 = _mm_mul_ps(*(__m128*)logP0, x);
			__m128 x6 = _mm_mul_ps(*(__m128*)logQ0, x);

			x4 = _mm_add_ps(x4, *(__m128*)logP1);
			x6 = _mm_add_ps(x6, *(__m128*)logQ1);

			x4 = _mm_mul_ps(x4, x);
			x6 = _mm_mul_ps(x6, x);

			x4 = _mm_add_ps(x4, *(__m128*)logP2);
			x6 = _mm_add_ps(x6, *(__m128*)logQ2);

			x = _mm_mul_ps(x, x4);
			x6 = _mm_rcp_ps(x6);

			x = _mm_mul_ps(x, x6);
			x = _mm_mul_ps(x, bs);

			emm0 = _mm_sub_epi32(emm0, *(__m128i*)int0x7f);
			__m128 x1 = _mm_mul_ps(_mm_cvtepi32_ps(emm0), *(__m128*)logC0);

			x = _mm_add_ps(x, bs);
			x = _mm_add_ps(x, x1);
		}
	}

	/// Average absolute error 0.000046
	/// Max absolute error 169.777725 for r=1
	/// Max absolute error 0.001070 elsewhere
	/// About 3x faster than ::logf for 4 simultaneous values
	HK_FORCE_INLINE static hkQuadFloat32 HK_CALL quadLog(const hkQuadFloat32 &r)
	{
		__m128 x = r;
		quadLogHelper(x);
		return x;
	}

	HK_FORCE_INLINE static hkQuadDouble64 HK_CALL quadLog(const hkQuadDouble64 &r)
	{
		#if HK_SSE_VERSION >= 0x50
		__m128 x = _mm256_cvtpd_ps(r);
#else
		const __m128 xy = _mm_cvtpd_ps(r.xy);
		const __m128 zw = _mm_cvtpd_ps(r.zw);
		__m128 x = _mm_shuffle_ps(xy,zw,_MM_SHUFFLE(1,0,1,0));
#endif
		quadLogHelper(x);

#		if HK_SSE_VERSION >= 0x50
		return _mm256_cvtps_pd(x);
#else
		hkQuadDouble64 result;
		result.xy = _mm_cvtps_pd(x);
		result.zw = _mm_cvtps_pd(_mm_shuffle_ps(x,x,_MM_SHUFFLE(1,0,3,2)));
		return result;
#endif
	}

	/// Adapted from the book "Methods and Programs for Mathematical Functions",
	/// Stephen Lloyd Baluk Moshier, Prentice-Hall, 1989
	///
	/// Returns radian angle between -pi/2 and +pi/2 whose tangent is x.
	/// Range reduction is from three intervals into the interval
	/// from zero to 0.66.  The approximation uses a rational
	/// function of degree 4/5 of the form x + x**3 P(x)/Q(x).
	///
	/// ACCURACY: matches cmath on MSVC
	///
	///                      Relative error:
	/// arithmetic   domain        peak       rms
	///    IEEE      -10,10       1.8e-16     5.0e-17
	///
	/// PERFORMANCE: About 1.2x faster than ::atan for 2 simultaneous values

	HK_FORCE_INLINE static __m128d HK_CALL twoAtan(const __m128d& inX)
	{
		static HK_ALIGN16(const hkInt64 tan3pi8[2])	= { 0x4003504F333F9DE6ull, 0x4003504F333F9DE6ull }; // tan(3*pi/8) = 1+sqrt(2)
		static HK_ALIGN16(const hkInt64 point66[2])	= { 0x3FE51EB851EB851Full, 0x3FE51EB851EB851Full }; // 0.66
		static HK_ALIGN16(const hkInt64 morebits[2])= { 0x3C91A62633145C07ull, 0x3C91A62633145C07ull }; // 6.123233995736765886130E-17 + hkSse_D_piOver2 = pi/2

		// make argument positive and save the sign
		__m128d sign = _mm_and_pd( *(__m128d*)hkSse_D_signMask, inX );
		__m128d x = _mm_andnot_pd( *(__m128d*)hkSse_D_signMask, inX );

		// range reduction
		__m128d a1 = _mm_cmpgt_pd(x , *(__m128d*)tan3pi8 );
		__m128d a2 = _mm_cmple_pd(x , *(__m128d*)point66 );

		__m128d y = _mm_andnot_pd(a2, *(__m128d*)hkSse_D_piOver4);
		__m128d z1 = _mm_div_pd(_mm_sub_pd(x,*(__m128d*)hkSse_doubleOne), _mm_add_pd(x,*(__m128d*)hkSse_doubleOne));

#if HK_SSE_VERSION >= 0x41
		z1 = _mm_blendv_pd(z1,x,a2);
		y = _mm_blendv_pd(y, *(__m128d*)hkSse_D_piOver2, a1);
		x = _mm_blendv_pd(z1, _mm_sub_pd(_mm_setzero_pd(), _mm_div_pd(*(__m128d*)hkSse_doubleOne, x)), a1);
#else
		z1 = _mm_or_pd(_mm_andnot_pd(a2, z1), _mm_and_pd(a2, x));
		y = _mm_or_pd(_mm_andnot_pd(a1, y), _mm_and_pd(a1, *(__m128d*)hkSse_D_piOver2));
		x = _mm_or_pd(_mm_andnot_pd(a1, z1), _mm_and_pd(a1, _mm_sub_pd(_mm_setzero_pd(), _mm_div_pd(*(__m128d*)hkSse_doubleOne, x))));
#endif

		// eval polynoms (Horner)
		__m128d z = _mm_mul_pd(x, x);

		__m128d polyP = *(__m128d*)hkSse_D_atanP0;
		polyP = _mm_add_pd(_mm_mul_pd(polyP, z),*(__m128d*)hkSse_D_atanP1);
		polyP = _mm_add_pd(_mm_mul_pd(polyP, z),*(__m128d*)hkSse_D_atanP2);
		polyP = _mm_add_pd(_mm_mul_pd(polyP, z),*(__m128d*)hkSse_D_atanP3);
		polyP = _mm_add_pd(_mm_mul_pd(polyP, z),*(__m128d*)hkSse_D_atanP4);

		// Q0 = 1
		__m128d polyQ = _mm_add_pd(z,*(__m128d*)hkSse_D_atanQ1);
		polyQ = _mm_add_pd(_mm_mul_pd(polyQ, z),*(__m128d*)hkSse_D_atanQ2);
		polyQ = _mm_add_pd(_mm_mul_pd(polyQ, z),*(__m128d*)hkSse_D_atanQ3);
		polyQ = _mm_add_pd(_mm_mul_pd(polyQ, z),*(__m128d*)hkSse_D_atanQ4);
		polyQ = _mm_add_pd(_mm_mul_pd(polyQ, z),*(__m128d*)hkSse_D_atanQ5);

		// calc differential
		z = _mm_div_pd(_mm_mul_pd(z, polyP), polyQ);
		z = _mm_add_pd(_mm_mul_pd(x,z),x);

		// apply correction term for truncated constant
		__m128d m = _mm_andnot_pd(a2, _mm_mul_pd(*(__m128d*)morebits,*(__m128d*)hkSse_doubleHalf));
#if HK_SSE_VERSION >= 0x41
		m = _mm_blendv_pd(m, *(__m128d*)morebits, a1);
#else
		m = _mm_or_pd(_mm_andnot_pd(a1, m), _mm_and_pd(a1, *(__m128d*)morebits));
#endif
		z = _mm_add_pd(z, m);

		// add in
		y = _mm_add_pd(y,z);

		// update sign
		y = _mm_xor_pd(y, sign);

		return y;
	}

	/// Approximate version of above using reduced accuracy for reciprocals
	/// and polynoms of degree only 3/4.
	///
	/// Average absolute error 0.000004
	/// Max absolute error 0.000221
	/// About 1.8x faster than ::atan for 2 simultaneous values

	HK_FORCE_INLINE static __m128d HK_CALL twoAtanApproximation(const __m128d& inX)
	{
		static HK_ALIGN16(const hkInt64 tan3pi8[2])	= { 0x4003504F333F9DE6ull, 0x4003504F333F9DE6ull }; // tan(3*pi/8) = 1+sqrt(2)
		static HK_ALIGN16(const hkInt64 point66[2])	= { 0x3FE51EB851EB851Full, 0x3FE51EB851EB851Full }; // 0.66

		// make argument positive and save the sign
		__m128d sign = _mm_and_pd( *(__m128d*)hkSse_D_signMask, inX );
		__m128d x = _mm_andnot_pd( *(__m128d*)hkSse_D_signMask, inX );

		// range reduction
		__m128d a1 = _mm_cmpgt_pd(x , *(__m128d*)tan3pi8 );
		__m128d a2 = _mm_cmple_pd(x , *(__m128d*)point66 );

		__m128d y = _mm_andnot_pd(a2, *(__m128d*)hkSse_D_piOver4);
		__m128d invZ = _mm_cvtps_pd(_mm_rcp_ps(_mm_add_ps(_mm_cvtpd_ps(x),*(__m128*)hkSse_floatOne)));
		__m128d z1 = _mm_mul_pd(_mm_sub_pd(x,*(__m128d*)hkSse_doubleOne), invZ);

#if HK_SSE_VERSION >= 0x41
		z1 = _mm_blendv_pd(z1,x,a2);
		y = _mm_blendv_pd(y, *(__m128d*)hkSse_D_piOver2, a1);
		x = _mm_blendv_pd(z1, _mm_sub_pd(_mm_setzero_pd(), _mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(x)))), a1);
#else
		z1 = _mm_or_pd(_mm_andnot_pd(a2, z1), _mm_and_pd(a2, x));
		y = _mm_or_pd(_mm_andnot_pd(a1, y), _mm_and_pd(a1, *(__m128d*)hkSse_D_piOver2));
		x = _mm_or_pd(_mm_andnot_pd(a1, z1), _mm_and_pd(a1, _mm_sub_pd(_mm_setzero_pd(), _mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(x))))));
#endif

		// eval polynoms (Horner)
		__m128d z = _mm_mul_pd(x, x);

		__m128d polyP = *(__m128d*)hkSse_D_atanP1;
		polyP = _mm_add_pd(_mm_mul_pd(polyP, z),*(__m128d*)hkSse_D_atanP2);
		polyP = _mm_add_pd(_mm_mul_pd(polyP, z),*(__m128d*)hkSse_D_atanP3);
		polyP = _mm_add_pd(_mm_mul_pd(polyP, z),*(__m128d*)hkSse_D_atanP4);

		// Q1 = 1
		__m128d polyQ = _mm_add_pd(z,*(__m128d*)hkSse_D_atanQ2);
		polyQ = _mm_add_pd(_mm_mul_pd(polyQ, z),*(__m128d*)hkSse_D_atanQ3);
		polyQ = _mm_add_pd(_mm_mul_pd(polyQ, z),*(__m128d*)hkSse_D_atanQ4);
		polyQ = _mm_add_pd(_mm_mul_pd(polyQ, z),*(__m128d*)hkSse_D_atanQ5);

		// calc differential
		__m128d invPolyQ = _mm_cvtps_pd(_mm_rcp_ps(_mm_cvtpd_ps(polyQ)));
		z = _mm_mul_pd(_mm_mul_pd(z, polyP), invPolyQ);
		z = _mm_add_pd(_mm_mul_pd(x,z),x);

		// add in
		y = _mm_add_pd(y,z);

		// update sign
		y = _mm_xor_pd(y, sign);

		return y;
	}

	/// Adapted from the book "Methods and Programs for Mathematical Functions",
	/// Stephen Lloyd Baluk Moshier, Prentice-Hall, 1989
	///
	/// Returns radian angle between -pi/2 and +pi/2 whose tangent is x.
	/// Range reduction is to two intervals which are approximated by
	/// a polynomial. Unlike the method in the book, the polynomials are
	/// factored into quadratic evaluation which is faster than a Horner scheme.
	///
	/// ACCURACY: matches cmath on MSVC
	///
	///                      Relative error:
	/// arithmetic   domain        peak       rms
	///    IEEE      -10,10       1.9e-7     4.1e-8
	///
	/// PERFORMANCE: About 5.5x faster than ::atanf for 4 simultaneous values

	HK_FORCE_INLINE static __m128 HK_CALL quadAtan(const __m128& inX)
	{
		static HK_ALIGN16(const hkInt32 a1[4])	= { 0x3B3BD74A, 0x3B3BD74A, 0x3B3BD74A, 0x3B3BD74A }; // 0.0028662257
		static HK_ALIGN16(const hkInt32 a0[4])	= { 0xBBEB7F9E, 0xBBEB7F9E, 0xBBEB7F9E, 0xBBEB7F9E }; // -0.00718684420434729
		static HK_ALIGN16(const hkInt32 b1[4])	= { 0xC0753EB3, 0xC0753EB3, 0xC0753EB3, 0xC0753EB3 }; // -3.83195178589435
		static HK_ALIGN16(const hkInt32 b0[4])	= { 0x40B019CA, 0x40B019CA, 0x40B019CA, 0x40B019CA }; // 5.50314831143450
		static HK_ALIGN16(const hkInt32 d1[4])	= { 0xBF809FF7, 0xBF809FF7, 0xBF809FF7, 0xBF809FF7 }; // -1.00488174720983
		static HK_ALIGN16(const hkInt32 d0[4])	= { 0x40712D99, 0x40712D99, 0x40712D99, 0x40712D99 }; // 3.76840794390466
		static HK_ALIGN16(const hkInt32 e1[4])	= { 0x3FDA2291, 0x3FDA2291, 0x3FDA2291, 0x3FDA2291 }; // 1.70417985002100
		static HK_ALIGN16(const hkInt32 e0[4])	= { 0x400F22D2, 0x400F22D2, 0x400F22D2, 0x400F22D2 }; // 2.23650017675129

		__m128 x = inX;

		// get sign and abs
		__m128 sign = _mm_and_ps(*(__m128*)hkSse_signMask, x);
		__m128 xabs = _mm_andnot_ps(*(__m128*)hkSse_signMask, x);

		// get abs reciprocal
		__m128 inv_x = hkMath::quadReciprocal(x);
		inv_x = _mm_xor_ps(inv_x, *(__m128*)hkSse_signMask);

		// calc which half
		__m128 select = _mm_cmpgt_ps(xabs, *(__m128*)hkSse_floatOne);

		// get signed bias
		sign = _mm_or_ps(sign, *(__m128*)hkSse_piOver2);
		__m128 bias = _mm_and_ps(sign, select);

		// choose solution
#if HK_SSE_VERSION >= 0x41
		x = _mm_blendv_ps(x, inv_x, select);
#else
		x = _mm_or_ps(_mm_andnot_ps(select, x), _mm_and_ps(select, inv_x));
#endif

		// approximate
		__m128  z  = _mm_mul_ps(x,x);
		__m128  zm = _mm_mul_ps(z,x);
		bias = _mm_add_ps(bias,x);

		// eval polynom (Estrin)
		__m128 y  = _mm_add_ps(_mm_mul_ps(z, *(__m128*)a1), *(__m128*)a0);
		__m128 z0 = _mm_add_ps(z, *(__m128*)b1);
		__m128 z1 = _mm_add_ps(z, *(__m128*)d1);
		__m128 z2 = _mm_add_ps(z, *(__m128*)e1);
		__m128 y0 = _mm_add_ps(_mm_mul_ps(z0, z),*(__m128*)b0);
		__m128 y1 = _mm_add_ps(_mm_mul_ps(z1, z),*(__m128*)d0);
		__m128 y2 = _mm_add_ps(_mm_mul_ps(z2, z),*(__m128*)e0);
		y   = _mm_mul_ps(zm,y);
		y0  = _mm_mul_ps(y1,y0);
		y2  = _mm_mul_ps(y,y2);
		y0  = _mm_add_ps(_mm_mul_ps(y0,y2),bias);

		return y0;
	}

	/// Returns radian angle whose tangent is y/x.
	/// This function adheres to the ANSI standard, ie. range -PI < z=atan2(y,x) <= +PI
	/// with argument sequence (y,x) to match the cmath interface.
	/// The implementation forwards to the quadAtan(z) function.
	///
	/// ACCURACY: matches cmath on MSVC
	///
	///                      Relative error:
	/// arithmetic   domain        peak       rms
	///    IEEE      -10,10       1.9e-7     4.1e-8
	///
	/// PERFORMANCE: About 6.4x faster than ::atanf for 4 simultaneous values

	HK_FORCE_INLINE static __m128 HK_CALL quadAtan2(const __m128& y, const __m128& x)
	{
		__m128 xIsZero  = _mm_cmpeq_ps(x, _mm_setzero_ps());				// by value
		__m128 yIsZero  = _mm_cmpeq_ps(y, _mm_setzero_ps());				// by value
		__m128 xIsNeg   = _mm_cmplt_ps(x, _mm_setzero_ps());				// by value
		__m128 ySign    = _mm_and_ps(*(__m128*)hkSse_signMask, y);	// by sign

		// compute common case and zero if not applicable
#if defined(HK_ALLOW_FPU_EXCEPTION_CHECKING)
		// this is slightly less accurate and slower than the full precision call below
		__m128 ratio = _mm_mul_ps(y, quadReciprocal(x));
#else
		__m128 ratio = _mm_div_ps(y, x);
#endif
		__m128 z = quadAtan( ratio );
		z = _mm_andnot_ps(_mm_or_ps(xIsZero,yIsZero), z);

		// special case x<0: depends on y
		__m128 wx = _mm_and_ps(xIsNeg, *(__m128*)hkSse_pi);
		wx = _mm_xor_ps(wx, ySign);

		// special case x=0: depends on y<0 only
		__m128 wy = _mm_xor_ps(*(__m128*)hkSse_piOver2, ySign);
		wy = _mm_andnot_ps(yIsZero, wy);

		// select special case
#if HK_SSE_VERSION >= 0x41
		__m128 w = _mm_blendv_ps(wx,wy,xIsZero);
#else
		__m128 w = _mm_or_ps(_mm_and_ps(xIsZero,wy), _mm_andnot_ps(xIsZero, wx));
#endif

		// assemble common + special cases
		__m128 result = _mm_add_ps(w, z);

		return result;
	}

	/// Double precision version of above
	///
	///                      Relative error:
	/// arithmetic   domain        peak       rms
	///    IEEE     -10,10        2.5e-16    6.9e-17
	///
	/// PERFORMANCE: About 2.1x faster than ::atan2 for 2 simultaneous values

	HK_FORCE_INLINE static __m128d HK_CALL twoAtan2(const __m128d& y, const __m128d& x)
	{
		__m128d xIsZero  = _mm_cmpeq_pd(x, _mm_setzero_pd());				// by value
		__m128d yIsZero  = _mm_cmpeq_pd(y, _mm_setzero_pd());				// by value
		__m128d xIsNeg   = _mm_cmplt_pd(x, _mm_setzero_pd());				// by value
		__m128d ySign    = _mm_and_pd(*(__m128d*)hkSse_D_signMask, y);	// by sign

		// compute common case and zero if not applicable
		__m128d ratio = _mm_div_pd(y, x);
		__m128d z = twoAtan( ratio );
		z = _mm_andnot_pd(_mm_or_pd(xIsZero,yIsZero), z);

		// special case x<0: depends on y
		__m128d wx = _mm_and_pd(xIsNeg, *(__m128d*)hkSse_D_pi);
		wx = _mm_xor_pd(wx, ySign);

		// special case x=0: depends on y<0 only
		__m128d wy = _mm_xor_pd(*(__m128d*)hkSse_D_piOver2, ySign);
		wy = _mm_andnot_pd(yIsZero, wy);

		// select special case
#if HK_SSE_VERSION >= 0x41
		__m128d w = _mm_blendv_pd(wx,wy,xIsZero);
#else
		__m128d w = _mm_or_pd(_mm_and_pd(xIsZero,wy), _mm_andnot_pd(xIsZero, wx));
#endif

		// assemble common + special cases
		__m128d result = _mm_add_pd(w, z);

		return result;
	}

#	define HK_MATH_prefetch128
	HK_FORCE_INLINE static void HK_CALL prefetch128( const void* p)
	{
		_mm_prefetch( (const char*)p, _MM_HINT_NTA );
	}

#	define HK_MATH_forcePrefetch
	template<int SIZE>
	HK_FORCE_INLINE static void HK_CALL forcePrefetch( const void* p )
	{
		const char* q = (const char*)p;
		_mm_prefetch( q, _MM_HINT_NTA );
		if ( SIZE > 64){  _mm_prefetch( q + 64, _MM_HINT_NTA ); }
		if ( SIZE > 128){ _mm_prefetch( q + 128, _MM_HINT_NTA ); }
		if ( SIZE > 192){ _mm_prefetch( q + 192, _MM_HINT_NTA ); }
	}

#	define HK_MATH_hkToIntFast
	HK_FORCE_INLINE static int HK_CALL hkToIntFast( const hkDouble64 r )
	{
		return _mm_cvttsd_si32(_mm_load_sd(&r));
	}
	HK_FORCE_INLINE static int HK_CALL hkToIntFast( const hkFloat32 r )
	{
		return _mm_cvtt_ss2si(_mm_load_ss(&r));
	}

#	define HK_MATH_hkFloatToInt
	HK_FORCE_INLINE static int HK_CALL hkFloatToInt(const hkFloat32 r)
	{
		return hkMath::hkToIntFast(r);
	}
	HK_FORCE_INLINE static int HK_CALL hkFloatToInt(const hkDouble64 r)
	{
		return hkMath::hkToIntFast(r);
	}

	HK_FORCE_INLINE static hkQuadUint HK_CALL quadF2I(const hkQuadFloat32& f)
	{
		return _mm_cvttps_epi32(f);
	}

	HK_FORCE_INLINE static hkQuadUint HK_CALL quadF2I(const hkQuadDouble64& f)
	{
#if HK_SSE_VERSION >= 0x50
		return _mm256_cvttpd_epi32(f);
#else
		__m128i xy = _mm_cvttpd_epi32(f.xy);
		__m128i zw = _mm_cvttpd_epi32(f.zw);
		return _mm_castps_si128(_mm_shuffle_ps(_mm_castsi128_ps(xy),_mm_castsi128_ps(zw),_MM_SHUFFLE(1,0,1,0)));
#endif
	}

	HK_FORCE_INLINE static __m128 HK_CALL quadFabs(const __m128 &v)
	{
		return _mm_castsi128_ps( _mm_srli_epi32( _mm_slli_epi32( _mm_castps_si128(v), 1 ), 1 ) );
	}

	HK_FORCE_INLINE static __m128d HK_CALL twoFabs(const __m128d &v)
	{
		return _mm_castsi128_pd( _mm_srli_epi64( _mm_slli_epi64( _mm_castpd_si128(v), 1 ), 1 ) );
	}

#	define HK_MATH_fabs
	HK_FORCE_INLINE static hkFloat32 HK_CALL fabs(const hkFloat32 r)
	{
		const __m128 v = _mm_load_ss(&r);
		const __m128 abs = quadFabs(v);
		return _mm_cvtss_f32(abs);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL fabs(const hkDouble64 r)
	{
		const __m128d v = _mm_load_sd(&r);
		const __m128d abs = twoFabs(v);
		return _mm_cvtsd_f64(abs);
	}

#if HK_SSE_VERSION >= 0x31
#define HK_MATH_abs
	template<typename T>
	HK_FORCE_INLINE static T HK_CALL abs(T t) { return t < T(0) ? -t : t; }

	template<>
	HK_FORCE_INLINE hkFloat32 HK_CALL abs(hkFloat32 r) { return fabs(r); }

	template<>
	HK_FORCE_INLINE hkDouble64 HK_CALL abs(hkDouble64 r) { return fabs(r); }

	template<>
	HK_FORCE_INLINE hkInt32 HK_CALL abs(hkInt32 r)
	{
		__m128i rr = _mm_cvtsi32_si128(r);
		__m128i rabs = _mm_abs_epi32(rr);
		return _mm_cvtsi128_si32(rabs);
	}

#endif

#	define HK_MATH_equal
	HK_FORCE_INLINE static bool HK_CALL equal(hkFloat32 x, hkFloat32 y)
	{
		const __m128 xx = _mm_load_ss(&x);
		const __m128 yy = _mm_load_ss(&y);
		const __m128 abs = quadFabs(_mm_sub_ss(xx,yy));
		const __m128 tol = _mm_set1_ps(1e-5f);
		const int mask = _mm_ucomile_ss(abs, tol);
		return bool(mask);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkFloat32 x, hkFloat32 y, hkFloat32 tolerance2)
	{
		const __m128 xx = _mm_load_ss(&x);
		const __m128 yy = _mm_load_ss(&y);
		const __m128 abs = quadFabs(_mm_sub_ss(xx,yy));
		const int mask = _mm_ucomile_ss(abs, _mm_load_ss(&tolerance2));
		return bool(mask);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkDouble64 x, hkFloat32 y)
	{
		const __m128d xxd = _mm_load_sd(&x);
		const __m128 xx = _mm_cvtsd_ss(_mm_setzero_ps(), xxd);
		const __m128 yy = _mm_load_ss(&y);
		const __m128 abs = quadFabs(_mm_sub_ss(xx,yy));
		const __m128 tol = _mm_set1_ps(1e-5f);
		const int mask = _mm_ucomile_ss(abs, tol);
		return bool(mask);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkDouble64 x, hkFloat32 y, hkFloat32 tolerance2)
	{
		const __m128d xxd = _mm_load_sd(&x);
		const __m128 xx = _mm_cvtsd_ss(_mm_setzero_ps(), xxd);
		const __m128 yy = _mm_load_ss(&y);
		const __m128 abs = quadFabs(_mm_sub_ss(xx,yy));
		const int mask = _mm_ucomile_ss(abs, _mm_load_ss(&tolerance2));
		return bool(mask);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkFloat32 x, hkDouble64 y)
	{
		const __m128d yyd = _mm_load_sd(&y);
		const __m128 yy = _mm_cvtsd_ss(_mm_setzero_ps(), yyd);
		const __m128 xx = _mm_load_ss(&x);
		const __m128 abs = quadFabs(_mm_sub_ss(xx,yy));
		const __m128 tol = _mm_set1_ps(1e-5f);
		const int mask = _mm_ucomile_ss(abs, tol);
		return bool(mask);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkFloat32 x, hkDouble64 y, hkFloat32 tolerance2)
	{
		const __m128d yyd = _mm_load_sd(&y);
		const __m128 yy = _mm_cvtsd_ss(_mm_setzero_ps(), yyd);
		const __m128 xx = _mm_load_ss(&x);
		const __m128 abs = quadFabs(_mm_sub_ss(xx,yy));
		const int mask = _mm_ucomile_ss(abs, _mm_load_ss(&tolerance2));
		return bool(mask);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkDouble64 x, hkDouble64 y)
	{
		const __m128d xx = _mm_load_sd(&x);
		const __m128d yy = _mm_load_sd(&y);
		const __m128d abs = twoFabs(_mm_sub_sd(xx,yy));
		const __m128d tol = _mm_set1_pd(1e-5);
		const int mask = _mm_ucomile_sd(abs, tol);
		return bool(mask);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkDouble64 x, hkDouble64 y, hkDouble64 tolerance2)
	{
		const __m128d xx = _mm_load_sd(&x);
		const __m128d yy = _mm_load_sd(&y);
		const __m128d abs = twoFabs(_mm_sub_sd(xx,yy));
		const int mask = _mm_ucomile_sd(abs, _mm_load_sd(&tolerance2));
		return bool(mask);
	}
	HK_FORCE_INLINE static bool HK_CALL equal(hkDouble64 x, hkDouble64 y, hkFloat32 tolerance2)
	{
		const __m128d xx = _mm_load_sd(&x);
		const __m128d yy = _mm_load_sd(&y);
		const __m128d abs = twoFabs(_mm_sub_sd(xx,yy));
		const __m128 tolf = _mm_load_ss(&tolerance2);
		const __m128d told = _mm_cvtss_sd(_mm_setzero_pd(), tolf);
		const int mask = _mm_ucomile_sd(abs, told);
		return bool(mask);
	}


#	define HK_MATH_max2
	template <typename T1,typename T2>
	HK_FORCE_INLINE static T1 HK_CALL max2( T1 x, T2 y)
	{
		return x > (T1)y ? x : (T1)y;
	}
	template <>
	HK_FORCE_INLINE hkFloat32 HK_CALL max2<hkFloat32, hkFloat32>( hkFloat32 x, hkFloat32 y)
	{
		const __m128 v = _mm_max_ss(_mm_load_ss(&x),_mm_load_ss(&y));
		return _mm_cvtss_f32(v);
	}
	template <>
	HK_FORCE_INLINE hkDouble64 HK_CALL max2<hkDouble64, hkDouble64>( hkDouble64 x, hkDouble64 y)
	{
		const __m128d v = _mm_max_sd(_mm_load_sd(&x),_mm_load_sd(&y));
		return _mm_cvtsd_f64(v);
	}
#if HK_SSE_VERSION >= 0x41
	template <>
	HK_FORCE_INLINE hkUint32 HK_CALL max2<hkUint32>( hkUint32 x, hkUint32 y)
	{
		const __m128i v = _mm_max_epu32(_mm_cvtsi32_si128(x),_mm_cvtsi32_si128(y));
		return (hkUint32)_mm_cvtsi128_si32(v);
	}
	template <>
	HK_FORCE_INLINE hkInt32 HK_CALL max2<hkInt32>( hkInt32 x, hkInt32 y)
	{
		const __m128i v = _mm_max_epi32(_mm_cvtsi32_si128(x),_mm_cvtsi32_si128(y));
		return _mm_cvtsi128_si32(v);
	}
#endif

#	define HK_MATH_min2
	template <typename T1,typename T2>
	HK_FORCE_INLINE static T1 HK_CALL min2( T1 x, T2 y)
	{
		return x < (T1)y ? x : (T1)y;
	}
	template <>
	HK_FORCE_INLINE hkFloat32 HK_CALL min2<hkFloat32, hkFloat32>( hkFloat32 x, hkFloat32 y)
	{
		const __m128 v = _mm_min_ss(_mm_load_ss(&x),_mm_load_ss(&y));
		return _mm_cvtss_f32(v);
	}
	template <>
	HK_FORCE_INLINE hkDouble64 HK_CALL min2<hkDouble64, hkDouble64>( hkDouble64 x, hkDouble64 y)
	{
		const __m128d v = _mm_min_sd(_mm_load_sd(&x),_mm_load_sd(&y));
		return _mm_cvtsd_f64(v);
	}
#if HK_SSE_VERSION >= 0x41
	template <>
	HK_FORCE_INLINE hkUint32 HK_CALL min2<hkUint32>( hkUint32 x, hkUint32 y)
	{
		const __m128i v = _mm_min_epu32(_mm_cvtsi32_si128(x),_mm_cvtsi32_si128(y));
		return (hkUint32)_mm_cvtsi128_si32(v);
	}
	template <>
	HK_FORCE_INLINE hkInt32 HK_CALL min2<hkInt32>( hkInt32 x, hkInt32 y)
	{
		const __m128i v = _mm_min_epi32(_mm_cvtsi32_si128(x),_mm_cvtsi32_si128(y));
		return _mm_cvtsi128_si32(v);
	}
#endif

#	define HK_MATH_clamp
	template <typename T1, typename T2, typename T3>
	HK_FORCE_INLINE static T1 HK_CALL clamp( T1 x, T2 mi, T3 ma)
	{
		if ( x < (T1)mi ) return (T1)mi;
		if ( x > (T1)ma ) return (T1)ma;
		return x;
	}
	template <>
	HK_FORCE_INLINE hkFloat32 HK_CALL clamp<hkFloat32, hkFloat32, hkFloat32>( hkFloat32 x, hkFloat32 mi, hkFloat32 ma)
	{
		const __m128 lo = _mm_max_ss(_mm_load_ss(&x),_mm_load_ss(&mi));
		const __m128 hi = _mm_min_ss(             lo,_mm_load_ss(&ma));
		return _mm_cvtss_f32(hi);
	}
	template <>
	HK_FORCE_INLINE hkDouble64 HK_CALL clamp<hkDouble64, hkDouble64, hkDouble64>( hkDouble64 x, hkDouble64 mi, hkDouble64 ma)
	{
		const __m128d lo = _mm_max_sd(_mm_load_sd(&x),_mm_load_sd(&mi));
		const __m128d hi = _mm_min_sd(             lo,_mm_load_sd(&ma));
		return _mm_cvtsd_f64(hi);
	}
#if HK_SSE_VERSION >= 0x41
	template <>
	HK_FORCE_INLINE hkInt32 HK_CALL clamp<hkInt32>( hkInt32 x, hkInt32 mi, hkInt32 ma)
	{
		const __m128i lo = _mm_max_epi32(_mm_cvtsi32_si128(x),_mm_cvtsi32_si128(mi));
		const __m128i hi = _mm_min_epi32(                  lo,_mm_cvtsi32_si128(ma));
		return _mm_cvtsi128_si32(hi);
	}
	template <>
	HK_FORCE_INLINE hkUint32 HK_CALL clamp<hkUint32>( hkUint32 x, hkUint32 mi, hkUint32 ma)
	{
		const __m128i lo = _mm_max_epu32(_mm_cvtsi32_si128(x),_mm_cvtsi32_si128(mi));
		const __m128i hi = _mm_min_epu32(                  lo,_mm_cvtsi32_si128(ma));
		return (hkUint32)_mm_cvtsi128_si32(hi);
	}
#endif

	// Define but don't implement the specializations for hkSimdFloat32.
	// On MSVC, accidentally calling these can cause misaligned SSE access.
	template <>
	HK_FORCE_INLINE hkSimdFloat32 HK_CALL min2<hkSimdFloat32, hkSimdFloat32>( hkSimdFloat32 x, hkSimdFloat32 y);

	template <>
	HK_FORCE_INLINE hkSimdFloat32 HK_CALL max2<hkSimdFloat32, hkSimdFloat32>( hkSimdFloat32 x, hkSimdFloat32 y);

	template <>
	HK_FORCE_INLINE hkSimdFloat32 HK_CALL clamp<hkSimdFloat32, hkSimdFloat32, hkSimdFloat32>( hkSimdFloat32 x, hkSimdFloat32 mi, hkSimdFloat32 ma);

	template <>
	HK_FORCE_INLINE hkSimdDouble64 HK_CALL min2<hkSimdDouble64, hkSimdDouble64>( hkSimdDouble64 x, hkSimdDouble64 y);

	template <>
	HK_FORCE_INLINE hkSimdDouble64 HK_CALL max2<hkSimdDouble64, hkSimdDouble64>( hkSimdDouble64 x, hkSimdDouble64 y);

	template <>
	HK_FORCE_INLINE hkSimdDouble64 HK_CALL clamp<hkSimdDouble64, hkSimdDouble64, hkSimdDouble64>( hkSimdDouble64 x, hkSimdDouble64 mi, hkSimdDouble64 ma);



	HK_FORCE_INLINE static __m128 HK_CALL quadFloor(const __m128 &v)
	{
#if HK_SSE_VERSION >= 0x41
		const __m128 result = _mm_floor_ps(v);
#else
		static HK_ALIGN16( const hkUint32 two23[4] )  = { 0x4B000000, 0x4B000000, 0x4B000000, 0x4B000000 }; // 2^23 as float

		const __m128 b = _mm_castsi128_ps( _mm_srli_epi32( _mm_slli_epi32( _mm_castps_si128(v), 1 ), 1 ) ); // fabs(v)
		const __m128 d = _mm_sub_ps( _mm_add_ps( _mm_add_ps( _mm_sub_ps( v, *(__m128*)&two23 ), *(__m128*)&two23 ), *(__m128*)&two23 ), *(__m128*)&two23 ); // the meat of floor
		const __m128 largeMaskE = _mm_cmpgt_ps( b, *(__m128*)&two23 ); // $ffffffff if v >= 2^23
		const __m128 g = _mm_cmplt_ps( v, d ); // check for possible off by one error
		const __m128 h = _mm_cvtepi32_ps( _mm_castps_si128(g) ); // convert positive check result to -1.0, negative to 0.0
		const __m128 t = _mm_add_ps( d, h ); // add in the error if there is one

		// Select between output result and input value based on v >= 2^23
		const __m128 result = _mm_or_ps( _mm_and_ps(largeMaskE, v), _mm_andnot_ps(largeMaskE, t) );
#endif
		return result;
	}

	HK_FORCE_INLINE static __m128d HK_CALL twoFloor(const __m128d &v)
	{
#if HK_SSE_VERSION >= 0x41
		const __m128d result = _mm_floor_pd(v);
#else
		static HK_ALIGN16( const hkUint64 two52[2] )  = { 0x4330000000000000ull, 0x4330000000000000ull }; // 2^52 as double

		const __m128d b = _mm_castsi128_pd( _mm_srli_epi64( _mm_slli_epi64( _mm_castpd_si128(v), 1 ), 1 ) ); // fabs(v)
		const __m128d d = _mm_sub_pd( _mm_add_pd( _mm_add_pd( _mm_sub_pd( v, *(__m128d*)&two52 ), *(__m128d*)&two52 ), *(__m128d*)&two52 ), *(__m128d*)&two52 ); // the meat of floor
		const __m128d largeMaskE = _mm_cmpgt_pd( b, *(__m128d*)&two52 ); // $ffffffffffffffff if v >= 2^52
		const __m128d g = _mm_cmplt_pd( v, d ); // check for possible off by one error
		const __m128d h = _mm_cvtepi32_pd( _mm_castpd_si128(g) ); // convert positive check result to -1.0, negative to 0.0 (only need the lower 64 bit anyways, so cvtepi32 is fine)
		const __m128d t = _mm_add_pd( d, h ); // add in the error if there is one

		// Select between output result and input value based on v >= 2^52
		const __m128d result = _mm_or_pd( _mm_and_pd(largeMaskE, v), _mm_andnot_pd(largeMaskE, t) );
#endif
		return result;
	}

#	define HK_MATH_floor
	HK_FORCE_INLINE static hkFloat32 HK_CALL floor(const hkFloat32 r)
	{
		const __m128 v = _mm_load_ss(&r);
		const __m128 result = quadFloor(v);
		return _mm_cvtss_f32(result);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL floor(const hkDouble64 r)
	{
		const __m128d v = _mm_load_sd(&r);
		const __m128d result = twoFloor(v);
		return _mm_cvtsd_f64(result);
	}

#	define HK_MATH_hkFloor
	HK_FORCE_INLINE static hkFloat32 HK_CALL hkFloor(const hkFloat32 r)
	{
		return hkMath::floor(r);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL hkFloor(const hkDouble64 r)
	{
		return hkMath::floor(r);
	}

#	define HK_MATH_hkFloorToInt
	HK_FORCE_INLINE static int HK_CALL hkFloorToInt(const hkFloat32 r)
	{
		const __m128 v = _mm_load_ss(&r);
		const __m128 result = quadFloor(v);
		return _mm_cvtt_ss2si(result);
	}
	HK_FORCE_INLINE static int HK_CALL hkFloorToInt(const hkDouble64 r)
	{
		const __m128d v = _mm_load_sd(&r);
		const __m128d result = twoFloor(v);
		return _mm_cvttsd_si32(result);
	}

#	define HK_MATH_ceil
	HK_FORCE_INLINE static hkFloat32 HK_CALL ceil( const hkFloat32 r )
	{
		const __m128 v = _mm_load_ss(&r);
#if HK_SSE_VERSION >= 0x41
		const __m128 result = _mm_ceil_ss(v, v);
#else
		const __m128 result = _mm_add_ps(*(__m128*)hkSse_floatOne, quadFloor(v));
#endif
		return _mm_cvtss_f32(result);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL ceil( const hkDouble64 r )
	{
		const __m128d v = _mm_load_sd(&r);
#if HK_SSE_VERSION >= 0x41
		const __m128d result = _mm_ceil_sd(v, v);
#else
		const __m128d result = _mm_add_pd(*(__m128d*)hkSse_doubleOne, twoFloor(v));
#endif
		return _mm_cvtsd_f64(result);
	}

	HK_FORCE_INLINE static __m128 HK_CALL quadMod(const __m128 &a, const __m128 &b)
	{
		const __m128 denomIsZero = _mm_cmpeq_ps(b,_mm_setzero_ps());
		const __m128 q = quadFloor(_mm_div_ps(a,b));
		__m128 result = _mm_sub_ps(a, _mm_mul_ps(q,b));
		return _mm_andnot_ps(denomIsZero, result);
	}

	HK_FORCE_INLINE static __m128d HK_CALL twoMod(const __m128d &a, const __m128d &b)
	{
		const __m128d denomIsZero = _mm_cmpeq_pd(b,_mm_setzero_pd());
		const __m128d q = twoFloor(_mm_div_pd(a,b));
		__m128d result = _mm_sub_pd(a, _mm_mul_pd(q,b));
		return _mm_andnot_pd(denomIsZero, result);
	}

#	define HK_MATH_fmod
	HK_FORCE_INLINE static hkFloat32 HK_CALL fmod(const hkFloat32 n, const hkFloat32 d)
	{
		const __m128 numer = _mm_load_ss(&n);
		const __m128 denom = _mm_load_ss(&d);
		__m128 result = quadMod(numer, denom);
		return _mm_cvtss_f32(result);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL fmod(const hkDouble64 n, const hkDouble64 d)
	{
		const __m128d numer = _mm_load_sd(&n);
		const __m128d denom = _mm_load_sd(&d);
		__m128d result = twoMod(numer, denom);
		return _mm_cvtsd_f64(result);
	}

#	define HK_MATH_signBitSet
	HK_FORCE_INLINE static bool HK_CALL signBitSet(const hkFloat32& r)
	{
		return (bool)_mm_movemask_ps(_mm_load_ss(&r));
	}
	HK_FORCE_INLINE static bool HK_CALL signBitSet(const hkDouble64& r)
	{
		return (bool)_mm_movemask_pd(_mm_load_sd(&r));
	}

#	define HK_MATH_logApproximation
	HK_FORCE_INLINE static hkFloat32 HK_CALL logApproximation(const hkFloat32& r)
	{
		const hkQuadFloat32 q = _mm_load1_ps(&r);
		const hkQuadFloat32 l = quadLog(q);
		return _mm_cvtss_f32(l);
	}

	HK_FORCE_INLINE static hkDouble64 HK_CALL logApproximation(const hkDouble64& r)
	{
#if HK_SSE_VERSION >= 0x50
		hkQuadDouble64 q = _mm256_set1_pd(r);
		hkQuadDouble64 l = quadLog(q);
		return l.m256d_f64[0];
#else
		hkQuadDouble64 q;
		q.xy = _mm_load1_pd(&r);
		q.zw = _mm_load1_pd(&r);
		hkQuadDouble64 l = quadLog(q); // change this!
		return _mm_cvtsd_f64(l.xy);
#endif
	}

	/// Average absolute error 0.001961
	/// Max absolute error 0.013429
	/// About 10x faster than ::sinf for 4 simultaneous values
	HK_FORCE_INLINE static __m128 HK_CALL quadSinApproximation(const __m128& inX)
	{
		static HK_ALIGN16( const hkUint32 C[4] )      = { 0xBECF817B, 0xBECF817B, 0xBECF817B, 0xBECF817B }; // -4/(pi*pi)
		static HK_ALIGN16( const hkUint32 P[4] )      = { 0x3E666666, 0x3E666666, 0x3E666666, 0x3E666666 }; // 0.225

		__m128 x = inX;

		// xx = remap to [0,pi]
		__m128 gePi = _mm_cmpnlt_ps(x, *(__m128*)hkSse_pi);
		__m128 limit = _mm_and_ps(gePi, *(__m128*)hkSse_twoPi);
		__m128 xx = _mm_sub_ps(x, limit);

		// y = B * x + C * x * abs(xx)
		__m128 abs = quadFabs(xx);
		__m128 y = _mm_mul_ps(abs, xx);
		__m128 Bx = _mm_mul_ps(xx, *(__m128*)hkSse_fourOverPi);
		__m128 Cx_abs = _mm_mul_ps(y, *(__m128*)&C);
		__m128 parabola = _mm_add_ps(Bx, Cx_abs);

		// y = P * (y * abs(y) - y) + y
		abs = quadFabs(parabola);
		y = _mm_sub_ps(_mm_mul_ps(parabola, abs),parabola);
		__m128 blend = _mm_mul_ps(y, *(__m128*)&P);
		__m128 result = _mm_add_ps(blend, parabola);

		return result;
	}


	/// Average absolute error 0.001961
	/// Max absolute error 0.013429
	/// About 10x faster than ::sin for 4 simultaneous values
	HK_FORCE_INLINE static __m128d HK_CALL twoSinApproximation(const __m128d& inX)
	{
		static HK_ALIGN16( const hkUint64 C[2] )      = { 0xBFD9F02F6222C720ull, 0xBFD9F02F6222C720ull }; // -4/(pi*pi)
		static HK_ALIGN16( const hkUint64 P[2] )      = { 0x3FCCCCCCCCCCCCCDull, 0x3FCCCCCCCCCCCCCDull }; // 0.225

		__m128d x = inX;

		// xx = remap to [0,pi]
		__m128d gePi = _mm_cmpnlt_pd(x, *(__m128d*)&hkSse_D_pi);
		__m128d limit = _mm_and_pd(gePi, *(__m128d*)&hkSse_D_twoPi);
		__m128d xx = _mm_sub_pd(x, limit);

		// y = B * x + C * x * abs(xx)
		__m128d abs = twoFabs(xx);
		__m128d y = _mm_mul_pd(abs, xx);
		__m128d Bx = _mm_mul_pd(xx, *(__m128d*)&hkSse_D_fourOverPi);
		__m128d Cx_abs = _mm_mul_pd(y, *(__m128d*)&C);
		__m128d parabola = _mm_add_pd(Bx, Cx_abs);

		// y = P * (y * abs(y) - y) + y
		abs = twoFabs(parabola);
		y = _mm_sub_pd(_mm_mul_pd(parabola, abs),parabola);
		__m128d blend = _mm_mul_pd(y, *(__m128d*)&P);
		__m128d result = _mm_add_pd(blend, parabola);

		return result;
	}

	/// Adapted from the book "Methods and Programs for Mathematical Functions",
	/// Stephen Lloyd Baluk Moshier, Prentice-Hall, 1989
	///
	/// Range reduction is into intervals of pi/4.  The reduction error is nearly eliminated
	/// by extended precision modular arithmetic.
	///
	/// Two polynomial approximating functions are employed.
	/// Between 0 and pi/4 the sine is approximated by
	///      x  +  x**3 P(x**2).
	/// Between pi/4 and pi/2 the cosine is represented as
	///      1  -  x**2 Q(x**2).
	///
	/// ACCURACY: matches cmath on MSVC
	///
	///                      Relative error:
	/// arithmetic   domain        peak       rms
	///    IEEE    -4096,+4096    1.2e-7     3.0e-8
	///    IEEE    -8192,+8192    3.0e-7     3.0e-8
	/// Partial loss of accuracy begins to occur at x = 2^13
	/// = 8192. Results may be meaningless for x >= 2^24
	///
	/// PERFORMANCE: About 4.3x faster than ::sinf for 4 simultaneous values

	HK_FORCE_INLINE static __m128 HK_CALL quadSin(const __m128& inX)
	{
		// get abs and sign
		__m128 x = _mm_andnot_ps( *(__m128*)hkSse_signMask, inX);
		__m128 sign_bit = _mm_and_ps( *(__m128*)hkSse_signMask, inX);

		// scale by 4/Pi
		__m128 y = _mm_mul_ps(x, *(__m128*)hkSse_fourOverPi);

		__m128i one = *(__m128i*)hkSse_intOne;
		__m128i two = _mm_add_epi32(one,one);
		__m128i four = _mm_add_epi32(two,two);
		// store the integer part of y in emm2
		__m128i emm2 = _mm_cvttps_epi32(y);
		// j=(j+1) & (~1)
		emm2 = _mm_add_epi32(emm2, one);
		emm2 = _mm_andnot_si128(one, emm2);
		y = _mm_cvtepi32_ps(emm2);
		// get the swap sign flag
		__m128i emm0 = _mm_and_si128(emm2, four);
		emm0 = _mm_slli_epi32(emm0, 29);
		__m128 swap_sign_bit = _mm_castsi128_ps(emm0);
		sign_bit = _mm_xor_ps(sign_bit, swap_sign_bit);

		// The magic pass: Extended precision modular arithmetic
		//   x = ((x - y * DP1) - y * DP2) - y * DP3
		__m128 xmm1 = *(__m128*)hkSse_DP1;
		__m128 xmm2 = *(__m128*)hkSse_DP2;
		__m128 xmm3 = *(__m128*)hkSse_DP3;
		xmm1 = _mm_mul_ps(y, xmm1);
		xmm2 = _mm_mul_ps(y, xmm2);
		xmm3 = _mm_mul_ps(y, xmm3);
		x = _mm_add_ps(x, xmm1);
		x = _mm_add_ps(x, xmm2);
		x = _mm_add_ps(x, xmm3);

		// Evaluate the first polynom  (0 <= x <= Pi/4)
		y = *(__m128*)hkSse_cosCoeff0;
		__m128 z = _mm_mul_ps(x,x);

		y = _mm_mul_ps(y, z);
		y = _mm_add_ps(y, *(__m128*)hkSse_cosCoeff1);
		y = _mm_mul_ps(y, z);
		y = _mm_add_ps(y, *(__m128*)hkSse_cosCoeff2);
		y = _mm_mul_ps(y, z);
		y = _mm_mul_ps(y, z);
		__m128 tmp = _mm_mul_ps(z, *(__m128*)hkSse_floatHalf);
		y = _mm_sub_ps(y, tmp);
		y = _mm_add_ps(y, *(__m128*)hkSse_floatOne);

		// Evaluate the second polynom  (Pi/4 <= x <= 0)
		__m128 y2 = *(__m128*)hkSse_sinCoeff0;
		y2 = _mm_mul_ps(y2, z);
		y2 = _mm_add_ps(y2, *(__m128*)hkSse_sinCoeff1);
		y2 = _mm_mul_ps(y2, z);
		y2 = _mm_add_ps(y2, *(__m128*)hkSse_sinCoeff2);
		y2 = _mm_mul_ps(y2, z);
		y2 = _mm_mul_ps(y2, x);
		y2 = _mm_add_ps(y2, x);

		// get the polynom selection mask and
		// select the correct result from the two polynoms
#if HK_SSE_VERSION >= 0x41
		emm2 = _mm_slli_epi32(emm2, 30);
		__m128 poly_mask = _mm_castsi128_ps(emm2);
		y = _mm_blendv_ps(y2,y,poly_mask);
#else
		emm2 = _mm_and_si128(emm2, two);
		emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());
		__m128 poly_mask = _mm_castsi128_ps(emm2);
		y2 = _mm_and_ps(poly_mask, y2);
		y = _mm_andnot_ps(poly_mask, y);
		y = _mm_or_ps(y,y2);
#endif
		// clamp
		y = _mm_min_ps(y, *(__m128*)hkSse_floatOne);

		// update the sign
		y = _mm_xor_ps(y, sign_bit);

		return y;
	}

	/// Double precision version of above
	///
	///                      Relative error:
	/// arithmetic   domain        peak       rms
	///    IEEE -1.07e9,+1.07e9  2.1e-16     5.4e-17
	/// Partial loss of accuracy begins to occur at x = 2**30
	/// = 1.074e9.  The loss is not gradual, but jumps suddenly to
	/// about 1 part in 10e7.  Results may be meaningless for
	/// x > 2**49 = 5.6e14.
	///
	/// PERFORMANCE: About 1.3x faster than ::sin for 2 simultaneous values

	HK_FORCE_INLINE static __m128d HK_CALL twoSin(const __m128d& inX)
	{
		// get abs and sign
		__m128d x = _mm_andnot_pd( *(__m128d*)hkSse_D_signMask, inX);
		__m128d sign_bit = _mm_and_pd( *(__m128d*)hkSse_D_signMask, inX);

		// scale by 4/Pi
		__m128d y = _mm_mul_pd(x, *(__m128d*)hkSse_D_fourOverPi);

		__m128i one = *(__m128i*)hkSse_intOne;
		__m128i two = _mm_add_epi32(one,one);
		__m128i four = _mm_add_epi32(two,two);
		// store the integer part of y in emm2
		__m128i emm2 = _mm_cvttpd_epi32(y);
		// j=(j+1) & (~1)
		emm2 = _mm_add_epi32(emm2, one);
		emm2 = _mm_andnot_si128(one, emm2);
		y = _mm_cvtepi32_pd(emm2);
		// get the swap sign flag
		__m128i emm0 = _mm_and_si128(emm2, four);
		emm0 = _mm_slli_epi32(emm0, 29);
		emm0 = _mm_move_epi64(emm0);
		emm0 = _mm_shuffle_epi32(emm0, _MM_SHUFFLE(1,3,0,2));
		__m128d swap_sign_bit = _mm_castsi128_pd(emm0);
		sign_bit = _mm_xor_pd(sign_bit, swap_sign_bit);

		// The magic pass: Extended precision modular arithmetic
		//   x = ((x - y * DP1) - y * DP2) - y * DP3
		__m128d xmm1 = *(__m128d*)hkSse_D_DP1;
		__m128d xmm2 = *(__m128d*)hkSse_D_DP2;
		__m128d xmm3 = *(__m128d*)hkSse_D_DP3;
		xmm1 = _mm_mul_pd(y, xmm1);
		xmm2 = _mm_mul_pd(y, xmm2);
		xmm3 = _mm_mul_pd(y, xmm3);
		x = _mm_add_pd(x, xmm1);
		x = _mm_add_pd(x, xmm2);
		x = _mm_add_pd(x, xmm3);

		__m128d z = _mm_mul_pd(x,x);

		// Evaluate the first polynom  (0 <= x <= Pi/4)
		y = *(__m128d*)hkSse_D_cosCoeff0;
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)hkSse_D_cosCoeff1);
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)hkSse_D_cosCoeff2);
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)hkSse_D_cosCoeff3);
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)hkSse_D_cosCoeff4);
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)hkSse_D_cosCoeff5);
		y = _mm_mul_pd(y, z);
		y = _mm_mul_pd(y, z);
		__m128d tmp = _mm_mul_pd(z, *(__m128d*)hkSse_doubleHalf);
		y = _mm_sub_pd(y, tmp);
		y = _mm_add_pd(y, *(__m128d*)hkSse_doubleOne);

		// Evaluate the second polynom  (Pi/4 <= x <= 0)
		__m128d y2 = *(__m128d*)hkSse_D_sinCoeff0;
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)hkSse_D_sinCoeff1);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)hkSse_D_sinCoeff2);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)hkSse_D_sinCoeff3);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)hkSse_D_sinCoeff4);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)hkSse_D_sinCoeff5);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_mul_pd(y2, x);
		y2 = _mm_add_pd(y2, x);

		// get the polynom selection mask and
		// select the correct result from the two polynoms
#if HK_SSE_VERSION >= 0x41
		emm2 = _mm_slli_epi32(emm2, 30);
		emm2 = _mm_shuffle_epi32(emm2, _MM_SHUFFLE(1,1,0,0));
		__m128d poly_mask = _mm_castsi128_pd(emm2);
		y = _mm_blendv_pd(y2,y,poly_mask);
#else
		emm2 = _mm_and_si128(emm2, two);
		emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());
		emm2 = _mm_shuffle_epi32(emm2, _MM_SHUFFLE(1,1,0,0));
		__m128d poly_mask = _mm_castsi128_pd(emm2);
		y2 = _mm_and_pd(poly_mask, y2);
		y = _mm_andnot_pd(poly_mask, y);
		y = _mm_or_pd(y,y2);
#endif
		// clamp
		y = _mm_min_pd(y, *(__m128d*)hkSse_doubleOne);

		// update the sign
		y = _mm_xor_pd(y, sign_bit);

		return y;
	}

	/// Adapted from the book "Methods and Programs for Mathematical Functions",
	/// Stephen Lloyd Baluk Moshier, Prentice-Hall, 1989
	///
	/// Range reduction is into intervals of pi/4.  The reduction error is nearly eliminated
	/// by extended precision modular arithmetic.
	///
	/// Two polynomial approximating functions are employed.
	/// Between 0 and pi/4 the sine is approximated by
	///      1  -  x**2 Q(x**2).
	/// Between pi/4 and pi/2 the cosine is represented as
	///      x  +  x**3 P(x**2).
	///
	/// ACCURACY: matches cmath on MSVC
	///
	///                      Relative error:
	/// arithmetic   domain        peak       rms
	///    IEEE    -8192,+8192    3.0e-7     3.0e-8
	/// Partial loss of accuracy begins to occur at x = 2^13
	/// = 8192. Results may be meaningless for x >= 2^24
	///
	/// PERFORMANCE: About 4.3x faster than ::cosf for 4 simultaneous values

	HK_FORCE_INLINE static __m128 HK_CALL quadCos(const __m128& inX)
	{
		// get abs and sign
		__m128 x = _mm_andnot_ps( *(__m128*)hkSse_signMask, inX);

		// scale by 4/Pi
		__m128 y = _mm_mul_ps(x, *(__m128*)hkSse_fourOverPi);

		__m128i one = *(__m128i*)hkSse_intOne;
		__m128i two = _mm_add_epi32(one,one);
		__m128i four = _mm_add_epi32(two,two);
		// store the integer part of y in emm2
		__m128i emm2 = _mm_cvttps_epi32(y);
		// j=(j+1) & (~1)
		emm2 = _mm_add_epi32(emm2, one);
		emm2 = _mm_andnot_si128(one, emm2);
		y = _mm_cvtepi32_ps(emm2);
		emm2 = _mm_sub_epi32(emm2, two);
		// get the swap sign flag
		__m128i emm0 = _mm_andnot_si128(emm2, four);
		emm0 = _mm_slli_epi32(emm0, 29);
		__m128 sign_bit = _mm_castsi128_ps(emm0);

		// The magic pass: Extended precision modular arithmetic
		//   x = ((x - y * DP1) - y * DP2) - y * DP3
		__m128 xmm1 = *(__m128*)hkSse_DP1;
		__m128 xmm2 = *(__m128*)hkSse_DP2;
		__m128 xmm3 = *(__m128*)hkSse_DP3;
		xmm1 = _mm_mul_ps(y, xmm1);
		xmm2 = _mm_mul_ps(y, xmm2);
		xmm3 = _mm_mul_ps(y, xmm3);
		x = _mm_add_ps(x, xmm1);
		x = _mm_add_ps(x, xmm2);
		x = _mm_add_ps(x, xmm3);

		// Evaluate the first polynom  (0 <= x <= Pi/4)
		y = *(__m128*)hkSse_cosCoeff0;
		__m128 z = _mm_mul_ps(x,x);

		y = _mm_mul_ps(y, z);
		y = _mm_add_ps(y, *(__m128*)hkSse_cosCoeff1);
		y = _mm_mul_ps(y, z);
		y = _mm_add_ps(y, *(__m128*)hkSse_cosCoeff2);
		y = _mm_mul_ps(y, z);
		y = _mm_mul_ps(y, z);
		__m128 tmp = _mm_mul_ps(z, *(__m128*)hkSse_floatHalf);
		y = _mm_sub_ps(y, tmp);
		y = _mm_add_ps(y, *(__m128*)hkSse_floatOne);

		// Evaluate the second polynom  (Pi/4 <= x <= 0)
		__m128 y2 = *(__m128*)hkSse_sinCoeff0;
		y2 = _mm_mul_ps(y2, z);
		y2 = _mm_add_ps(y2, *(__m128*)hkSse_sinCoeff1);
		y2 = _mm_mul_ps(y2, z);
		y2 = _mm_add_ps(y2, *(__m128*)hkSse_sinCoeff2);
		y2 = _mm_mul_ps(y2, z);
		y2 = _mm_mul_ps(y2, x);
		y2 = _mm_add_ps(y2, x);

		// get the polynom selection mask and
		// select the correct result from the two polynoms
#if HK_SSE_VERSION >= 0x41
		emm2 = _mm_slli_epi32(emm2, 30);
		__m128 poly_mask = _mm_castsi128_ps(emm2);
		y = _mm_blendv_ps(y2,y,poly_mask);
#else
		emm2 = _mm_and_si128(emm2, two);
		emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());
		__m128 poly_mask = _mm_castsi128_ps(emm2);
		y2 = _mm_and_ps(poly_mask, y2);
		y = _mm_andnot_ps(poly_mask, y);
		y = _mm_or_ps(y,y2);
#endif
		// clamp
		y = _mm_min_ps(y, *(__m128*)hkSse_floatOne);

		// update the sign
		y = _mm_xor_ps(y, sign_bit);

		return y;
	}

	/// Double precision version of above
	///
	///                      Relative error:
	/// arithmetic   domain        peak       rms
	///    IEEE -1.07e9,+1.07e9  2.1e-16     5.4e-17
	/// Partial loss of accuracy begins to occur at x = 2**30
	/// = 1.074e9.  The loss is not gradual, but jumps suddenly to
	/// about 1 part in 10e7.  Results may be meaningless for
	/// x > 2**49 = 5.6e14.
	///
	/// PERFORMANCE: About 1.3x faster than ::cos for 2 simultaneous values

	HK_FORCE_INLINE static __m128d HK_CALL twoCos(const __m128d& inX)
	{
		// get abs and sign
		__m128d x = _mm_andnot_pd( *(__m128d*)hkSse_D_signMask, inX);

		// scale by 4/Pi
		__m128d y = _mm_mul_pd(x, *(__m128d*)hkSse_D_fourOverPi);

		__m128i one = *(__m128i*)hkSse_intOne;
		__m128i two = _mm_add_epi32(one,one);
		__m128i four = _mm_add_epi32(two,two);
		// store the integer part of y in emm2
		__m128i emm2 = _mm_cvttpd_epi32(y);
		// j=(j+1) & (~1)
		emm2 = _mm_add_epi32(emm2, one);
		emm2 = _mm_andnot_si128(one, emm2);
		y = _mm_cvtepi32_pd(emm2);
		emm2 = _mm_sub_epi32(emm2, two);
		// get the swap sign flag
		__m128i emm0 = _mm_andnot_si128(emm2, four);
		emm0 = _mm_slli_epi32(emm0, 29);
		emm0 = _mm_move_epi64(emm0);
		emm0 = _mm_shuffle_epi32(emm0, _MM_SHUFFLE(1,3,0,2));
		__m128d sign_bit = _mm_castsi128_pd(emm0);

		// The magic pass: Extended precision modular arithmetic
		//   x = ((x - y * DP1) - y * DP2) - y * DP3
		__m128d xmm1 = *(__m128d*)hkSse_D_DP1;
		__m128d xmm2 = *(__m128d*)hkSse_D_DP2;
		__m128d xmm3 = *(__m128d*)hkSse_D_DP3;
		xmm1 = _mm_mul_pd(y, xmm1);
		xmm2 = _mm_mul_pd(y, xmm2);
		xmm3 = _mm_mul_pd(y, xmm3);
		x = _mm_add_pd(x, xmm1);
		x = _mm_add_pd(x, xmm2);
		x = _mm_add_pd(x, xmm3);

		__m128d z = _mm_mul_pd(x,x);

		// Evaluate the first polynom  (0 <= x <= Pi/4)
		y = *(__m128d*)hkSse_D_cosCoeff0;
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)hkSse_D_cosCoeff1);
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)hkSse_D_cosCoeff2);
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)hkSse_D_cosCoeff3);
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)hkSse_D_cosCoeff4);
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)hkSse_D_cosCoeff5);
		y = _mm_mul_pd(y, z);
		y = _mm_mul_pd(y, z);
		__m128d tmp = _mm_mul_pd(z, *(__m128d*)hkSse_doubleHalf);
		y = _mm_sub_pd(y, tmp);
		y = _mm_add_pd(y, *(__m128d*)hkSse_doubleOne);

		// Evaluate the second polynom  (Pi/4 <= x <= 0)
		__m128d y2 = *(__m128d*)hkSse_D_sinCoeff0;
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)hkSse_D_sinCoeff1);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)hkSse_D_sinCoeff2);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)hkSse_D_sinCoeff3);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)hkSse_D_sinCoeff4);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)hkSse_D_sinCoeff5);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_mul_pd(y2, x);
		y2 = _mm_add_pd(y2, x);

		// get the polynom selection mask and
		// select the correct result from the two polynoms
#if HK_SSE_VERSION >= 0x41
		emm2 = _mm_slli_epi32(emm2, 30);
		emm2 = _mm_shuffle_epi32(emm2, _MM_SHUFFLE(1,1,0,0));
		__m128d poly_mask = _mm_castsi128_pd(emm2);
		y = _mm_blendv_pd(y2,y,poly_mask);
#else
		emm2 = _mm_and_si128(emm2, two);
		emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());
		emm2 = _mm_shuffle_epi32(emm2, _MM_SHUFFLE(1,1,0,0));
		__m128d poly_mask = _mm_castsi128_pd(emm2);
		y2 = _mm_and_pd(poly_mask, y2);
		y = _mm_andnot_pd(poly_mask, y);
		y = _mm_or_pd(y,y2);
#endif
		// clamp
		y = _mm_min_pd(y, *(__m128d*)hkSse_doubleOne);

		// update the sign
		y = _mm_xor_pd(y, sign_bit);

		return y;
	}

	/// Combined sin and cos calculation derived from the algorithms above.
	///
	/// PERFORMANCE: About 5.9x faster than ::sin and ::cos for 2 simultaneous values

	HK_FORCE_INLINE static void HK_CALL twoSinCos(const __m128d& inX, __m128d& s, __m128d& c)
	{
		// get abs and sign
		__m128d x = _mm_andnot_pd( *(__m128d*)hkSse_D_signMask, inX);
		__m128d sign_bit_sin = _mm_and_pd( *(__m128d*)hkSse_D_signMask, inX);

		// scale by 4/Pi
		__m128d y = _mm_mul_pd(x, *(__m128d*)hkSse_D_fourOverPi);

		__m128i one = *(__m128i*)hkSse_intOne;
		__m128i two = _mm_add_epi32(one,one);
		__m128i four = _mm_add_epi32(two,two);
		// store the integer part of y in emm2
		__m128i emm2 = _mm_cvttpd_epi32(y);
		// j=(j+1) & (~1)
		emm2 = _mm_add_epi32(emm2, one);
		emm2 = _mm_andnot_si128(one, emm2);
		y = _mm_cvtepi32_pd(emm2);

		__m128i emm4 = emm2;
		emm4 = _mm_sub_epi32(emm4, two);
		emm4 = _mm_andnot_si128(emm4, four);
		emm4 = _mm_slli_epi32(emm4, 29);
		emm4 = _mm_move_epi64(emm4);
		emm4 = _mm_shuffle_epi32(emm4, _MM_SHUFFLE(1,3,0,2));
		__m128d sign_bit_cos = _mm_castsi128_pd(emm4);

		// get the swap sign flag for the sine
		__m128i emm0 = _mm_and_si128(emm2, four);
		emm0 = _mm_slli_epi32(emm0, 29);
		emm0 = _mm_move_epi64(emm0);
		emm0 = _mm_shuffle_epi32(emm0, _MM_SHUFFLE(1,3,0,2));
		sign_bit_sin = _mm_xor_pd(sign_bit_sin, _mm_castsi128_pd(emm0));

		// The magic pass: Extended precision modular arithmetic
		//   x = ((x - y * DP1) - y * DP2) - y * DP3
		__m128d xmm1 = *(__m128d*)hkSse_D_DP1;
		__m128d xmm2 = *(__m128d*)hkSse_D_DP2;
		__m128d xmm3 = *(__m128d*)hkSse_D_DP3;
		xmm1 = _mm_mul_pd(y, xmm1);
		xmm2 = _mm_mul_pd(y, xmm2);
		xmm3 = _mm_mul_pd(y, xmm3);
		x = _mm_add_pd(x, xmm1);
		x = _mm_add_pd(x, xmm2);
		x = _mm_add_pd(x, xmm3);

		__m128d z = _mm_mul_pd(x,x);

		// Evaluate the first polynom  (0 <= x <= Pi/4)
		y = *(__m128d*)hkSse_D_cosCoeff0;
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)hkSse_D_cosCoeff1);
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)hkSse_D_cosCoeff2);
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)hkSse_D_cosCoeff3);
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)hkSse_D_cosCoeff4);
		y = _mm_mul_pd(y, z);
		y = _mm_add_pd(y, *(__m128d*)hkSse_D_cosCoeff5);
		y = _mm_mul_pd(y, z);
		y = _mm_mul_pd(y, z);
		__m128d tmp = _mm_mul_pd(z, *(__m128d*)hkSse_doubleHalf);
		y = _mm_sub_pd(y, tmp);
		y = _mm_add_pd(y, *(__m128d*)hkSse_doubleOne);

		// Evaluate the second polynom  (Pi/4 <= x <= 0)
		__m128d y2 = *(__m128d*)hkSse_D_sinCoeff0;
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)hkSse_D_sinCoeff1);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)hkSse_D_sinCoeff2);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)hkSse_D_sinCoeff3);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)hkSse_D_sinCoeff4);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_add_pd(y2, *(__m128d*)hkSse_D_sinCoeff5);
		y2 = _mm_mul_pd(y2, z);
		y2 = _mm_mul_pd(y2, x);
		y2 = _mm_add_pd(y2, x);

		// get the polynom selection mask for the sine
		emm2 = _mm_and_si128(emm2, two);
		emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());
		emm2 = _mm_shuffle_epi32(emm2, _MM_SHUFFLE(1,1,0,0));
		__m128d poly_mask = _mm_castsi128_pd(emm2);

		// select the correct result from the two polynoms
		__m128d ysin2 = _mm_and_pd(poly_mask, y2);
		__m128d ysin1 = _mm_andnot_pd(poly_mask, y);
		y2 = _mm_sub_pd(y2,ysin2);
		y = _mm_sub_pd(y, ysin1);

		xmm1 = _mm_add_pd(ysin1,ysin2);
		xmm2 = _mm_add_pd(y,y2);

		// clamp
		xmm1 = _mm_min_pd(xmm1, *(__m128d*)hkSse_doubleOne);
		xmm2 = _mm_min_pd(xmm2, *(__m128d*)hkSse_doubleOne);

		// update the signs
		s = _mm_xor_pd(xmm1, sign_bit_sin);
		c = _mm_xor_pd(xmm2, sign_bit_cos);
	}

	/// Combined sin and cos calculation derived from the algorithms above.
	///
	/// PERFORMANCE: About 6.1x faster than ::sinf and ::cosf for 4 simultaneous values

	HK_FORCE_INLINE static void HK_CALL quadSinCos(const __m128& inX, __m128& s, __m128& c)
	{
		// get abs and sign
		__m128 x = _mm_andnot_ps( *(__m128*)hkSse_signMask, inX);
		// extract the sign bit (upper one)
		__m128 sign_bit_sin = _mm_and_ps( *(__m128*)hkSse_signMask, inX);

		// scale by 4/Pi
		__m128 y = _mm_mul_ps(x, *(__m128*)hkSse_fourOverPi);

		__m128i one = *(__m128i*)hkSse_intOne;
		__m128i two = _mm_add_epi32(one,one);
		__m128i four = _mm_add_epi32(two,two);
		// store the integer part of y in emm2
		__m128i emm2 = _mm_cvttps_epi32(y);
		// j=(j+1) & (~1)
		emm2 = _mm_add_epi32(emm2, one);
		emm2 = _mm_andnot_si128(one, emm2);
		y = _mm_cvtepi32_ps(emm2);

		__m128i emm4 = emm2;
		emm4 = _mm_sub_epi32(emm4, two);
		emm4 = _mm_andnot_si128(emm4, four);
		emm4 = _mm_slli_epi32(emm4, 29);
		__m128 sign_bit_cos = _mm_castsi128_ps(emm4);

		// get the swap sign flag for the sine
		__m128i emm0 = _mm_and_si128(emm2, four);
		emm0 = _mm_slli_epi32(emm0, 29);
		sign_bit_sin = _mm_xor_ps(sign_bit_sin, _mm_castsi128_ps(emm0));

		// The magic pass: Extended precision modular arithmetic
		//   x = ((x - y * DP1) - y * DP2) - y * DP3
		__m128 xmm1 = *(__m128*)hkSse_DP1;
		__m128 xmm2 = *(__m128*)hkSse_DP2;
		__m128 xmm3 = *(__m128*)hkSse_DP3;
		xmm1 = _mm_mul_ps(y, xmm1);
		xmm2 = _mm_mul_ps(y, xmm2);
		xmm3 = _mm_mul_ps(y, xmm3);
		x = _mm_add_ps(x, xmm1);
		x = _mm_add_ps(x, xmm2);
		x = _mm_add_ps(x, xmm3);

		// Evaluate the first polynom  (0 <= x <= Pi/4)
		y = *(__m128*)hkSse_cosCoeff0;
		__m128 z = _mm_mul_ps(x,x);

		y = _mm_mul_ps(y, z);
		y = _mm_add_ps(y, *(__m128*)hkSse_cosCoeff1);
		y = _mm_mul_ps(y, z);
		y = _mm_add_ps(y, *(__m128*)hkSse_cosCoeff2);
		y = _mm_mul_ps(y, z);
		y = _mm_mul_ps(y, z);
		__m128 tmp = _mm_mul_ps(z, *(__m128*)hkSse_floatHalf);
		y = _mm_sub_ps(y, tmp);
		y = _mm_add_ps(y, *(__m128*)hkSse_floatOne);

		// Evaluate the second polynom  (Pi/4 <= x <= 0)
		__m128 y2 = *(__m128*)hkSse_sinCoeff0;
		y2 = _mm_mul_ps(y2, z);
		y2 = _mm_add_ps(y2, *(__m128*)hkSse_sinCoeff1);
		y2 = _mm_mul_ps(y2, z);
		y2 = _mm_add_ps(y2, *(__m128*)hkSse_sinCoeff2);
		y2 = _mm_mul_ps(y2, z);
		y2 = _mm_mul_ps(y2, x);
		y2 = _mm_add_ps(y2, x);

		// get the polynom selection mask for the sine
		emm2 = _mm_and_si128(emm2, two);
		emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());
		__m128 poly_mask = _mm_castsi128_ps(emm2);

		// select the correct result from the two polynoms
		__m128 ysin2 = _mm_and_ps(poly_mask, y2);
		__m128 ysin1 = _mm_andnot_ps(poly_mask, y);
		y2 = _mm_sub_ps(y2,ysin2);
		y = _mm_sub_ps(y, ysin1);

		xmm1 = _mm_add_ps(ysin1,ysin2);
		xmm2 = _mm_add_ps(y,y2);

		// clamp
		xmm1 = _mm_min_ps(xmm1, *(__m128*)hkSse_floatOne);
		xmm2 = _mm_min_ps(xmm2, *(__m128*)hkSse_floatOne);

		// update the signs
		s = _mm_xor_ps(xmm1, sign_bit_sin);
		c = _mm_xor_ps(xmm2, sign_bit_cos);
	}


	/// Adapted from the book "Methods and Programs for Mathematical Functions",
	/// Stephen Lloyd Baluk Moshier, Prentice-Hall, 1989
	///
	/// A polynomial of the form x + x**3 P(x**2)
	/// is used for |x| in the interval [0, 0.5].  If |x| > 0.5 it is
	/// transformed by the identity
	///
	///    asin(x) = pi/2 - 2 asin( sqrt( (1-x)/2 ) ).
	///
	/// ACCURACY: matches cmath on MSVC
	///
	/// Important: unlike the cmath function, this one clamps the input to [-1,1]
	///
	///                      Relative error:
	/// arithmetic   domain      peak         rms
	///    IEEE     -1, 1       2.5e-7       5.0e-8
	///
	/// PERFORMANCE: About 8x faster than ::asinf for 4 simultaneous values

	HK_FORCE_INLINE static __m128 HK_CALL quadAsin(const __m128& xx)
	{
		HK_ALIGN16(static const hkInt32 linearLimit[4])  = { 0x38D1B717, 0x38D1B717, 0x38D1B717, 0x38D1B717 }; // 1e-4
		HK_ALIGN16(static const hkInt32 coeff4[4])       = { 0x3D2CB352, 0x3D2CB352, 0x3D2CB352, 0x3D2CB352 }; // 4.2163199048E-2
		HK_ALIGN16(static const hkInt32 coeff3[4])       = { 0x3CC617E3, 0x3CC617E3, 0x3CC617E3, 0x3CC617E3 }; // 2.4181311049E-2
		HK_ALIGN16(static const hkInt32 coeff2[4])       = { 0x3D3A3EC7, 0x3D3A3EC7, 0x3D3A3EC7, 0x3D3A3EC7 }; // 4.5470025998E-2
		HK_ALIGN16(static const hkInt32 coeff1[4])       = { 0x3D9980F6, 0x3D9980F6, 0x3D9980F6, 0x3D9980F6 }; // 7.4953002686E-2
		HK_ALIGN16(static const hkInt32 coeff0[4])       = { 0x3E2AAAE4, 0x3E2AAAE4, 0x3E2AAAE4, 0x3E2AAAE4 }; // 1.6666752422E-1

		__m128 a = _mm_andnot_ps( *(__m128*)hkSse_signMask, xx); a = _mm_min_ps(*(__m128*)hkSse_floatOne,a);
		__m128 sign = _mm_and_ps(*(__m128*)hkSse_signMask, xx);

		// linear approximation
		__m128 lessLimit = _mm_cmplt_ps(a,*(__m128*)linearLimit);

		// a > 0.5
		__m128 zGT = _mm_mul_ps(*(__m128*)hkSse_floatHalf, _mm_sub_ps(*(__m128*)hkSse_floatOne, a));
		__m128 xGT = _mm_sqrt_ps(zGT);

		// a <= 0.5
		__m128 xLE = a;
		__m128 zLE = _mm_mul_ps(xLE,xLE);

		// select polynom
		__m128 rangeMask = _mm_cmpgt_ps(a, *(__m128*)hkSse_floatHalf);
#if HK_SSE_VERSION >= 0x41
		__m128 x = _mm_blendv_ps(xLE,xGT,rangeMask);
		__m128 z = _mm_blendv_ps(zLE,zGT,rangeMask);
#else
		__m128 x = _mm_or_ps(_mm_andnot_ps(rangeMask, xLE),_mm_and_ps(rangeMask, xGT));
		__m128 z = _mm_or_ps(_mm_andnot_ps(rangeMask, zLE),_mm_and_ps(rangeMask, zGT));
#endif

		// zz = (((((c4*z)+c3)*z+c2)*z+c1)*z+c0)*z*x+x
		__m128 zz = _mm_mul_ps(*(__m128*)coeff4, z);
		zz = _mm_add_ps(*(__m128*)coeff3, zz);
		zz = _mm_mul_ps(zz,z);
		zz = _mm_add_ps(*(__m128*)coeff2, zz);
		zz = _mm_mul_ps(zz,z);
		zz = _mm_add_ps(*(__m128*)coeff1, zz);
		zz = _mm_mul_ps(zz,z);
		zz = _mm_add_ps(*(__m128*)coeff0, zz);
		zz = _mm_mul_ps(zz,z);
		zz = _mm_mul_ps(zz,x);
		zz = _mm_add_ps(zz,x);

		// transform
		__m128 zzGT = _mm_add_ps(zz,zz);
		zzGT = _mm_sub_ps(*(__m128*)hkSse_piOver2,zzGT);
#if HK_SSE_VERSION >= 0x41
		zz = _mm_blendv_ps(zz,zzGT,rangeMask);
#else
		zz = _mm_or_ps(_mm_andnot_ps(rangeMask, zz),_mm_and_ps(rangeMask, zzGT));
#endif

		// select linear approximation
#if HK_SSE_VERSION >= 0x41
		zz = _mm_blendv_ps(zz,a,lessLimit);
#else
		zz = _mm_or_ps(_mm_andnot_ps(lessLimit, zz),_mm_and_ps(lessLimit, a));
#endif

		// update the sign
		zz = _mm_xor_ps(zz, sign);

		return zz;
	}

	/// Double precision version of above except that it uses
	/// a rational function of the form x + x**3 P(x**2)/Q(x**2)
	///
	///                      Relative error:
	/// arithmetic   domain        peak       rms
	///    IEEE     -1, 1       1.9e-16     5.4e-17
	///
	/// PERFORMANCE: About 2x faster than ::asin for 2 simultaneous values

	HK_FORCE_INLINE static __m128d HK_CALL twoAsin(const __m128d& xx)
	{
		HK_ALIGN16(static const hkInt64 linearLimit[2])  = { 0x3E45798EE2308C3Aull, 0x3E45798EE2308C3Aull }; // 1e-8
		HK_ALIGN16(static const hkInt64 limit[2])        = { 0x3FE4000000000000ull, 0x3FE4000000000000ull }; // 0.625
		HK_ALIGN16(static const hkInt64 morebits[2])     = { 0x3C91A62633145C07ull, 0x3C91A62633145C07ull }; // 6.123233995736765886130E-17
		HK_ALIGN16(static const hkInt64 R0[2])           = { 0x3f684fc3988e9f08ull, 0x3f684fc3988e9f08ull }; //  2.967721961301243206100E-3
		HK_ALIGN16(static const hkInt64 R1[2])           = { 0xbfe2079259f9290full, 0xbfe2079259f9290full }; // -5.634242780008963776856E-1
		HK_ALIGN16(static const hkInt64 R2[2])           = { 0x401bdff5baf33e6aull, 0x401bdff5baf33e6aull }; //  6.968710824104713396794E0
		HK_ALIGN16(static const hkInt64 R3[2])           = { 0xc03991aaac01ab68ull, 0xc03991aaac01ab68ull }; // -2.556901049652824852289E1
		HK_ALIGN16(static const hkInt64 R4[2])           = { 0x403c896240f3081dull, 0x403c896240f3081dull }; //  2.853665548261061424989E1
		HK_ALIGN16(static const hkInt64 S1[2])           = { 0xc035f2a2b6bf5d8cull, 0xc035f2a2b6bf5d8cull }; // -2.194779531642920639778E1
		HK_ALIGN16(static const hkInt64 S2[2])           = { 0x40626219af6a7f42ull, 0x40626219af6a7f42ull }; //  1.470656354026814941758E2
		HK_ALIGN16(static const hkInt64 S3[2])           = { 0xc077fe08959063eeull, 0xc077fe08959063eeull }; // -3.838770957603691357202E2
		HK_ALIGN16(static const hkInt64 S4[2])           = { 0x40756709b0b644beull, 0x40756709b0b644beull }; //  3.424398657913078477438E2
		HK_ALIGN16(static const hkInt64 P0[2])           = { 0x3f716b9b0bd48ad3ull, 0x3f716b9b0bd48ad3ull }; //  4.253011369004428248960E-3
		HK_ALIGN16(static const hkInt64 P1[2])           = { 0xbfe34341333e5c16ull, 0xbfe34341333e5c16ull }; // -6.019598008014123785661E-1
		HK_ALIGN16(static const hkInt64 P2[2])           = { 0x4015c74b178a2dd9ull, 0x4015c74b178a2dd9ull }; //  5.444622390564711410273E0
		HK_ALIGN16(static const hkInt64 P3[2])           = { 0xc0304331de27907bull, 0xc0304331de27907bull }; // -1.626247967210700244449E1
		HK_ALIGN16(static const hkInt64 P4[2])           = { 0x40339007da779259ull, 0x40339007da779259ull }; //  1.956261983317594739197E1
		HK_ALIGN16(static const hkInt64 P5[2])           = { 0xc020656c06ceafd5ull, 0xc020656c06ceafd5ull }; // -8.198089802484824371615E0
		HK_ALIGN16(static const hkInt64 Q1[2])           = { 0xc02d7b590b5e0eabull, 0xc02d7b590b5e0eabull }; // -1.474091372988853791896E1
		HK_ALIGN16(static const hkInt64 Q2[2])           = { 0x40519fc025fe9054ull, 0x40519fc025fe9054ull }; //  7.049610280856842141659E1
		HK_ALIGN16(static const hkInt64 Q3[2])           = { 0xc06265bb6d3576d7ull, 0xc06265bb6d3576d7ull }; // -1.471791292232726029859E2
		HK_ALIGN16(static const hkInt64 Q4[2])           = { 0x4061705684ffbf9dull, 0x4061705684ffbf9dull }; //  1.395105614657485689735E2
		HK_ALIGN16(static const hkInt64 Q5[2])           = { 0xc04898220a3607acull, 0xc04898220a3607acull }; // -4.918853881490881290097E1


		__m128d a = _mm_andnot_pd( *(__m128d*)hkSse_D_signMask, xx); a = _mm_min_pd(*(__m128d*)hkSse_doubleOne,a);
		__m128d sign = _mm_and_pd(*(__m128d*)hkSse_D_signMask, xx);

		// linear approximation
		__m128d lessLimit = _mm_cmplt_pd(a,*(__m128d*)linearLimit);

		__m128d selectGT = _mm_cmpgt_pd(a, *(__m128d*)limit);

		// a > 0.625
		__m128d zGT;
		{
			__m128d zz = _mm_sub_pd(*(__m128d*)hkSse_doubleOne, a);

			__m128d polR = _mm_mul_pd(*(__m128d*)R0, zz);
			polR = _mm_add_pd(polR, *(__m128d*)R1);
			polR = _mm_mul_pd(polR, zz);
			polR = _mm_add_pd(polR, *(__m128d*)R2);
			polR = _mm_mul_pd(polR, zz);
			polR = _mm_add_pd(polR, *(__m128d*)R3);
			polR = _mm_mul_pd(polR, zz);
			polR = _mm_add_pd(polR, *(__m128d*)R4);
			polR = _mm_mul_pd(polR, zz);

			__m128d polS = zz; // coeff0 = 1
			polS = _mm_add_pd(polS, *(__m128d*)S1);
			polS = _mm_mul_pd(polS, zz);
			polS = _mm_add_pd(polS, *(__m128d*)S2);
			polS = _mm_mul_pd(polS, zz);
			polS = _mm_add_pd(polS, *(__m128d*)S3);
			polS = _mm_mul_pd(polS, zz);
			polS = _mm_add_pd(polS, *(__m128d*)S4);

			__m128d p = _mm_div_pd(polR,polS);
			zz = _mm_sqrt_pd(_mm_add_pd(zz,zz));
			zGT = _mm_sub_pd(*(__m128d*)hkSse_D_piOver4, zz);
			zz = _mm_sub_pd(_mm_mul_pd(zz,p),*(__m128d*)morebits);
			zGT = _mm_sub_pd(zGT,zz);
			zGT = _mm_add_pd(zGT, *(__m128d*)hkSse_D_piOver4);
		}

		// a <= 0.625
		__m128d zLT;
		{
			__m128d zz = _mm_mul_pd(a,a);

			__m128d polP = _mm_mul_pd(*(__m128d*)P0, zz);
			polP = _mm_add_pd(polP, *(__m128d*)P1);
			polP = _mm_mul_pd(polP, zz);
			polP = _mm_add_pd(polP, *(__m128d*)P2);
			polP = _mm_mul_pd(polP, zz);
			polP = _mm_add_pd(polP, *(__m128d*)P3);
			polP = _mm_mul_pd(polP, zz);
			polP = _mm_add_pd(polP, *(__m128d*)P4);
			polP = _mm_mul_pd(polP, zz);
			polP = _mm_add_pd(polP, *(__m128d*)P5);
			polP = _mm_mul_pd(polP, zz);

			__m128d polQ = zz; // coeff0 = 1
			polQ = _mm_add_pd(polQ, *(__m128d*)Q1);
			polQ = _mm_mul_pd(polQ, zz);
			polQ = _mm_add_pd(polQ, *(__m128d*)Q2);
			polQ = _mm_mul_pd(polQ, zz);
			polQ = _mm_add_pd(polQ, *(__m128d*)Q3);
			polQ = _mm_mul_pd(polQ, zz);
			polQ = _mm_add_pd(polQ, *(__m128d*)Q4);
			polQ = _mm_mul_pd(polQ, zz);
			polQ = _mm_add_pd(polQ, *(__m128d*)Q5);

			zLT = _mm_div_pd(polP,polQ);
			zLT = _mm_mul_pd(a,zLT);
			zLT = _mm_add_pd(a,zLT);
		}

		__m128d z;

		// select case and linear approximation
#if HK_SSE_VERSION >= 0x41
		z = _mm_blendv_pd(zLT,zGT,selectGT);
		z = _mm_blendv_pd(z,a,lessLimit);
#else
		z = _mm_or_pd(_mm_andnot_pd(selectGT, zLT),_mm_and_pd(selectGT, zGT));
		z = _mm_or_pd(_mm_andnot_pd(lessLimit, z),_mm_and_pd(lessLimit, a));
#endif

		// update the sign
		z = _mm_xor_pd(z, sign);

		return z;
	}



	/// Properties see quadSinApproximation
	HK_FORCE_INLINE static __m128 HK_CALL quadCosApproximation(const __m128& x)
	{
		// cos(x) = sin(x + pi/2)
		__m128 xx = _mm_add_ps(x, *(__m128*)&hkSse_piOver2);
		return quadSinApproximation(xx);
	}

	/// Properties see quadSinApproximation
	HK_FORCE_INLINE static __m128d HK_CALL twoCosApproximation(const __m128d& x)
	{
		// cos(x) = sin(x + pi/2)
		__m128d xx = _mm_add_pd(x, *(__m128d*)hkSse_D_piOver2);
		return twoSinApproximation(xx);
	}

	HK_FORCE_INLINE static __m128 HK_CALL quadAcos(const __m128& xx)
	{
		// acos(x) = pi/2 - asin(x)
		__m128 x = _mm_sub_ps(*(__m128*)hkSse_piOver2, quadAsin(xx));
		return x;
	}

	HK_FORCE_INLINE static __m128d HK_CALL twoAcos(const __m128d& xx)
	{
		// acos(x) = pi/2 - asin(x)
		__m128d x = _mm_sub_pd(*(__m128d*)hkSse_D_piOver2, twoAsin(xx));
		return x;
	}

	/// Calc cos/sin at the same time: xyzw -> sin(x)cos(y)sin(z)cos(w)
	/// Properties see quadSinApproximation
	HK_FORCE_INLINE static __m128 HK_CALL quadSinCosApproximation(const __m128& x)
	{
		// cos(x) = sin(x + pi/2)
		static HK_ALIGN16( const hkUint32 offset[4] ) = { 0x00000000, 0x3FC90FDB, 0x00000000, 0x3FC90FDB };
		__m128 xx = _mm_add_ps(x, *(__m128*)&offset);
		return quadSinApproximation(xx);
	}

	/// Calc cos/sin at the same time: xy -> sin(x)cos(y)
	/// Properties see twoSinApproximation
	HK_FORCE_INLINE static __m128d HK_CALL twoSinCosApproximation(const __m128d& x)
	{
		// cos(x) = sin(x + pi/2)
		static HK_ALIGN16( const hkUint64 offset[2] ) = { 0x0000000000000000ull, 0x3FF921FB54442D18ull };
		__m128d xx = _mm_add_pd(x, *(__m128d*)&offset);
		return twoSinApproximation(xx);
	}

	/// Calc acos/asin at the same time: xyzw -> asin(x)acos(y)asin(z)acos(w)
	/// Properties see quadAsin
	HK_FORCE_INLINE static __m128 HK_CALL quadAsinAcos(const __m128& x)
	{
		// acos(x) = pi/2 - asin(x)
		__m128 asinx = quadAsin(x);
#if HK_SSE_VERSION >= 0x41
		__m128 acosx = _mm_sub_ps(*(__m128*)hkSse_piOver2, asinx);
		return _mm_blend_ps(asinx,acosx,0xA);
#else
		HK_ALIGN16(static const hkInt32 selectSin[4])     = { 0x00000000, 0x3FC90FDB, 0x00000000, 0x3FC90FDB };
		__m128 acosx = _mm_sub_ps(*(__m128*)selectSin, asinx);
		__m128 sinselect = _mm_cmpeq_ps(*(__m128*)selectSin, _mm_setzero_ps());
		return _mm_or_ps(_mm_andnot_ps(sinselect, acosx),_mm_and_ps(sinselect, asinx));
#endif
	}

	/// Calc acos/asin at the same time: xy -> asin(x)acos(y)
	/// Properties see twoAsin
	HK_FORCE_INLINE static __m128d HK_CALL twoAsinAcos(const __m128d& x)
	{
		// acos(x) = pi/2 - asin(x)
		__m128d asinx = twoAsin(x);
		__m128d acosx = _mm_sub_pd(*(__m128d*)hkSse_D_piOver2, asinx);
		// Gcc 4.5.1 can mis-optimize _mm_move_sd
#if defined(HK_COMPILER_GCC) && (HK_COMPILER_GCC_VERSION <= 40501)
		return _mm_shuffle_pd(asinx, acosx, _MM_SHUFFLE2(1, 0));
#else
		return _mm_move_sd(acosx, asinx);
#endif
	}

#	define HK_MATH_sin
	HK_FORCE_INLINE static hkFloat32 HK_CALL sin (const hkFloat32 r)
	{
		__m128 rr = _mm_load_ss(&r);
		__m128 s = quadSin(rr);
		return _mm_cvtss_f32(s);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL sin (const hkDouble64 r)
	{
		__m128d rr = _mm_load_sd(&r);
		__m128d s = twoSin(rr);
		return _mm_cvtsd_f64(s);
	}

#	define HK_MATH_cos
	HK_FORCE_INLINE static hkFloat32 HK_CALL cos (const hkFloat32 r)
	{
		__m128 rr = _mm_load_ss(&r);
		__m128 c = quadCos(rr);
		return _mm_cvtss_f32(c);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL cos (const hkDouble64 r)
	{
		__m128d rr = _mm_load_sd(&r);
		__m128d s = twoCos(rr);
		return _mm_cvtsd_f64(s);
	}

#	define HK_MATH_asin
	HK_FORCE_INLINE static hkFloat32 HK_CALL asin(const hkFloat32 r)
	{
		// be generous about numbers outside range
		HK_ASSERT(0x286a6f5f,  hkMath::fabs(r) < 1.001f ); // assert imported from default impl
		__m128 rr = _mm_load_ss(&r);
		__m128 s = quadAsin(rr); // quadAsin clamps [-1;1]
		return _mm_cvtss_f32(s);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL asin(const hkDouble64 r)
	{
		// be generous about numbers outside range
		HK_ASSERT(0x286a6f5f,  hkMath::fabs(r) < 1.001 ); // assert imported from default impl
		__m128d rr = _mm_load_sd(&r);
		__m128d s = twoAsin(rr);  // twoAsin clamps [-1;1]
		return _mm_cvtsd_f64(s);
	}

#	define HK_MATH_acos
	HK_FORCE_INLINE static hkFloat32 HK_CALL acos(const hkFloat32 r)
	{
		// be generous about numbers outside range
		HK_ASSERT(0x41278654,  hkMath::fabs(r) < 1.001f ); // assert imported from default impl
		__m128 rr = _mm_load_ss(&r);
		__m128 s = quadAcos(rr); // quadAcos clamps [-1;1]
		return _mm_cvtss_f32(s);
	}
	HK_FORCE_INLINE static hkDouble64 HK_CALL acos(const hkDouble64 r)
	{
		// be generous about numbers outside range
		HK_ASSERT(0x41278654,  hkMath::fabs(r) < 1.001 ); // assert imported from default impl
		__m128d rr = _mm_load_sd(&r);
		__m128d s = twoAcos(rr);  // twoAcos clamps [-1;1]
		return _mm_cvtsd_f64(s);
	}

#if defined(HK_COMPILER_GCC)
#	define HK_MATH_countLeadingZeros

	template <typename T> HK_FORCE_INLINE int HK_CALL countLeadingZeros(T x);

	template <> HK_FORCE_INLINE int HK_CALL countLeadingZeros<hkUint32>(hkUint32 bitMask)	{	return bitMask ? __builtin_clz(bitMask) : 32;	}
	template <> HK_FORCE_INLINE int HK_CALL countLeadingZeros<hkUint64>(hkUint64 bitMask)	{	return bitMask ? __builtin_clzll(bitMask) : 64;	}
	template <> HK_FORCE_INLINE int HK_CALL countLeadingZeros<int>(int bitMask)				{	return countLeadingZeros<hkUint32>((hkUint32)bitMask);	}

#	define HK_MATH_countTrailingZeros

	template <typename T> HK_FORCE_INLINE int HK_CALL countTrailingZeros(T x);

	template <> HK_FORCE_INLINE int HK_CALL countTrailingZeros<hkUint32>(hkUint32 bitMask)	{	return bitMask ? __builtin_ctz(bitMask) : 32;	}
	template <> HK_FORCE_INLINE int HK_CALL countTrailingZeros<hkUint64>(hkUint64 bitMask)	{	return bitMask ? __builtin_ctzll(bitMask) : 64;	}
	template <> HK_FORCE_INLINE int HK_CALL countTrailingZeros<int>(int bitMask)			{	return countTrailingZeros<hkUint32>((hkUint32)bitMask);	}

// 	HK_SSE_VERSION >= 0x50 needs CPUID flag LZCNT in addition
// 	template <> HK_FORCE_INLINE int HK_CALL countLeadingZeros<hkUint32>(hkUint32 bitMask)	{	return (int)_lzcnt_u32(bitMask);	}
// 	template <> HK_FORCE_INLINE int HK_CALL countLeadingZeros<hkUint64>(hkUint64 bitMask)	{	return (int)_lzcnt_u64(bitMask);	}
// 	template <> HK_FORCE_INLINE int HK_CALL countLeadingZeros<int>(int bitMask)				{	return countLeadingZeros<hkUint32>((hkUint32)bitMask);	}

// 	HK_SSE_VERSION >= 0x50 needs CPUID flag BMI1 in addition
// 	template <> HK_FORCE_INLINE int HK_CALL countTrailingZeros<hkUint32>(hkUint32 bitMask)	{	return (int)_tzcnt_u32(bitMask);	}
// 	template <> HK_FORCE_INLINE int HK_CALL countTrailingZeros<hkUint64>(hkUint64 bitMask)	{	return (int)_tzcnt_u64(bitMask);	}
// 	template <> HK_FORCE_INLINE int HK_CALL countTrailingZeros<int>(int bitMask)			{	return countTrailingZeros<hkUint32>((hkUint32)bitMask);	}

#elif 0	// no CPU instruction yet, and _BitScanReverse requires an if
	// Returns the number of zeros at the start (MSB) of the given bitMask
#	define HK_MATH_countLeadingZeros
#	pragma intrinsic(_BitScanReverse)
#	pragma intrinsic(_BitScanReverse64)

	template <typename T>
	HK_FORCE_INLINE int HK_CALL countLeadingZeros(T x);

	template<>
	HK_FORCE_INLINE static int HK_CALL countLeadingZeros<hkUint32>(hkUint32 bitMask)
	{
		unsigned long idx;
		return (int)(_BitScanReverse(&idx, bitMask) ? 31 - idx : 32);
	}

	template<>
	HK_FORCE_INLINE static int HK_CALL countLeadingZeros<int>(int bitMask)
	{
		return countLeadingZeros<hkUint32>((hkUint32)x);
	}

	template <>
	static HK_FORCE_INLINE int HK_CALL countLeadingZeros<hkUint64>(hkUint64 bitMask)
	{
		unsigned long idx;
		return (int)(_BitScanReverse64(&idx, bitMask) ? 63 - idx : 64);
	}

	// Returns the number of zeros at the end (LSB) of the given bitMask
#	define HK_MATH_countTrailingZeros
#	pragma intrinsic(_BitScanForward)
#	pragma intrinsic(_BitScanForward64)

	template <typename T>
	static HK_FORCE_INLINE int HK_CALL countTrailingZeros(T x);

	template <>
	static HK_FORCE_INLINE int HK_CALL countTrailingZeros<hkUint32>(hkUint32 bitMask)
	{
		unsigned long idx;
		return (int)(_BitScanForward(&idx, bitMask) ? idx : 32);
	}

	template <>
	static HK_FORCE_INLINE int HK_CALL countTrailingZeros<int>(int x)
	{
		return countTrailingZeros<hkUint32>((hkUint32)x);
	}

	template <>
	static HK_FORCE_INLINE int HK_CALL countTrailingZeros<hkUint64>(hkUint64 bitMask)
	{
		unsigned long idx;
		return (int)(_BitScanForward64(&idx, bitMask) ? idx : 64);
	}
#endif


	// Returns the number of bits set to one in the given number
#	define HK_MATH_countBitsSet
#if defined(HK_COMPILER_GCC)
	HK_FORCE_INLINE static int HK_CALL countBitsSet(hkUint32 number)
	{
		return __builtin_popcount(number);
	}
	//HK_SSE_VERSION >= 0x42 needs CPUID flag POPCNT in addition
	//HK_FORCE_INLINE static int HK_CALL countBitsSet(hkUint32 number)
	//{
	//	return  _mm_popcnt_u32(number);
	//}
#elif HK_SSE_VERSION >= 0x31
	HK_FORCE_INLINE static int HK_CALL countBitsSet(hkUint32 number)
	{
		const __m128i mask_lo = _mm_set1_epi8(0x0F);
		const __m128i mask_popcnt = _mm_setr_epi8(0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4);

		__m128i cnt = _mm_cvtsi32_si128(number);
		__m128i lo = _mm_and_si128(cnt, mask_lo);
		__m128i hi = _mm_and_si128(_mm_srli_epi16(cnt, 4), mask_lo);
		lo = _mm_shuffle_epi8(mask_popcnt, lo);
		hi = _mm_shuffle_epi8(mask_popcnt, hi);
		cnt = _mm_add_epi8(lo, hi);
		// Horizontally sum up byte counters
		__m128i sum = _mm_sad_epu8(cnt, _mm_setzero_si128());
		// Horizontally add 32-bit accumulators
		sum = _mm_add_epi32(_mm_shuffle_epi32(sum, _MM_SHUFFLE(1,0,3,2)), sum);
		return _mm_cvtsi128_si32(sum);
	}
#else
	HK_FORCE_INLINE static int HK_CALL countBitsSet(hkUint32 number)
	{
		const __m128i mask1 = _mm_set1_epi8(0x55);
		const __m128i mask2 = _mm_set1_epi8(0x33);
		const __m128i mask4 = _mm_set1_epi8(0x0F);

		__m128i cnt = _mm_cvtsi32_si128(number);
		cnt = _mm_add_epi8( _mm_and_si128(cnt, mask1), _mm_and_si128(_mm_srli_epi16(cnt, 1), mask1) );
		cnt = _mm_add_epi8( _mm_and_si128(cnt, mask2), _mm_and_si128(_mm_srli_epi16(cnt, 2), mask2) );
		cnt = _mm_and_si128( _mm_add_epi8(cnt, _mm_srli_epi16(cnt, 4)), mask4 );
		// Horizontally sum up byte counters
		__m128i sum = _mm_sad_epu8(cnt, _mm_setzero_si128());
		// Horizontally add 32-bit accumulators
		sum = _mm_add_epi32(_mm_shuffle_epi32(sum, _MM_SHUFFLE(1,0,3,2)), sum);
		return _mm_cvtsi128_si32(sum);
	}
#endif

#	define HK_MATH_isPower2
	HK_FORCE_INLINE static bool isPower2(unsigned int v)
	{
		return countBitsSet(v)==1;
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
