#include "Window.h"

float Window::WINDOW_WIDTH = 800.0f;
float Window::WINDOW_HEIGHT = 600.0f;

Window::Window(char* title, int width, int height) {
	WINDOW_HEIGHT = height;
	WINDOW_WIDTH = width;
	// Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(width, height, title, nullptr, nullptr); // Windowed
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the required callback functions
	glfwSetKeyCallback(window, &Input::KeyCallback);
	glfwSetCursorPosCallback(window, &Input::MouseCallback);
}

Window::~Window() {

}

bool Window::ShouldClose() {
	return (glfwWindowShouldClose(window) == 1) ? true : false;
}