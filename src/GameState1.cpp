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
	backgroundMusic = *new Music("./assets/audio/soundtrack/shadow miniboss.ogg");
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

	//Background de detalhe
	/*
	auto bgDetalheGO = new GameObject();
	auto bgDetalhe = new Sprite(*bgDetalheGO, "./assets/img/Level1/objeto_mapa2.png");

	// Seta a escala e posiciona no centro da tela
	//bg->SetScale(1.3333, 1.42);	// (resolution width / image width) * escala que queremos, (resolution height / image height) * escala que queremos

	//auto bgCamFollower = new CameraFollower(*bgDetalheGO);
	//bgDetalheGO->AddComponent(bgCamFollower);


	bgDetalheGO->box.h = bgDetalhe->GetHeight();
	bgDetalheGO->box.w = bgDetalhe->GetWidth();

	bgDetalheGO->AddComponent(bgDetalhe);
	objectArray.emplace_back(bgDetalheGO);
	*/


	///////////////////////////////////////////////////
	//		Carrega os Predios de Background		//
	/////////////////////////////////////////////////
	tileSet = new TileSet(64, 64, "./assets/img/tile003.png");

	auto predioGO = new GameObject();
	auto TileMap_Predio = new TileMap(*predioGO, "./assets/map/Level1/Mapa_2.txt", tileSet);

	TileMap_Predio->colide = false;

	predioGO->box.x = 35 * ONETILESQUARE;
	predioGO->box.y = 800 - 32 * ONETILESQUARE;
	predioGO->box.w = TileMap_Predio->GetWidth() * tileSet->GetTileWidth();
	predioGO->box.h = TileMap_Predio->GetHeight() * tileSet->GetTileHeight();

	predioGO->AddComponent(TileMap_Predio);
	objectArray.emplace_back(predioGO);


	// Teste do novo TileSet
	chaoGO->box.x = 0;
	chaoGO->box.y = 800;

	// Carrega os tiles que colidem
	LoadLevel();

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
	//		Carrega o CoatGuy		//
	/////////////////////////////////
	//auto coatGuyGO = new GameObject();
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
	playerGO->box.x = 33 * ONETILESQUARE;
	playerGO->box.y = 800 - playerGO->box.h - 100;

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


	///////////////////////////////////
	//	  Barra de HP do Coat Guy	//
	/////////////////////////////////

	HPbarCoatGuyGO = new GameObject();
	HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_28.png");

	HPbarCoatGuyGO->initialX = Game::GetInstance().GetWidth() - HPbarCoatGuySprite->GetWidth();

	auto HPbarCoatGuyCamFollower = new CameraFollower(*HPbarCoatGuyGO);
	HPbarCoatGuyGO->AddComponent(HPbarCoatGuyCamFollower);

	HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
	objectArray.emplace_back(HPbarCoatGuyGO);

	/////////////////////////////////////////////////////////////////////////////////////
	//ICONES//
	/////////////////////////////////////////////////////////////////////////////////////
	///////////////
	//CURA
	///////////////
	CuraGO = new GameObject();
	CuraSprite = new Sprite(*CuraGO, "./assets/img/Protagonista/icones/icone_cura.png");

	CuraGO->initialX = HPbarGO->box.Center().x + 7.8;
	CuraGO->initialY = HPbarGO->box.Center().y + 17;
	auto CuraCamFollower = new CameraFollower(*CuraGO);
	CuraGO->AddComponent(CuraCamFollower);

	CuraGO->AddComponent(CuraSprite);
	objectArray.emplace_back(CuraGO);
	/////////////

	///////////////
	//ATAQUE FORTE
	///////////////
	AtkFortGO = new GameObject();

	//if (SetAtkForte == true) {
		AtkFortSprite = new Sprite(*AtkFortGO, "./assets/img/Protagonista/icones/icone_ark_forte.png");
	//}
	//else {
		//AtkFortSprite = new Sprite(*AtkFortGO, "./assets/img/Protagonista/icones/icone_ark_forte2.png");
	//}

	AtkFortGO->initialX = HPbarGO->box.Center().x + 35.5;
	AtkFortGO->initialY = HPbarGO->box.Center().y + 17;
	auto AtkFortCamFollower = new CameraFollower(*AtkFortGO);
	AtkFortGO->AddComponent(AtkFortCamFollower);

	AtkFortGO->AddComponent(AtkFortSprite);
	objectArray.emplace_back(AtkFortGO);
	///////////////

	////////////////////
	//ATAQUE A DISTANCIA
	////////////////////
	AtkDistGO = new GameObject();

	//if (SetAtkDist == true) {
		AtkDistSprite = new Sprite(*AtkDistGO, "./assets/img/Protagonista/icones/icone_atk_distancia.png");
	//}
	//else {
		//AtkDistSprite = new Sprite(*AtkDistGO, "./assets/img/Protagonista/icones/icone_atk_distancia2.png");
	//}

	AtkDistGO->initialX = HPbarGO->box.Center().x + 63.2;
	AtkDistGO->initialY = HPbarGO->box.Center().y + 17;
	auto AtkDistCamFollower = new CameraFollower(*AtkDistGO);
	AtkDistGO->AddComponent(AtkDistCamFollower);

	AtkDistGO->AddComponent(AtkDistSprite);
	objectArray.emplace_back(AtkDistGO);
	//////////////////

	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////

}

