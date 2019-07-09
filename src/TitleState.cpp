#include "TitleState.h"
#include "Game.h"

TitleState::TitleState() {

}

TitleState::~TitleState() {
	objectArray.clear();				// Esvazia o vetor de objetos
}

void TitleState::LoadAssets() {
	// Background de titulo
	auto bgGO = new GameObject();
	bgGO->box = { 0, -36 };
	auto bg = new Sprite(*bgGO, "./assets/img/Menu/menu.png");
	bgGO->AddComponent(bg);
	objectArray.emplace_back(bgGO);

	// Texto "Press to Play"
	auto textGO = new GameObject();
	SDL_Color textColor = { 120, 120, 255, 255 };		// R, G, B, A
	// todo - colocar ultimo parametro para ser o tempo de pisca pisca
	auto text = new Text(*textGO, "./assets/font/Call me maybe.ttf", 60, Text::SOLID, "Press ENTER to play!", textColor/*, 0.7*/);
	textGO->AddComponent(text);

	// Posiciona o texto
	textGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, Game::GetInstance().GetHeight() * 5 / 7.0f });
	objectArray.emplace_back(textGO);
}

void TitleState::Update(float dt) {
	auto& inputManager = InputManager::GetInstance();

	// Seta o quitRequested ao fechar o jogo ou apertar ESC
	quitRequested = inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();

	if (inputManager.KeyPress(ENTER_KEY) || inputManager.KeyPress(NUMPAD_ENTER_KEY))
		Game::GetInstance().Push(new GameState0);

	UpdateArray(dt);	// executa o update em cada um dos objetos no objectArray
}

void TitleState::Render() {
	RenderArray();					// Renderiza cada GameObject no objectArray
}

void TitleState::Start() {
	LoadAssets();
	StartArray();					// Da Start em cada GameObject no objectArray
}

void TitleState::Pause() {

}

void TitleState::Resume() {
	Camera::pos = { 0,0 };
}
