/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */
#ifndef HKBASE_HK_THREAD_LOCAL_POINTER_H
#define HKBASE_HK_THREAD_LOCAL_POINTER_H

#include <Common/Base/Config/hkConfigThread.h>
//HK_THREAD_LOCAL - declare a thread local variable
//HK_THREAD_LOCAL_SET(var,value) - assign to tls var
//HK_THREAD_LOCAL_GET(var) - get from tls var
#ifndef HK_XBOX360_EXPLICIT_TLS
#	define HK_XBOX360_EXPLICIT_TLS 0
#endif

// disable TLS on PlayStation(R)3 if we want to build a PRX (internal builds only).
#ifdef HK_PS3_PRX_BUILD
#	define HK_PS3_NO_TLS
#endif

#if (HK_CONFIG_THREAD == HK_CONFIG_MULTI_THREADED) && !defined(HK_PLATFORM_SPU)
#	if defined(HK_PLATFORM_WINRT) || ( defined(HK_PLATFORM_XBOX360) && (HK_XBOX360_EXPLICIT_TLS == 0) )
#		define HK_THREAD_LOCAL(TYPE) __declspec(thread) TYPE
#	elif (defined(HK_PLATFORM_PS3_PPU) && !defined (HK_PS3_NO_TLS)) || defined(HK_PLATFORM_LINUX) || defined(HK_PLATFORM_ANDROID) || defined(HK_PLATFORM_PS4) // || defined(HK_PLATFORM_TIZEN)
#		define HK_THREAD_LOCAL(TYPE) __thread TYPE
#	elif defined(HK_PLATFORM_TIZEN)

#		include <pthread.h> 

			template < typename T > 
			class hkThreadLocalData
			{
				public:
					hkThreadLocalData() { pthread_key_create(&m_key, HK_NULL); }
					~hkThreadLocalData() { pthread_key_delete(m_key); }

					HK_FORCE_INLINE T getData() 
					{
						return (T) pthread_getspecific(m_key);
					}

					HK_FORCE_INLINE void setData(T p) 
					{					
						pthread_setspecific(m_key, (void*)p );
					}

				protected:
					pthread_key_t m_key; 
			};

#		define HK_THREAD_LOCAL(TYPE) hkThreadLocalData<TYPE>
#		define HK_THREAD_LOCAL_SET(var,value) var.setData(value)
#		define HK_THREAD_LOCAL_GET(var) var.getData()

#	elif defined(HK_PLATFORM_WIN32) || ( defined(HK_PLATFORM_XBOX360) && (HK_XBOX360_EXPLICIT_TLS == 1) )

		#define HK_WIN32_TLS_INVALID ((hkUint32)0xFFFFFFFF)

		extern "C" {
			__declspec(dllimport) unsigned long _stdcall TlsAlloc(void);
			__declspec(dllimport) void* _stdcall TlsGetValue( unsigned long dwTlsIndex );		
			__declspec(dllimport) int _stdcall TlsSetValue( unsigned long dwTlsIndex, void* lpTlsValue);
			__declspec(dllimport) int _stdcall TlsFree( unsigned long dwTlsIndex );
		}


		/// A platform independent wrapper for thread local storage.
		/// We assume we always just store a pointer (or data the same size or smaller than a pointer)
		/// i.e., sizeof(T) <= sizeof(char*).
		/// In debug it will now stop when platform limits are reached as it will soon cause a crash anyway
		/// such as threadmem being null etc
		template<typename T>
		class hkThreadLocalData
		{
			public:

				hkThreadLocalData() 
				{ 
					m_slotID = TlsAlloc();
					HK_ON_DEBUG( if (m_slotID == HK_WIN32_TLS_INVALID) { HK_BREAKPOINT(0xabba3651); } ) 
				}
				~hkThreadLocalData() 
				{ 
					HK_ON_DEBUG( int r = ) TlsFree(m_slotID);
					HK_ON_DEBUG( if (r == 0) { HK_BREAKPOINT(0xabba3652); } ) 
				}
				HK_FORCE_INLINE T getData() const
				{
					return (T)(hkUlong)TlsGetValue(m_slotID) ;
				}
				HK_FORCE_INLINE void setData(T p) 
				{
					hkUlong v = hkUlong(p);
					HK_ON_DEBUG( int r = ) TlsSetValue( m_slotID, (void*)v );
					HK_ON_DEBUG( if (r == 0) { HK_BREAKPOINT(0xabba3653); } )
				}
				unsigned long m_slotID; 
		};
#		define HK_THREAD_LOCAL(TYPE) hkThreadLocalData<TYPE>
#		define HK_THREAD_LOCAL_SET(var,value) var.setData(value)
#		define HK_THREAD_LOCAL_GET(var) var.getData()
#	elif defined(HK_PLATFORM_MACPPC) || defined(HK_PLATFORM_MAC386) || defined(HK_PLATFORM_IOS) || defined(HK_PLATFORM_LRB) || (defined(HK_PLATFORM_ANDROID) && defined(HK_ARCH_IA32))

#		include <pthread.h> 

			template < typename T > 
			class hkThreadLocalData
			{
				public:
					hkThreadLocalData() { pthread_key_create(&m_key, HK_NULL); }
					~hkThreadLocalData() { pthread_key_delete(m_key); }

					HK_FORCE_INLINE T getData() const
					{
						return (T) pthread_getspecific(m_key);
					}

					HK_FORCE_INLINE void setData(T p) 
					{					
						pthread_setspecific(m_key, (void*)p );
					}

				protected:
					pthread_key_t m_key; 
			};
#		define HK_THREAD_LOCAL(TYPE) hkThreadLocalData<TYPE>
#		define HK_THREAD_LOCAL_SET(var,value) var.setData(value)
#		define HK_THREAD_LOCAL_GET(var) var.getData()

#	elif defined(HK_PLATFORM_WIIU)

#		include <Common/Base/Thread/Thread/WiiU/hkThreadLocalDataWiiU.h>

#	elif defined(HK_PLATFORM_PSVITA)

#		define HK_THREAD_LOCAL(TYPE) __declspec(thread) TYPE
#		define HK_THREAD_LOCAL_SET(var,value) var = value
#		define HK_THREAD_LOCAL_GET(var) var
#elif defined(HK_PLATFORM_PS3_PPU) && defined (HK_PS3_NO_TLS)
#		include <Common/Base/Thread/Thread/Ps3/hkPs3PrxThreadLocalStorage.h>
#	else
#		error fixme, unkown MT platform for TLS
#	endif
#else
#	define HK_THREAD_LOCAL(TYPE) TYPE
#endif

#ifndef HK_THREAD_LOCAL_SET
#	define HK_THREAD_LOCAL_SET(var,value) var = value
#endif
#ifndef HK_THREAD_LOCAL_GET
#	define HK_THREAD_LOCAL_GET(var) var
#endif

#endif // HKBASE_HK_THREAD_LOCAL_POINTER_H

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
