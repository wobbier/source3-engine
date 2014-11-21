/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#define HKA_USE_TEMPLATES

#if defined(HKA_USE_TEMPLATES)

#define HKA_DECLARE_TEMPLATE_FUNC_T1_P0( RETURN_TYPE, NAME, T1 ) \
	template < T1 > \
	RETURN_TYPE NAME()
#define HKA_DECLARE_TEMPLATE_FUNC_T1_P1( RETURN_TYPE, NAME, T1, P1 ) \
	template < T1 > \
	RETURN_TYPE NAME( P1 )
#define HKA_DECLARE_TEMPLATE_FUNC_T1_P2( RETURN_TYPE, NAME, T1, P1, P2 ) \
	template < T1 > \
	RETURN_TYPE NAME( P1, P2 )
#define HKA_DECLARE_TEMPLATE_FUNC_T1_P4( RETURN_TYPE, NAME, T1, P1, P2, P3, P4 ) \
	template < T1 > \
	RETURN_TYPE NAME( P1, P2, P3, P4 )
#define HKA_DECLARE_TEMPLATE_FUNC_T1_P5( RETURN_TYPE, NAME, T1, P1, P2, P3, P4, P5 ) \
	template < T1 > \
	RETURN_TYPE NAME( P1, P2, P3, P4, P5 )
#define HKA_DECLARE_TEMPLATE_FUNC_T1_P6( RETURN_TYPE, NAME, T1, P1, P2, P3, P4, P5, P6 ) \
	template < T1 > \
	RETURN_TYPE NAME( P1, P2, P3, P4, P5, P6 )
#define HKA_DECLARE_TEMPLATE_FUNC_T1_P7( RETURN_TYPE, NAME, T1, P1, P2, P3, P4, P5, P6, P7 ) \
	template < T1 > \
	RETURN_TYPE NAME( P1, P2, P3, P4, P5, P6, P7 )

//#define HKA_DEFINE_TEMPLATE_FUNC_T1_P0( RETURN_TYPE, NAME, T1 )
//#define HKA_DEFINE_TEMPLATE_FUNC_T1_P1( RETURN_TYPE, NAME, T1, P1 )
//#define HKA_DEFINE_TEMPLATE_FUNC_T1_P2( RETURN_TYPE, NAME, T1, P1, P2 )
//#define HKA_DEFINE_TEMPLATE_FUNC_T1_P4( RETURN_TYPE, NAME, T1, P1, P2, P3, P4 )
#define HKA_DEFINE_TEMPLATE_FUNC_T1_P5( RETURN_TYPE, NAME, T1, P1, P2, P3, P4, P5 ) \
	template < T1 > \
	RETURN_TYPE hkaSplineCompressedAnimation::NAME( P1, P2, P3, P4, P5 )
#define HKA_DEFINE_TEMPLATE_FUNC_T1_P6( RETURN_TYPE, NAME, T1, P1, P2, P3, P4, P5, P6 ) \
	template < T1 > \
	RETURN_TYPE hkaSplineCompressedAnimation::NAME( P1, P2, P3, P4, P5, P6 )
#define HKA_DEFINE_TEMPLATE_FUNC_T1_P7( RETURN_TYPE, NAME, T1, P1, P2, P3, P4, P5, P6, P7 ) \
	template < T1 > \
	RETURN_TYPE hkaSplineCompressedAnimation::NAME( P1, P2, P3, P4, P5, P6, P7 )

#define HKA_CALL_TEMPLATE_FUNC_T1_P0( NAME, T1 ) NAME< T1 >()
#define HKA_CALL_TEMPLATE_FUNC_T1_P1( NAME, T1, P1 ) NAME< T1 >( P1 )
#define HKA_CALL_TEMPLATE_FUNC_T1_P2( NAME, T1, P1, P2 ) NAME< T1 >( P1, P2 )
#define HKA_CALL_TEMPLATE_FUNC_T1_P4( NAME, T1, P1, P2, P3, P4 ) NAME< T1 >( P1, P2, P3, P4 )
#define HKA_CALL_TEMPLATE_FUNC_T1_P5( NAME, T1, P1, P2, P3, P4, P5 ) NAME< T1 >( P1, P2, P3, P4, P5 )
#define HKA_CALL_TEMPLATE_FUNC_T1_P6( NAME, T1, P1, P2, P3, P4, P5, P6 ) NAME< T1 >( P1, P2, P3, P4, P5, P6 )
#define HKA_CALL_TEMPLATE_FUNC_T1_P7( NAME, T1, P1, P2, P3, P4, P5, P6, P7 ) NAME< T1 >( P1, P2, P3, P4, P5, P6, P7 )

