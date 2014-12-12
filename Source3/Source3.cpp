#include "Source3.h"
#include "Time.h"

Source3::Source3() {
	window = new Window("Source 3 Engine - Mitchell Andrews 2014", 800, 600);
	renderer = new Renderer();
	currentScene = new Scene();
	bIsRunning = true;
}

void Source3::Start() {
	Initialize();
	// Game loop
	while (!window->ShouldClose()) {
		// Check and call events
		glfwPollEvents();
		float time = Time::Get()->GetTimeInMilliseconds();
		Time::Get()->deltaTime = (time <= 0.0f || time >= 0.3) ? 0.0001f : time;
		// Update our engine
		Update();
		glClearColor(1.0f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Render(renderer);
		// Swap the buffers
		glfwSwapBuffers(window->window);
	}
	glfwTerminate();
}