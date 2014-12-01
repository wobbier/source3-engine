#include "Scene.h"
#include <list>

// Keycode
#include <Physics2012\Collide\Shape\hkpShape.h>
#include <Physics2012\Collide\Shape\Convex\Sphere\hkpSphereShape.h>
#include <Physics2012\Collide\hkpCollide.h>
#include <Physics2012\Utilities\Dynamics\Inertia\hkpInertiaTensorComputer.h>
#include <Physics2012\Dynamics\Entity\hkpRigidBodyCinfo.h>
#include <Physics2012\Dynamics\Entity\hkpRigidBody.h>
#include "Geometry/Internal/Types/hkcdRay.h"

// Raycasting
#include <Physics2012\Collide\Query\CastUtil\hkpWorldRayCastInput.h>
#include <Physics2012\Collide\Query\CastUtil\hkpWorldRayCastOutput.h>
#include <Physics2012\Collide/Query/Multithreaded/RayCastQuery/hkpRayCastQueryJobs.h>
#include <Physics2012/Collide/Query/Collector/RayCollector/hkpClosestRayHitCollector.h>
Scene::Scene() {
	root = new Entity("World");
	currentCamera = new Camera(glm::vec3(0.0f, 0.0f, 10.0f));
	mHavokCore = new HavokCore();
	mHavokCore->InitializeHavok();
	skybox = new Skybox();
	skybox->LoadSkybox("Skybox/skybox");
}

Scene::~Scene() {
}

void Scene::Update(Entity* node) {
	if (!currentCamera->frustum->pointInFrustum(node->transform.position) && node != root) return;
	node->Update();
	for (int i = 0; i < node->ChildSize(); i++) {
		Update(node->GetChildById(i));
	}
}

void Scene::Update() {
	mHavokCore->StepHavok();
	mHavokCore->StepVDB();
	// Ray Test
	hkpWorldRayCastInput input;

	input.m_from = currentCamera->ScreenPointToRay(400, 300).m_origin;
	hkVector4 added = currentCamera->ScreenPointToRay(400, 300).m_origin;
	added.add(currentCamera->ScreenPointToRay(400, 300).m_direction);
	input.m_to = added;
	input.m_filterInfo = 0;

	hkpClosestRayHitCollector result;
	mHavokCore->g_pWorld->lock();
	mHavokCore->g_pWorld->castRay(input, result);
	mHavokCore->g_pWorld->unlock();
	if (result.hasHit()) {
		printf("HIT!\n");
	}
	currentCamera->Update();
	if (root->ChildSize() != 0) {
		Update(root);
	}
}

std::list<Transform> modelViewStack;
void Scene::Render(Entity* node, Renderer* renderer) {
	if (!currentCamera->frustum->pointInFrustum(node->transform.position) && node != root) return;
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
	renderer->mCamera = currentCamera;
	renderer->RenderSkybox(skybox);

	// Ray test
	//input.m_from = currentCamera->ScreenPointToRay(400, 300).m_origin;
	hkVector4 added = currentCamera->ScreenPointToRay(400, 300).m_origin;
	renderer->RenderLine(currentCamera->ScreenPointToRay(400, 300).m_origin, currentCamera->ScreenPointToRay(400, 300).m_direction);

	currentCamera->frustum->RenderDebug(renderer);

	if (root->ChildSize() != 0) {
		Render(root, renderer);
	}
}

void Scene::AddEntity(Entity* entity) {
	if (entity->GetParent() == nullptr) {
		root->AddChildNode(entity);
	}
	if (entity->mRigidbody != nullptr) {
		mHavokCore->g_pWorld->lock();
		mHavokCore->g_pWorld->addEntity(entity->mRigidbody);
		mHavokCore->g_pWorld->unlock();
	}
}