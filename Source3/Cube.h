#pragma once
#include "Entity.h"
#include "Renderer.h"
#include <Common/Base/Math/hkMath.h>

class Cube : public Entity {
public:
	Cube(hkVector4& size, const char* _name = "Cube");
	~Cube();
	virtual void Update() override;
	virtual void Render(Renderer* renderer) override;
};
