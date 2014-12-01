#pragma once
#include "Renderer.h"
#include "Node.h"
#include "Entity.h"
#include "gtx\quaternion.hpp"
#include "HavokCore.h"
#include "Skybox.h"

class Scene {
private:
public:
	Entity* root;
	Camera* currentCamera;
	HavokCore* mHavokCore;
	Skybox* skybox;
	Scene();
	~Scene();
	void LoadScene(const char* filename);
	void Update(Entity* node);

	void Update();
	void Render(Entity* node, Renderer* renderer);
	void Render(Renderer* renderer);

	void AddEntity(Entity* entity);
};