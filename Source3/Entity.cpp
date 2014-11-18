#include "Entity.h"

Entity::Entity(const char* _name, Node* parent) : Node(_name, parent){
}

Entity::~Entity() {
}

void Entity::Update() {
	//transform.position.x += 1 * Time::Get()->deltaTime;
	if (mRigidbody != nullptr){
		transform.position.x = mRigidbody->getPosition()(0);
		transform.position.y = mRigidbody->getPosition()(1);
		transform.position.z = mRigidbody->getPosition()(2);
		transform.rotation.x = mRigidbody->getRotation()(0);
		transform.rotation.y = mRigidbody->getRotation()(1);
		transform.rotation.z = mRigidbody->getRotation()(2);
		transform.rotation.w = mRigidbody->getRotation()(3);
	}
}

void Entity::Render(Renderer* renderer) {
	//renderer->RenderSquare(transform.position.x, transform.position.y, transform.scale.x, transform.scale.y);
}

Entity* Entity::GetChildById(int i)
{
	return (Entity*)(mChildren[i]);
}