#else

#define HKA_DECLARE_TEMPLATE_FUNC_T1_P0( RETURN_TYPE, NAME, T1 ) RETURN_TYPE NAME( T1 )
#define HKA_DECLARE_TEMPLATE_FUNC_T1_P1( RETURN_TYPE, NAME, T1, P1 ) RETURN_TYPE NAME( T1, P1 )
#define HKA_DECLARE_TEMPLATE_FUNC_T1_P2( RETURN_TYPE, NAME, T1, P1, P2 ) RETURN_TYPE NAME( T1, P1, P2 )
#define HKA_DECLARE_TEMPLATE_FUNC_T1_P4( RETURN_TYPE, NAME, T1, P1, P2, P3, P4 ) RETURN_TYPE NAME( T1, P1, P2, P3, P4 )
#define HKA_DECLARE_TEMPLATE_FUNC_T1_P5( RETURN_TYPE, NAME, T1, P1, P2, P3, P4, P5 ) RETURN_TYPE NAME( T1, P1, P2, P3, P4, P5 )
#define HKA_DECLARE_TEMPLATE_FUNC_T1_P6( RETURN_TYPE, NAME, T1, P1, P2, P3, P4, P5, P6 ) RETURN_TYPE NAME( T1, P1, P2, P3, P4, P5, P6 )
#define HKA_DECLARE_TEMPLATE_FUNC_T1_P7( RETURN_TYPE, NAME, T1, P1, P2, P3, P4, P5, P6, P7 ) RETURN_TYPE NAME( T1, P1, P2, P3, P4, P5, P6, P7 )

//#define HKA_DEFINE_TEMPLATE_FUNC_T1_P0( RETURN_TYPE, NAME, T1 ) RETURN_TYPE hkaSplineCompressedAnimation::NAME( T1 )
//#define HKA_DEFINE_TEMPLATE_FUNC_T1_P1( RETURN_TYPE, NAME, T1, P1 ) RETURN_TYPE hkaSplineCompressedAnimation::NAME( T1, P1 )
//#define HKA_DEFINE_TEMPLATE_FUNC_T1_P2( RETURN_TYPE, NAME, T1, P1, P2 ) RETURN_TYPE hkaSplineCompressedAnimation::NAME( T1, P1, P2 )
//#define HKA_DEFINE_TEMPLATE_FUNC_T1_P4( RETURN_TYPE, NAME, T1, P1, P2, P3, P4 ) RETURN_TYPE hkaSplineCompressedAnimation::NAME( T1, P1, P2, P3, P4 )
#define HKA_DEFINE_TEMPLATE_FUNC_T1_P5( RETURN_TYPE, NAME, T1, P1, P2, P3, P4, P5 ) RETURN_TYPE hkaSplineCompressedAnimation::NAME( T1, P1, P2, P3, P4, P5 )
#define HKA_DEFINE_TEMPLATE_FUNC_T1_P6( RETURN_TYPE, NAME, T1, P1, P2, P3, P4, P5, P6 ) RETURN_TYPE hkaSplineCompressedAnimation::NAME( T1, P1, P2, P3, P4, P5, P6 )
#define HKA_DEFINE_TEMPLATE_FUNC_T1_P7( RETURN_TYPE, NAME, T1, P1, P2, P3, P4, P5, P6, P7 ) RETURN_TYPE hkaSplineCompressedAnimation::NAME( T1, P1, P2, P3, P4, P5, P6, P7 )

#define HKA_CALL_TEMPLATE_FUNC_T1_P0( NAME, T1 ) NAME( T1 )
#define HKA_CALL_TEMPLATE_FUNC_T1_P1( NAME, T1, P1 ) NAME( T1, P1 )
#define HKA_CALL_TEMPLATE_FUNC_T1_P2( NAME, T1, P1, P2 ) NAME( T1, P1, P2 )
#define HKA_CALL_TEMPLATE_FUNC_T1_P4( NAME, T1, P1, P2, P3, P4 ) NAME( T1, P1, P2, P3, P4 )
#define HKA_CALL_TEMPLATE_FUNC_T1_P5( NAME, T1, P1, P2, P3, P4, P5 ) NAME( T1, P1, P2, P3, P4, P5 )
#define HKA_CALL_TEMPLATE_FUNC_T1_P6( NAME, T1, P1, P2, P3, P4, P5, P6 ) NAME( T1, P1, P2, P3, P4, P5, P6 )
#define HKA_CALL_TEMPLATE_FUNC_T1_P7( NAME, T1, P1, P2, P3, P4, P5, P6, P7 ) NAME( T1, P1, P2, P3, P4, P5, P6, P7 )

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
