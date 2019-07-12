#include "CreditsState.h"
#include "Game.h"

CreditsState::CreditsState() {

}

CreditsState::~CreditsState() {
	objectArray.clear();				// Esvazia o vetor de objetos
}

void CreditsState::LoadAssets() {

	///////////////////////////
	//		Background		//
	/////////////////////////
	auto bgGO = new GameObject();
	auto bg = new Sprite(*bgGO, "./assets/img/fundao.png");

	bgGO->AddComponent(bg);
	objectArray.emplace_back(bgGO);
	
	///////////////////////////////////
	//		Texto de CREDITS		//
	/////////////////////////////////
	auto creditsGO = new GameObject();
	//	auto textColor = Text::GetSDLColor(255, 150, 40, 255);
	auto creditsText = new Text(*creditsGO, "./assets/font/ARCADE.ttf", 120, Text::SOLID, "CREDITS", { 255, 40, 40, 255 }/*textColor/*, 40.7*/);
	creditsGO->AddComponent(creditsText);
	creditsGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, 100 });
	objectArray.emplace_back(creditsGO);
	

	///////////////////////////////
	//		Textos de Art		//
	///////////////////////////////
	auto artGO = new GameObject();
	//	auto textColor = Text::GetSDLColor(255, 150, 40, 255);
	auto artText = new Text(*artGO, "./assets/font/hellovetica.ttf", 35, Text::SOLID, "Art", { 255, 40, 40, 255 }/*textColor/*, 40.7*/);
	artGO->AddComponent(artText);
	artGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, 200 });
	objectArray.emplace_back(artGO);

	// Artistas
	auto camilaGO = new GameObject();
	//	auto textColor = Text::GetSDLColor(255, 150, 40, 255);
	auto camilaText = new Text(*camilaGO, "./assets/font/hellovetica.ttf", 20, Text::SOLID,
								"Camila Bontempo Sidersky", { 255, 40, 40, 255 }/*textColor/*, 40.7*/);
	camilaGO->AddComponent(camilaText);
	camilaGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, artGO->box.y + 75 });
	objectArray.emplace_back(camilaGO);


	auto patyGO = new GameObject();
	//	auto textColor = Text::GetSDLColor(255, 150, 40, 255);
	auto patyText = new Text(*patyGO, "./assets/font/hellovetica.ttf", 20, Text::SOLID,
							 "Patricia Tayna Pereira Silva", { 255, 40, 40, 255 }/*textColor/*, 40.7*/);
	patyGO->AddComponent(patyText);
	patyGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, camilaGO->box.y + 55 });
	objectArray.emplace_back(patyGO);


	auto ralisonGO = new GameObject();
	//	auto textColor = Text::GetSDLColor(255, 150, 40, 255);
	auto ralisonText = new Text(*ralisonGO, "./assets/font/hellovetica.ttf", 20, Text::SOLID,
								"Ralison Marcal Resende", { 255, 40, 40, 255 }/*textColor/*, 40.7*/);
	ralisonGO->AddComponent(ralisonText);
	ralisonGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, patyGO->box.y + 55 });
	objectArray.emplace_back(ralisonGO);
	

	///////////////////////////////////////////////
	//		Texto de Music & Sound Effects		//
	/////////////////////////////////////////////
	auto soundGO = new GameObject();
	//	auto textColor = Text::GetSDLColor(255, 150, 40, 255);
	auto soundText = new Text(*soundGO, "./assets/font/hellovetica.ttf", 30, Text::SOLID, "Music & Sound Effects", { 255, 40, 40, 255 }/*textColor/*, 40.79=*/);
	soundGO->AddComponent(soundText);
	soundGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, ralisonGO->box.y + 90 });
	objectArray.emplace_back(soundGO);

	// Musicos
	auto enzoGO = new GameObject();
	//	auto textColor = Text::GetSDLColor(255, 150, 40, 255);
	auto enzoText = new Text(*enzoGO, "./assets/font/hellovetica.ttf", 20, Text::SOLID,
		"Enzo Aprile Lopes Velloso", { 255, 40, 40, 255 }/*textColor/*, 40.7*/);
	enzoGO->AddComponent(enzoText);
	enzoGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, soundGO->box.y + 75 });
	objectArray.emplace_back(enzoGO);


	auto filipeGO = new GameObject();
	//	auto textColor = Text::GetSDLColor(255, 150, 40, 255);
	auto filipeText = new Text(*filipeGO, "./assets/font/hellovetica.ttf", 20, Text::SOLID,
		"Filipe Campos Nunes de Souza", { 255, 40, 40, 255 }/*textColor/*, 40.7*/);
	filipeGO->AddComponent(filipeText);
	filipeGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, enzoGO->box.y + 55 });
	objectArray.emplace_back(filipeGO);

	///////////////////////////////////
	//		Texto de Programing		//
	/////////////////////////////////
	auto programingGO = new GameObject();
	//	auto textColor = Text::GetSDLColor(255, 150, 40, 255);
	auto programingText = new Text(*programingGO, "./assets/font/hellovetica.ttf", 30, Text::SOLID, "Programing", { 255, 40, 40, 255 }/*textColor/*, 40.79=*/);
	programingGO->AddComponent(programingText);
	programingGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, filipeGO->box.y + 90 });
	objectArray.emplace_back(programingGO);

	// Programadores
	auto fernandoGO = new GameObject();
	//	auto textColor = Text::GetSDLColor(255, 150, 40, 255);
	auto fernandoText = new Text(*fernandoGO, "./assets/font/hellovetica.ttf", 20, Text::SOLID,
		"Fernando Sobral Nobrega", { 255, 40, 40, 255 }/*textColor/*, 40.7*/);
	fernandoGO->AddComponent(fernandoText);
	fernandoGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, programingGO->box.y + 75 });
	objectArray.emplace_back(fernandoGO);


	auto negraoGO = new GameObject();
	//	auto textColor = Text::GetSDLColor(255, 150, 40, 255);
	auto negraoText = new Text(*negraoGO, "./assets/font/hellovetica.ttf", 20, Text::SOLID,
		"Pedro Augusto de Sousa Negrao", { 255, 40, 40, 255 }/*textColor/*, 40.7*/);
	negraoGO->AddComponent(negraoText);
	negraoGO->box.PlaceCenter({ Game::GetInstance().GetWidth() / 2.0f, fernandoGO->box.y + 55 });
	objectArray.emplace_back(negraoGO);


	///////////////////////////////////////
	//		TEXTO DE BACK TO MENU		//
	/////////////////////////////////////
	auto backGO = new GameObject();
	//	auto textColor = Text::GetSDLColor(255, 150, 40, 255);
	auto backText = new Text(*backGO, "./assets/font/hellovetica.ttf", 20, Text::SOLID,
		"Press ESC to go back", { 255, 255, 255, 255 }/*textColor/*, 40.7*/);
	backGO->AddComponent(backText);
	backGO->box.PlaceCenter({ Game::GetInstance().GetWidth()/7.f, Game::GetInstance().GetHeight() - 60.f });
	objectArray.emplace_back(backGO);

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
	Camera::pos = { 0,0 };
	StartArray();					// Da Start em cada GameObject no objectArray
}

void CreditsState::Pause() {

}

void CreditsState::Resume() {

}
