#include "CreditsState.h"
#include "Game.h"

CreditsState::CreditsState() {

}

CreditsState::~CreditsState() {
	objectArray.clear();				// Esvazia o vetor de objetos
}

void CreditsState::LoadAssets() {
	/*
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
	auto text = new Text(*textGO, "./assets/font/Call me maybe.ttf", 60, Text::SOLID, "Press ENTER to play!", textColor/*, 0.7/);
	textGO->AddComponent(text);

	// Posiciona o texto
	textGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, Game::GetInstance().GetHeight() * 5 / 7.0f });
	//objectArray.emplace_back(textGO);


	// Botao de START
	auto startButtonGO = new GameObject();
	auto startButton = new Sprite(*startButtonGO, "./assets/img/Menu/menu_start.png");
	startButtonGO->AddComponent(startButton);
	startButtonGO->box.h = startButton->GetHeight();
	startButtonGO->box.w = startButton->GetWidth();
	startButtonGO->box.PlaceCenter( {Game::GetInstance().GetWidth() / 2.0f + startButtonGO->box.w / 2 - 4,
									 Game::GetInstance().GetHeight() / 2.0f + 3 * startButtonGO->box.h + 11} );
	objectArray.emplace_back(startButtonGO);

	// Botao de CREDITS
	auto creditsButtonGO = new GameObject();
	auto creditsButton = new Sprite(*creditsButtonGO, "./assets/img/Menu/credits.png");
	creditsButtonGO->AddComponent(creditsButton);
	creditsButtonGO->box.h = creditsButton->GetHeight();
	creditsButtonGO->box.w = creditsButton->GetWidth();
	creditsButtonGO->box.PlaceCenter(  {Game::GetInstance().GetWidth() / 2.0f + creditsButtonGO->box.w / 2 - 4,
										Game::GetInstance().GetHeight() / 2.0f + 4 * creditsButtonGO->box.h + 7} );
	objectArray.emplace_back(creditsButtonGO);
	*/

}

void CreditsState::Update(float dt) {
	auto& inputManager = InputManager::GetInstance();

	// Seta o quitRequested ao fechar o jogo ou apertar ESC
	quitRequested = /*inputManager.KeyPress(ESCAPE_KEY) ||*/ inputManager.QuitRequested();

	if (inputManager.KeyPress(ESCAPE_KEY))
		popRequested = true;

	UpdateArray(dt);	// executa o update em cada um dos objetos no objectArray
	
}

void CreditsState::Render() {
	RenderArray();					// Renderiza cada GameObject no objectArray
}

void CreditsState::Start() {
	LoadAssets();
	StartArray();					// Da Start em cada GameObject no objectArray
}

void CreditsState::Pause() {

}

void CreditsState::Resume() {
	Camera::pos = { 0,0 };
}
