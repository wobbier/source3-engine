/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef HAVOK_FILTER_DLL_MANAGER__H
#define HAVOK_FILTER_DLL_MANAGER__H

/// This class verifies and loads any filter DLLs,
/// provides enumerated access to the individual filters,
/// and provides functions which operate on the set of DLL's as a whole
class hctFilterDllManager
{
	public:

		/// Access to the filter list
		virtual int getNumFilters() const = 0;
		virtual const hctFilterDescriptor* getFilterDescByIndex( int index ) const = 0;
		virtual int getFilterIndexByID( unsigned int filterID ) const = 0;
};

#endif // HAVOK_FILTER_DLL_MANAGER__H

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
