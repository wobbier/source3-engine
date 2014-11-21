#include "Scene.h"
#include <list>


// Keycode
#include <Common/Base/keycode.cxx>
#include <Common/Base/Config/hkProductFeatures.cxx>
#include "Common/Base/System/Init/PlatformInit.cxx"

#include <Physics2012\Collide\Shape\hkpShape.h>
#include <Physics2012\Collide\Shape\Convex\Sphere\hkpSphereShape.h>
#include <Physics2012\Collide\hkpCollide.h>
#include <Physics2012\Utilities\Dynamics\Inertia\hkpInertiaTensorComputer.h>
#include <Physics2012\Dynamics\Entity\hkpRigidBodyCinfo.h>
#include <Physics2012\Dynamics\Entity\hkpRigidBody.h>
Scene::Scene() {
	root = new Entity("World");
	InitializeHavok();
	// Perfrom platform specific initialization for this demo - you should already have something similar in your own code.
	//PlatformInit();

	//hkMallocAllocator baseMalloc;
	//hkLargeBlockAllocator largeBlockAllocator(&baseMalloc);
	//hkFreeListAllocator freeListAllocator(&largeBlockAllocator, &largeBlockAllocator);
	//hkFreeListMemorySystem memorySystem(&baseMalloc, &freeListAllocator, &freeListAllocator);
	//hkMemorySystem::replaceInstance(&memorySystem);

	//hkMemoryRouter* memoryRouter = memorySystem.mainInit(hkMemorySystem::FrameInfo(1024));
	//hkBaseSystem::init(memoryRouter, errorReport);
	//{
	//	HK_WARN_ALWAYS(0x417ffd72, "Hello world!");
	//}
	g_bVdbEnabled = true;
}

Scene::~Scene() {
}

void Scene::Update(Entity* node) {
	node->Update();
	for (int i = 0; i < node->ChildSize(); i++) {
		Update(node->GetChildById(i));
	}
}

void Scene::Update() {
	StepHavok();
	StepVDB();
	if (root->ChildSize() != 0) {
		Update(root);
	}
}

std::list<Transform> modelViewStack;
void Scene::Render(Entity* node, Renderer* renderer) {
	modelViewStack.push_back(node->transform);
	glm::mat4 trans;
	for (std::list<Transform>::iterator i = modelViewStack.begin(); i != modelViewStack.end(); i++) {
		trans = glm::translate(trans, i->position);
		trans = glm::scale(trans, i->scale);
		trans = trans * glm::toMat4(i->rotation);
	}
	renderer->SetModelView(trans);
	node->Render(renderer);
	for (int i = 0; i < node->ChildSize(); ++i) {
		Render(node->GetChildById(i), renderer);
	}
	modelViewStack.pop_back();
}

void Scene::Render(Renderer* renderer) {
	if (root->ChildSize() != 0) {
		Render(root, renderer);
	}
}

void Scene::InitializeHavok()
{
	std::cout << "Init Havok";
	InitMemory();
	InitPhysicalWorld();
	if (g_bVdbEnabled)
		InitVDB();
	std::cout << "Done Init Havok";
}