void GameState1::Update(float dt) {
	unsigned i, j;
	auto inputManager = InputManager::GetInstance();

	playerHitTimer.Update(dt);
	coatGuyHitTimer.Update(dt);


	// Faz o update na camera e na box do mapa
	Camera::Update(dt);

	quitRequested = inputManager.QuitRequested();			// Seta o quitRequested ao fechar o jogo
	//if (inputManager.KeyPress(ESCAPE_KEY)) {
		//popRequested = true;
		//backgroundMusic.Stop();
	//}
	UpdateArray(dt);										// Faz o update de cada GameObject no objectArray

	
	if (playerGO->box.y + playerGO->box.h > 800) {
		playerGO->RequestDelete();
	}
	
	/*
	if (coatGuyGO->box.y + coatGuyGO->box.h > 800) {
		coatGuyGO->box.y = 800 - coatGuyGO->box.h;
	}
	*/
	/*if (playerGO->box.x < 10) {
		playerGO->box.x = 10;
	}
	*/
	/*
	if (playerGO->box.x + playerGO->box.w > 71 * ONETILESQUARE) {
		playerGO->box.x = 71 * ONETILESQUARE - playerGO->box.w;
	}
	*/
	/*
	if (playerGO->box.y  >  * ONETILESQUARE) {
		playerGO->box.x = 64 * ONETILESQUARE - playerGO->box.w;
	}
	*/


	// Reseta o contador para piscar a personagem
	if (player->damaged) {
		playerHitTimer.Restart();
	}

	// Reseta o contador para piscar o coatGuy
	if (coatGuy->damaged) {
		coatGuyHitTimer.Restart();
		//coatGuy->damaged = false;
	}

	ChangePlayerHP();
	ChangeCoatGuyHP();

	// Pisca o jogador
	if (player->gotHit) {
		if (playerHitTimer.Get() > 1.0) {
			playerGO->render = true;
			player->gotHit = false;
		}
		else if (playerHitTimer.Get() > 0.9) {
			playerGO->render = false;
		}
		else if (playerHitTimer.Get() > 0.8) {
			playerGO->render = true;
		}
		else if (playerHitTimer.Get() > 0.7) {
			playerGO->render = false;
		}
		else if (playerHitTimer.Get() > 0.6) {
			playerGO->render = true;
		}
		else if (playerHitTimer.Get() > 0.5) {
			playerGO->render = false;
		}
		else if (playerHitTimer.Get() > 0.4) {
			playerGO->render = true;
		}
		else if (playerHitTimer.Get() > 0.3) {
			playerGO->render = false;
		}
		else if (playerHitTimer.Get() > 0.2) {
			playerGO->render = true;
		}
		else if (playerHitTimer.Get() > 0.1) {
			playerGO->render = false;
		}
	}

	// Pisca o coatGuy
	if (coatGuy->gotHit) {
		if (coatGuyHitTimer.Get() > 1.0) {
			coatGuyGO->render = true;
			coatGuy->gotHit = false;
		}
		else if (coatGuyHitTimer.Get() > 0.9) {
			coatGuyGO->render = false;
		}
		else if (coatGuyHitTimer.Get() > 0.8) {
			coatGuyGO->render = true;
		}
		else if (coatGuyHitTimer.Get() > 0.7) {
			coatGuyGO->render = false;
		}
		else if (coatGuyHitTimer.Get() > 0.6) {
			coatGuyGO->render = true;
		}
		else if (coatGuyHitTimer.Get() > 0.5) {
			coatGuyGO->render = false;
		}
		else if (coatGuyHitTimer.Get() > 0.4) {
			coatGuyGO->render = true;
		}
		else if (coatGuyHitTimer.Get() > 0.3) {
			coatGuyGO->render = false;
		}
		else if (coatGuyHitTimer.Get() > 0.2) {
			coatGuyGO->render = true;
		}
		else if (coatGuyHitTimer.Get() > 0.1) {
			coatGuyGO->render = false;
		}
	}

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
		if ((inputManager.KeyRelease(TWO_KEY) || inputManager.KeyRelease(NUMPAD_TWO_KEY)) && !dois) {
			dois = true;
			tres = quatro = cinco = meia = sete = oito = false;
		}
		if ((inputManager.KeyRelease(THREE_KEY) || inputManager.KeyRelease(NUMPAD_THREE_KEY)) && dois) {
			tres = true;
			dois = quatro = cinco = meia = sete = oito = false;
		}
		if ((inputManager.KeyRelease(FOUR_KEY) || inputManager.KeyRelease(NUMPAD_FOUR_KEY)) && tres) {
			quatro = true;
			dois = tres = cinco = meia = sete = oito = false;
		}
		if ((inputManager.KeyRelease(FIVE_KEY) || inputManager.KeyRelease(NUMPAD_FIVE_KEY)) && quatro) {
			cinco = true;
			dois = tres = quatro = meia = sete = oito = false;
		}
		if ((inputManager.KeyRelease(SIX_KEY) || inputManager.KeyRelease(NUMPAD_SIX_KEY)) && cinco) {
			meia = true;
			dois = tres = quatro = cinco = sete = oito = false;
		}
		if ((inputManager.KeyRelease(SEVEN_KEY) || inputManager.KeyRelease(NUMPAD_SEVEN_KEY)) && meia) {
			sete = true;
			dois = tres = quatro = cinco = meia = oito = false;
		}
		if ((inputManager.KeyRelease(EIGHT_KEY) || inputManager.KeyRelease(NUMPAD_EIGHT_KEY)) && sete) {
			oito = true;
			dois = tres = quatro = cinco = meia = sete = false;
		}

		if (oito && inputManager.KeyPress(Z_KEY)) {
			mostrando = true;
			surpriseGO->render = true;
		}
		else if (mostrando && inputManager.KeyPress(X_KEY)) {
			mostrando = false;
			surpriseGO->render = false;
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
	else if (inputManager.KeyPress(BACKSPACE_KEY)) {
		GameData::playerVictory = true;
		popRequested = true;
		Game::GetInstance().Push(new EndState());
	}
	else if (inputManager.KeyPress(NUMPAD_NINE_KEY) || inputManager.KeyPress(NINE_KEY) ||
			((playerGO->box.x + playerGO->box.w > 71 * ONETILESQUARE) && (playerGO->box.y < 800 - 6 * ONETILESQUARE) &&
			 (playerGO->box.y > 800 - 9 * ONETILESQUARE)) ) {
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

	////////////////////////////
	///////DETALHES		//
	/////////////////////////////

	auto DetalheGO = new GameObject();

	DetalheSprite = new Sprite(*DetalheGO, "./assets/img/Level1/objeto_mapa2.png");

	DetalheGO->box.x = (0) * tileSet->GetTileWidth() + chaoGO->box.x;
	DetalheGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	DetalheGO->AddComponent(DetalheSprite);
	objectArray.emplace_back(DetalheGO);

	/////////////////////////


	///////////////////////////////
	//		MAXIMUM EFFORT		//
	/////////////////////////////
	auto telhadoGO = new GameObject();
	telhadoGO->box.x = (24) * tileSet->GetTileWidth()/* + chaoGO->box.x*/;
	telhadoGO->box.y = (-3) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Telhado = new TileMap(*telhadoGO, "./assets/map/Level1/TileMap_Telhado.txt", tileSet);
	tileMap_Telhado->colide = true;

	telhadoGO->box.w = tileMap_Telhado->GetWidth() * tileSet->GetTileWidth();
	telhadoGO->box.h = tileMap_Telhado->GetHeight() * tileSet->GetTileHeight();

	telhadoGO->AddComponent(tileMap_Telhado);
	objectArray.emplace_back(telhadoGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto janelaGO = new GameObject();
	janelaGO->box.x = telhadoGO->box.x + telhadoGO->box.w + (7) * tileSet->GetTileWidth()/* + chaoGO->box.x*/;
	janelaGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Janela = new TileMap(*janelaGO, "./assets/map/Level1/TileMap_Janela.txt", tileSet);
	tileMap_Janela->colide = true;

	janelaGO->box.w = tileMap_Janela->GetWidth() * tileSet->GetTileWidth();
	janelaGO->box.h = tileMap_Janela->GetHeight() * tileSet->GetTileHeight();

	janelaGO->AddComponent(tileMap_Janela);
	objectArray.emplace_back(janelaGO);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto tetoGO = new GameObject();
	tetoGO->box.x = telhadoGO->box.x + telhadoGO->box.w + (7) * tileSet->GetTileWidth()/* + chaoGO->box.x*/;
	tetoGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Teto = new TileMap(*tetoGO, "./assets/map/Level1/tileMap_Teto.txt", tileSet);
	tileMap_Teto->colide = true;

	tetoGO->box.w = tileMap_Teto->GetWidth() * tileSet->GetTileWidth();
	tetoGO->box.h = tileMap_Teto->GetHeight() * tileSet->GetTileHeight();

	tetoGO->AddComponent(tileMap_Teto);
	objectArray.emplace_back(tetoGO);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
}

void GameState1::ChangeCoatGuyHP() {
	int hp = coatGuy->GetHP();

	if (coatGuy->damaged) {
		switch (hp) {
		case 0:

			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_00.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 1:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_01.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 2:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_02.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 3:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_03.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 4:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_04.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 5:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_05.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 6:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_06.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 7:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_07.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 8:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_08.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 9:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_09.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 10:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_10.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 11:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_11.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 12:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_12.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 13:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_13.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 14:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_14.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 15:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_15.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 16:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_16.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 17:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_17.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 18:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_18.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 19:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_19.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 20:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_20.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 21:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_21.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 22:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_22.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 23:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_23.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 24:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_24.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 25:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_25.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 26:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_26.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 27:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_27.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		case 28:
			HPbarCoatGuyGO->RemoveComponent(HPbarCoatGuySprite);
			HPbarCoatGuySprite = new Sprite(*HPbarCoatGuyGO, "./assets/img/Vilao/barra_de_HP/HP_vilao_28.png");
			HPbarCoatGuyGO->AddComponent(HPbarCoatGuySprite);
			break;

		default:
			break;
		}


		coatGuy->damaged = false;
	}
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
