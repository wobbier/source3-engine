#pragma once
#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Window {
private:
public:
	GLFWwindow* window;
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	}
	Window(char* title, int width, int height) {
		// Init GLFW
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		window = glfwCreateWindow(width, height, title, nullptr, nullptr); // Windowed
		glfwMakeContextCurrent(window);

		// Set the required callback functions
		//glfwSetKeyCallback(window, key_callback);
	}

	~Window() {
	}
	bool ShouldClose() {
		return (glfwWindowShouldClose(window) == 1) ? true : false;
	}
};
