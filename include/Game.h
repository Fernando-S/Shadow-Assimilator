#pragma once

/************************************
*				Game				*
************************************/

#ifndef GAME_H
#define GAME_H
#include <stack>
#include <iostream>
#include "InputManager.h"
#include "Resources.h"
#include "State.h"
#include "SDL.h"							// Comentar e usar SDL_include.h para enviar
#include "SDL_ttf.h"						// Comentar e usar SDL_include.h para enviar
#include "SDL_mixer.h"						// Comentar e usar SDL_include.h para enviar
#include "SDL_image.h"						// Comentar e usar SDL_include.h para enviar
// #define INDLUDE_SDL
// #define INCLUDE_SDL_IMAGE
// #define INCLUDE_SDL_MIXER
// #define INCLUDE_SDL_TTF
// #include "SDL_include.h"


class Game {
public:
	~Game();
	static Game& GetInstance();
	SDL_Renderer* GetRenderer();
	State& GetCurrentState();
	void Push(State* state);
	void Run();
	float GetDeltaTime();
	int GetWidth();
	int GetHeight();
	
private:
	Game(const char* title, int width, int height);		// Precisa ser privado. Se for publico, pode ocorrer mais de uma instancia do jogo rodando ao mesmo tempo
	void CalculateDeltaTime();

	int frameStart;
	float dt;
	static Game* instance;
	State* storedState;
	SDL_Window* window;
	SDL_Renderer* renderer;
	std::stack<std::unique_ptr<State>> stateStack;
	int width, height;

};
#endif // GAME_H