#include "Input.h"
#include <glm.hpp>
#include <iostream>

Input* Input::Instance = nullptr;

Input* Input::Get() {
	if (Instance) {
		return Instance;
	}
	else {
		return Instance = new Input();
	}
}
#pragma region KeyboardInput

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	printf("%i, %i, %i, %i\n", key, scancode, action, mode);
	Get()->KeyCallback_Impl(window, key, scancode, action, mode);
}

void Input::KeyCallback_Impl(GLFWwindow* window, int key, int scancode, int action, int mode) {
	keys[key].Id = key;
	keys[key].Scancode = scancode;
	keys[key].Action = action;
	keys[key].Mode = mode;
}

bool Input::IsKeyDown(int key) {
	if (keys[key].Action == 0) {
		return false;
	}
	printf("KEY IS DOWN!");
	return true;
}

#pragma endregion

#pragma region MouseInput

void Input::MouseCallback(GLFWwindow* window, double xpos, double ypos) {
	Get()->MouseCallback_Impl(window, xpos, ypos);
}

void Input::MouseCallback_Impl(GLFWwindow* window, double xpos, double ypos) {
	mouse.position = glm::vec2(xpos, ypos);
}

glm::vec2 Input::GetMousePosition() {
	return mouse.position;
}

#pragma endregion