#include "HL3Game.h"
#include "Entity.h"
#include "Cube.h"
#include "Sphere.h"
#include "Player.h"

Entity* cube;
Entity* square;
Cube* cubeNew;
Cube* otherCube;
Sphere* sphere;
Cube* ground;
Player* player;

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
	cubeNew = new Cube(hkVector4(1, 1, 1), "HavokCube");
	cubeNew->SetPosition(glm::vec3(1.0f, 2, 0));
	currentScene->AddEntity(cubeNew);

	otherCube = new Cube(hkVector4(1, 1, 1), "HavokChildCube");
	otherCube->SetPosition(glm::vec3(-1.0f, 2, 0));
	currentScene->AddEntity(otherCube);

	ground = new Cube(hkVector4(4, 0.5f, 4), "Ground");
	ground->SetPosition(glm::vec3(0, -2, 0));
	ground->mRigidbody->setMotionType(hkpMotion::MOTION_FIXED);
	currentScene->AddEntity(ground);

	sphere = new Sphere(1.0f);
	sphere->SetPosition(glm::vec3(0, 2, 0));
	currentScene->AddEntity(sphere);
	player = new Player("Gordon Freeman");
	player->SetPosition(glm::vec3(0, 3, 0));
	currentScene->AddEntity(player);
}

void HL3Game::Update() {
	currentScene->Update();
}

void HL3Game::Render(Renderer* renderer) {
	currentScene->Render(renderer);
}

void HL3Game::End() {
}

void HL3Game::LogMessage() {
}