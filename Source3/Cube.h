#pragma once
#include "Entity.h"
class Cube : public Entity
{
public:
	Cube(const char* _name);
	~Cube();
	virtual void Update() override;
	virtual void Render(Renderer* renderer) override;
	void SetSize(glm::vec3 scale);
};

