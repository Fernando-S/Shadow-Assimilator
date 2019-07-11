#include "EndState.h"
#include "Game.h"


EndState::EndState() {

}

EndState::~EndState() {
	objectArray.clear();				// Esvazia o vetor de objetos
}

void EndState::LoadAssets() {
	auto bgGO = new GameObject();
	bgGO->box = { 0,0 };
	Sprite* bg = nullptr;

	if (GameData::playerVictory) {
		backgroundMusic = Music("./assets/audio/soundtrack/shadowWIN.ogg");
		//backgroundMusic.Play();			// Toca em loop
		backgroundMusic.Play(1);			// Toca soh uma vez

		bg = new Sprite(*bgGO, "./assets/img/win.jpg");


		// criacao do texto de "YOU WIN"
		auto textGO = new GameObject();
		//	auto textColor = Text::GetSDLColor(255, 150, 0, 255);
		//auto text = new Text(*textGO, "./assets/font/Call me maybe.ttf", 60, Text::SOLID, "YOU WIN", { 255, 0, 0, 255 }/*textColor/*, 0.7*/);
		auto text = new Text(*textGO, "./assets/font/ARCADE.ttf", 200, Text::SOLID, "YOU WIN", { 255, 0, 0, 255 }/*textColor/*, 0.7*/);
		textGO->AddComponent(text);
		textGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, 220 });
		objectArray.emplace_back(textGO);

	}
	else {
		backgroundMusic = Music("./assets/audio/soundtrack/shadowLOSS.ogg");
		//backgroundMusic.Play();			// Toca em loop
		backgroundMusic.Play(1);			// Toca soh uma vez

		bg = new Sprite(*bgGO, "./assets/img/lose.jpg");

		// criacao do texto de "YOU LOSE"
		auto textGO = new GameObject();
		//	auto textColor = Text::GetSDLColor(255, 150, 0, 255);
		//auto text = new Text(*textGO, "./assets/font/Call me maybe.ttf", 60, Text::SOLID, "SE FODEU", { 255, 0, 0, 255 }/*textColor/*, 0.7*/);
		auto text = new Text(*textGO, "./assets/font/ARCADE.ttf", 200, Text::SOLID, "GAME OVER", { 255, 0, 0, 255 }/*textColor/*, 0.7*/);
		textGO->AddComponent(text);
		textGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, 220 });
		objectArray.emplace_back(textGO);
	}

	bgGO->AddComponent(bg);
	//objectArray.emplace_back(bgGO);

	// criacao do texto de "press to play"
	auto textGO = new GameObject();
	//	auto textColor = Text::GetSDLColor(255, 150, 0, 255);
	//auto text = new Text(*textGO, "./assets/font/Call me maybe.ttf", 40, Text::SOLID, "Press ENTER to play again, or ESC to exit", { 255, 150, 0, 255 }/*textColor/*, 0.7*/);
	auto text = new Text(*textGO, "./assets/font/hellovetica.ttf", 30, Text::SOLID, "Press ENTER to play again, or ESC to exit", { 255, 150, 0, 255 }/*textColor/*, 0.7*/);
	textGO->AddComponent(text);
	textGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f + 25, Game::GetInstance().GetHeight() * 2/3.0f/*/ 2.0f*/ });
	objectArray.emplace_back(textGO);
}

void EndState::Update(float dt) {
	auto& inputManager = InputManager::GetInstance();

	// Seta o quitRequested ao fechar o jogo ou apertar ESC
	quitRequested = inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();

	if (inputManager.KeyPress(ENTER_KEY) || inputManager.KeyPress(NUMPAD_ENTER_KEY)) {
		popRequested = true;				// Seta o popRequested para retornar a TitleSet ao apertar ESPACO
		GameData::backToMenuScreen = true;
	}

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
