#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Texture.h"
#include "Shader.h"
#include <glm.hpp>
#include <string>

class Skybox {
private:
	GLuint VAO, VBO, EBO;

public:
	// top, bottom, left, right, front, back
	Texture textures[6];
	glm::mat4 Transform;
	Skybox();
	~Skybox();
	void LoadSkybox(std::string name);
	void Draw(const Shader& shader);
};

