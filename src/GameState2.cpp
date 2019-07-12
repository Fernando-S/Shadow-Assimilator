#include "GameState2.h"
#include "Game.h"
#include "GameData.h"


GameState2::GameState2() {
	playerGO = new GameObject();
	coatGuyGO = new GameObject();
	finalBossGO = new GameObject();
	escudoGO = new GameObject();
	chaoGO = new GameObject();
}

void GameState2::LoadAssets() {
	int i;

	/////////////////////////////////////////////
	//	  Carrega a Musica e aperta o play	  //
	///////////////////////////////////////////
	backgroundMusic = *new Music("./assets/audio/soundtrack/shadowboss.ogg");
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
	//		Carrega o Final BOSS	//
	/////////////////////////////////
	finalBoss = new FinalBoss(*finalBossGO);

	finalBossGO->AddComponent(finalBoss);
	finalBossGO->box.x = 100;
	finalBossGO->box.y = 800 - finalBossGO->box.h;
	objectArray.emplace_back(finalBossGO);


	///////////////////////////////////////////////
	//		Carrega o escudo do Final BOSS		//
	/////////////////////////////////////////////
	escudo = new Escudo(*escudoGO);

	escudoGO->AddComponent(escudo);
	escudoGO->box.x = 100;
	escudoGO->box.y = 800 - escudoGO->box.h;
	objectArray.emplace_back(escudoGO);


	///////////////////////////////////
	//		Carrega o CoatGuy		//
	/////////////////////////////////
	coatGuy = new CoatGuy(*coatGuyGO);

	coatGuyGO->AddComponent(coatGuy);
	coatGuyGO->box.x = 60 * ONETILESQUARE;
	coatGuyGO->box.y = 800 - coatGuyGO->box.h - 100;

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

void GameState2::Update(float dt){
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
	if (!Player::player) {
		GameData::playerVictory = false;
		popRequested = true;
		Game::GetInstance().Push(new EndState());
	}	// Tela de WIN
	/// todo - colocar uma condicao de vitoria
	else if (inputManager.KeyPress(BACKSPACE_KEY) || !FinalBoss::finalBoss) {
		GameData::playerVictory = true;
		popRequested = true;
		Game::GetInstance().Push(new EndState());
	}
	/*
	else if (inputManager.KeyPress(NUMPAD_NINE_KEY)) {
		popRequested = true;
		Game::GetInstance().Push(new GameState3());
	}
	*/
	
}

GameState2::~GameState2() {
	objectArray.clear();			// Esvazia o vetor de objetos
}

void GameState2::Render() {
	RenderArray();					// Renderiza cada GameObject no objectArray
}

void GameState2::Start() {
	LoadAssets();					// Carrega os assets a serem usados no jogo
	StartArray();					// Da Start em cada GameObject no objectArray
}

void GameState2::Pause() {

}

void GameState2::Resume() {

}

void GameState2::LoadLevel() {
	
	///////////////////////////////
	//		Carrega o Chao		//
	/////////////////////////////
	//auto tileSet = new TileSet(64, 64, "./assets/img/tilesaaaaa.png");
	//auto Chao = new TileMap(*chaoGO, "./assets/map/Tile31_Chao_pra_caralho.txt", tileSet);

	//auto tileSet = new TileSet(64, 64, "./assets/img/Level0/tile001.png");
	//auto Chao = new TileMap(*chaoGO, "./assets/map/Level0/TileMap_Chao.txt", tileSet);

	//auto tileSet = new TileSet(64, 64, "./assets/img/Level0/agora vai/tile003.png");
	auto Chao = new TileMap(*chaoGO, "./assets/map/Level0/TileMap_Chao1.txt", tileSet);

	Chao->colide = true;

	//chaoGO->box.w = Chao->GetWidth() * tileSet->GetTileWidth();
	//chaoGO->box.h = Chao->GetHeight() * tileSet->GetTileHeight();

	chaoGO->box.w = Chao->GetWidth() * tileSet->GetTileWidth();
	chaoGO->box.h = Chao->GetHeight() * tileSet->GetTileHeight();

	chaoGO->AddComponent(Chao);
	objectArray.emplace_back(chaoGO);
	
	///////////////////////////////
	//		MAXIMUM EFFORT		//
	/////////////////////////////
	/*
	auto Tile00_ColunaGO = new GameObject();
	Tile00_ColunaGO->box.x = (0) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile00_ColunaGO->box.y = (-21) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile00_Coluna = new TileMap(*Tile00_ColunaGO, "./assets/map/Level0/Tile00_Coluna.txt", tileSet);
	tileMap_Tile00_Coluna->colide = true;

	Tile00_ColunaGO->box.w = tileMap_Tile00_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile00_ColunaGO->box.h = tileMap_Tile00_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile00_ColunaGO->AddComponent(tileMap_Tile00_Coluna);
	objectArray.emplace_back(Tile00_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
	*/
	
}

void GameState2::ChangePlayerHP() {
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


