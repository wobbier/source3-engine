/*
 *
 * Confidential Information of Telekinesys Research Limited (t/a Havok). Not for disclosure or distribution without Havok's
 * prior written consent. This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Product and Trade Secret source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2014 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 *
 */

#ifndef FILE_SERVER_H
#define FILE_SERVER_H

class hkSeekableStreamReader;
class hkSocket;

class hkFileServer
{
	HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, hkFileServer);

public:

	enum ReturnCode
	{
			// Socket was closed gracefully on client side
		RETURN_SOCKET_CLOSED = 0,

			// Socket was closed for unknown reason on client side
		RETURN_SOCKET_ERROR,

			// Server was stopped on server
		RETURN_SERVER_SHUTDOWN,
	};

	struct OpenReadFiles
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, OpenReadFiles);

		hkUint32 id;
		hkRefPtr<hkSeekableStreamReader> s;
		hkUint32 bytesReadTotal;
		hkStringPtr filename;
	};

	struct OpenWriteFiles
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, OpenWriteFiles);

		hkUint32 id;
		hkRefPtr<hkOstream> s;
		hkUint32 bytesWrittenTotal;
		hkStringPtr filename;
	};

	typedef void (HK_CALL *ProgressReportFunction)(const char* filename, int progress, const char* info);
	typedef void (HK_CALL *LogFunction)(const char* logInfo);

	struct ThreadData
	{
		HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_BASE, ThreadData);

		ThreadData();

		hkCriticalSection* m_dataLock;
		bool m_requestShutdown;
		hkStringPtr m_rootDir;
		hkSocket* m_socket;
		ProgressReportFunction m_progressFunc;
		LogFunction m_logFunc;
	};

	static void* HK_CALL FileServerMain(void* td);
	static ReturnCode serve(ThreadData* threadData);
};

#endif // FILE_SERVER_H

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
