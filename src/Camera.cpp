#include "Camera.h"
#include "Game.h"

GameObject* Camera::focus = nullptr;
Vec2 Camera::pos = {0, 0};
Vec2 Camera::speed = {0, 0};
bool Camera::isMoving = false;

void Camera::Follow(GameObject* newFocus) {
	focus = newFocus;			// Coloca um novo foco na camera
}

void Camera::Unfollow() {
	focus = nullptr;			// Tira o foco da camera
}

void Camera::Update(float dt) {
	auto inputManager = InputManager::GetInstance();
	bool directionalPressed = false;
	speed = { CAMERA_SPEED*dt, 0 };

	if (focus) {
		pos.x = focus->box.Center().x - Game::GetInstance().GetWidth() / 2;		// alinha pos.x da camera com x do foco se houver um
		pos.y = focus->box.Center().y - Game::GetInstance().GetHeight() / 2;	// alinha pos.y da camera com y do foco se houver um
	}
	else {				// faz a posicao da camera variar de acordo com os inputs se nao houver um foco

			// Esquerda cima
		if (inputManager.IsKeyDown(LEFT_ARROW_KEY) && inputManager.IsKeyDown(UP_ARROW_KEY)) {
			speed = speed.GetRotated((float)(5*PI/4));
			directionalPressed = true;
		}	// Esquerda baixo
		else if (inputManager.IsKeyDown(LEFT_ARROW_KEY) && inputManager.IsKeyDown(DOWN_ARROW_KEY)) {
			speed = speed.GetRotated((float)(3*PI/4));
			directionalPressed = true;
		}	// Direita baixo
		else if (inputManager.IsKeyDown(RIGHT_ARROW_KEY) && inputManager.IsKeyDown(DOWN_ARROW_KEY)) {
			speed = speed.GetRotated((float)(PI/4));
			directionalPressed = true;
		}	// Direita cima
		else if (inputManager.IsKeyDown(RIGHT_ARROW_KEY) && inputManager.IsKeyDown(UP_ARROW_KEY)) {
			speed = speed.GetRotated((float)(7*PI/4));
			directionalPressed = true;
		}	// Cima
		else if (inputManager.IsKeyDown(UP_ARROW_KEY)) {
			speed = speed.GetRotated((float)(6*PI/4));
			directionalPressed = true;
		}	// Baixo
		else if (inputManager.IsKeyDown(DOWN_ARROW_KEY)) {
			speed = speed.GetRotated((float)(2*PI/4));
			directionalPressed = true;
		}	// Esquerda
		else if (inputManager.IsKeyDown(LEFT_ARROW_KEY)) {
			speed = speed.GetRotated((float)(PI));
			directionalPressed = true;
		}	// Direita
		else if (inputManager.IsKeyDown(RIGHT_ARROW_KEY))
			directionalPressed = true;

		if (directionalPressed) {
			pos = pos + speed;		// muda a vetor velocidade da camera coisa se um direcional foi apertado
			isMoving = true;
		}
		else
			isMoving = false;
	}
}