#include "GameState1.h"
#include "Game.h"
#include "GameData.h"


GameState1::GameState1() {
	playerGO = new GameObject();
	coatGuyGO = new GameObject();
	chaoGO = new GameObject();
}

void GameState1::LoadAssets() {
	int i;

	/////////////////////////////////////////////
	//	  Carrega a Musica e aperta o play	  //
	///////////////////////////////////////////
	//backgroundMusic = *new Music("./assets/audio/soundtrack/Shadow_Assimilator_-_Theme_1.mp3");
	//backgroundMusic = *new Music("./assets/audio/soundtrack/Shadow Assimilator track 1.ogg");
	//backgroundMusic.Play();

	
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
	tileSet = new TileSet(64, 64, "./assets/img/Level0/agora vai/tile003.png");

	/*

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
	*/
	
	// Teste do novo TileSet
	chaoGO->box.x = 0;
	chaoGO->box.y = 800;

	// Carrega os tiles que colidem
	LoadLevel();

	// Detalhes dos predios
	/*
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
	*/

	////////////////////////////////
	//	   Carrega o Ricardo	 //
	//////////////////////////////
	surpriseGO = new GameObject();
	auto surprise = new Sprite(*surpriseGO, "./assets/img/Ricardo.png");

	// Seta a escala e posiciona no centro da tela
	surprise->SetScale(0.53, 0.55);	// (resolution width / image width) * escala que queremos, (resolution height / image height) * escala que queremos
	surpriseGO->box.x = (Game::GetInstance().GetWidth() - surprise->GetWidth()) / 2;
	surpriseGO->box.y = (Game::GetInstance().GetHeight() - surprise->GetHeight()) / 2;

	surpriseGO->AddComponent(surprise);
	objectArray.emplace_back(surpriseGO);
	surpriseGO->render = false;


	///////////////////////////////////
	//		Carrega Final BOSS		//
	/////////////////////////////////
	/*
	auto finalBossGO = new GameObject();
	auto finalBoss = new FinalBoss(*finalBossGO);
	finalBossGO->AddComponent(finalBoss);
	finalBossGO->box.x = 800;
	finalBossGO->box.y = 800 - finalBossGO->box.h;
	objectArray.emplace_back(finalBossGO);
	*/

	///////////////////////////////////
	//		Carrega um Robo			//
	/////////////////////////////////
	/*
	auto robotGO = new GameObject();
	auto robot = new Robot(*robotGO);

	robotGO->AddComponent(robot);
	robotGO->box.x = 800;
	robotGO->box.y = 800 - robotGO->box.h;

	objectArray.emplace_back(robotGO);
	*/

	///////////////////////////////////
	//		Carrega o CoatGuy		//
	/////////////////////////////////
	//auto coatGuyGO = new GameObject();
	auto coatGuy = new CoatGuy(*coatGuyGO);

	coatGuyGO->AddComponent(coatGuy);
	coatGuyGO->box.x = 1200;
	coatGuyGO->box.y = 800 - coatGuyGO->box.h;

	objectArray.emplace_back(coatGuyGO);


	///////////////////////////////////
	//		Carrega a Personagem	//
	/////////////////////////////////
	player = new Player(*playerGO);

	playerGO->AddComponent(player);
	playerGO->box.x = 400;
	playerGO->box.y = 800 - playerGO->box.h;

	objectArray.emplace_back(playerGO);
	Camera::Follow(playerGO);			// Coloca a camera para seguir o Penguin


	///////////////////////
	//	  Barra de HP	//
	/////////////////////
	HPbarGO = new GameObject();
	HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_22.png");
	auto HPbarCamFollower = new CameraFollower(*HPbarGO);
	HPbarGO->AddComponent(HPbarCamFollower);

	HPbarGO->AddComponent(HPbarSprite);
	objectArray.emplace_back(HPbarGO);
	
}

