#include "TitleState.h"
#include "Game.h"

TitleState::TitleState() {

}

TitleState::~TitleState() {
	objectArray.clear();				// Esvazia o vetor de objetos
}

void TitleState::LoadAssets() {

	/////////////////////////////////////////////
	//	  Carrega a Musica e aperta o play	  //
	///////////////////////////////////////////
	backgroundMusic = *new Music("./assets/audio/soundtrack/Shadow_Assimilator_demo.ogg");
	backgroundMusic.Play();

	// Background de titulo
	bgGO = new GameObject();
	bgGO->box = { 0, /*-36 */ 0 };		/// todo - mudar se nao for fullscreen
	auto bg = new Sprite(*bgGO, "./assets/img/Menu/menu.png");
	bgGO->AddComponent(bg);
	objectArray.emplace_back(bgGO);

	// Texto "Press to Play"
	auto textGO = new GameObject();
	SDL_Color textColor = { 120, 120, 255, 255 };		// R, G, B, A
	// todo - colocar ultimo parametro para ser o tempo de pisca pisca
	//auto text = new Text(*textGO, "./assets/font/Call me maybe.ttf", 60, Text::SOLID, "Press ENTER to play!", textColor/*, 0.7*/);
	auto text = new Text(*textGO, "./assets/font/hellovetica.ttf", 60, Text::SOLID, "Press ENTER to play!", textColor/*, 0.7*/);
	textGO->AddComponent(text);

	// Posiciona o texto
	textGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, Game::GetInstance().GetHeight() * 5 / 7.0f });
	//objectArray.emplace_back(textGO);


	// Botao de START
	startButtonGO = new GameObject();
	auto startButton = new Sprite(*startButtonGO, "./assets/img/Menu/menu_start.png");
	startButtonGO->AddComponent(startButton);
	startButtonGO->box.h = startButton->GetHeight();
	startButtonGO->box.w = startButton->GetWidth();
	//startButtonGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f + startButtonGO->box.w / 2 - 4,
	//									 bgGO->box.Center().y + 3 * startButtonGO->box.h + 7 });
	objectArray.emplace_back(startButtonGO);

	// Botao de CREDITS
	creditsButtonGO = new GameObject();
	auto creditsButton = new Sprite(*creditsButtonGO, "./assets/img/Menu/menu_credits.png");
	creditsButtonGO->AddComponent(creditsButton);
	creditsButtonGO->box.h = creditsButton->GetHeight();
	creditsButtonGO->box.w = creditsButton->GetWidth();
	//creditsButtonGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f + creditsButtonGO->box.w / 2 - 4,
		//									bgGO->box.Center().y + 4 * creditsButtonGO->box.h + 2 });
	objectArray.emplace_back(creditsButtonGO);

	hoverSound = new Sound(*startButtonGO, "./assets/audio/SFX/DashPrincipal(Assim.)1.wav");
	clickSound = new Sound(*startButtonGO, "./assets/audio/SFX/Hit_Fraco.wav");
	
	startButtonGO->AddComponent(hoverSound);
	startButtonGO->AddComponent(clickSound);

	creditsButtonGO->AddComponent(hoverSound);
	creditsButtonGO->AddComponent(clickSound);

}

void TitleState::Update(float dt) {
	auto& inputManager = InputManager::GetInstance();
	mousePos = Vec2(inputManager.GetMouseX(), inputManager.GetMouseY());

	if (GameData::backToMenuScreen) {
		backgroundMusic.Play();
		GameData::backToMenuScreen = false;
	}

	// Seta o quitRequested ao fechar o jogo ou apertar ESC
	quitRequested = inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();


	if (startButtonGO->box.Contains(mousePos)) {
		startButtonGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f + startButtonGO->box.w/2 - 1 /** 2/3 + 18*/,
										 bgGO->box.Center().y + 3 * startButtonGO->box.h + 11});
		
		if(startHoverSound)
			hoverSound->Play();
		startHoverSound = false;

		if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
			backgroundMusic.Stop();
			clickSound->Play();
			Game::GetInstance().Push(new GameState0);
		}
	}
	else {
		startHoverSound = true;
		startButtonGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f + startButtonGO->box.w/2 - 3 /** 2/3 + 17*/,
										 bgGO->box.Center().y + 3 * startButtonGO->box.h + 13});
	}

	if (creditsButtonGO->box.Contains(mousePos)) {
		creditsButtonGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f + creditsButtonGO->box.w/2 - 2 /**2/3 + 16*/,
											 bgGO->box.Center().y + 6 * creditsButtonGO->box.h - 3});

		if (creditsHoverSound)
			hoverSound->Play();
		creditsHoverSound = false;

		if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
			clickSound->Play();
			Game::GetInstance().Push(new CreditsState);
		}
	}
	else {
		creditsHoverSound = true;
		creditsButtonGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f + creditsButtonGO->box.w/2 - 4/* *2/3 + 15*/,
											bgGO->box.Center().y + 6 * creditsButtonGO->box.h - 1});
	}

	UpdateArray(dt);	// executa o update em cada um dos objetos no objectArray
}

void TitleState::Render() {
	RenderArray();					// Renderiza cada GameObject no objectArray
}

void TitleState::Start() {
	LoadAssets();
	Camera::pos = { 0,0 };
	StartArray();					// Da Start em cada GameObject no objectArray
}

void TitleState::Pause() {

}

void TitleState::Resume() {
}
