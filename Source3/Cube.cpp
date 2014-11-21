#include "Cube.h"
Cube::Cube(hkVector4& size, const char* _name) : Entity(_name)
{
	float scaler = .45f;
	hkVector4 vec = hkVector4(size(0) * scaler, size(1) * scaler, size(2) * scaler);
	transform.scale = glm::vec3(size(0), size(1), size(2));
	hkpBoxShape* box = new hkpBoxShape(vec);
	// convex radius for spheres is exactly the sphere radius
	hkpRigidBodyCinfo rigidBodyInfo;
	rigidBodyInfo.m_shape = box;
	rigidBodyInfo.m_motionType = hkpMotion::MOTION_DYNAMIC;
	hkpInertiaTensorComputer::setShapeVolumeMassProperties(box, 1.0f, rigidBodyInfo);
	rigidBodyInfo.m_position.set(0.0f, 0.0f, 0.0f);
	rigidBodyInfo.m_friction = 1.0f;
	rigidBodyInfo.m_restitution = 0.2f;
	mRigidbody = new hkpRigidBody(rigidBodyInfo);
	box->removeReference();
}

Cube::~Cube()
{
}

void Cube::Update()
{
	Entity::Update();
}

void Cube::Render(Renderer* renderer)
{
	renderer->RenderCube(transform.position, transform.rotation, transform.scale);
}