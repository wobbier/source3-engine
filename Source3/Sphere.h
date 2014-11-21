#pragma once
#include "Entity.h"
#include <Physics2012/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
class Sphere :
	public Entity
{
public:
	Sphere(hkReal radius, const char* _name = "Sphere");
	~Sphere();
	virtual void Update() override;
	virtual void Render(Renderer* renderer) override;
};

