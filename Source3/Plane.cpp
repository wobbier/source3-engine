#include "Plane.h"
#include <stdio.h>

Plane::Plane(glm::vec3 &v1, glm::vec3 &v2, glm::vec3 &v3) {
	glm::vec3 a = v2 - v1;
	glm::vec3 b = v3 - v1;
	normal = glm::normalize(glm::cross(a, b));
	d = -(normal.x * v1[0] + normal.y * v1[1] + normal.z * v1[2]);
	point = v1;
}

Plane::Plane() {
	point = glm::vec3(0, 0, 0);
}

Plane::~Plane() {
}

void Plane::SetPoints(glm::vec3 &v1, glm::vec3 &v2, glm::vec3 &v3) {
	glm::vec3 aux1, aux2;

	aux1 = v2 - v1;
	aux2 = v3 - v1;

	normal = glm::normalize(glm::cross(aux1, aux2));
	d = normal.x * v1.x + normal.y * v1.y + normal.z * v1.z;
	point = v1;
	//d = (glm::dot(normal, point));
}

void Plane::SetNormalAndPoint(glm::vec3 &normal, glm::vec3 &point) {
	this->normal = glm::normalize(normal);
	d = -(glm::dot(this->normal, point));
}

void Plane::setCoefficients(float a, float b, float c, float d) {
	// set the normal vector
	normal = glm::vec3(a, b, c);
	//compute the lenght of the vector
	float l = (float)normal.length();
	// normalize the vector
	normal = glm::normalize(normal);
	// and divide d by th length as well
	this->d = d / l;
}

float Plane::distance(glm::vec3 &p) {
	return (d + glm::dot(normal, p));
}

void Plane::print() {
	//printf("Plane("); normal.print(); printf("# %f)", d);
}