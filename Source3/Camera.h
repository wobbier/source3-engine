#pragma once

// Std. Includes
#include <vector>

// GL Includes
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Frustum.h"
#include "Input.h"
#include "Time.h"
#include "Geometry/Internal/Types/hkcdRay.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// An abstract camera class that processes input and calculates the corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera {
public:
	Frustum* frustum;
	// Camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// Eular Angles
	GLfloat Yaw;
	GLfloat Pitch;
	// Camera options
	GLfloat MovementSpeed;
	GLfloat MouseSensitivity;
	GLfloat Zoom;

	glm::vec2 lastMousePos;
	// Constructor with vectors
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = -90.0f, GLfloat pitch = 0.0f) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(5.0f), MouseSensitivity(0.25f), Zoom(45.0f) {
		frustum = new Frustum();
		this->Position = position;
		this->WorldUp = up;
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->updateCameraVectors();
	}
	// Constructor with scalar values
	Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(5.0f), MouseSensitivity(0.25f), Zoom(45.0f) {
		frustum = new Frustum();
		this->Position = glm::vec3(posX, posY, posZ);
		this->WorldUp = glm::vec3(upX, upY, upZ);
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->updateCameraVectors();
	}

	// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix() {
		return glm::lookAt(this->Position, this->Position + this->Front, this->WorldUp);
	}

	void Update() {
		if (Input::Get()->IsKeyDown(GLFW_KEY_W)) {
			ProcessKeyboard(Camera_Movement::FORWARD);
		}
		if (Input::Get()->IsKeyDown(GLFW_KEY_S)) {
			ProcessKeyboard(Camera_Movement::BACKWARD);
		}
		if (Input::Get()->IsKeyDown(GLFW_KEY_A)) {
			ProcessKeyboard(Camera_Movement::LEFT);
		}
		if (Input::Get()->IsKeyDown(GLFW_KEY_D)) {
			ProcessKeyboard(Camera_Movement::RIGHT);
		}
		glm::vec2 mousePos = Input::Get()->GetMousePosition();
		float x = mousePos.x - lastMousePos.x;
		float y = lastMousePos.y - mousePos.y;
		lastMousePos = mousePos;
		ProcessMouseMovement(x, y);
	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(Camera_Movement direction) {
		GLfloat velocity = this->MovementSpeed * Time::Get()->deltaTime;
		if (direction == FORWARD)
			this->Position += this->Front * velocity;
		if (direction == BACKWARD)
			this->Position -= this->Front * velocity;
		if (direction == LEFT)
			this->Position -= this->Right * velocity;
		if (direction == RIGHT)
			this->Position += this->Right * velocity;
	}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true) {
		xoffset *= this->MouseSensitivity;
		yoffset *= this->MouseSensitivity;

		this->Yaw += xoffset;
		this->Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch) {
			if (this->Pitch > 89.0f)
				this->Pitch = 89.0f;
			if (this->Pitch < -89.0f)
				this->Pitch = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Eular angles
		this->updateCameraVectors();
	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(GLfloat yoffset) {
		if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
			this->Zoom -= yoffset;
		if (this->Zoom <= 1.0f)
			this->Zoom = 1.0f;
		if (this->Zoom >= 45.0f)
			this->Zoom = 45.0f;
	}

	hkcdRay ScreenPointToRay(int i, int j) {
		const float width = 800.0f;  // pixels across
		const float height = 600.0f;  // pixels high
		float normalized_i = (i / width) - 0.5f;
		float normalized_j = (j / height) - 0.5f;
		//glm::scale(normalized_i, Right);
		glm::vec3 image_point = normalized_i * Right +
			normalized_j * Up +
			Position + Front;
		glm::vec3 ray_direction = image_point - Position;
		hkcdRay ray;
		ray.m_origin = hkVector4(Position.x, Position.y, Position.z);
		ray.m_direction = hkVector4(ray_direction.x, ray_direction.y, ray_direction.z);
		return ray;//(camera_position, ray_direction);
	}

private:
	// Calculates the front vector from the Camera's (updated) Eular Angles
	void updateCameraVectors() {
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		front.y = sin(glm::radians(this->Pitch));
		front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		this->Front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		this->Up = glm::normalize(glm::cross(this->Front, this->Right));
		frustum->setCamInternals(this->Zoom, 800.0f / 600.0f, 0.1f, 100.0f);
		frustum->setCamDef(this->Position, this->Position + this->Front, this->WorldUp);
	}
};