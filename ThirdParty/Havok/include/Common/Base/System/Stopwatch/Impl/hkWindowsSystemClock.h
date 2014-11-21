
/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HK_WINDOWS_SYSTEM_CLOCK
#define HK_WINDOWS_SYSTEM_CLOCK

#	include <Common/Base/Fwd/hkwindows.h>

hkUint64 HK_CALL hkSystemClock::getTickCounter()
{
	hkUint64 ticks;
#if defined(HK_ARCH_X64)
	// Using intrinsics for AMD64 until the compiler supports __asm
	ticks = __rdtsc();
#else // Win32 or Xbox
	// note: using cpuid as a serializing makes timings more accurate, 
	// at the expense of more overhead. (1.5% without versus 5% with cpuid)
	#if defined(HK_ARCH_IA32)
		__asm {
			pushad
			cpuid 
			rdtsc
			mov dword ptr[ticks  ], eax
			mov dword ptr[ticks+4], edx
			popad
		}
	#elif defined(HK_ARCH_ARM) 
		//unsigned int value;
		// Read CCNT Register
		//__asm volatile ("MRC p15, 0, %0, c9, c13, 0\t\n": "=r"(value));
		LARGE_INTEGER i;
		QueryPerformanceCounter(&i);
		ticks = i.QuadPart;
	#else // PPC
		ticks = __mftb();
	#endif
#endif
	return ticks;
}

hkUint64 HK_CALL hkSystemClock::getTicksPerSecond()
{
	static hkUint64 freq = 0;
	if(freq==0)
	{
		hkUint64 ticks;
		hkUint64 qticks;
		hkUint64 ticks2;
		hkUint64 qticks2;
		double avgFactor = 0;
		const int numIters = 100;

		// Iterate several times
		for (int iter = 0; iter < numIters; iter++)
		{
			ticks = getTickCounter();
			QueryPerformanceCounter( (LARGE_INTEGER*) &qticks);

			///
			///	Sleep for a little while
			///
			volatile int x=1;
			for (int j=0; j< 50000; j++)
			{
				x += x*x;
			}


			ticks2 = getTickCounter();
			QueryPerformanceCounter( (LARGE_INTEGER*) &qticks2);

			// We assume that this is fixed & regular 
			QueryPerformanceFrequency( (LARGE_INTEGER*) &freq);

			// Work our calibration factor
			hkUint64 diff = ticks2 - ticks;
			hkUint64 qdiff = qticks2 - qticks;

			double factor = double(diff)/ double(qdiff);
			
			avgFactor += factor;
			}

		avgFactor /= numIters;
		freq = hkUint64(avgFactor * freq);
	}
	return freq;
}

#endif  // HK_WINDOWS_SYSTEM_CLOCK

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
