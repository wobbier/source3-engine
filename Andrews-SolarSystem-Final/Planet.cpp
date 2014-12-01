#include "Planet.h"
#include "gtx\quaternion.hpp"

Planet::Planet(std::string _name) : Entity(_name.c_str()) {
	ModelShader = Shader("shader.vert", "shader.frag");
	std::string file = std::string("Planets/" + _name + "/" + _name + ".obj");
	model = new Model(file);
	deg = 0;
}


Planet::~Planet() {
}
void Planet::Update() {
	Entity::Update();
	/*if (Input::Get()->IsKeyDown(GLFW_KEY_W)) {
	transform.position.y += MoveSpeed * Time::Get()->deltaTime;
	}
	if (Input::Get()->IsKeyDown(GLFW_KEY_S)) {
	transform.position.y -= MoveSpeed * Time::Get()->deltaTime;
	}
	if (Input::Get()->IsKeyDown(GLFW_KEY_A)) {
	transform.position.x -= MoveSpeed * Time::Get()->deltaTime;
	}
	if (Input::Get()->IsKeyDown(GLFW_KEY_D)) {
	transform.position.x += MoveSpeed * Time::Get()->deltaTime;
	}*/
	float newX = 0 + (transform.position.x - 0)*glm::cos(Time::Get()->deltaTime * 360.0f) - (transform.position.y - 0)*glm::sin(Time::Get()->deltaTime * 360.0f);

	float newZ = 0 + (transform.position.x - 0)*glm::sin(Time::Get()->deltaTime * 360.0f) + (transform.position.y - 0)*glm::cos(Time::Get()->deltaTime * 360.0f);
	//transform.position.x = newX;
	//transform.position.z = newZ;
	//glm::mat4 trans;
	//trans = glm::rotate(trans, Time::Get()->deltaTime * 180.0f, glm::vec3(0, 1, 0));
	//trans = glm::translate(trans, glm::vec3(newX, 0, newZ));
	//float x = glm::value_ptr(trans)[0];
	//float y = glm::value_ptr(trans)[5];
	//float z = glm::value_ptr(trans)[10];
	//transform.position = glm::vec3(x,y,z);

	float s = sin(360.0f);
	float c = cos(360.0f);

	// rotate point
	//transform.position.x = transform.position.x * c - transform.position.y * s;
	//transform.position.y = transform.position.x * s + transform.position.y * c;
	//transform.rotation = glm::quat(360.0f * Time::Get()->deltaTime, glm::vec3(0, 1, 0));
}

void Planet::Render(Renderer* renderer) {
	glm::mat4 trans;
	deg += Time::Get()->deltaTime * 90.0f;
	trans = glm::rotate(trans, deg, glm::vec3(0, 1, 0));
	trans = glm::translate(trans, transform.position);
	trans = glm::scale(trans, transform.scale);
	renderer->SetModelView(trans);
	renderer->RenderModel(model, ModelShader);
}
POINT rotate_point(float cx, float cy, float angle, POINT p) {
	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	p.x -= cx;
	p.y -= cy;

	// rotate point
	float xnew = p.x * c - p.y * s;
	float ynew = p.x * s + p.y * c;

	// translate point back:
	p.x = xnew + cx;
	p.y = ynew + cy;
	return p;
}