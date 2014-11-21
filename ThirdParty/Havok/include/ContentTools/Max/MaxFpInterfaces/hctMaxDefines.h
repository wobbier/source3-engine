/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HK_MAX_DEFINES__H
#define HK_MAX_DEFINES__H

#include <maxversion.h>

// Constness changes in version 2010 (v12)
#if MAX_VERSION_MAJOR>=12

	#define CONST12 const

#else

	#define CONST12

#endif

// Constness changes in version 2013 (v15)
#if MAX_VERSION_MAJOR>=15

	#define CONST15 const
	#define CONST15_CAST(X) X

#else

	#define CONST15

	template<typename T>
	inline T* CONST15_CAST(const T* x) {return const_cast<T*> (x);}

#endif

#endif // HK_MAX_DEFINES__H

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
