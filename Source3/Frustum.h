#pragma once
#include <glm.hpp>
#include <iostream>
#include "Plane.h"
class Renderer;
class Frustum {
private:
	enum {
		TOP = 0, BOTTOM, LEFT,
		RIGHT, NEARP, FARP
	};
public:
	Frustum();
	~Frustum();
	static enum { OUTSIDE, INTERSECT, INSIDE };
	Plane pl[6];
	glm::vec3 cornerPoints[8]; // ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
	float nearD, farD, ratio, angle, tang;
	float nw, nh, fw, fh;

	void setCamInternals(float angle, float ratio, float nearD, float farD);
	void setCamDef(glm::vec3 &p, glm::vec3 &l, glm::vec3 &u);
	bool pointInFrustum(glm::vec3 &p);
	bool sphereInFrustum(glm::vec3 &p, float raio);
	void RenderDebug(Renderer* renderer);
};
