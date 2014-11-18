#pragma once
// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "shader.h"

#include "SOIL.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Camera.h"

class Renderer {
private:
	Shader* mainShader;
	enum S3Shapes {
		Square = 0,
		Cube,
		TotalShapes
	};
	GLuint VBO[TotalShapes], VAO[TotalShapes], EBO[TotalShapes];

	GLuint texture1;
	GLuint viewLoc, modelLoc, projLoc;
	Camera* camera;
	glm::mat4 transform;
public:
	Renderer();
	~Renderer();
	void RenderSquare(float x, float y, float width, float height);
	void RenderCube(glm::vec3 position, glm::quat rotation, glm::vec3 scale);
	void SetModelView(glm::mat4 transform);
	//virtual void RenderModel(const Model& model) override;
};