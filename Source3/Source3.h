// Source3 Engine - 2014 Mitchell Andrews
#pragma once
#include "Window.h"
#include "Renderer.h"
#include "Scene.h"

class Source3 {
private:
	bool bIsRunning;
	Window* window;
	Renderer* renderer;
public:
	Scene* currentScene;
	Source3();
	~Source3() {}
	void Start();
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Render(Renderer* g) = 0;
	virtual void End() = 0;
	virtual void LogMessage() = 0;
};
