#include "GameState0.h"
#include "Game.h"
#include "GameData.h"


GameState0::GameState0() {
	HPbarGO = new GameObject();
	surpriseGO = new GameObject();
	playerGO = new GameObject();
	player = new Player(*playerGO);
	chaoGO = new GameObject();
}

void GameState0::LoadAssets() {
	int i;

	/////////////////////////////////////////////
	//	  Carrega a Musica e aperta o play	  //
	///////////////////////////////////////////
	backgroundMusic = *new Music("./assets/audio/soundtrack/Shadow_Assimilator_-_Theme_1.mp3");
	backgroundMusic.Play();

	
	/////////////////////////////////
	//	  Carrega o Background	  //
	///////////////////////////////
	auto bgGO = new GameObject();
	auto bg = new Sprite(*bgGO, "./assets/img/background.png");

	// Seta a escala e posiciona no centro da tela
	bg->SetScale(1.3333, 1.3333);	// (resolution width / image width) * escala que queremos, (resolution height / image height) * escala que queremos

	auto bgCamFollower = new CameraFollower(*bgGO);
	bgGO->AddComponent(bgCamFollower);


	bgGO->box.h = bg->GetHeight();
	bgGO->box.w = bg->GetWidth();

	bgGO->AddComponent(bg);
	objectArray.emplace_back(bgGO);


	///////////////////////////////////////////////////
	//		Carrega os Predios de Background		//
	/////////////////////////////////////////////////
	
	auto prediosGO = new GameObject();
	//auto tileSet_Level0 = new TileSet(64, 64, "./assets/img/Level0/tileLevel0.png");
	auto tileSet_Background = new TileSet(64, 64, "./assets/img/Level0/tile001.png");
	auto prediosBackground = new TileMap(*prediosGO, "./assets/map/Level0/TileMap_Predios.txt", tileSet_Background);
	//auto prediosBackground = new TileMap(*prediosGO, "./assets/img/Level0/TileMap_Predios.txt", tileSet_Level0);

	prediosBackground->colide = false;

	prediosGO->box.x = 0;
	prediosGO->box.y =  800 - 29 * ONETILESQUARE;
	prediosGO->box.w = prediosBackground->GetWidth() * tileSet_Background->GetTileWidth();
	prediosGO->box.h = prediosBackground->GetHeight() * tileSet_Background->GetTileHeight();
	//prediosGO->box.w = prediosBackground->GetWidth() * tileSet_Level0->GetTileWidth();
	//prediosGO->box.h = prediosBackground->GetHeight() * tileSet_Level0->GetTileHeight();

	prediosGO->AddComponent(prediosBackground);
	objectArray.emplace_back(prediosGO);

	// Detalhes dos predios
	auto detalhesGO = new GameObject();
	auto tileSet_Detalhes = new TileSet(64, 64, "./assets/img/Level0/tileENFEITES001.png");
	auto detalhesBackground = new TileMap(*detalhesGO, "./assets/map/Level0/TileMap_Detalhes.txt", tileSet_Detalhes);
	//auto detalhesBackground = new TileMap(*detalhesGO, "./assets/img/Level0/TileMap_Detalhes.txt", tileSet_Level0);

	detalhesBackground->colide = false;

	detalhesGO->box.x = 0;
	detalhesGO->box.y = 800 - 29 * ONETILESQUARE;
	detalhesGO->box.w = detalhesBackground->GetWidth() * tileSet_Detalhes->GetTileWidth();
	detalhesGO->box.h = detalhesBackground->GetHeight() * tileSet_Detalhes->GetTileHeight();
	//detalhesGO->box.w = detalhesBackground->GetWidth() * tileSet_Level0->GetTileWidth();
	//detalhesGO->box.h = detalhesBackground->GetHeight() * tileSet_Level0->GetTileHeight();

	detalhesGO->AddComponent(detalhesBackground);
	objectArray.emplace_back(detalhesGO);
	




	
	// Teste do novo TileSet
	chaoGO->box.x = 0;
	chaoGO->box.y = 800;

	LoadLevel();

	auto colidemGO = new GameObject();
	colidemGO->box.x = 0;
	colidemGO->box.y = -288;

	auto backgroundGO = new GameObject();
	backgroundGO->box.x = 0;
	backgroundGO->box.y = -352;
	

	////////////////////////////////
	//	   Carrega o Ricardo	 //
	//////////////////////////////
	auto surprise = new Sprite(*surpriseGO, "./assets/img/Ricardo.png");

	// Seta a escala e posiciona no centro da tela
	surprise->SetScale(0.53, 0.55);	// (resolution width / image width) * escala que queremos, (resolution height / image height) * escala que queremos
	surpriseGO->box.x = (Game::GetInstance().GetWidth() - surprise->GetWidth()) / 2;
	surpriseGO->box.y = (Game::GetInstance().GetHeight() - surprise->GetHeight()) / 2;

	surpriseGO->AddComponent(surprise);
	objectArray.emplace_back(surpriseGO);
	surpriseGO->render = false;


	///////////////////////////////////
	//		Carrega um Robo			//
	/////////////////////////////////
	auto robotGO = new GameObject();
	auto robot = new Robot(*robotGO);

	robotGO->AddComponent(robot);
	robotGO->box.x = 3000;
	robotGO->box.y = 800 - robotGO->box.h;

	objectArray.emplace_back(robotGO);


	///////////////////////////////////
	//		Carrega o CoatGuy		//
	/////////////////////////////////
	auto coatGuyGO = new GameObject();
	auto coatGuy = new CoatGuy(*coatGuyGO);

	coatGuyGO->AddComponent(coatGuy);
	coatGuyGO->box.x = 3000;
	coatGuyGO->box.y = 800 - coatGuyGO->box.h;

	objectArray.emplace_back(coatGuyGO);


	///////////////////////////////////
	//		Carrega a Personagem	//
	/////////////////////////////////
	playerGO->AddComponent(player);
	playerGO->box.x = 400;
	playerGO->box.y = 800 - playerGO->box.h;

	objectArray.emplace_back(playerGO);
	Camera::Follow(playerGO);			// Coloca a camera para seguir o Penguin


	///////////////////////
	//	  Barra de HP	//
	/////////////////////
	HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_22.png");
	auto HPbarCamFollower = new CameraFollower(*HPbarGO);
	HPbarGO->AddComponent(HPbarCamFollower);

	HPbarGO->AddComponent(HPbarSprite);
	objectArray.emplace_back(HPbarGO);
	
}

