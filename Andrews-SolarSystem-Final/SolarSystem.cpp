#include "SolarSystem.h"
#include "Entity.h"
#include "Cube.h"
#include "Sphere.h"
#include "Planet.h"
#include <map>
std::map<std::string, Planet*> planets;

SolarSystem::SolarSystem() : Source3() {
}

SolarSystem::~SolarSystem() {
}

void SolarSystem::Initialize() {
	//cube = new Entity(nullptr, "root");
	//cube->transform.position.y = 3;
	//cube->transform.scale.x = -2;
	//currentScene->SetRootNode(cube);

	//square = new Entity(cube, "square");
	//square->transform.position.y = -3;
	//cube->AddChildNode(square);

	planets["Earth"] = new Planet("Earth");
	planets["Earth"]->SetPosition(glm::vec3(30.0f, 0.0f, 0.0f));
	currentScene->AddEntity(planets["Earth"]);

	planets["Sun"] = new Planet("Sun");
	planets["Sun"]->SetScale(planets["Earth"]->transform.scale * glm::vec3(10.0f));
	currentScene->AddEntity(planets["Sun"]);

	planets["Mercury"] = new Planet("Mercury");
	planets["Mercury"]->SetPosition(glm::vec3(3.0f, 0.0f, 0.0f));
	planets["Mercury"]->SetPosition(planets["Earth"]->transform.position * glm::vec3(0.387f, 0, 0));
	planets["Mercury"]->SetScale(planets["Earth"]->transform.scale * glm::vec3(0.383f * 2.0));
	currentScene->AddEntity(planets["Mercury"]);

	planets["Venus"] = new Planet("Venus");
	planets["Venus"]->SetPosition(glm::vec3(6.0f, 0.0f, 0.0f));
	planets["Venus"]->SetPosition(planets["Earth"]->transform.position * glm::vec3(0.723f, 0, 0));
	planets["Venus"]->SetScale(planets["Earth"]->transform.scale * glm::vec3(0.949f * 2.0));
	currentScene->AddEntity(planets["Venus"]);

	planets["Mars"] = new Planet("Mars");
	planets["Mars"]->SetPosition(glm::vec3(9.0f, 0.0f, 0.0f));
	planets["Mars"]->SetPosition(planets["Earth"]->transform.position * glm::vec3(1.52f, 0, 0));
	planets["Mars"]->SetScale(planets["Earth"]->transform.scale * glm::vec3(0.532f * 2.0));
	currentScene->AddEntity(planets["Mars"]);

	planets["Jupiter"] = new Planet("Jupiter");
	planets["Jupiter"]->SetPosition(glm::vec3(9.0f, 0.0f, 0.0f));
	planets["Jupiter"]->SetPosition(planets["Earth"]->transform.position * glm::vec3(5.20f, 0, 0));
	planets["Jupiter"]->SetScale(planets["Earth"]->transform.scale * glm::vec3(11.21f * 2.0));
	currentScene->AddEntity(planets["Jupiter"]);

	planets["Saturn"] = new Planet("Saturn");
	planets["Saturn"]->SetPosition(glm::vec3(9.0f, 0.0f, 0.0f));
	planets["Saturn"]->SetPosition(planets["Earth"]->transform.position * glm::vec3(9.58f, 0, 0));
	planets["Saturn"]->SetScale(planets["Earth"]->transform.scale * glm::vec3(9.45f * 2.0));
	currentScene->AddEntity(planets["Saturn"]);

	planets["Uranus"] = new Planet("Uranus");
	planets["Uranus"]->SetPosition(glm::vec3(9.0f, 0.0f, 0.0f));
	planets["Uranus"]->SetPosition(planets["Earth"]->transform.position * glm::vec3(10.20f, 0, 0));
	planets["Uranus"]->SetScale(planets["Earth"]->transform.scale * glm::vec3(4.01f * 2.0));
	currentScene->AddEntity(planets["Uranus"]);

	planets["Neptune"] = new Planet("Neptune");
	planets["Neptune"]->SetPosition(glm::vec3(9.0f, 0.0f, 0.0f));
	planets["Neptune"]->SetPosition(planets["Earth"]->transform.position * glm::vec3(11.05f, 0, 0));
	planets["Neptune"]->SetScale(planets["Earth"]->transform.scale * glm::vec3(3.88f * 2.0));
	currentScene->AddEntity(planets["Neptune"]);
	/*planets[0] = Planet("Sun");
	currentScene->AddEntity(&planets[0]);
	planets[0] = Planet("Sun");
	currentScene->AddEntity(&planets[0]);
	planets[0] = Planet("Sun");
	currentScene->AddEntity(&planets[0]);
	planets[0] = Planet("Sun");
	currentScene->AddEntity(&planets[0]);*/
}

void SolarSystem::Update() {
	currentScene->Update();
}

void SolarSystem::Render(Renderer* renderer) {

	currentScene->Render(renderer);
}

void SolarSystem::End() {
}

void SolarSystem::LogMessage() {
}