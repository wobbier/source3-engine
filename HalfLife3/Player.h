#pragma once
#include "Entity.h"
#include "Shader.h"

class Player : public Entity {
public:
	float MoveSpeed;
	Model* model;
	Shader ModelShader;
	Player(const char* _name = "Cube");
	~Player();

	virtual void Update() override;
	virtual void Render(Renderer* renderer) override;
};
