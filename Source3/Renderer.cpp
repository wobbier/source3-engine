#include "Renderer.h"
Renderer::Renderer() {
	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, 800, 600);

	glEnable(GL_DEPTH_TEST);

	// Build and compile our shader program
	DefaultShader = new Shader("Shaders/Default.vert", "Shaders/Default.frag");
	ModelShader = new Shader("Shaders/Model.vert", "Shaders/Model.frag");

	GLfloat squareVerts[] = {
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,	// Top Right
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f,	// Bottom Right
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,  // Bottom Left
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f	// Top Left
	};
	GLuint squareIndices[] = {  // Note that we start from 0!
		0, 1, 3,	// First Triangle
		1, 2, 3		// Second Triangle
	};
	glGenVertexArrays(TotalShapes, VAO);
	glGenBuffers(TotalShapes, VBO);
	glGenBuffers(TotalShapes, EBO);
	// Bind our Vertex Array Object first, then bind and set our buffers and pointers.
	glBindVertexArray(VAO[Square]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[Square]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(squareVerts), squareVerts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[Square]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(squareIndices), squareIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Position attribute
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer to prevent strange bugs), remember: do NOT unbind the VBO, keep it bound to this VAO

	// Cube
	GLfloat cubeVerts[] = {
		// front
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f,

		0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f,

		// back
		-0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 1.0f,

		// left
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		//right
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f,

		0.5f, 0.5f, -0.5f, 1.0f, 0.0f,//
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,//
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,

		0.5f, -0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f,//

		// top
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		 // bottom
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	};
	GLuint cubeIndices[] = {  // Note that we start from 0!
		0, 1, 3,	// First Triangle
		1, 2, 3,		// Second Triangle
		4, 5, 7,	// First Triangle
		5, 6, 7		// Second Triangle
	};
	glBindVertexArray(VAO[Cube]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[Cube]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[Cube]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer to prevent strange bugs), remember: do NOT unbind the VBO, keep it bound to this VAO

	DefaultTexture = new Texture("default.png");

	float line[6] = {
		0, 0, 0,
		0, 0, 0
	};
	glBindVertexArray(VAO[Line]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[Line]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[Line]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer to prevent strange bugs), remember: do NOT unbind the VBO, keep it bound to this VAO

	// Get the uniform locations
	modelLoc = glGetUniformLocation(DefaultShader->Program, "model");
	viewLoc = glGetUniformLocation(DefaultShader->Program, "view");
	projLoc = glGetUniformLocation(DefaultShader->Program, "projection");
}

Renderer::~Renderer() {
}

void Renderer::RenderSquare(float x, float y, float width, float height) {
	DefaultShader->Use();
	// Create camera transformation
	glm::mat4 view;
	view = mCamera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(mCamera->Zoom, 800.0f / 600.0f, 0.1f, 1000.0f);
	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glBindVertexArray(VAO[Square]);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
	//trans = glm::scale(trans, glm::vec3(height, width, 1.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, DefaultTexture->Id);
	glUniform1i(glGetUniformLocation(DefaultShader->Program, "texture_diffuse"), 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

hkMatrix4f glmToHK(glm::mat4 vec) {
	hkMatrix4f mat;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			mat(i, j) = vec[j][i];
		}
	}
	return mat;
}

void Renderer::RenderCube() {
	DefaultShader->Use();
	// Create camera transformation
	glm::mat4 view = mCamera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(mCamera->Zoom, 800.0f / 600.0f, 0.1f, 1000.0f);
	hkMatrix4f vec = glmToHK(view);
	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &vec(0, 0));// glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glBindVertexArray(VAO[Cube]);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
	//trans = glm::scale(trans, glm::vec3(height, width, 1.0f));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, DefaultTexture->Id);
	glUniform1i(glGetUniformLocation(DefaultShader->Program, "texture_diffuse"), 0);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void Renderer::SetModelView(glm::mat4 transform) {
	this->transform = transform;
}

void Renderer::RenderLine(const hkVector4& from, const hkVector4& to) {
	float line[6] = {
		from(0), from(1), from(2),
		to(0), to(1), to(2)
	};
	glBindVertexArray(VAO[Line]); // setup for the layout of LineSegment_t
	glBindBuffer(GL_ARRAY_BUFFER, VBO[Line]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line) / 2 * 2, &line[0], GL_DYNAMIC_DRAW);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}

void Renderer::RenderLine(const glm::vec3& from, const glm::vec3& to) {
	float line[6] = {
		from.x, from.y, from.z,
		to.x, to.y, to.z
	};
	glBindVertexArray(VAO[Line]); // setup for the layout of LineSegment_t
	glBindBuffer(GL_ARRAY_BUFFER, VBO[Line]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(line) / 2 * 2, &line[0], GL_DYNAMIC_DRAW);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}

void Renderer::RenderModel(Model* model, Shader shader) {
	ModelShader->Use();
	// Create camera transformation
	glm::mat4 view = mCamera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(mCamera->Zoom, 800.0f / 600.0f, 0.1f, 1000.0f);
	hkMatrix4f vec = glmToHK(view);
	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &vec(0, 0));// glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(transform));
	model->Draw(shader);
}

void Renderer::RenderSkybox(Skybox* skybox) {
	DefaultShader->Use();
	// Create camera transformation
	glm::mat4 view = mCamera->GetViewMatrix();
	glm::mat4 projection = glm::perspective(mCamera->Zoom, 800.0f / 600.0f, 0.1f, 1000.0f);
	hkMatrix4f vec = glmToHK(view);
	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &vec(0, 0));// glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	transform = glm::mat4();
	transform = glm::translate(transform, mCamera->Position);
	transform = glm::scale(transform, glm::vec3(1000, 1000, 1000));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(transform));
	glBindVertexArray(VAO[Cube]);
	skybox->Draw(*DefaultShader);
	//RenderCube();
}