void Scene::InitMemory()
{
#ifdef HK_COMPILER_HAS_INTRINSICS_IA32

	HK_CONFIG_SIMD == HK_CONFIG_SIMD_ENABLED;
	// Flush all denormal/subnormal numbers to zero.
	// Operations on denormals are very slow,

	// up to 100 times slower than normal numbers.
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#endif

	// Initialize the base system including our memory system
	// Allocate 0.5MB of physics solver buffer.
	hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initDefault(hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo(500 * 1024));
	hkBaseSystem::init(memoryRouter, errorReport);

	// We can cap the number of threads used - here we use the maximum for whatever multithreaded platform we are running on. This variable is
	// set in the following code sections.
	int totalNumThreadsUsed;

	// Get the number of physical threads available on the system
	hkHardwareInfo hwInfo;
	totalNumThreadsUsed = hkHardwareInfo::getNumHardwareThreads();

	// We use one less than this for our thread pool, because we must also use this thread for our simulation
	hkCpuThreadPoolCinfo threadPoolCinfo;
	threadPoolCinfo.m_numThreads = totalNumThreadsUsed - 1;

	// This line enables timers collection, by allocating 200 Kb per thread.  If you leave this at its default (0),
	// timer collection will not be enabled.
	threadPoolCinfo.m_timerBufferPerThreadAllocation = 200000;
	g_pThreadPool = new hkCpuThreadPool(threadPoolCinfo);

	// We also need to create a Job queue. This job queue will be used by all Havok modules to run multithreaded work.
	// Here we only use it for physics.
	hkJobQueueCinfo info;
	info.m_jobQueueHwSetup.m_numCpuThreads = totalNumThreadsUsed;
	g_pJobQueue = new hkJobQueue(info);

	// Enable monitors for this thread.
	// Monitors have been enabled for thread pool threads already (see above comment).
	hkMonitorStream::getInstance().resize(200000);
}
void Scene::InitPhysicalWorld()
{
	g_pWorldInfo.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_MULTITHREADED;
	g_pWorldInfo.m_broadPhaseBorderBehaviour = hkpWorldCinfo::BROADPHASE_BORDER_REMOVE_ENTITY;
	g_pWorldInfo.m_gravity.set(0, -9.8f, 0);
	g_pWorld = new hkpWorld(g_pWorldInfo);
	g_pWorld->m_wantDeactivation = false;
	g_pWorld->markForWrite();
	hkpAgentRegisterUtil::registerAllAgents(g_pWorld->getCollisionDispatcher());
	g_pWorld->registerWithJobQueue(g_pJobQueue);
}

void Scene::InitVDB()
{
	hkArray<hkProcessContext*> contexts;
	{
		g_pContext = new hkpPhysicsContext();
		hkpPhysicsContext::registerAllPhysicsProcesses();
		g_pContext->addWorld(g_pWorld);
		contexts.pushBack(g_pContext);
		g_pWorld->unmarkForWrite();
	}

	g_pVdb = new hkVisualDebugger(contexts);
	g_pVdb->serve();
}

void Scene::StepHavok()
{
	g_pWorld->stepMultithreaded(g_pJobQueue, g_pThreadPool, Time::Get()->deltaTime);

	if (g_bVdbEnabled)
		StepVDB();

	hkMonitorStream::getInstance().reset();
	g_pThreadPool->clearTimerData();
}

void Scene::StepVDB()
{
	g_pContext->syncTimers(g_pThreadPool);
	g_pVdb->step(Time::Get()->deltaTime);
}

void Scene::ShutdownHavok()
{
	g_pWorld->markForWrite();
	g_pWorld->removeReference();

	delete g_pJobQueue;

	// Clean up the thread pool
	g_pThreadPool->removeReference();

	if (g_bVdbEnabled)
		ShutdownVDB();

	hkBaseSystem::quit();
	hkMemoryInitUtil::quit();
}

void Scene::ShutdownVDB()
{
	g_pVdb->removeReference();

	// Contexts are not reference counted at the base class level by the VDB as
	// they are just interfaces really. So only delete the context after you have
	// finished using the VDB.
	g_pContext->removeReference();
}

void Scene::AddEntity(Entity* entity)
{
	if (entity->GetParent() == nullptr){
		root->AddChildNode(entity);
	}
	g_pWorld->lock();
	g_pWorld->addEntity(entity->mRigidbody);
	g_pWorld->unlock();
}

// Keycode
#undef HK_FEATURE_PRODUCT_AI
#undef HK_FEATURE_PRODUCT_ANIMATION
#undef HK_FEATURE_PRODUCT_CLOTH
#undef HK_FEATURE_PRODUCT_DESTRUCTION_2012
#undef HK_FEATURE_PRODUCT_DESTRUCTION
#undef HK_FEATURE_PRODUCT_BEHAVIOR
#undef HK_FEATURE_PRODUCT_PHYSICS_2012
#undef HK_FEATURE_PRODUCT_PHYSICS

#define HK_EXCLUDE_FEATURE_SerializeDeprecatedPre700
#define HK_EXCLUDE_FEATURE_RegisterVersionPatches
#define HK_EXCLUDE_FEATURE_RegisterReflectedClasses
#define HK_EXCLUDE_FEATURE_MemoryTracker