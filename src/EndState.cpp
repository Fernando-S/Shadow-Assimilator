#include "EndState.h"
#include "Game.h"


EndState::EndState() {
	auto bgGO = new GameObject();
	bgGO->box = { 0,0 };
	Sprite* bg = nullptr;

	if (GameData::playerVictory) {
		backgroundMusic = Music("./assets/audio/endStateWin.ogg");
		backgroundMusic.Play();

		bg = new Sprite(*bgGO, "./assets/img/win.jpg");
	}
	else {
		backgroundMusic = Music("./assets/audio/endStateLose.ogg");
		backgroundMusic.Play();

		bg = new Sprite(*bgGO, "./assets/img/lose.jpg");
	}

	bgGO->AddComponent(bg);
	objectArray.emplace_back(bgGO);

	// criacao do texto de "press to play"
	auto textGO = new GameObject();
//	auto textColor = Text::GetSDLColor(255, 150, 0, 255);
	auto text = new Text(*textGO, "./assets/font/Call me maybe.ttf", 40, Text::SOLID, "Press SPACE to play again, or ESC to exit", { 255, 150, 0, 255 }/*textColor/*, 0.7*/);
	textGO->AddComponent(text);
	textGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, Game::GetInstance().GetHeight() / 2.0f });
	objectArray.emplace_back(textGO);
}

EndState::~EndState() {
	objectArray.clear();				// Esvazia o vetor de objetos
}

void EndState::LoadAssets() {

}

void EndState::Update(float dt) {
	auto& inputManager = InputManager::GetInstance();

	// Seta o quitRequested ao fechar o jogo ou apertar ESC
	quitRequested = inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();

	if (inputManager.KeyPress(SPACE_KEY))
		popRequested = true;				// Seta o popRequested para retornar a TitleSet ao apertar ESPACO

	UpdateArray(dt);	// executa o update em cada um dos objetos no objectArray
}

void EndState::Render() {
	RenderArray();					// Renderiza cada GameObject no objectArray
}

void EndState::Start() {
	LoadAssets();
	Camera::pos = { 0,0 };
	StartArray();					// Da Start em cada GameObject no objectArray
}

void EndState::Pause() {

}

void EndState::Resume() {

}