#include "Frustum.h"
#include <iostream>
#include <gtc/matrix_transform.hpp>
#include "Renderer.h"
#define ANG2RAD 3.14159265358979323846/180.0

Frustum::Frustum() {
}

Frustum::~Frustum() {
}

void Frustum::setCamInternals(float angle, float ratio, float nearD, float farD) {
	// store the information
	this->ratio = ratio;
	this->angle = angle;
	this->nearD = nearD;
	this->farD = farD;
	//glm::mat4 fru;
	//fru = glm::frustum(-ratio, ratio, -ratio, ratio, nearD, farD);
	// compute width and height of the near and far plane sections
	tang = (float)tan((ANG2RAD * angle) * 0.5);
	nh = nearD * tang;
	nw = nh * ratio;
	fh = farD  * tang;
	fw = fh * ratio;
}

void Frustum::setCamDef(glm::vec3 &p, glm::vec3 &l, glm::vec3 &u) {
	glm::vec3 dir, nearCenter, farCenter, X, upDir, Z;

	Z = glm::normalize(p - l);

	X = glm::normalize(glm::cross(u, Z));

	upDir = glm::cross(Z, X);

	nearCenter = p - (Z * nearD);
	farCenter = p - (Z * farD);

	// ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
	cornerPoints[0] = nearCenter + upDir * nh - X * nw;
	cornerPoints[1] = nearCenter + upDir * nh + X * nw;
	cornerPoints[2] = nearCenter - upDir * nh - X * nw;
	cornerPoints[3] = nearCenter - upDir * nh + X * nw;

	cornerPoints[4] = farCenter + upDir * fh - X * fw;
	cornerPoints[5] = farCenter + upDir * fh + X * fw;
	cornerPoints[6] = farCenter - upDir * fh - X * fw;
	cornerPoints[7] = farCenter - upDir * fh + X * fw;

	pl[TOP] = Plane(cornerPoints[1], cornerPoints[0], cornerPoints[4]);
	pl[BOTTOM] = Plane(cornerPoints[2], cornerPoints[3], cornerPoints[7]);
	pl[LEFT] = Plane(cornerPoints[0], cornerPoints[2], cornerPoints[6]);
	pl[RIGHT] = Plane(cornerPoints[3], cornerPoints[1], cornerPoints[7]);
	pl[NEARP] = Plane(cornerPoints[0], cornerPoints[1], cornerPoints[3]);
	pl[FARP] = Plane(cornerPoints[5], cornerPoints[4], cornerPoints[6]);
}

bool Frustum::pointInFrustum(glm::vec3 &p) {
	int result = true;

	for (int i = 0; i < 6; i++) {
		float l = pl[i].distance(p);
		if (l < 0) {
			return false;
		}
	}
	return result;
}

bool Frustum::sphereInFrustum(glm::vec3 &p, float raio) {
	return 1;
}

void Frustum::RenderDebug(Renderer* renderer) {
	// ntl, ntr, nbl, nbr, ftl, ftr, fbl, fbr;
	renderer->RenderLine(cornerPoints[4], cornerPoints[5]);
	renderer->RenderLine(cornerPoints[5], cornerPoints[7]);
	renderer->RenderLine(cornerPoints[7], cornerPoints[6]);
	renderer->RenderLine(cornerPoints[6], cornerPoints[4]);
}