void GameState0::Update(float dt){
	unsigned i, j;
	auto inputManager = InputManager::GetInstance();


	// Faz o update na camera e na box do mapa
	Camera::Update(dt);

	quitRequested = inputManager.QuitRequested();			// Seta o quitRequested ao fechar o jogo
	if (inputManager.KeyPress(ESCAPE_KEY)) {
		popRequested = true;
		//backgroundMusic.Stop();
	}
	UpdateArray(dt);										// Faz o update de cada GameObject no objectArray

	
	if (playerGO->box.y + playerGO->box.h > 800) {
		playerGO->box.y = 800 - playerGO->box.h;
	}

	ChangePlayerHP();


	// KONAMI CODE
	// todo - Apertar 2 teclas seguidas nao funciona (reconhece as duas apertando soh uma vez). Usar um timer pra resolver isso
	/*
	if (surpriseGO) {
		if (inputManager.KeyPress(UP_ARROW_KEY) && !cima2) {
			cima1 = true;
			cima2 = baixo1 = baixo2 = esquerda1 = direita1 = esquerda2 = direita2 = false;
			std::cout << "cima1 = true" << std::endl;
		}
		if (inputManager.KeyPress(UP_ARROW_KEY) && cima1) {
			cima2 = true;
			cima1 = false;
			std::cout << "cima2 = true" << std::endl;
		}
		if (inputManager.KeyPress(DOWN_ARROW_KEY) && cima2) {
			baixo1 = true;
			cima2 = false;
			std::cout << "baixo1 = true" << std::endl;
		}
		if (inputManager.KeyPress(DOWN_ARROW_KEY) && baixo1) {
			baixo2 = true;
			baixo1 = false;
			std::cout << "baixo2 = true" << std::endl;
		}
		if (inputManager.KeyPress(LEFT_ARROW_KEY) && baixo2) {
			esquerda1 = true;
			baixo2 = false;
			std::cout << "esquerda1 = true" << std::endl;
		}
		if (inputManager.KeyPress(RIGHT_ARROW_KEY) && esquerda1) {
			direita1 = true;
			esquerda1 = false;
			std::cout << "direita1 = true" << std::endl;
		}
		if (inputManager.KeyPress(LEFT_ARROW_KEY) && direita1) {
			esquerda2 = true;
			direita1 = false;
			std::cout << "esquerda2 = true" << std::endl;
		}
		if (inputManager.KeyPress(RIGHT_ARROW_KEY) && esquerda2) {
			direita2 = true;
			esquerda2 = false;
			std::cout << "direita2 = true" << std::endl;
		}

		if (direita2 && inputManager.KeyPress(Z_KEY)) {
			mostrando = true;
			surpriseGO->render = true;
			std::cout << "mostrando = true" << std::endl;
		}
		//else if (mostrando && inputManager.MouseRelease(LEFT_MOUSE_BUTTON)) {
		else if (mostrando && inputManager.KeyPress(X_KEY)) {
			mostrando = false;
			surpriseGO->render = false;
			std::cout << "mostrando = false" << std::endl;
		}
	}
	*/




	// PENSADOR CODE
	if (surpriseGO) {
		if ( (inputManager.KeyRelease(TWO_KEY) || inputManager.KeyRelease(NUMPAD_TWO_KEY)) && !dois) {
			dois = true;
			tres = quatro = cinco = meia = sete = oito = false;
			//std::cout << "dois = true" << std::endl;
		}
		if ( (inputManager.KeyRelease(THREE_KEY) || inputManager.KeyRelease(NUMPAD_THREE_KEY)) && dois) {
			tres = true;
			dois = quatro = cinco = meia = sete = oito = false;
			//std::cout << "tres = true" << std::endl;
		}
		if ( (inputManager.KeyRelease(FOUR_KEY) || inputManager.KeyRelease(NUMPAD_FOUR_KEY)) && tres) {
			quatro = true;
			dois = tres = cinco = meia = sete = oito = false;
			//std::cout << "quatro = true" << std::endl;
		}
		if ( (inputManager.KeyRelease(FIVE_KEY) || inputManager.KeyRelease(NUMPAD_FIVE_KEY)) && quatro) {
			cinco = true;
			dois = tres = quatro = meia = sete = oito = false;
			//std::cout << "cinco = true" << std::endl;
		}
		if ( (inputManager.KeyRelease(SIX_KEY) || inputManager.KeyRelease(NUMPAD_SIX_KEY)) && cinco) {
			meia = true;
			dois = tres = quatro = cinco = sete = oito = false;
			//std::cout << "meia = true" << std::endl;
		}
		if ( (inputManager.KeyRelease(SEVEN_KEY) || inputManager.KeyRelease(NUMPAD_SEVEN_KEY)) && meia) {
			sete = true;
			dois = tres = quatro = cinco = meia = oito = false;
			//std::cout << "sete = true" << std::endl;
		}
		if ((inputManager.KeyRelease(EIGHT_KEY) || inputManager.KeyRelease(NUMPAD_EIGHT_KEY)) && sete) {
			oito = true;
			dois = tres = quatro = cinco = meia = sete = false;
			//std::cout << "oito = true" << std::endl;
		}

		if (oito && inputManager.KeyPress(Z_KEY)) {
			mostrando = true;
			surpriseGO->render = true;
			//std::cout << "mostrando = true" << std::endl;
		}
		else if (mostrando && inputManager.KeyPress(X_KEY)) {
			mostrando = false;
			surpriseGO->render = false;
			//std::cout << "mostrando = false" << std::endl;
		}
	}


	// Colisoes
	std::vector<Collider*> colliders(objectArray.size(), nullptr);
	bool collidersArrayFilled = false;

	// Checa colisoes entre os Colliders dos GameObjects
	for (i = 0; i < objectArray.size() - 1; i++) {
		if (!collidersArrayFilled)
			colliders[i] = (Collider*)objectArray[i]->GetComponent("Collider");

		if (colliders[i]) {
			for (j = i + 1; j < objectArray.size(); j++) {
				if (!collidersArrayFilled)
					colliders[j] = (Collider*)objectArray[j]->GetComponent("Collider");

				if (colliders[j] && Collision::IsColliding(colliders[i]->box, colliders[j]->box, objectArray[i]->angleDeg, objectArray[j]->angleDeg)) {
					// Notifica ambos os GameObjects que houve colisao
					objectArray[i]->NotifyCollision(*objectArray[j]);
					objectArray[j]->NotifyCollision(*objectArray[i]);
				}
			}
			collidersArrayFilled = true;
		}
	}

	// Checa se houve a morte de algum objeto
	for (i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin() + i);
			i--;					// Ajuste da posicao  no index do vetor de objetos
		}
	}



	// Tela de GAME OVER
	if (!Player::player) {
		GameData::playerVictory = false;
		popRequested = true;
		Game::GetInstance().Push(new EndState());
	}	// Tela de WIN
	/// todo - colocar uma condicao de vitoria
	else if (/*Alien::alienCount == 0*/inputManager.KeyPress(BACKSPACE_KEY)) {
		GameData::playerVictory = true;
		popRequested = true;
		Game::GetInstance().Push(new EndState());
	}
	
}

