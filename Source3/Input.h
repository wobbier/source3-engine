#pragma once
#include <GLFW/glfw3.h>
#include <map>
#include <glm.hpp>

struct Key {
	int Id;
	int Scancode;
	int Action;
	int Mode;
};

struct Mouse {
	glm::vec2 position;
};

class Input {
private:
	static Input* Instance;

	std::map<int, Key> keys;
	Mouse mouse;

	void KeyCallback_Impl(GLFWwindow* window, int key, int scancode, int action, int mode);
	void MouseCallback_Impl(GLFWwindow* window, double xpos, double ypos);

public:
	static Input* Get();

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
	bool IsKeyDown(int key);
	glm::vec2 GetMousePosition();
};