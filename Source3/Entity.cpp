#include "Entity.h"

Entity::Entity(const char* _name, Node* parent) : Node(_name, parent) {
}

Entity::~Entity() {
}

void Entity::Update() {
	//transform.position.x += 1 * Time::Get()->deltaTime;
	if (mRigidbody != nullptr) {
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

Entity* Entity::GetChildById(int i) {
	return (Entity*)(mChildren[i]);
}

void Entity::SetPosition(glm::vec3 pos) {
	transform.position = pos;
	if (mRigidbody != nullptr) {
		mRigidbody->setPosition(hkVector4(pos.x, pos.y, pos.z, 1));
	}
}

void Entity::SetScale(glm::vec3 scale) {
	transform.scale = scale;
	if (mRigidbody != nullptr) {
		float scaler = .45f;
		hkVector4 vec = hkVector4(scale.x * scaler, scale.y * scaler, scale.z * scaler);
		hkpBoxShape* box = new hkpBoxShape(vec);
		mRigidbody->setShape(box);
		box->removeReference();
	}
}

void Entity::SetRotation(glm::quat rot) {
	transform.rotation = rot;
}

