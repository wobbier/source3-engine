#pragma once
#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Input.h"

class Window {
private:
public:
	static float WINDOW_HEIGHT, WINDOW_WIDTH;
	GLFWwindow* window;

	Window(char* title, int width, int height);
	~Window();

	bool ShouldClose();
};