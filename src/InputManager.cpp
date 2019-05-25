#include "InputManager.h"

	
void InputManager::Update() {
	SDL_Event event;

	SDL_GetMouseState(&mouseX, &mouseY);		// Pega as coordenadas do mouse
	quitRequested = false;						// Reseta o quitRequested
	updateCounter++;							// Passa para o proximo frame

	while (SDL_PollEvent(&event)) {				// Enquanto houver um evento

		switch (event.type) {
		case SDL_QUIT:
			quitRequested = true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.key.repeat == 0) {
				mouseState[event.button.button] = true;
				mouseUpdate[event.button.button] = updateCounter;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			mouseState[event.button.button] = false;
			mouseUpdate[event.button.button] = updateCounter;
			break;

		case SDL_KEYDOWN:
			keyState[event.key.keysym.sym] = true;
			keyUpdate[event.key.keysym.sym] = updateCounter;
			break;

		case SDL_KEYUP:
			keyState[event.key.keysym.sym] = false;
			keyUpdate[event.key.keysym.sym] = updateCounter;
			break;

		default:
			break;

		}
	}
}

bool InputManager::KeyPress(int key) {
	if (keyState[key] && (keyUpdate[key] == updateCounter)) 
		return true;					// Retorna verdadeiro se a tecla foi pressionada
	else
		return false;					// Retorna falso se a tecla nao foi pressionada
}

bool InputManager::KeyRelease(int key) {
	if (!keyState[key] && (keyUpdate[key] == updateCounter)) {
		return true;					// Retorna verdadeiro se a tecla foi solta
	}
	else
		return false;					// Retorna falso se a tecla nao foi solta
}

bool InputManager::IsKeyDown(int key) {
	if (keyState[key])
		return true;					// Retorna verdadeiro se a tecla ainda esta sendo apertada
	else
		return false;					// Retorna falso se a tecla nao esta sendo apertada
}

bool InputManager::MousePress(int button) {
	if (mouseState[button] && (mouseUpdate[button] == updateCounter))
		return true;					// Retorna verdadeiro se o botao do mouse foi pressionado
	else
		return false;					// Retorna falso se o botao do mouse nao foi pressionado
}

bool InputManager::MouseRelease(int button) {
	if ( !mouseState[button] && (mouseUpdate[button] == updateCounter))
		return true;					// Retorna verdadeiro se o botao do mouse foi solto
	else
		return false;					// Retorna falso se o botao do mouse nao foi solto
}

bool InputManager::IsMouseDown(int button) {
	if (mouseState[button])
		return true;					// Retorna verdadeiro se o botao do mouse ainda esta sendo apertado
	else
		return false;					// Retorna falso se o botao do mouse nao esta sendo apertado
}

int InputManager::GetMouseX() {
	return mouseX;
}

int InputManager::GetMouseY() {
	return mouseY;
}

int InputManager::QuitRequested() {
	return quitRequested;
}

InputManager& InputManager::GetInstance() {
	static InputManager MeyerSingleton;

	return MeyerSingleton;
}

InputManager::InputManager() {
	quitRequested = false;
	updateCounter = 0;
	mouseX = 0;
	mouseY = 0;

	memset(mouseState, false, sizeof(mouseState));	// Inicializa mouseState com falses
	memset(mouseUpdate, 0, sizeof(mouseUpdate));	// Inicializa mouseUpdate com zeros
}

InputManager::~InputManager() {

}