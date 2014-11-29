#pragma once
#include <vector>
#include "Renderer.h"

class Transform {
public:
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;
	Transform() {
		position = glm::vec3(0, 0, 0);
		rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
		scale = glm::vec3(1, 1, 1);
	}
};

class Node {
public:
	Node(const char* name = "Node", Node* parent = nullptr);
	virtual ~Node();

	//virtual void Update(float deltaTime);
	//virtual void Render(Renderer* renderer);
	Node* GetParent() const;
	void SetParentNode(Node* newParent);

	void AddChildNode(Node* child);
	void RemoveChildNode(Node* child);

	const char* GetNodeName() const;
	const int ChildSize(const bool& recursive = false);

	Node* GetChildByName(const char* name);
	const Node& operator[](int index) const;
	Transform transform;
protected:
	Node* mParent;
	const char* mName;
	std::vector<Node*> mChildren;
};