GameState0::~GameState0() {
	objectArray.clear();			// Esvazia o vetor de objetos
}

void GameState0::Render() {
	RenderArray();					// Renderiza cada GameObject no objectArray
}

void GameState0::Start() {
	LoadAssets();					// Carrega os assets a serem usados no jogo
	StartArray();					// Da Start em cada GameObject no objectArray
}

void GameState0::Pause() {

}

void GameState0::Resume() {

}

void GameState0::LoadLevel() {
	
	///////////////////////////////
	//		Carrega o Chao		//
	/////////////////////////////
	//auto tileSet = new TileSet(64, 64, "./assets/img/tilesaaaaa.png");
	//auto Chao = new TileMap(*chaoGO, "./assets/map/Tile31_Chao_pra_caralho.txt", tileSet);

	auto tileSet_Chao = new TileSet(64, 64, "./assets/img/Level0/tile001.png");
	auto Chao = new TileMap(*chaoGO, "./assets/map/Level0/TileMap_Chao.txt", tileSet_Chao);

	Chao->colide = true;

	//chaoGO->box.w = Chao->GetWidth() * tileSet->GetTileWidth();
	//chaoGO->box.h = Chao->GetHeight() * tileSet->GetTileHeight();

	chaoGO->box.w = Chao->GetWidth() * tileSet_Chao->GetTileWidth();
	chaoGO->box.h = Chao->GetHeight() * tileSet_Chao->GetTileHeight();

	chaoGO->AddComponent(Chao);
	objectArray.emplace_back(chaoGO);

	/*
	////////////////////////////////////
	//		HERE WE GO
	///////////////////////////////////
	auto Tile00_Coluna_novoGO = new GameObject();
	Tile00_Coluna_novoGO->box.x = (0) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile00_Coluna_novoGO->box.y = (-22) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile00_Coluna_novo = new TileMap(*Tile00_Coluna_novoGO, "./assets/map/Tile00_Coluna_novo.txt", tileSet);
	tileMap_Tile00_Coluna_novo->colide = true;

	Tile00_Coluna_novoGO->box.w = tileMap_Tile00_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile00_Coluna_novoGO->box.h = tileMap_Tile00_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile00_Coluna_novoGO->AddComponent(tileMap_Tile00_Coluna_novo);
	objectArray.emplace_back(Tile00_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile01_Coluna_novoGO = new GameObject();
	Tile01_Coluna_novoGO->box.x = (4) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile01_Coluna_novoGO->box.y = (-22) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile01_Coluna_novo = new TileMap(*Tile01_Coluna_novoGO, "./assets/map/Tile01_Coluna_novo.txt", tileSet);
	tileMap_Tile01_Coluna_novo->colide = true;

	Tile01_Coluna_novoGO->box.w = tileMap_Tile01_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile01_Coluna_novoGO->box.h = tileMap_Tile01_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile01_Coluna_novoGO->AddComponent(tileMap_Tile01_Coluna_novo);
	objectArray.emplace_back(Tile01_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile02_Coluna_novoGO = new GameObject();
	Tile02_Coluna_novoGO->box.x = (5) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile02_Coluna_novoGO->box.y = (-21) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile02_Coluna_novo = new TileMap(*Tile02_Coluna_novoGO, "./assets/map/Tile02_Coluna_novo.txt", tileSet);
	tileMap_Tile02_Coluna_novo->colide = true;

	Tile02_Coluna_novoGO->box.w = tileMap_Tile02_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile02_Coluna_novoGO->box.h = tileMap_Tile02_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile02_Coluna_novoGO->AddComponent(tileMap_Tile02_Coluna_novo);
	objectArray.emplace_back(Tile02_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile03_Coluna_novoGO = new GameObject();
	Tile03_Coluna_novoGO->box.x = (6) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile03_Coluna_novoGO->box.y = (-20) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile03_Coluna_novo = new TileMap(*Tile03_Coluna_novoGO, "./assets/map/Tile03_Coluna_novo.txt", tileSet);
	tileMap_Tile03_Coluna_novo->colide = true;

	Tile03_Coluna_novoGO->box.w = tileMap_Tile03_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile03_Coluna_novoGO->box.h = tileMap_Tile03_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile03_Coluna_novoGO->AddComponent(tileMap_Tile03_Coluna_novo);
	objectArray.emplace_back(Tile03_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile04_Coluna_novoGO = new GameObject();
	Tile04_Coluna_novoGO->box.x = (7) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile04_Coluna_novoGO->box.y = (-19) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile04_Coluna_novo = new TileMap(*Tile04_Coluna_novoGO, "./assets/map/Tile04_Coluna_novo.txt", tileSet);
	tileMap_Tile04_Coluna_novo->colide = true;

	Tile04_Coluna_novoGO->box.w = tileMap_Tile04_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile04_Coluna_novoGO->box.h = tileMap_Tile04_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile04_Coluna_novoGO->AddComponent(tileMap_Tile04_Coluna_novo);
	objectArray.emplace_back(Tile04_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile05_Coluna_novoGO = new GameObject();
	Tile05_Coluna_novoGO->box.x = (8) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile05_Coluna_novoGO->box.y = (-18) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile05_Coluna_novo = new TileMap(*Tile05_Coluna_novoGO, "./assets/map/Tile05_Coluna_novo.txt", tileSet);
	tileMap_Tile05_Coluna_novo->colide = true;

	Tile05_Coluna_novoGO->box.w = tileMap_Tile05_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile05_Coluna_novoGO->box.h = tileMap_Tile05_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile05_Coluna_novoGO->AddComponent(tileMap_Tile05_Coluna_novo);
	objectArray.emplace_back(Tile05_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile06_Coluna_novoGO = new GameObject();
	Tile06_Coluna_novoGO->box.x = (9) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile06_Coluna_novoGO->box.y = (-17) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile06_Coluna_novo = new TileMap(*Tile06_Coluna_novoGO, "./assets/map/Tile06_Coluna_novo.txt", tileSet);
	tileMap_Tile06_Coluna_novo->colide = true;

	Tile06_Coluna_novoGO->box.w = tileMap_Tile06_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile06_Coluna_novoGO->box.h = tileMap_Tile06_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile06_Coluna_novoGO->AddComponent(tileMap_Tile06_Coluna_novo);
	objectArray.emplace_back(Tile06_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile07_Coluna_novoGO = new GameObject();
	Tile07_Coluna_novoGO->box.x = (10) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile07_Coluna_novoGO->box.y = (-16) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile07_Coluna_novo = new TileMap(*Tile07_Coluna_novoGO, "./assets/map/Tile07_Coluna_novo.txt", tileSet);
	tileMap_Tile07_Coluna_novo->colide = true;

	Tile07_Coluna_novoGO->box.w = tileMap_Tile07_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile07_Coluna_novoGO->box.h = tileMap_Tile07_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile07_Coluna_novoGO->AddComponent(tileMap_Tile07_Coluna_novo);
	objectArray.emplace_back(Tile07_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile08_Coluna_novoGO = new GameObject();
	Tile08_Coluna_novoGO->box.x = (11) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile08_Coluna_novoGO->box.y = (-15) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile08_Coluna_novo = new TileMap(*Tile08_Coluna_novoGO, "./assets/map/Tile08_Coluna_novo.txt", tileSet);
	tileMap_Tile08_Coluna_novo->colide = true;

	Tile08_Coluna_novoGO->box.w = tileMap_Tile08_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile08_Coluna_novoGO->box.h = tileMap_Tile08_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile08_Coluna_novoGO->AddComponent(tileMap_Tile08_Coluna_novo);
	objectArray.emplace_back(Tile08_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile09_Coluna_novoGO = new GameObject();
	Tile09_Coluna_novoGO->box.x = (12) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile09_Coluna_novoGO->box.y = (-14) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile09_Coluna_novo = new TileMap(*Tile09_Coluna_novoGO, "./assets/map/Tile09_Coluna_novo.txt", tileSet);
	tileMap_Tile09_Coluna_novo->colide = true;

	Tile09_Coluna_novoGO->box.w = tileMap_Tile09_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile09_Coluna_novoGO->box.h = tileMap_Tile09_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile09_Coluna_novoGO->AddComponent(tileMap_Tile09_Coluna_novo);
	objectArray.emplace_back(Tile09_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile10_Coluna_novoGO = new GameObject();
	Tile10_Coluna_novoGO->box.x = (33) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile10_Coluna_novoGO->box.y = (-13) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile10_Coluna_novo = new TileMap(*Tile10_Coluna_novoGO, "./assets/map/Tile10_Coluna_novo.txt", tileSet);
	tileMap_Tile10_Coluna_novo->colide = true;

	Tile10_Coluna_novoGO->box.w = tileMap_Tile10_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile10_Coluna_novoGO->box.h = tileMap_Tile10_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile10_Coluna_novoGO->AddComponent(tileMap_Tile10_Coluna_novo);
	objectArray.emplace_back(Tile10_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile11_Coluna_novoGO = new GameObject();
	Tile11_Coluna_novoGO->box.x = (42) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile11_Coluna_novoGO->box.y = (-13) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile11_Coluna_novo = new TileMap(*Tile11_Coluna_novoGO, "./assets/map/Tile11_Coluna_novo.txt", tileSet);
	tileMap_Tile11_Coluna_novo->colide = true;

	Tile11_Coluna_novoGO->box.w = tileMap_Tile11_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile11_Coluna_novoGO->box.h = tileMap_Tile11_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile11_Coluna_novoGO->AddComponent(tileMap_Tile11_Coluna_novo);
	objectArray.emplace_back(Tile11_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile12_Coluna_novoGO = new GameObject();
	Tile12_Coluna_novoGO->box.x = (43) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile12_Coluna_novoGO->box.y = (-10) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile12_Coluna_novo = new TileMap(*Tile12_Coluna_novoGO, "./assets/map/Tile12_Coluna_novo.txt", tileSet);
	tileMap_Tile12_Coluna_novo->colide = true;

	Tile12_Coluna_novoGO->box.w = tileMap_Tile12_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile12_Coluna_novoGO->box.h = tileMap_Tile12_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile12_Coluna_novoGO->AddComponent(tileMap_Tile12_Coluna_novo);
	objectArray.emplace_back(Tile12_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile13_Coluna_novoGO = new GameObject();
	Tile13_Coluna_novoGO->box.x = (49) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile13_Coluna_novoGO->box.y = (-10) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile13_Coluna_novo = new TileMap(*Tile13_Coluna_novoGO, "./assets/map/Tile13_Coluna_novo.txt", tileSet);
	tileMap_Tile13_Coluna_novo->colide = true;

	Tile13_Coluna_novoGO->box.w = tileMap_Tile13_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile13_Coluna_novoGO->box.h = tileMap_Tile13_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile13_Coluna_novoGO->AddComponent(tileMap_Tile13_Coluna_novo);
	objectArray.emplace_back(Tile13_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile14_Coluna_novoGO = new GameObject();
	Tile14_Coluna_novoGO->box.x = (50) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile14_Coluna_novoGO->box.y = (-16) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile14_Coluna_novo = new TileMap(*Tile14_Coluna_novoGO, "./assets/map/Tile14_Coluna_novo.txt", tileSet);
	tileMap_Tile14_Coluna_novo->colide = true;

	Tile14_Coluna_novoGO->box.w = tileMap_Tile14_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile14_Coluna_novoGO->box.h = tileMap_Tile14_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile14_Coluna_novoGO->AddComponent(tileMap_Tile14_Coluna_novo);
	objectArray.emplace_back(Tile14_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile15_Coluna_novoGO = new GameObject();
	Tile15_Coluna_novoGO->box.x = (57) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile15_Coluna_novoGO->box.y = (-16) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile15_Coluna_novo = new TileMap(*Tile15_Coluna_novoGO, "./assets/map/Tile15_Coluna_novo.txt", tileSet);
	tileMap_Tile15_Coluna_novo->colide = true;

	Tile15_Coluna_novoGO->box.w = tileMap_Tile15_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile15_Coluna_novoGO->box.h = tileMap_Tile15_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile15_Coluna_novoGO->AddComponent(tileMap_Tile15_Coluna_novo);
	objectArray.emplace_back(Tile15_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile16_Coluna_novoGO = new GameObject();
	Tile16_Coluna_novoGO->box.x = (61) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile16_Coluna_novoGO->box.y = (-21) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile16_Coluna_novo = new TileMap(*Tile16_Coluna_novoGO, "./assets/map/Tile16_Coluna_novo.txt", tileSet);
	tileMap_Tile16_Coluna_novo->colide = true;

	Tile16_Coluna_novoGO->box.w = tileMap_Tile16_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile16_Coluna_novoGO->box.h = tileMap_Tile16_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile16_Coluna_novoGO->AddComponent(tileMap_Tile16_Coluna_novo);
	objectArray.emplace_back(Tile16_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile17_Coluna_novoGO = new GameObject();
	Tile17_Coluna_novoGO->box.x = (69) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile17_Coluna_novoGO->box.y = (-21) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile17_Coluna_novo = new TileMap(*Tile17_Coluna_novoGO, "./assets/map/Tile17_Coluna_novo.txt", tileSet);
	tileMap_Tile17_Coluna_novo->colide = true;

	Tile17_Coluna_novoGO->box.w = tileMap_Tile17_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile17_Coluna_novoGO->box.h = tileMap_Tile17_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile17_Coluna_novoGO->AddComponent(tileMap_Tile17_Coluna_novo);
	objectArray.emplace_back(Tile17_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile18_Coluna_novoGO = new GameObject();
	Tile18_Coluna_novoGO->box.x = (70) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile18_Coluna_novoGO->box.y = (-16) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile18_Coluna_novo = new TileMap(*Tile18_Coluna_novoGO, "./assets/map/Tile18_Coluna_novo.txt", tileSet);
	tileMap_Tile18_Coluna_novo->colide = true;

	Tile18_Coluna_novoGO->box.w = tileMap_Tile18_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile18_Coluna_novoGO->box.h = tileMap_Tile18_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile18_Coluna_novoGO->AddComponent(tileMap_Tile18_Coluna_novo);
	objectArray.emplace_back(Tile18_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile19_Coluna_novoGO = new GameObject();
	Tile19_Coluna_novoGO->box.x = (74) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile19_Coluna_novoGO->box.y = (-16) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile19_Coluna_novo = new TileMap(*Tile19_Coluna_novoGO, "./assets/map/Tile19_Coluna_novo.txt", tileSet);
	tileMap_Tile19_Coluna_novo->colide = true;

	Tile19_Coluna_novoGO->box.w = tileMap_Tile19_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile19_Coluna_novoGO->box.h = tileMap_Tile19_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile19_Coluna_novoGO->AddComponent(tileMap_Tile19_Coluna_novo);
	objectArray.emplace_back(Tile19_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile20_Coluna_novoGO = new GameObject();
	Tile20_Coluna_novoGO->box.x = (75) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile20_Coluna_novoGO->box.y = (-19) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile20_Coluna_novo = new TileMap(*Tile20_Coluna_novoGO, "./assets/map/Tile20_Coluna_novo.txt", tileSet);
	tileMap_Tile20_Coluna_novo->colide = true;

	Tile20_Coluna_novoGO->box.w = tileMap_Tile20_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile20_Coluna_novoGO->box.h = tileMap_Tile20_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile20_Coluna_novoGO->AddComponent(tileMap_Tile20_Coluna_novo);
	objectArray.emplace_back(Tile20_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile21_Coluna_novoGO = new GameObject();
	Tile21_Coluna_novoGO->box.x = (83) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile21_Coluna_novoGO->box.y = (-19) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile21_Coluna_novo = new TileMap(*Tile21_Coluna_novoGO, "./assets/map/Tile21_Coluna_novo.txt", tileSet);
	tileMap_Tile21_Coluna_novo->colide = true;

	Tile21_Coluna_novoGO->box.w = tileMap_Tile21_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile21_Coluna_novoGO->box.h = tileMap_Tile21_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile21_Coluna_novoGO->AddComponent(tileMap_Tile21_Coluna_novo);
	objectArray.emplace_back(Tile21_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile22_Coluna_novoGO = new GameObject();
	Tile22_Coluna_novoGO->box.x = (88) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile22_Coluna_novoGO->box.y = (-29) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile22_Coluna_novo = new TileMap(*Tile22_Coluna_novoGO, "./assets/map/Tile22_Coluna_novo.txt", tileSet);
	tileMap_Tile22_Coluna_novo->colide = true;

	Tile22_Coluna_novoGO->box.w = tileMap_Tile22_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile22_Coluna_novoGO->box.h = tileMap_Tile22_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile22_Coluna_novoGO->AddComponent(tileMap_Tile22_Coluna_novo);
	objectArray.emplace_back(Tile22_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile23_Coluna_novoGO = new GameObject();
	Tile23_Coluna_novoGO->box.x = (95) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile23_Coluna_novoGO->box.y = (-29) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile23_Coluna_novo = new TileMap(*Tile23_Coluna_novoGO, "./assets/map/Tile23_Coluna_novo.txt", tileSet);
	tileMap_Tile23_Coluna_novo->colide = true;

	Tile23_Coluna_novoGO->box.w = tileMap_Tile23_Coluna_novo->GetWidth() * tileSet->GetTileWidth();
	Tile23_Coluna_novoGO->box.h = tileMap_Tile23_Coluna_novo->GetHeight() * tileSet->GetTileHeight();

	Tile23_Coluna_novoGO->AddComponent(tileMap_Tile23_Coluna_novo);
	objectArray.emplace_back(Tile23_Coluna_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile24_Linha_novoGO = new GameObject();
	Tile24_Linha_novoGO->box.x = (89) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile24_Linha_novoGO->box.y = (-29) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile24_Linha_novo = new TileMap(*Tile24_Linha_novoGO, "./assets/map/Tile24_Linha_novo.txt", tileSet);
	tileMap_Tile24_Linha_novo->colide = true;

	Tile24_Linha_novoGO->box.w = tileMap_Tile24_Linha_novo->GetWidth() * tileSet->GetTileWidth();
	Tile24_Linha_novoGO->box.h = tileMap_Tile24_Linha_novo->GetHeight() * tileSet->GetTileHeight();

	Tile24_Linha_novoGO->AddComponent(tileMap_Tile24_Linha_novo);
	objectArray.emplace_back(Tile24_Linha_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile25_Linha_novoGO = new GameObject();
	Tile25_Linha_novoGO->box.x = (62) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile25_Linha_novoGO->box.y = (-21) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile25_Linha_novo = new TileMap(*Tile25_Linha_novoGO, "./assets/map/Tile25_Linha_novo.txt", tileSet);
	tileMap_Tile25_Linha_novo->colide = true;

	Tile25_Linha_novoGO->box.w = tileMap_Tile25_Linha_novo->GetWidth() * tileSet->GetTileWidth();
	Tile25_Linha_novoGO->box.h = tileMap_Tile25_Linha_novo->GetHeight() * tileSet->GetTileHeight();

	Tile25_Linha_novoGO->AddComponent(tileMap_Tile25_Linha_novo);
	objectArray.emplace_back(Tile25_Linha_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile26_Linha_novoGO = new GameObject();
	Tile26_Linha_novoGO->box.x = (76) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile26_Linha_novoGO->box.y = (-19) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile26_Linha_novo = new TileMap(*Tile26_Linha_novoGO, "./assets/map/Tile26_Linha_novo.txt", tileSet);
	tileMap_Tile26_Linha_novo->colide = true;

	Tile26_Linha_novoGO->box.w = tileMap_Tile26_Linha_novo->GetWidth() * tileSet->GetTileWidth();
	Tile26_Linha_novoGO->box.h = tileMap_Tile26_Linha_novo->GetHeight() * tileSet->GetTileHeight();

	Tile26_Linha_novoGO->AddComponent(tileMap_Tile26_Linha_novo);
	objectArray.emplace_back(Tile26_Linha_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile27_Linha_novoGO = new GameObject();
	Tile27_Linha_novoGO->box.x = (51) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile27_Linha_novoGO->box.y = (-16) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile27_Linha_novo = new TileMap(*Tile27_Linha_novoGO, "./assets/map/Tile27_Linha_novo.txt", tileSet);
	tileMap_Tile27_Linha_novo->colide = true;

	Tile27_Linha_novoGO->box.w = tileMap_Tile27_Linha_novo->GetWidth() * tileSet->GetTileWidth();
	Tile27_Linha_novoGO->box.h = tileMap_Tile27_Linha_novo->GetHeight() * tileSet->GetTileHeight();

	Tile27_Linha_novoGO->AddComponent(tileMap_Tile27_Linha_novo);
	objectArray.emplace_back(Tile27_Linha_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile28_Linha_novoGO = new GameObject();
	Tile28_Linha_novoGO->box.x = (71) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile28_Linha_novoGO->box.y = (-16) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile28_Linha_novo = new TileMap(*Tile28_Linha_novoGO, "./assets/map/Tile28_Linha_novo.txt", tileSet);
	tileMap_Tile28_Linha_novo->colide = true;

	Tile28_Linha_novoGO->box.w = tileMap_Tile28_Linha_novo->GetWidth() * tileSet->GetTileWidth();
	Tile28_Linha_novoGO->box.h = tileMap_Tile28_Linha_novo->GetHeight() * tileSet->GetTileHeight();

	Tile28_Linha_novoGO->AddComponent(tileMap_Tile28_Linha_novo);
	objectArray.emplace_back(Tile28_Linha_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile29_Linha_novoGO = new GameObject();
	Tile29_Linha_novoGO->box.x = (34) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile29_Linha_novoGO->box.y = (-13) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile29_Linha_novo = new TileMap(*Tile29_Linha_novoGO, "./assets/map/Tile29_Linha_novo.txt", tileSet);
	tileMap_Tile29_Linha_novo->colide = true;

	Tile29_Linha_novoGO->box.w = tileMap_Tile29_Linha_novo->GetWidth() * tileSet->GetTileWidth();
	Tile29_Linha_novoGO->box.h = tileMap_Tile29_Linha_novo->GetHeight() * tileSet->GetTileHeight();

	Tile29_Linha_novoGO->AddComponent(tileMap_Tile29_Linha_novo);
	objectArray.emplace_back(Tile29_Linha_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto Tile30_Linha_novoGO = new GameObject();
	Tile30_Linha_novoGO->box.x = (44) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile30_Linha_novoGO->box.y = (-10) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile30_Linha_novo = new TileMap(*Tile30_Linha_novoGO, "./assets/map/Tile30_Linha_novo.txt", tileSet);
	tileMap_Tile30_Linha_novo->colide = true;

	Tile30_Linha_novoGO->box.w = tileMap_Tile30_Linha_novo->GetWidth() * tileSet->GetTileWidth();
	Tile30_Linha_novoGO->box.h = tileMap_Tile30_Linha_novo->GetHeight() * tileSet->GetTileHeight();

	Tile30_Linha_novoGO->AddComponent(tileMap_Tile30_Linha_novo);
	objectArray.emplace_back(Tile30_Linha_novoGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	*/
}

void GameState0::ChangePlayerHP() {
	int hp = player->GetHP();

	if (player->damaged) {
		switch (hp) {
		case 0:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_00.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 1:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_01.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 2:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_02.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 3:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_03.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 4:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_04.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 5:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_05.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 6:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_06.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 7:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_07.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 8:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_08.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 9:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_09.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 10:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_10.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 11:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_11.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 12:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_12.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 13:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_13.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 14:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_14.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 15:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_15.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 16:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_16.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 17:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_17.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 18:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_18.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 19:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_19.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 20:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_20.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 21:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_21.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 22:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/barra_de_HP/HP_22.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		default:
			break;
		}

		player->damaged = false;
	}
	
}


