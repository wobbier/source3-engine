#pragma once
#include "Renderer.h"
#include "Node.h"
#include "Entity.h"
#include "gtx\quaternion.hpp"
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
static void HK_CALL errorReport(const char* msg, void* userContext)
{
	using namespace std;
	printf("%s", msg);
}

class Scene {
private:
public:
	Entity* root;
	Camera* currentCamera;
	Scene();
	~Scene();
	void LoadScene(const char* filename);
	void Update(Entity* node);

	void Update();
	void Render(Entity* node, Renderer* renderer);
	void Render(Renderer* renderer);

	void AddEntity(Entity* entity);

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