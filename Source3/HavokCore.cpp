#include "HavokCore.h"
#include "Time.h"

HavokCore::HavokCore() {
	g_bVdbEnabled = true;
}

HavokCore::~HavokCore() {
}

void HavokCore::InitializeHavok() {
	std::cout << "Init Havok";
	InitMemory();
	InitPhysicalWorld();
	if (g_bVdbEnabled)
		InitVDB();
	std::cout << "Done Init Havok";
}

void HavokCore::InitMemory() {
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
void HavokCore::InitPhysicalWorld() {
	g_pWorldInfo.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_MULTITHREADED;
	g_pWorldInfo.m_broadPhaseBorderBehaviour = hkpWorldCinfo::BROADPHASE_BORDER_REMOVE_ENTITY;
	g_pWorldInfo.m_gravity.set(0, -9.8f, 0);
	g_pWorld = new hkpWorld(g_pWorldInfo);
	g_pWorld->m_wantDeactivation = false;
	g_pWorld->markForWrite();
	hkpAgentRegisterUtil::registerAllAgents(g_pWorld->getCollisionDispatcher());
	g_pWorld->registerWithJobQueue(g_pJobQueue);
}

void HavokCore::InitVDB() {
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

void HavokCore::StepHavok() {
	g_pWorld->stepMultithreaded(g_pJobQueue, g_pThreadPool, Time::Get()->deltaTime);

	if (g_bVdbEnabled)
		StepVDB();

	hkMonitorStream::getInstance().reset();
	g_pThreadPool->clearTimerData();
}

void HavokCore::StepVDB() {
	g_pContext->syncTimers(g_pThreadPool);
	g_pVdb->step(Time::Get()->deltaTime);
}

void HavokCore::ShutdownHavok() {
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

void HavokCore::ShutdownVDB() {
	g_pVdb->removeReference();

	// Contexts are not reference counted at the base class level by the VDB as
	// they are just interfaces really. So only delete the context after you have
	// finished using the VDB.
	g_pContext->removeReference();
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
#define HK_EXCLUDE_FEATURE_MemoryTracker

#define HK_EXCLUDE_FEATURE_hkpVehicle

#define HK_EXCLUDE_FEATURE_hkCompat
#define HK_EXCLUDE_FEATURE_hkSceneData
#define HK_EXCLUDE_FEATURE_hkcdCollide
#define HK_EXCLUDE_FEATURE_hkpHeightField
#define HK_EXCLUDE_FEATURE_hkpAccurateInertiaTensorComputer
#define HK_EXCLUDE_FEATURE_hkpUtilities
#define HK_EXCLUDE_FEATURE_hkpCompressedMeshShape
#define HK_EXCLUDE_FEATURE_hkpConvexPieceMeshShape
#define HK_EXCLUDE_FEATURE_hkpExtendedMeshShape
#define HK_EXCLUDE_FEATURE_hkpMeshShape
#define HK_EXCLUDE_FEATURE_hkpSimpleMeshShape
#define HK_EXCLUDE_FEATURE_hkpPoweredChainData
#define HK_EXCLUDE_FEATURE_hkMonitorStream

#define HK_EXCLUDE_FEATURE_hkaAnimation
#define HK_EXCLUDE_FEATURE_hkpAnimation
#define HK_EXCLUDE_FEATURE_hkaPhysics2012Bridge
#define HK_EXCLUDE_FEATURE_hkImageUtilities
#define HK_EXCLUDE_FEATURE_hkGeometryUtilities
#define HK_EXCLUDE_FEATURE_hkSerialize

#include <Common/Base/keycode.cxx>
#include <Common/Base/Config/hkProductFeatures.cxx>
#include "Common/Base/System/Init/PlatformInit.cxx"