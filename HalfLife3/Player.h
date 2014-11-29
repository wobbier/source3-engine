#pragma once
#include "Entity.h"

class Player : public Entity {
public:
	float MoveSpeed;
	Player(const char* _name = "Cube");
	~Player();

	virtual void Update() override;
	virtual void Render(Renderer* renderer) override;
};
