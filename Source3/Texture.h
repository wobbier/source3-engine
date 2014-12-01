#pragma once
#include <string>

#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include "assimp/Importer.hpp"
#include "SOIL.h"

class Texture {
public:
	GLuint Id;
	std::string Type;
	std::string Directory;
	aiString Path;

	Texture();
	Texture(std::string path);
	~Texture();
};
