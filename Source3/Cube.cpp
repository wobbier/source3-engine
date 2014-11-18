#include "Cube.h"

Cube::Cube(const char* _name) : Entity(_name)
{
	hkpBoxShape* sphere = new hkpBoxShape(hkVector4(0.5f, 0.5f, 0.5f, 1));
	// convex radius for spheres is exactly the sphere radius
	hkpRigidBodyCinfo rigidBodyInfo;
	rigidBodyInfo.m_shape = sphere;
	rigidBodyInfo.m_motionType = hkpMotion::MOTION_DYNAMIC;
	hkpInertiaTensorComputer::setShapeVolumeMassProperties(sphere, 1.0f, rigidBodyInfo);
	rigidBodyInfo.m_position.set(0.0f, 0.6f, 0.0f);
	rigidBodyInfo.m_friction = 1.0f;
	rigidBodyInfo.m_restitution = 0.2f;
	mRigidbody = new hkpRigidBody(rigidBodyInfo);
	sphere->removeReference();
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

void Cube::SetSize(glm::vec3 scale)
{

}
