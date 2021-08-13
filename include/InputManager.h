#pragma once

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <unordered_map>
#define INCLUDE_SDL
#include "SDL_include.h"

// Depende de onde colocou o SDL.h, mas o segundo eh no padrao atual
// #include "SDL.h"							// Comentar e usar SDL_include.h para enviar
// #include "SDL2/SDL.h"							// Comentar e usar SDL_include.h para enviar

#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN
#define ESCAPE_KEY          SDLK_ESCAPE
#define ENTER_KEY           SDLK_RETURN
#define NUMPAD_ENTER_KEY    SDLK_KP_ENTER
#define BACKSPACE_KEY    SDLK_BACKSPACE
#define SPACE_KEY           SDLK_SPACE
#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON  SDL_BUTTON_RIGHT
#define W_KEY               SDLK_w
#define A_KEY               SDLK_a
#define S_KEY               SDLK_s
#define D_KEY               SDLK_d
#define I_KEY               SDLK_i
#define J_KEY               SDLK_j
#define K_KEY               SDLK_k
#define L_KEY               SDLK_l
#define Z_KEY               SDLK_z
#define X_KEY               SDLK_x
#define Q_KEY               SDLK_q
#define E_KEY               SDLK_e
#define P_KEY               SDLK_p
#define O_KEY               SDLK_o
#define R_KEY               SDLK_r
#define ZERO_KEY            SDLK_0
#define ONE_KEY				SDLK_1
#define TWO_KEY             SDLK_2
#define THREE_KEY           SDLK_3
#define FOUR_KEY            SDLK_4
#define FIVE_KEY            SDLK_5
#define SIX_KEY             SDLK_6
#define SEVEN_KEY           SDLK_7
#define EIGHT_KEY           SDLK_8
#define NINE_KEY            SDLK_9
#define NUMPAD_ZERO_KEY     SDLK_KP_0
#define NUMPAD_ONE_KEY		SDLK_KP_1
#define NUMPAD_TWO_KEY		SDLK_KP_2
#define NUMPAD_THREE_KEY    SDLK_KP_3
#define NUMPAD_FOUR_KEY     SDLK_KP_4
#define NUMPAD_FIVE_KEY     SDLK_KP_5
#define NUMPAD_SIX_KEY		SDLK_KP_6
#define NUMPAD_SEVEN_KEY    SDLK_KP_7
#define NUMPAD_EIGHT_KEY    SDLK_KP_8
#define NUMPAD_NINE_KEY     SDLK_KP_9


class InputManager {
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