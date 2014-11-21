/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
//HK_REFLECTION_PARSER_EXCLUDE_FILE

#ifndef HK_MATH_TEST_UTIL_H
#define HK_MATH_TEST_UTIL_H

#include <Common/Base/UnitTest/hkUnitTest.h>
#include <Common/Base/Math/Vector/hkPackedVector3.h>

inline bool hkIsEqual23BitAccurate( const hkReal& x, const hkReal& y)
{
#ifdef  HK_REAL_IS_DOUBLE
	hkInt64 a = *(hkInt64*)&x;
	hkInt64 b = *(hkInt64*)&y;
	hkInt64 accuracy = ( hkInt64(1)<<30) + (hkInt64(1)<<29); // lsh 29 to account for f2d rounding
#else
	hkInt32 a = *(hkInt32*)&x;
	hkInt32 b = *(hkInt32*)&y;
	hkInt32 accuracy = (hkInt32(1)<<1) + hkInt32(1);
#endif
	return (a>=b-accuracy) && (a<=b+accuracy);
}

inline bool hkIsEqual12BitAccurate( const hkReal& x, const hkReal& y)
{
#ifdef  HK_REAL_IS_DOUBLE
	hkInt64 a = *(hkInt64*)&x;
	hkInt64 b = *(hkInt64*)&y;
	hkInt64 accuracy = ( hkInt64(1)<<41) + (hkInt64(1)<<40); // lsh 40 to account for f2d rounding
#else
	hkInt32 a = *(hkInt32*)&x;
	hkInt32 b = *(hkInt32*)&y;
	hkInt32 accuracy = (hkInt32(1)<<12) + (hkInt32(1)<<11);
#endif
	return (a>=b-accuracy) && (a<=b+accuracy);
}

template <int N>
inline void testEqual23Bit(hkVector4Parameter x, hkVector4Parameter y, const char* file, const int line)
{
	hkStringBuf msg;
	for (int i = 0; i < N; i++)
	{
		bool isGood = hkIsEqual23BitAccurate(x(i), y(i));
		if (!isGood)
		{
		#if defined(HK_REAL_IS_FLOAT)
			hkUint32* i0 = (hkUint32*)&x(i);
			hkUint32* i1 = (hkUint32*)&y(i);
			msg.printf("23Bit check failed: component %i - 0x%08x 0x%08x",i,*i0,*i1);
		#else
			hkUint64* i0 = (hkUint64*)&x(i);
			hkUint64* i1 = (hkUint64*)&y(i);
			msg.printf("23Bit check failed: component %i - 0x%016" HK_PRINTF_FORMAT_INT64_SIZE "x 0x%016" HK_PRINTF_FORMAT_INT64_SIZE "x",i,*i0,*i1);
		#endif
		}
		(*hkTestReportFunction)(isGood, msg.cString(), file, line);
	}
}

template <int N>
inline void testEqual12Bit(hkVector4Parameter x, hkVector4Parameter y, const char* file, const int line)
{
	hkStringBuf msg;

	for (int i = 0; i < N; i++)
	{
		bool isGood = hkIsEqual12BitAccurate(x(i), y(i));
		if (!isGood)
		{
		#if defined(HK_REAL_IS_FLOAT)
			hkUint32* i0 = (hkUint32*)&x(i);
			hkUint32* i1 = (hkUint32*)&y(i);
			msg.printf("12Bit check failed: component %i - 0x%08x 0x%08x",i,*i0,*i1);
		#else
			hkUint64* i0 = (hkUint64*)&x(i);
			hkUint64* i1 = (hkUint64*)&y(i);
			msg.printf("12Bit check failed: component %i - 0x%016" HK_PRINTF_FORMAT_INT64_SIZE "x 0x%016" HK_PRINTF_FORMAT_INT64_SIZE "x",i,*i0,*i1);
		#endif
		}
		(*hkTestReportFunction)(isGood, msg.cString(), file, line);
	}
}

inline void testEqual23Bit(hkSimdRealParameter x, hkSimdRealParameter y, const char* file, const int line)
{
	hkReal a = x.getReal();
	hkReal b = y.getReal();
	bool isGood = hkIsEqual23BitAccurate(a,b);

	hkStringBuf msg;
	if (!isGood)
	{
	#if defined(HK_REAL_IS_FLOAT)
		hkUint32* i0 = (hkUint32*)&a;
		hkUint32* i1 = (hkUint32*)&b;
		msg.printf("23Bit check failed: 0x%08x 0x%08x",*i0,*i1);
	#else
		hkUint64* i0 = (hkUint64*)&a;
		hkUint64* i1 = (hkUint64*)&b;
		msg.printf("23Bit check failed: 0x%016" HK_PRINTF_FORMAT_INT64_SIZE "x 0x%016" HK_PRINTF_FORMAT_INT64_SIZE "x",*i0,*i1);
	#endif
	}
	(*hkTestReportFunction)(isGood, msg.cString(), file, line);
}

