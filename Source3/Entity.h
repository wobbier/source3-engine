#pragma once
#include "glm.hpp"
#include "Node.h"
#include "Renderer.h"
#include "Time.h"

// Havok
#include <Common/Base/hkBase.h>
#include <Physics2012\Collide\Shape\Convex\Box\hkpBoxShape.h>
#include <Physics2012\Utilities\Dynamics\Inertia\hkpInertiaTensorComputer.h>
#include <Physics2012\Dynamics\Entity\hkpRigidBodyCinfo.h>
#include <Physics2012\Dynamics\Entity\hkpRigidBody.h>

class Entity : public Node {
public:
	hkpRigidBody* mRigidbody;
	Entity(const char* name = "Entity", Node* parent = nullptr);
	~Entity();
	//virtual void Update(float deltaTime) override;
	virtual void Update();
	virtual void Render(Renderer* renderer);
	void SetPosition();
	void SetRotation();
	void SetScale();
	Entity* GetChildById(int i);

};
