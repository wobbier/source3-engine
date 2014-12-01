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
#include <Common/Base/Math/hkMath.h>
#include "Model.h"
#include "Skybox.h"
#include "Texture.h"

class Renderer {
private:
	Shader* mainShader;
	enum S3Shapes {
		Square = 0,
		Cube,
		Line,
		TotalShapes
	};
	GLuint VBO[TotalShapes], VAO[TotalShapes], EBO[TotalShapes];

	GLuint texture1;
	GLuint viewLoc, modelLoc, projLoc;
	glm::mat4 transform;
	Texture* DefaultTexture;

public:
	Renderer();
	~Renderer();
	Camera* mCamera;
	void RenderSquare(float x, float y, float width, float height);
	void RenderCube();
	void SetModelView(glm::mat4 transform);
	void RenderLine(const hkVector4& from, const hkVector4& to);
	void RenderLine(const glm::vec3& from, const glm::vec3& to);
	void RenderModel(Model* model, Shader shader);
	void RenderSkybox(Skybox* skybox);
};