#include "Node.h"

Node::Node(const char* name, Node* parent) {
	mName = name;
	mParent = nullptr;
}

Node::~Node() {
	mParent = nullptr;
	mChildren.clear();
}

//void Node::Update(float deltaTime) {
//	if (!mChildren.empty()) {
//		for (int i = 0; i < mChildren.size(); ++i) {
//			if (mChildren[i] != nullptr) {
//				mChildren[i]->Update(deltaTime);
//			}
//		}
//	}
//}

Node* Node::GetParent() const {
	return mParent;
}

void Node::SetParentNode(Node* newParent) {
	if (mParent != nullptr) {
		mParent->RemoveChildNode(this);
	}
	mParent = newParent;
}

void Node::AddChildNode(Node* child) {
	mChildren.push_back(child);
}

void Node::RemoveChildNode(Node* child) {
	//mChildren.erase(mChildren.at(child));
}

const char* Node::GetNodeName() const {
	return mName;
}

const int Node::ChildSize(const bool& recursive) {
	return mChildren.size();
}

Node* Node::GetChildByName(const char* name) {
	return nullptr;
}