inline void testEqual12Bit(hkSimdRealParameter x, hkSimdRealParameter y, const char* file, const int line)
{
	hkReal a = x.getReal();
	hkReal b = y.getReal();
	bool isGood = hkIsEqual12BitAccurate(a,b);
	hkStringBuf msg;
	if (!isGood)
	{
	#if defined(HK_REAL_IS_FLOAT)
		hkUint32* i0 = (hkUint32*)&a;
		hkUint32* i1 = (hkUint32*)&b;
		msg.printf("12Bit check failed: 0x%08x 0x%08x",*i0,*i1);
	#else
		hkUint64* i0 = (hkUint64*)&a;
		hkUint64* i1 = (hkUint64*)&b;
		msg.printf("12Bit check failed: 0x%016" HK_PRINTF_FORMAT_INT64_SIZE "x 0x%016" HK_PRINTF_FORMAT_INT64_SIZE "x",*i0,*i1);
	#endif
	}
	(*hkTestReportFunction)(isGood, msg.cString(), file, line);
}

inline void testEqual23Bit(hkReal a, hkReal b, const char* file, const int line)
{
	bool isGood = hkIsEqual23BitAccurate(a,b);
	hkStringBuf msg;
	if (!isGood)
	{
	#if defined(HK_REAL_IS_FLOAT)
		hkUint32* i0 = (hkUint32*)&a;
		hkUint32* i1 = (hkUint32*)&b;
		msg.printf("23Bit check failed: 0x%08x 0x%08x",*i0,*i1);
	#else
		hkUint64* i0 = (hkUint64*)&a;
		hkUint64* i1 = (hkUint64*)&b;
		msg.printf("23Bit check failed: 0x%016" HK_PRINTF_FORMAT_INT64_SIZE "x 0x%016" HK_PRINTF_FORMAT_INT64_SIZE "x",*i0,*i1);
	#endif
	}
	(*hkTestReportFunction)(isGood, msg.cString(), file, line);
}

inline void testEqual12Bit(hkReal a, hkReal b, const char* file, const int line)
{
	bool isGood = hkIsEqual12BitAccurate(a,b);
	hkStringBuf msg;
	if (!isGood)
	{
	#if defined(HK_REAL_IS_FLOAT)
		hkUint32* i0 = (hkUint32*)&a;
		hkUint32* i1 = (hkUint32*)&b;
		msg.printf("12Bit check failed: 0x%08x 0x%08x",*i0,*i1);
	#else
		hkUint64* i0 = (hkUint64*)&a;
		hkUint64* i1 = (hkUint64*)&b;
		msg.printf("12Bit check failed: 0x%016" HK_PRINTF_FORMAT_INT64_SIZE "x 0x%016" HK_PRINTF_FORMAT_INT64_SIZE "x",*i0,*i1);
	#endif
	}
	(*hkTestReportFunction)(isGood, msg.cString(), file, line);
}


#include <limits>

inline bool compareEqualNan(const hkFloat32& x)
{
#if defined(HK_COMPILER_GCC) || defined(HK_PLATFORM_IOS) || defined(HK_PLATFORM_MAC386) || defined(HK_PLATFORM_MACPPC)
	// on iOS denormals get flushed to zero when assigning from vector pipe
	const hkFloat32 f_nan = NAN;
#else
	const hkFloat32 f_nan = std::numeric_limits<hkFloat32>::quiet_NaN();
#endif
	const hkInt32* nan = (const hkInt32*)&f_nan;
	const hkInt32* val = (const hkInt32*)&x;
	return ( *val == *nan );
}

inline bool compareEqualNan(const hkDouble64& x)
{
#if defined(HK_COMPILER_GCC) || defined(HK_PLATFORM_IOS) || defined(HK_PLATFORM_MAC386) || defined(HK_PLATFORM_MACPPC)
	// on iOS denormals get flushed to zero when assigning from vector pipe
	const hkDouble64 d_nan = NAN;
#else
	const hkDouble64 d_nan = std::numeric_limits<hkDouble64>::quiet_NaN();
#endif
	const hkInt64* nan = (const hkInt64*)&d_nan;
	const hkInt64* val = (const hkInt64*)&x;
	return ( *val == *nan );
}

#define checkEqualNan(A)	HK_TEST( compareEqualNan((A)) == true )
#define checkNotEqualNan(A)	HK_TEST( compareEqualNan((A)) == false )
#define check4Equal23Bit(A,B) testEqual23Bit<4>((A),(B),__FILE__,__LINE__)
#define check4Equal12Bit(A,B) testEqual12Bit<4>((A),(B),__FILE__,__LINE__)
#define check3Equal23Bit(A,B) testEqual23Bit<3>((A),(B),__FILE__,__LINE__)
#define check3Equal12Bit(A,B) testEqual12Bit<3>((A),(B),__FILE__,__LINE__)
#define checkEqual23Bit(A,B)  testEqual23Bit((A),(B),__FILE__,__LINE__)
#define checkEqual12Bit(A,B)  testEqual12Bit((A),(B),__FILE__,__LINE__)

#endif // HK_MATH_TEST_UTIL_H

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
