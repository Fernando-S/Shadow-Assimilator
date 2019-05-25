#pragma once

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
//#define INCLUDE_SDL
//#include "SDL_include.h"
#include "SDL.h"							// Comentar e usar SDL_include.h para enviar

#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN
#define ESCAPE_KEY          SDLK_ESCAPE
#define SPACE_KEY           SDLK_SPACE
#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON  SDL_BUTTON_RIGHT
#define W_KEY               SDLK_w
#define A_KEY               SDLK_a
#define S_KEY               SDLK_s
#define D_KEY               SDLK_d


class InputManager{
public:
	void Update();
	bool KeyPress(int key);
	bool KeyRelease(int key);
	bool IsKeyDown(int key);
	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);
	int GetMouseX();
	int GetMouseY();
	int QuitRequested();
	static InputManager& GetInstance();
	~InputManager();					// movi para publico para poder acessar no Camera.cpp

private:
		InputManager();
		bool mouseState[6];
		int mouseUpdate[6];
		std::unordered_map<int, bool> keyState;
		std::unordered_map<int, int> keyUpdate;
		bool quitRequested;
		int updateCounter;
		int mouseX;
		int mouseY;

};

#endif	//INPUTMANAGER_H