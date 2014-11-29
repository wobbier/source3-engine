#include "Sphere.h"
Sphere::Sphere(hkReal radius, const char* _name) : Entity(_name) {
	float scaler = .45f;
	hkpSphereShape* sphere = new hkpSphereShape(radius*scaler);
	// convex radius for spheres is exactly the sphere radius
	hkpRigidBodyCinfo rigidBodyInfo;
	rigidBodyInfo.m_shape = sphere;
	rigidBodyInfo.m_motionType = hkpMotion::MOTION_DYNAMIC;
	hkpInertiaTensorComputer::setShapeVolumeMassProperties(sphere, 1.0f, rigidBodyInfo);
	rigidBodyInfo.m_position.set(0.0f, 0.0f, 0.0f);
	rigidBodyInfo.m_friction = 1.0f;
	rigidBodyInfo.m_restitution = 0.2f;
	mRigidbody = new hkpRigidBody(rigidBodyInfo);
	sphere->removeReference();
}

Sphere::~Sphere() {
}

void Sphere::Update() {
	Entity::Update();
}

void Sphere::Render(Renderer* renderer) {
	renderer->RenderCube();
}