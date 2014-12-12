#include "Planet.h"
#include "gtx\quaternion.hpp"

Planet::Planet(std::string _name) : Entity(_name.c_str()) {
	ModelShader = Shader("Shaders/Model.vert", "Shaders/Model.frag");
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
	// Set uniforms
	renderer->ModelShader->Use(); // Use cooresponding shader when setting uniforms/drawing objects

	glm::mat4 view;
	view = renderer->mCamera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(renderer->mCamera->Zoom, 800.0f / 600.0f, 0.1f, 1000.0f);
	// Pass the matrices to the shader
	glUniformMatrix4fv(glGetUniformLocation(renderer->ModelShader->Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(renderer->ModelShader->Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	GLint viewPosLoc = glGetUniformLocation(renderer->ModelShader->Program, "viewPos");
	glUniform3f(viewPosLoc, renderer->mCamera->Position.x, renderer->mCamera->Position.y, renderer->mCamera->Position.z);
	// Set the light's properties
	GLint lightPosLoc = glGetUniformLocation(renderer->ModelShader->Program, "light.position");
	glUniform3f(lightPosLoc, renderer->mCamera->Position.x, renderer->mCamera->Position.y, renderer->mCamera->Position.z);
	glUniform3f(glGetUniformLocation(renderer->ModelShader->Program, "light.ambient"), 1.0f, 1.0f, 1.0f);
	// We set the diffuse intensity a bit higher; note that the right lighting conditions differ with each lighting method and environment.
	// Each environment and lighting type requires some tweaking of these variables to get the best out of your environment.
	glUniform3f(glGetUniformLocation(renderer->ModelShader->Program, "light.diffuse"), 1.0f, 1.0f, 1.0f);
	glUniform3f(glGetUniformLocation(renderer->ModelShader->Program, "light.specular"), 1.0f, 1.0f, 1.0f);
	glUniform1f(glGetUniformLocation(renderer->ModelShader->Program, "light.constant"), 1.0f);
	glUniform1f(glGetUniformLocation(renderer->ModelShader->Program, "light.linear"), 0.014);
	glUniform1f(glGetUniformLocation(renderer->ModelShader->Program, "light.quadratic"), 0.0000002);
	glUniform3f(glGetUniformLocation(renderer->ModelShader->Program, "light.spotDir"), renderer->mCamera->Front.x, renderer->mCamera->Front.y, renderer->mCamera->Front.z);
	glUniform1f(glGetUniformLocation(renderer->ModelShader->Program, "light.spotCutOff"), glm::cos(glm::radians(45.0f)));
	glUniform1f(glGetUniformLocation(renderer->ModelShader->Program, "light.spotOuterCutOff"), glm::cos(glm::radians(50.0f)));

	// Set diffuse map
	glUniform1f(glGetUniformLocation(renderer->ModelShader->Program, "material.diffuse"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	// Set other material properties
	glUniform1f(glGetUniformLocation(renderer->ModelShader->Program, "material.shininess"), 64.0f);
	glm::mat4 trans;
	deg += Time::Get()->deltaTime * 90.0f;
	trans = glm::rotate(trans, deg, glm::vec3(0, 1, 0));
	trans = glm::translate(trans, transform.position);
	trans = glm::scale(trans, transform.scale);
	renderer->SetModelView(trans);
	renderer->RenderModel(model, ModelShader);
}