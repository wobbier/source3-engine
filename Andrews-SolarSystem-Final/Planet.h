#pragma once
#include "Entity.h"
#include "Model.h"
#include "Shader.h"

class Planet : public Entity {
public:
	Model* model;
	Shader ModelShader;
	Planet(std::string _name);
	Planet() {}
	~Planet();
	virtual void Update() override;
	virtual void Render(Renderer* renderer) override;
	float deg;
	glm::vec3 position;
};

