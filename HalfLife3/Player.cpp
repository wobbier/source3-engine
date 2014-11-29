#include "Player.h"
#include "Time.h"
#include "Input.h"

Player::Player(const char* name) : Entity(name) {
	MoveSpeed = 5.0f;
}

Player::~Player() {
}

void Player::Update() {
	Entity::Update();
	if (Input::Get()->IsKeyDown(GLFW_KEY_W)) {
		transform.position.y += MoveSpeed * Time::Get()->deltaTime;
	}
	if (Input::Get()->IsKeyDown(GLFW_KEY_S)) {
		transform.position.y -= MoveSpeed * Time::Get()->deltaTime;
	}
	if (Input::Get()->IsKeyDown(GLFW_KEY_A)) {
		transform.position.x -= MoveSpeed * Time::Get()->deltaTime;
	}
	if (Input::Get()->IsKeyDown(GLFW_KEY_D)) {
		transform.position.x += MoveSpeed * Time::Get()->deltaTime;
	}
}

void Player::Render(Renderer* renderer) {
	renderer->RenderCube();
}