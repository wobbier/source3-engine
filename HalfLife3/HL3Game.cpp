#include "HL3Game.h"
#include "Entity.h"
#include "Cube.h"
float x = 0;
float y = 0;

Entity* cube;
Entity* square;
Cube* cubeNew;
Cube* otherCube;

HL3Game::HL3Game() : Source3() {
}

HL3Game::~HL3Game() {
}

void HL3Game::Initialize() {
	//cube = new Entity(nullptr, "root");
	//cube->transform.position.y = 3;
	//cube->transform.scale.x = -2;
	//currentScene->SetRootNode(cube);

	//square = new Entity(cube, "square");
	//square->transform.position.y = -3;
	//cube->AddChildNode(square);
	std::cout << "Adding Cube";
	cubeNew = new Cube("HavokCube");
	currentScene->AddEntity(cubeNew);

	otherCube = new Cube("HavokChildCube");
	currentScene->AddEntity(otherCube);
}

void HL3Game::Update() {
	x += 0.05f;
	y -= 0.1f;
	currentScene->Update();
}

void HL3Game::Render(Renderer* renderer) {
	currentScene->Render(renderer);
}

void HL3Game::End() {
}

void HL3Game::LogMessage() {
}