void GameState1::Update(float dt){
	unsigned i, j;
	auto inputManager = InputManager::GetInstance();


	// Faz o update na camera e na box do mapa
	Camera::Update(dt);

	quitRequested = inputManager.QuitRequested();			// Seta o quitRequested ao fechar o jogo
	//if (inputManager.KeyPress(ESCAPE_KEY)) {
		//popRequested = true;
		//backgroundMusic.Stop();
	//}
	UpdateArray(dt);										// Faz o update de cada GameObject no objectArray

	
	if (playerGO->box.y + playerGO->box.h > 800) {
		playerGO->box.y = 800 - playerGO->box.h;
	}

	if (coatGuyGO->box.y + coatGuyGO->box.h > 800) {
		coatGuyGO->box.y = 800 - coatGuyGO->box.h;
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
	if (!Player::player && playerGO->IsDead()) {
		GameData::playerVictory = false;
		popRequested = true;
		Game::GetInstance().Push(new EndState());
	}
	// Tela de WIN
	/// todo - colocar uma condicao de vitoria
	else if (inputManager.KeyPress(BACKSPACE_KEY)) {
		GameData::playerVictory = true;
		popRequested = true;
		Game::GetInstance().Push(new EndState());
	}
	else if (inputManager.KeyPress(NUMPAD_NINE_KEY)) {
		popRequested = true;
		Game::GetInstance().Push(new GameState2());
	}
	
}

GameState1::~GameState1() {
	objectArray.clear();			// Esvazia o vetor de objetos
}

void GameState1::Render() {
	RenderArray();					// Renderiza cada GameObject no objectArray
}

void GameState1::Start() {
	LoadAssets();					// Carrega os assets a serem usados no jogo
	StartArray();					// Da Start em cada GameObject no objectArray
}

void GameState1::Pause() {

}

void GameState1::Resume() {

}

void GameState1::LoadLevel() {
	
	///////////////////////////////
	//		Carrega o Chao		//
	/////////////////////////////
	auto Chao = new TileMap(*chaoGO, "./assets/map/Level0/TileMap_Chao1.txt", tileSet);

	Chao->colide = true;

	//chaoGO->box.w = Chao->GetWidth() * tileSet->GetTileWidth();
	//chaoGO->box.h = Chao->GetHeight() * tileSet->GetTileHeight();

	chaoGO->box.w = Chao->GetWidth() * tileSet->GetTileWidth();
	chaoGO->box.h = Chao->GetHeight() * tileSet->GetTileHeight();

	chaoGO->AddComponent(Chao);
	//objectArray.emplace_back(chaoGO);
	

	///////////////////////////////
	//		MAXIMUM EFFORT		//
	/////////////////////////////
	auto telhadoGO = new GameObject();
	telhadoGO->box.x = (32) * tileSet->GetTileWidth()/* + chaoGO->box.x*/;
	telhadoGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Telhado = new TileMap(*telhadoGO, "./assets/map/Level1/TileMap_Telhado.txt", tileSet);
	tileMap_Telhado->colide = true;

	telhadoGO->box.w = tileMap_Telhado->GetWidth() * tileSet->GetTileWidth();
	telhadoGO->box.h = tileMap_Telhado->GetHeight() * tileSet->GetTileHeight();

	telhadoGO->AddComponent(tileMap_Telhado);
	objectArray.emplace_back(telhadoGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	/*
	auto Tile00_ColunaGO = new GameObject();
	Tile00_ColunaGO->box.x = (0) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile00_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile00_Coluna = new TileMap(*Tile00_ColunaGO, "./assets/map/Level1/Tile00_Coluna.txt", tileSet);
	tileMap_Tile00_Coluna->colide = true;

	Tile00_ColunaGO->box.w = tileMap_Tile00_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile00_ColunaGO->box.h = tileMap_Tile00_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile00_ColunaGO->AddComponent(tileMap_Tile00_Coluna);
	objectArray.emplace_back(Tile00_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile01_ColunaGO = new GameObject();
	Tile01_ColunaGO->box.x = (1) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile01_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile01_Coluna = new TileMap(*Tile01_ColunaGO, "./assets/map/Level1/Tile01_Coluna.txt", tileSet);
	tileMap_Tile01_Coluna->colide = true;

	Tile01_ColunaGO->box.w = tileMap_Tile01_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile01_ColunaGO->box.h = tileMap_Tile01_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile01_ColunaGO->AddComponent(tileMap_Tile01_Coluna);
	objectArray.emplace_back(Tile01_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile02_ColunaGO = new GameObject();
	Tile02_ColunaGO->box.x = (2) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile02_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile02_Coluna = new TileMap(*Tile02_ColunaGO, "./assets/map/Level1/Tile02_Coluna.txt", tileSet);
	tileMap_Tile02_Coluna->colide = true;

	Tile02_ColunaGO->box.w = tileMap_Tile02_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile02_ColunaGO->box.h = tileMap_Tile02_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile02_ColunaGO->AddComponent(tileMap_Tile02_Coluna);
	objectArray.emplace_back(Tile02_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile03_ColunaGO = new GameObject();
	Tile03_ColunaGO->box.x = (3) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile03_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile03_Coluna = new TileMap(*Tile03_ColunaGO, "./assets/map/Level1/Tile03_Coluna.txt", tileSet);
	tileMap_Tile03_Coluna->colide = true;

	Tile03_ColunaGO->box.w = tileMap_Tile03_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile03_ColunaGO->box.h = tileMap_Tile03_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile03_ColunaGO->AddComponent(tileMap_Tile03_Coluna);
	objectArray.emplace_back(Tile03_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile04_ColunaGO = new GameObject();
	Tile04_ColunaGO->box.x = (4) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile04_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile04_Coluna = new TileMap(*Tile04_ColunaGO, "./assets/map/Level1/Tile04_Coluna.txt", tileSet);
	tileMap_Tile04_Coluna->colide = true;

	Tile04_ColunaGO->box.w = tileMap_Tile04_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile04_ColunaGO->box.h = tileMap_Tile04_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile04_ColunaGO->AddComponent(tileMap_Tile04_Coluna);
	objectArray.emplace_back(Tile04_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile05_ColunaGO = new GameObject();
	Tile05_ColunaGO->box.x = (5) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile05_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile05_Coluna = new TileMap(*Tile05_ColunaGO, "./assets/map/Level1/Tile05_Coluna.txt", tileSet);
	tileMap_Tile05_Coluna->colide = true;

	Tile05_ColunaGO->box.w = tileMap_Tile05_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile05_ColunaGO->box.h = tileMap_Tile05_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile05_ColunaGO->AddComponent(tileMap_Tile05_Coluna);
	objectArray.emplace_back(Tile05_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile06_ColunaGO = new GameObject();
	Tile06_ColunaGO->box.x = (6) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile06_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile06_Coluna = new TileMap(*Tile06_ColunaGO, "./assets/map/Level1/Tile06_Coluna.txt", tileSet);
	tileMap_Tile06_Coluna->colide = true;

	Tile06_ColunaGO->box.w = tileMap_Tile06_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile06_ColunaGO->box.h = tileMap_Tile06_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile06_ColunaGO->AddComponent(tileMap_Tile06_Coluna);
	objectArray.emplace_back(Tile06_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile07_ColunaGO = new GameObject();
	Tile07_ColunaGO->box.x = (7) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile07_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile07_Coluna = new TileMap(*Tile07_ColunaGO, "./assets/map/Level1/Tile07_Coluna.txt", tileSet);
	tileMap_Tile07_Coluna->colide = true;

	Tile07_ColunaGO->box.w = tileMap_Tile07_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile07_ColunaGO->box.h = tileMap_Tile07_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile07_ColunaGO->AddComponent(tileMap_Tile07_Coluna);
	objectArray.emplace_back(Tile07_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile08_ColunaGO = new GameObject();
	Tile08_ColunaGO->box.x = (8) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile08_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile08_Coluna = new TileMap(*Tile08_ColunaGO, "./assets/map/Level1/Tile08_Coluna.txt", tileSet);
	tileMap_Tile08_Coluna->colide = true;

	Tile08_ColunaGO->box.w = tileMap_Tile08_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile08_ColunaGO->box.h = tileMap_Tile08_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile08_ColunaGO->AddComponent(tileMap_Tile08_Coluna);
	objectArray.emplace_back(Tile08_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile09_ColunaGO = new GameObject();
	Tile09_ColunaGO->box.x = (9) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile09_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile09_Coluna = new TileMap(*Tile09_ColunaGO, "./assets/map/Level1/Tile09_Coluna.txt", tileSet);
	tileMap_Tile09_Coluna->colide = true;

	Tile09_ColunaGO->box.w = tileMap_Tile09_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile09_ColunaGO->box.h = tileMap_Tile09_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile09_ColunaGO->AddComponent(tileMap_Tile09_Coluna);
	objectArray.emplace_back(Tile09_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile10_ColunaGO = new GameObject();
	Tile10_ColunaGO->box.x = (10) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile10_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile10_Coluna = new TileMap(*Tile10_ColunaGO, "./assets/map/Level1/Tile10_Coluna.txt", tileSet);
	tileMap_Tile10_Coluna->colide = true;

	Tile10_ColunaGO->box.w = tileMap_Tile10_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile10_ColunaGO->box.h = tileMap_Tile10_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile10_ColunaGO->AddComponent(tileMap_Tile10_Coluna);
	objectArray.emplace_back(Tile10_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile11_ColunaGO = new GameObject();
	Tile11_ColunaGO->box.x = (11) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile11_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile11_Coluna = new TileMap(*Tile11_ColunaGO, "./assets/map/Level1/Tile11_Coluna.txt", tileSet);
	tileMap_Tile11_Coluna->colide = true;

	Tile11_ColunaGO->box.w = tileMap_Tile11_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile11_ColunaGO->box.h = tileMap_Tile11_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile11_ColunaGO->AddComponent(tileMap_Tile11_Coluna);
	objectArray.emplace_back(Tile11_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile12_ColunaGO = new GameObject();
	Tile12_ColunaGO->box.x = (12) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile12_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile12_Coluna = new TileMap(*Tile12_ColunaGO, "./assets/map/Level1/Tile12_Coluna.txt", tileSet);
	tileMap_Tile12_Coluna->colide = true;

	Tile12_ColunaGO->box.w = tileMap_Tile12_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile12_ColunaGO->box.h = tileMap_Tile12_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile12_ColunaGO->AddComponent(tileMap_Tile12_Coluna);
	objectArray.emplace_back(Tile12_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile13_ColunaGO = new GameObject();
	Tile13_ColunaGO->box.x = (13) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile13_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile13_Coluna = new TileMap(*Tile13_ColunaGO, "./assets/map/Level1/Tile13_Coluna.txt", tileSet);
	tileMap_Tile13_Coluna->colide = true;

	Tile13_ColunaGO->box.w = tileMap_Tile13_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile13_ColunaGO->box.h = tileMap_Tile13_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile13_ColunaGO->AddComponent(tileMap_Tile13_Coluna);
	objectArray.emplace_back(Tile13_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile14_ColunaGO = new GameObject();
	Tile14_ColunaGO->box.x = (14) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile14_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile14_Coluna = new TileMap(*Tile14_ColunaGO, "./assets/map/Level1/Tile14_Coluna.txt", tileSet);
	tileMap_Tile14_Coluna->colide = true;

	Tile14_ColunaGO->box.w = tileMap_Tile14_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile14_ColunaGO->box.h = tileMap_Tile14_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile14_ColunaGO->AddComponent(tileMap_Tile14_Coluna);
	objectArray.emplace_back(Tile14_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile15_ColunaGO = new GameObject();
	Tile15_ColunaGO->box.x = (15) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile15_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile15_Coluna = new TileMap(*Tile15_ColunaGO, "./assets/map/Level1/Tile15_Coluna.txt", tileSet);
	tileMap_Tile15_Coluna->colide = true;

	Tile15_ColunaGO->box.w = tileMap_Tile15_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile15_ColunaGO->box.h = tileMap_Tile15_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile15_ColunaGO->AddComponent(tileMap_Tile15_Coluna);
	objectArray.emplace_back(Tile15_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile16_ColunaGO = new GameObject();
	Tile16_ColunaGO->box.x = (16) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile16_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile16_Coluna = new TileMap(*Tile16_ColunaGO, "./assets/map/Level1/Tile16_Coluna.txt", tileSet);
	tileMap_Tile16_Coluna->colide = true;

	Tile16_ColunaGO->box.w = tileMap_Tile16_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile16_ColunaGO->box.h = tileMap_Tile16_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile16_ColunaGO->AddComponent(tileMap_Tile16_Coluna);
	objectArray.emplace_back(Tile16_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile17_ColunaGO = new GameObject();
	Tile17_ColunaGO->box.x = (17) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile17_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile17_Coluna = new TileMap(*Tile17_ColunaGO, "./assets/map/Level1/Tile17_Coluna.txt", tileSet);
	tileMap_Tile17_Coluna->colide = true;

	Tile17_ColunaGO->box.w = tileMap_Tile17_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile17_ColunaGO->box.h = tileMap_Tile17_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile17_ColunaGO->AddComponent(tileMap_Tile17_Coluna);
	objectArray.emplace_back(Tile17_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile18_ColunaGO = new GameObject();
	Tile18_ColunaGO->box.x = (18) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile18_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile18_Coluna = new TileMap(*Tile18_ColunaGO, "./assets/map/Level1/Tile18_Coluna.txt", tileSet);
	tileMap_Tile18_Coluna->colide = true;

	Tile18_ColunaGO->box.w = tileMap_Tile18_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile18_ColunaGO->box.h = tileMap_Tile18_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile18_ColunaGO->AddComponent(tileMap_Tile18_Coluna);
	objectArray.emplace_back(Tile18_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile19_ColunaGO = new GameObject();
	Tile19_ColunaGO->box.x = (19) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile19_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile19_Coluna = new TileMap(*Tile19_ColunaGO, "./assets/map/Level1/Tile19_Coluna.txt", tileSet);
	tileMap_Tile19_Coluna->colide = true;

	Tile19_ColunaGO->box.w = tileMap_Tile19_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile19_ColunaGO->box.h = tileMap_Tile19_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile19_ColunaGO->AddComponent(tileMap_Tile19_Coluna);
	objectArray.emplace_back(Tile19_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile20_ColunaGO = new GameObject();
	Tile20_ColunaGO->box.x = (20) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile20_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile20_Coluna = new TileMap(*Tile20_ColunaGO, "./assets/map/Level1/Tile20_Coluna.txt", tileSet);
	tileMap_Tile20_Coluna->colide = true;

	Tile20_ColunaGO->box.w = tileMap_Tile20_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile20_ColunaGO->box.h = tileMap_Tile20_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile20_ColunaGO->AddComponent(tileMap_Tile20_Coluna);
	objectArray.emplace_back(Tile20_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile21_ColunaGO = new GameObject();
	Tile21_ColunaGO->box.x = (21) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile21_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile21_Coluna = new TileMap(*Tile21_ColunaGO, "./assets/map/Level1/Tile21_Coluna.txt", tileSet);
	tileMap_Tile21_Coluna->colide = true;

	Tile21_ColunaGO->box.w = tileMap_Tile21_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile21_ColunaGO->box.h = tileMap_Tile21_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile21_ColunaGO->AddComponent(tileMap_Tile21_Coluna);
	objectArray.emplace_back(Tile21_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile22_ColunaGO = new GameObject();
	Tile22_ColunaGO->box.x = (22) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile22_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile22_Coluna = new TileMap(*Tile22_ColunaGO, "./assets/map/Level1/Tile22_Coluna.txt", tileSet);
	tileMap_Tile22_Coluna->colide = true;

	Tile22_ColunaGO->box.w = tileMap_Tile22_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile22_ColunaGO->box.h = tileMap_Tile22_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile22_ColunaGO->AddComponent(tileMap_Tile22_Coluna);
	objectArray.emplace_back(Tile22_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile23_ColunaGO = new GameObject();
	Tile23_ColunaGO->box.x = (23) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile23_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile23_Coluna = new TileMap(*Tile23_ColunaGO, "./assets/map/Level1/Tile23_Coluna.txt", tileSet);
	tileMap_Tile23_Coluna->colide = true;

	Tile23_ColunaGO->box.w = tileMap_Tile23_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile23_ColunaGO->box.h = tileMap_Tile23_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile23_ColunaGO->AddComponent(tileMap_Tile23_Coluna);
	objectArray.emplace_back(Tile23_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile24_ColunaGO = new GameObject();
	Tile24_ColunaGO->box.x = (24) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile24_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile24_Coluna = new TileMap(*Tile24_ColunaGO, "./assets/map/Level1/Tile24_Coluna.txt", tileSet);
	tileMap_Tile24_Coluna->colide = true;

	Tile24_ColunaGO->box.w = tileMap_Tile24_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile24_ColunaGO->box.h = tileMap_Tile24_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile24_ColunaGO->AddComponent(tileMap_Tile24_Coluna);
	objectArray.emplace_back(Tile24_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile25_ColunaGO = new GameObject();
	Tile25_ColunaGO->box.x = (25) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile25_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile25_Coluna = new TileMap(*Tile25_ColunaGO, "./assets/map/Level1/Tile25_Coluna.txt", tileSet);
	tileMap_Tile25_Coluna->colide = true;

	Tile25_ColunaGO->box.w = tileMap_Tile25_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile25_ColunaGO->box.h = tileMap_Tile25_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile25_ColunaGO->AddComponent(tileMap_Tile25_Coluna);
	objectArray.emplace_back(Tile25_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile26_ColunaGO = new GameObject();
	Tile26_ColunaGO->box.x = (26) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile26_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile26_Coluna = new TileMap(*Tile26_ColunaGO, "./assets/map/Level1/Tile26_Coluna.txt", tileSet);
	tileMap_Tile26_Coluna->colide = true;

	Tile26_ColunaGO->box.w = tileMap_Tile26_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile26_ColunaGO->box.h = tileMap_Tile26_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile26_ColunaGO->AddComponent(tileMap_Tile26_Coluna);
	objectArray.emplace_back(Tile26_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile27_ColunaGO = new GameObject();
	Tile27_ColunaGO->box.x = (27) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile27_ColunaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile27_Coluna = new TileMap(*Tile27_ColunaGO, "./assets/map/Level1/Tile27_Coluna.txt", tileSet);
	tileMap_Tile27_Coluna->colide = true;

	Tile27_ColunaGO->box.w = tileMap_Tile27_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile27_ColunaGO->box.h = tileMap_Tile27_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile27_ColunaGO->AddComponent(tileMap_Tile27_Coluna);
	objectArray.emplace_back(Tile27_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile28_ColunaGO = new GameObject();
	Tile28_ColunaGO->box.x = (32) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile28_ColunaGO->box.y = (-4) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile28_Coluna = new TileMap(*Tile28_ColunaGO, "./assets/map/Level1/Tile28_Coluna.txt", tileSet);
	tileMap_Tile28_Coluna->colide = true;

	Tile28_ColunaGO->box.w = tileMap_Tile28_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile28_ColunaGO->box.h = tileMap_Tile28_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile28_ColunaGO->AddComponent(tileMap_Tile28_Coluna);
	objectArray.emplace_back(Tile28_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile29_ColunaGO = new GameObject();
	Tile29_ColunaGO->box.x = (33) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile29_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile29_Coluna = new TileMap(*Tile29_ColunaGO, "./assets/map/Level1/Tile29_Coluna.txt", tileSet);
	tileMap_Tile29_Coluna->colide = true;

	Tile29_ColunaGO->box.w = tileMap_Tile29_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile29_ColunaGO->box.h = tileMap_Tile29_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile29_ColunaGO->AddComponent(tileMap_Tile29_Coluna);
	objectArray.emplace_back(Tile29_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile30_ColunaGO = new GameObject();
	Tile30_ColunaGO->box.x = (34) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile30_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile30_Coluna = new TileMap(*Tile30_ColunaGO, "./assets/map/Level1/Tile30_Coluna.txt", tileSet);
	tileMap_Tile30_Coluna->colide = true;

	Tile30_ColunaGO->box.w = tileMap_Tile30_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile30_ColunaGO->box.h = tileMap_Tile30_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile30_ColunaGO->AddComponent(tileMap_Tile30_Coluna);
	objectArray.emplace_back(Tile30_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile31_ColunaGO = new GameObject();
	Tile31_ColunaGO->box.x = (35) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile31_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile31_Coluna = new TileMap(*Tile31_ColunaGO, "./assets/map/Level1/Tile31_Coluna.txt", tileSet);
	tileMap_Tile31_Coluna->colide = true;

	Tile31_ColunaGO->box.w = tileMap_Tile31_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile31_ColunaGO->box.h = tileMap_Tile31_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile31_ColunaGO->AddComponent(tileMap_Tile31_Coluna);
	objectArray.emplace_back(Tile31_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile32_ColunaGO = new GameObject();
	Tile32_ColunaGO->box.x = (36) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile32_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile32_Coluna = new TileMap(*Tile32_ColunaGO, "./assets/map/Level1/Tile32_Coluna.txt", tileSet);
	tileMap_Tile32_Coluna->colide = true;

	Tile32_ColunaGO->box.w = tileMap_Tile32_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile32_ColunaGO->box.h = tileMap_Tile32_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile32_ColunaGO->AddComponent(tileMap_Tile32_Coluna);
	objectArray.emplace_back(Tile32_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile33_ColunaGO = new GameObject();
	Tile33_ColunaGO->box.x = (37) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile33_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile33_Coluna = new TileMap(*Tile33_ColunaGO, "./assets/map/Level1/Tile33_Coluna.txt", tileSet);
	tileMap_Tile33_Coluna->colide = true;

	Tile33_ColunaGO->box.w = tileMap_Tile33_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile33_ColunaGO->box.h = tileMap_Tile33_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile33_ColunaGO->AddComponent(tileMap_Tile33_Coluna);
	objectArray.emplace_back(Tile33_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile34_ColunaGO = new GameObject();
	Tile34_ColunaGO->box.x = (38) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile34_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile34_Coluna = new TileMap(*Tile34_ColunaGO, "./assets/map/Level1/Tile34_Coluna.txt", tileSet);
	tileMap_Tile34_Coluna->colide = true;

	Tile34_ColunaGO->box.w = tileMap_Tile34_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile34_ColunaGO->box.h = tileMap_Tile34_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile34_ColunaGO->AddComponent(tileMap_Tile34_Coluna);
	objectArray.emplace_back(Tile34_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile35_ColunaGO = new GameObject();
	Tile35_ColunaGO->box.x = (39) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile35_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile35_Coluna = new TileMap(*Tile35_ColunaGO, "./assets/map/Level1/Tile35_Coluna.txt", tileSet);
	tileMap_Tile35_Coluna->colide = true;

	Tile35_ColunaGO->box.w = tileMap_Tile35_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile35_ColunaGO->box.h = tileMap_Tile35_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile35_ColunaGO->AddComponent(tileMap_Tile35_Coluna);
	objectArray.emplace_back(Tile35_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile36_ColunaGO = new GameObject();
	Tile36_ColunaGO->box.x = (40) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile36_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile36_Coluna = new TileMap(*Tile36_ColunaGO, "./assets/map/Level1/Tile36_Coluna.txt", tileSet);
	tileMap_Tile36_Coluna->colide = true;

	Tile36_ColunaGO->box.w = tileMap_Tile36_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile36_ColunaGO->box.h = tileMap_Tile36_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile36_ColunaGO->AddComponent(tileMap_Tile36_Coluna);
	objectArray.emplace_back(Tile36_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile37_ColunaGO = new GameObject();
	Tile37_ColunaGO->box.x = (41) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile37_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile37_Coluna = new TileMap(*Tile37_ColunaGO, "./assets/map/Level1/Tile37_Coluna.txt", tileSet);
	tileMap_Tile37_Coluna->colide = true;

	Tile37_ColunaGO->box.w = tileMap_Tile37_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile37_ColunaGO->box.h = tileMap_Tile37_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile37_ColunaGO->AddComponent(tileMap_Tile37_Coluna);
	objectArray.emplace_back(Tile37_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile38_ColunaGO = new GameObject();
	Tile38_ColunaGO->box.x = (42) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile38_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile38_Coluna = new TileMap(*Tile38_ColunaGO, "./assets/map/Level1/Tile38_Coluna.txt", tileSet);
	tileMap_Tile38_Coluna->colide = true;

	Tile38_ColunaGO->box.w = tileMap_Tile38_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile38_ColunaGO->box.h = tileMap_Tile38_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile38_ColunaGO->AddComponent(tileMap_Tile38_Coluna);
	objectArray.emplace_back(Tile38_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile39_ColunaGO = new GameObject();
	Tile39_ColunaGO->box.x = (43) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile39_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile39_Coluna = new TileMap(*Tile39_ColunaGO, "./assets/map/Level1/Tile39_Coluna.txt", tileSet);
	tileMap_Tile39_Coluna->colide = true;

	Tile39_ColunaGO->box.w = tileMap_Tile39_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile39_ColunaGO->box.h = tileMap_Tile39_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile39_ColunaGO->AddComponent(tileMap_Tile39_Coluna);
	objectArray.emplace_back(Tile39_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile40_ColunaGO = new GameObject();
	Tile40_ColunaGO->box.x = (44) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile40_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile40_Coluna = new TileMap(*Tile40_ColunaGO, "./assets/map/Level1/Tile40_Coluna.txt", tileSet);
	tileMap_Tile40_Coluna->colide = true;

	Tile40_ColunaGO->box.w = tileMap_Tile40_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile40_ColunaGO->box.h = tileMap_Tile40_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile40_ColunaGO->AddComponent(tileMap_Tile40_Coluna);
	objectArray.emplace_back(Tile40_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile41_ColunaGO = new GameObject();
	Tile41_ColunaGO->box.x = (45) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile41_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile41_Coluna = new TileMap(*Tile41_ColunaGO, "./assets/map/Level1/Tile41_Coluna.txt", tileSet);
	tileMap_Tile41_Coluna->colide = true;

	Tile41_ColunaGO->box.w = tileMap_Tile41_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile41_ColunaGO->box.h = tileMap_Tile41_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile41_ColunaGO->AddComponent(tileMap_Tile41_Coluna);
	objectArray.emplace_back(Tile41_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile42_ColunaGO = new GameObject();
	Tile42_ColunaGO->box.x = (46) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile42_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile42_Coluna = new TileMap(*Tile42_ColunaGO, "./assets/map/Level1/Tile42_Coluna.txt", tileSet);
	tileMap_Tile42_Coluna->colide = true;

	Tile42_ColunaGO->box.w = tileMap_Tile42_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile42_ColunaGO->box.h = tileMap_Tile42_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile42_ColunaGO->AddComponent(tileMap_Tile42_Coluna);
	objectArray.emplace_back(Tile42_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile43_ColunaGO = new GameObject();
	Tile43_ColunaGO->box.x = (47) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile43_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile43_Coluna = new TileMap(*Tile43_ColunaGO, "./assets/map/Level1/Tile43_Coluna.txt", tileSet);
	tileMap_Tile43_Coluna->colide = true;

	Tile43_ColunaGO->box.w = tileMap_Tile43_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile43_ColunaGO->box.h = tileMap_Tile43_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile43_ColunaGO->AddComponent(tileMap_Tile43_Coluna);
	objectArray.emplace_back(Tile43_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile44_ColunaGO = new GameObject();
	Tile44_ColunaGO->box.x = (48) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile44_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile44_Coluna = new TileMap(*Tile44_ColunaGO, "./assets/map/Level1/Tile44_Coluna.txt", tileSet);
	tileMap_Tile44_Coluna->colide = true;

	Tile44_ColunaGO->box.w = tileMap_Tile44_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile44_ColunaGO->box.h = tileMap_Tile44_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile44_ColunaGO->AddComponent(tileMap_Tile44_Coluna);
	objectArray.emplace_back(Tile44_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile45_ColunaGO = new GameObject();
	Tile45_ColunaGO->box.x = (49) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile45_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile45_Coluna = new TileMap(*Tile45_ColunaGO, "./assets/map/Level1/Tile45_Coluna.txt", tileSet);
	tileMap_Tile45_Coluna->colide = true;

	Tile45_ColunaGO->box.w = tileMap_Tile45_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile45_ColunaGO->box.h = tileMap_Tile45_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile45_ColunaGO->AddComponent(tileMap_Tile45_Coluna);
	objectArray.emplace_back(Tile45_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile46_ColunaGO = new GameObject();
	Tile46_ColunaGO->box.x = (50) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile46_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile46_Coluna = new TileMap(*Tile46_ColunaGO, "./assets/map/Level1/Tile46_Coluna.txt", tileSet);
	tileMap_Tile46_Coluna->colide = true;

	Tile46_ColunaGO->box.w = tileMap_Tile46_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile46_ColunaGO->box.h = tileMap_Tile46_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile46_ColunaGO->AddComponent(tileMap_Tile46_Coluna);
	objectArray.emplace_back(Tile46_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile47_ColunaGO = new GameObject();
	Tile47_ColunaGO->box.x = (51) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile47_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile47_Coluna = new TileMap(*Tile47_ColunaGO, "./assets/map/Level1/Tile47_Coluna.txt", tileSet);
	tileMap_Tile47_Coluna->colide = true;

	Tile47_ColunaGO->box.w = tileMap_Tile47_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile47_ColunaGO->box.h = tileMap_Tile47_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile47_ColunaGO->AddComponent(tileMap_Tile47_Coluna);
	objectArray.emplace_back(Tile47_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile48_ColunaGO = new GameObject();
	Tile48_ColunaGO->box.x = (52) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile48_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile48_Coluna = new TileMap(*Tile48_ColunaGO, "./assets/map/Level1/Tile48_Coluna.txt", tileSet);
	tileMap_Tile48_Coluna->colide = true;

	Tile48_ColunaGO->box.w = tileMap_Tile48_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile48_ColunaGO->box.h = tileMap_Tile48_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile48_ColunaGO->AddComponent(tileMap_Tile48_Coluna);
	objectArray.emplace_back(Tile48_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile49_ColunaGO = new GameObject();
	Tile49_ColunaGO->box.x = (53) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile49_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile49_Coluna = new TileMap(*Tile49_ColunaGO, "./assets/map/Level1/Tile49_Coluna.txt", tileSet);
	tileMap_Tile49_Coluna->colide = true;

	Tile49_ColunaGO->box.w = tileMap_Tile49_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile49_ColunaGO->box.h = tileMap_Tile49_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile49_ColunaGO->AddComponent(tileMap_Tile49_Coluna);
	objectArray.emplace_back(Tile49_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile50_ColunaGO = new GameObject();
	Tile50_ColunaGO->box.x = (54) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile50_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile50_Coluna = new TileMap(*Tile50_ColunaGO, "./assets/map/Level1/Tile50_Coluna.txt", tileSet);
	tileMap_Tile50_Coluna->colide = true;

	Tile50_ColunaGO->box.w = tileMap_Tile50_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile50_ColunaGO->box.h = tileMap_Tile50_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile50_ColunaGO->AddComponent(tileMap_Tile50_Coluna);
	objectArray.emplace_back(Tile50_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile51_ColunaGO = new GameObject();
	Tile51_ColunaGO->box.x = (55) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile51_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile51_Coluna = new TileMap(*Tile51_ColunaGO, "./assets/map/Level1/Tile51_Coluna.txt", tileSet);
	tileMap_Tile51_Coluna->colide = true;

	Tile51_ColunaGO->box.w = tileMap_Tile51_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile51_ColunaGO->box.h = tileMap_Tile51_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile51_ColunaGO->AddComponent(tileMap_Tile51_Coluna);
	objectArray.emplace_back(Tile51_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile52_ColunaGO = new GameObject();
	Tile52_ColunaGO->box.x = (56) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile52_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile52_Coluna = new TileMap(*Tile52_ColunaGO, "./assets/map/Level1/Tile52_Coluna.txt", tileSet);
	tileMap_Tile52_Coluna->colide = true;

	Tile52_ColunaGO->box.w = tileMap_Tile52_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile52_ColunaGO->box.h = tileMap_Tile52_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile52_ColunaGO->AddComponent(tileMap_Tile52_Coluna);
	objectArray.emplace_back(Tile52_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile53_ColunaGO = new GameObject();
	Tile53_ColunaGO->box.x = (57) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile53_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile53_Coluna = new TileMap(*Tile53_ColunaGO, "./assets/map/Level1/Tile53_Coluna.txt", tileSet);
	tileMap_Tile53_Coluna->colide = true;

	Tile53_ColunaGO->box.w = tileMap_Tile53_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile53_ColunaGO->box.h = tileMap_Tile53_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile53_ColunaGO->AddComponent(tileMap_Tile53_Coluna);
	objectArray.emplace_back(Tile53_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile54_ColunaGO = new GameObject();
	Tile54_ColunaGO->box.x = (58) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile54_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile54_Coluna = new TileMap(*Tile54_ColunaGO, "./assets/map/Level1/Tile54_Coluna.txt", tileSet);
	tileMap_Tile54_Coluna->colide = true;

	Tile54_ColunaGO->box.w = tileMap_Tile54_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile54_ColunaGO->box.h = tileMap_Tile54_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile54_ColunaGO->AddComponent(tileMap_Tile54_Coluna);
	objectArray.emplace_back(Tile54_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile55_ColunaGO = new GameObject();
	Tile55_ColunaGO->box.x = (59) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile55_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile55_Coluna = new TileMap(*Tile55_ColunaGO, "./assets/map/Level1/Tile55_Coluna.txt", tileSet);
	tileMap_Tile55_Coluna->colide = true;

	Tile55_ColunaGO->box.w = tileMap_Tile55_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile55_ColunaGO->box.h = tileMap_Tile55_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile55_ColunaGO->AddComponent(tileMap_Tile55_Coluna);
	objectArray.emplace_back(Tile55_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile56_ColunaGO = new GameObject();
	Tile56_ColunaGO->box.x = (60) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile56_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile56_Coluna = new TileMap(*Tile56_ColunaGO, "./assets/map/Level1/Tile56_Coluna.txt", tileSet);
	tileMap_Tile56_Coluna->colide = true;

	Tile56_ColunaGO->box.w = tileMap_Tile56_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile56_ColunaGO->box.h = tileMap_Tile56_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile56_ColunaGO->AddComponent(tileMap_Tile56_Coluna);
	objectArray.emplace_back(Tile56_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile57_ColunaGO = new GameObject();
	Tile57_ColunaGO->box.x = (61) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile57_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile57_Coluna = new TileMap(*Tile57_ColunaGO, "./assets/map/Level1/Tile57_Coluna.txt", tileSet);
	tileMap_Tile57_Coluna->colide = true;

	Tile57_ColunaGO->box.w = tileMap_Tile57_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile57_ColunaGO->box.h = tileMap_Tile57_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile57_ColunaGO->AddComponent(tileMap_Tile57_Coluna);
	objectArray.emplace_back(Tile57_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile58_ColunaGO = new GameObject();
	Tile58_ColunaGO->box.x = (62) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile58_ColunaGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile58_Coluna = new TileMap(*Tile58_ColunaGO, "./assets/map/Level1/Tile58_Coluna.txt", tileSet);
	tileMap_Tile58_Coluna->colide = true;

	Tile58_ColunaGO->box.w = tileMap_Tile58_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile58_ColunaGO->box.h = tileMap_Tile58_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile58_ColunaGO->AddComponent(tileMap_Tile58_Coluna);
	objectArray.emplace_back(Tile58_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile59_ColunaGO = new GameObject();
	Tile59_ColunaGO->box.x = (63) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile59_ColunaGO->box.y = (-4) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile59_Coluna = new TileMap(*Tile59_ColunaGO, "./assets/map/Level1/Tile59_Coluna.txt", tileSet);
	tileMap_Tile59_Coluna->colide = true;

	Tile59_ColunaGO->box.w = tileMap_Tile59_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile59_ColunaGO->box.h = tileMap_Tile59_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile59_ColunaGO->AddComponent(tileMap_Tile59_Coluna);
	objectArray.emplace_back(Tile59_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
	*/



	
	
}

void GameState1::ChangePlayerHP() {
	int hp = player->GetHP();

	if (player->damaged) {
		switch (hp) {
		case 0:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_00.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 1:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_01.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 2:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_02.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 3:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_03.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 4:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_04.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 5:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_05.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 6:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_06.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 7:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_07.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 8:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_08.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 9:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_09.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 10:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_10.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 11:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_11.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 12:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_12.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 13:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_13.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 14:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_14.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 15:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_15.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 16:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_16.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 17:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_17.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 18:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_18.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 19:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_19.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 20:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_20.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 21:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_21.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		case 22:
			HPbarGO->RemoveComponent(HPbarSprite);
			HPbarSprite = new Sprite(*HPbarGO, "./assets/img/Protagonista/barra_de_HP/HP_22.png");
			HPbarGO->AddComponent(HPbarSprite);
			break;

		default:
			break;
		}

		player->damaged = false;
	}
	
}


