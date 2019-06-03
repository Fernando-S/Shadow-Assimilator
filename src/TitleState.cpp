#include "TitleState.h"
#include "Game.h"

TitleState::TitleState() {

}

TitleState::~TitleState() {
	objectArray.clear();				// Esvazia o vetor de objetos
}

void TitleState::LoadAssets() {
	// criacao da imagem de titulo
	auto bgGO = new GameObject();
	bgGO->box = { 0,0 };
	auto bg = new Sprite(*bgGO, "./assets/img/title.jpg");
	bgGO->AddComponent(bg);
	objectArray.emplace_back(bgGO);

	// criacao do texto de "press to play"
	auto textGO = new GameObject();
	SDL_Color textColor = { 255, 150, 0, 255 };
	auto text = new Text(*textGO, "./assets/font/Call me maybe.ttf", 60, Text::SOLID, "Press SPACE to play!", /*{ 255, 150, 0, 255 }*/ textColor/*, 0.7*/);
	textGO->AddComponent(text);
	textGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, Game::GetInstance().GetHeight() / 2.0f });
	objectArray.emplace_back(textGO);
}

void TitleState::Update(float dt) {
	auto& inputManager = InputManager::GetInstance();

	// Seta o quitRequested ao fechar o jogo ou apertar ESC
	quitRequested = inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();

	if (inputManager.KeyPress(SPACE_KEY)) 
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
