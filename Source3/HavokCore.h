#pragma once
#include <iostream>
//Havok headers

// Math and base includes
#include <Common/Base/hkBase.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <Common/Base/Memory/Allocator/LargeBlock/hkLargeBlockAllocator.h>
#include <Common/Base/System/Hardware/hkHardwareInfo.h>
#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Physics2012/Collide/Dispatch/hkpAgentRegisterUtil.h>

// Visual Debugger includes
#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics2012/Utilities/VisualDebugger/hkpPhysicsContext.h>

#include <Common/Base/Thread/Pool/hkThreadPool.h>
#include <Common/Base/Thread/Pool/hkCpuThreadPool.h>
#include <Common/Base/Container/Array/hkArray.h>
static void HK_CALL errorReport(const char* msg, void* userContext) {
	using namespace std;
	printf("%s", msg);
}

class HavokCore {
public:
	HavokCore();
	~HavokCore();

	bool g_bVdbEnabled;
	hkCpuThreadPool* g_pThreadPool;
	hkJobQueue* g_pJobQueue;

	hkpWorld* g_pWorld;			// Physics world.
	hkpWorldCinfo g_pWorldInfo; // Info about global simulation parameters.

	hkpPhysicsContext* g_pContext;
	hkVisualDebugger* g_pVdb;
	void InitializeHavok();
	void InitMemory();
	void InitPhysicalWorld();
	void InitVDB();
	void StepHavok();
	void StepVDB();
	void ShutdownHavok();
	void ShutdownVDB();
};
