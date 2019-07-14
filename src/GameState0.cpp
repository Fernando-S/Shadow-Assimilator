#include "GameState0.h"
#include "Game.h"
#include "GameData.h"


GameState0::GameState0() {
	playerGO = new GameObject();
	chaoGO = new GameObject();
	robot1GO = new GameObject();
	robot2GO = new GameObject();
	robot3GO = new GameObject();
}

void GameState0::LoadAssets() {
	int i;

	/////////////////////////////////////////////
	//	  Carrega a Musica e aperta o play	  //
	///////////////////////////////////////////
	//backgroundMusic = *new Music("./assets/audio/soundtrack/Shadow Assimilator track 1.ogg");
	backgroundMusic = *new Music("./assets/audio/soundtrack/shadowCITY.ogg");
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

	tileSet = new TileSet(64, 64, "./assets/img/tile003.png");
	//auto prediosBackground = new TileMap(*prediosGO, "./assets/map/Level0/TileMap_Predios1.txt", tileSet);
	auto prediosBackground = new TileMap(*prediosGO, "./assets/map/Level0/final/Mapa_1.1.txt", tileSet);

	prediosBackground->colide = false;

	prediosGO->box.x = 0;
	prediosGO->box.y = 800 - 29 * ONETILESQUARE;

	prediosGO->box.w = prediosBackground->GetWidth() * tileSet->GetTileWidth();
	prediosGO->box.h = prediosBackground->GetHeight() * tileSet->GetTileHeight();

	prediosGO->AddComponent(prediosBackground);
	objectArray.emplace_back(prediosGO);

	// Teste do novo TileSet
	chaoGO->box.x = 0;
	chaoGO->box.y = 800;

	// Carrega os tiles que colidem
	LoadLevel();

	// Detalhes dos predios 1 
	auto detalhesGO = new GameObject();
	auto detalhesBackground = new TileMap(*detalhesGO, "./assets/map/Level0/final/Mapa_1.3.txt", tileSet);

	detalhesBackground->colide = false;

	detalhesGO->box.x = 0;
	detalhesGO->box.y = 800 - 29 * ONETILESQUARE;


	detalhesGO->box.w = detalhesBackground->GetWidth() * tileSet->GetTileWidth();
	detalhesGO->box.h = detalhesBackground->GetHeight() * tileSet->GetTileHeight();

	detalhesGO->AddComponent(detalhesBackground);
	objectArray.emplace_back(detalhesGO);
	///////////////////////////////////////////////

	// Detalhes dos predios 2 
	auto detalhesGO1 = new GameObject();
	auto detalhesBackground1 = new TileMap(*detalhesGO, "./assets/map/Level0/final/Mapa_1.4.txt", tileSet);

	detalhesBackground1->colide = false;

	detalhesGO1->box.x = 0;
	detalhesGO1->box.y = 800 - 29 * ONETILESQUARE;


	detalhesGO1->box.w = detalhesBackground1->GetWidth() * tileSet->GetTileWidth();
	detalhesGO1->box.h = detalhesBackground1->GetHeight() * tileSet->GetTileHeight();

	detalhesGO1->AddComponent(detalhesBackground1);
	objectArray.emplace_back(detalhesGO1);
	///////////////////////////////////////////////

	// Detalhes dos predios 2 
	auto detalhesGO2 = new GameObject();
	auto detalhesBackground2 = new TileMap(*detalhesGO, "./assets/map/Level0/final/Mapa_1.5.txt", tileSet);

	detalhesBackground2->colide = false;

	detalhesGO2->box.x = 0;
	detalhesGO2->box.y = 800 - 29 * ONETILESQUARE;


	detalhesGO2->box.w = detalhesBackground2->GetWidth() * tileSet->GetTileWidth();
	detalhesGO2->box.h = detalhesBackground2->GetHeight() * tileSet->GetTileHeight();

	detalhesGO2->AddComponent(detalhesBackground2);
	objectArray.emplace_back(detalhesGO2);
	///////////////////////////////////////////////

	// Detalhes dos predios 3 OPCIONAL 

	detalhesGO3 = new GameObject();
	auto detalhesBackground3 = new TileMap(*detalhesGO, "./assets/map/Level0/final/Mapa_1.2.txt", tileSet);
	detalhesGO3->render = false;

	detalhesBackground3->colide = false;

	detalhesGO3->box.x = 0;
	detalhesGO3->box.y = 800 - 29 * ONETILESQUARE;


	detalhesGO3->box.w = detalhesBackground3->GetWidth() * tileSet->GetTileWidth();
	detalhesGO3->box.h = detalhesBackground3->GetHeight() * tileSet->GetTileHeight();

	detalhesGO3->AddComponent(detalhesBackground3);
	objectArray.emplace_back(detalhesGO3);


	///////////////////////////////////////////////

	//////////////////////////////////////
	//			DETALHES RALISON		//
	//////////////////////////////////////
	DetalheGO = new GameObject();
	DetalheSprite = new Sprite(*DetalheGO, "./assets/img/Level0/objeto_mapa1.png");
	DetalheGO->render = false;

	DetalheGO->box.x = (0) * tileSet->GetTileWidth() + chaoGO->box.x;
	DetalheGO->box.y = (-29) * tileSet->GetTileHeight() + chaoGO->box.y;

	DetalheGO->AddComponent(DetalheSprite);
	objectArray.emplace_back(DetalheGO);
	////////////////////////////////

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
	//		Carrega os Robos		//
	/////////////////////////////////

	// Primeiro Robo
	robot1 = new Robot(*robot1GO);

	robot1GO->AddComponent(robot1);
	robot1GO->box.x = 38 * ONETILESQUARE;
	robot1GO->box.y = 800 - robot1GO->box.h;

	objectArray.emplace_back(robot1GO);

	// Segundo Robo
	robot2 = new Robot(*robot2GO);

	robot2GO->AddComponent(robot2);
	robot2GO->box.x = 65 * ONETILESQUARE;
	robot2GO->box.y = 800 - robot2GO->box.h - 20 * ONETILESQUARE;

	objectArray.emplace_back(robot2GO);

	// Terceiro Robo
	robot3 = new Robot(*robot3GO);

	robot3GO->AddComponent(robot3);
	robot3GO->box.x = 80 * ONETILESQUARE;
	robot3GO->box.y = 800 - robot3GO->box.h/* - 20 * ONETILESQUARE*/;

	objectArray.emplace_back(robot3GO);





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
//	}
	//else {
	//	AtkFortSprite = new Sprite(*AtkFortGO, "./assets/img/Protagonista/icones/icone_ark_forte2.png");
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
		//AtkDistSprite = new Sprite(*AtkDistGO, "./assets/img/Protagonista/icones/icone_atk_distancia.png");
	//}
	//else {
		AtkDistSprite = new Sprite(*AtkDistGO, "./assets/img/Protagonista/icones/icone_atk_distancia.png");
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

void GameState0::Update(float dt) {
	unsigned i, j;
	auto inputManager = InputManager::GetInstance();
	playerHitTimer.Update(dt);
	robot1HitTimer.Update(dt);
	robot2HitTimer.Update(dt);
	robot3HitTimer.Update(dt);


	// Faz o update na camera e na box do mapa
	Camera::Update(dt);

	quitRequested = inputManager.QuitRequested();			// Seta o quitRequested ao fechar o jogo

	UpdateArray(dt);										// Faz o update de cada GameObject no objectArray


	if (playerGO->box.y + playerGO->box.h > 800) {
		playerGO->box.y = 800 - playerGO->box.h;
	}

	if (playerGO->box.x < 10) {
		playerGO->box.x = 10;
	}

	if (playerGO->box.x + playerGO->box.w > 96 * ONETILESQUARE) {
		//playerGO->box.x = 96 * ONETILESQUARE - playerGO->box.w;
		popRequested = true;
		Game::GetInstance().Push(new GameState1());
	}



	if (playerGO->box.x > 20 * ONETILESQUARE) {
		GameData::saiuDoGalpao = true;
	}
	else {
		GameData::saiuDoGalpao = false;
	}

	if (GameData::saiuDoGalpao == true) {
		detalhesGO3->render = true;
		DetalheGO->render = true;
	}
	else {
		detalhesGO3->render = false;
		DetalheGO->render = false;
	}



	if (inputManager.IsKeyDown(R_KEY)) {
		GameData::saiuDoGalpao = true;
	}

	// Reseta o contador para piscar a personagem
	if (player->damaged) {
		playerHitTimer.Restart();
	}

	// Reseta o contador para piscar o primeiro robo
	if (robot1->damaged) {
		robot1HitTimer.Restart();
		robot1->damaged = false;
	}

	// Reseta o contador para piscar o segundo robo
	if (robot2->damaged) {
		robot2HitTimer.Restart();
		robot2->damaged = false;
	}

	// Reseta o contador para piscar o terceiro robo
	if (robot3->damaged) {
		robot3HitTimer.Restart();
		robot3->damaged = false;
	}

	ChangePlayerHP();

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

	// Pisca o primeiro robo
	if (robot1->gotHit) {

		if (robot1HitTimer.Get() > 1.0) {
			robot1GO->render = true;
			robot1->gotHit = false;
		}
		else if (robot1HitTimer.Get() > 0.9) {
			robot1GO->render = false;
		}
		else if (robot1HitTimer.Get() > 0.8) {
			robot1GO->render = true;
		}
		else if (robot1HitTimer.Get() > 0.7) {
			robot1GO->render = false;
		}
		else if (robot1HitTimer.Get() > 0.6) {
			robot1GO->render = true;
		}
		else if (robot1HitTimer.Get() > 0.5) {
			robot1GO->render = false;
		}
		else if (robot1HitTimer.Get() > 0.4) {
			robot1GO->render = true;
		}
		else if (robot1HitTimer.Get() > 0.3) {
			robot1GO->render = false;
		}
		else if (robot1HitTimer.Get() > 0.2) {
			robot1GO->render = true;
		}
		else if (robot1HitTimer.Get() > 0.1) {
			robot1GO->render = false;
		}
	}

	// Pisca o segundo robo
	if (robot2->gotHit) {

		if (robot2HitTimer.Get() > 1.0) {
			robot2GO->render = true;
			robot2->gotHit = false;
		}
		else if (robot2HitTimer.Get() > 0.9) {
			robot2GO->render = false;
		}
		else if (robot2HitTimer.Get() > 0.8) {
			robot2GO->render = true;
		}
		else if (robot2HitTimer.Get() > 0.7) {
			robot2GO->render = false;
		}
		else if (robot2HitTimer.Get() > 0.6) {
			robot2GO->render = true;
		}
		else if (robot2HitTimer.Get() > 0.5) {
			robot2GO->render = false;
		}
		else if (robot2HitTimer.Get() > 0.4) {
			robot2GO->render = true;
		}
		else if (robot2HitTimer.Get() > 0.3) {
			robot2GO->render = false;
		}
		else if (robot2HitTimer.Get() > 0.2) {
			robot2GO->render = true;
		}
		else if (robot2HitTimer.Get() > 0.1) {
			robot2GO->render = false;
		}
	}

	// Pisca o segundo robo
	if (robot3->gotHit) {

		if (robot3HitTimer.Get() > 1.0) {
			robot3GO->render = true;
			robot3->gotHit = false;
		}
		else if (robot3HitTimer.Get() > 0.9) {
			robot3GO->render = false;
		}
		else if (robot3HitTimer.Get() > 0.8) {
			robot3GO->render = true;
		}
		else if (robot3HitTimer.Get() > 0.7) {
			robot3GO->render = false;
		}
		else if (robot3HitTimer.Get() > 0.6) {
			robot3GO->render = true;
		}
		else if (robot3HitTimer.Get() > 0.5) {
			robot3GO->render = false;
		}
		else if (robot3HitTimer.Get() > 0.4) {
			robot3GO->render = true;
		}
		else if (robot3HitTimer.Get() > 0.3) {
			robot3GO->render = false;
		}
		else if (robot3HitTimer.Get() > 0.2) {
			robot3GO->render = true;
		}
		else if (robot3HitTimer.Get() > 0.1) {
			robot2GO->render = false;
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
			//std::cout << "dois = true" << std::endl;
		}
		if ((inputManager.KeyRelease(THREE_KEY) || inputManager.KeyRelease(NUMPAD_THREE_KEY)) && dois) {
			tres = true;
			dois = quatro = cinco = meia = sete = oito = false;
			//std::cout << "tres = true" << std::endl;
		}
		if ((inputManager.KeyRelease(FOUR_KEY) || inputManager.KeyRelease(NUMPAD_FOUR_KEY)) && tres) {
			quatro = true;
			dois = tres = cinco = meia = sete = oito = false;
			//std::cout << "quatro = true" << std::endl;
		}
		if ((inputManager.KeyRelease(FIVE_KEY) || inputManager.KeyRelease(NUMPAD_FIVE_KEY)) && quatro) {
			cinco = true;
			dois = tres = quatro = meia = sete = oito = false;
			//std::cout << "cinco = true" << std::endl;
		}
		if ((inputManager.KeyRelease(SIX_KEY) || inputManager.KeyRelease(NUMPAD_SIX_KEY)) && cinco) {
			meia = true;
			dois = tres = quatro = cinco = sete = oito = false;
			//std::cout << "meia = true" << std::endl;
		}
		if ((inputManager.KeyRelease(SEVEN_KEY) || inputManager.KeyRelease(NUMPAD_SEVEN_KEY)) && meia) {
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
	else if (inputManager.KeyPress(NUMPAD_NINE_KEY) || inputManager.KeyPress(NINE_KEY)) {
		popRequested = true;		/// todo - comentar se for poder voltar nas telas
		Game::GetInstance().Push(new GameState1());
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

	auto Chao = new TileMap(*chaoGO, "./assets/map/Level0/TileMap_Chao1.txt", tileSet);


	Chao->colide = true;

	//chaoGO->box.w = Chao->GetWidth() * tileSet->GetTileWidth();
	//chaoGO->box.h = Chao->GetHeight() * tileSet->GetTileHeight();

	chaoGO->box.w = Chao->GetWidth() * tileSet->GetTileWidth();
	chaoGO->box.h = Chao->GetHeight() * tileSet->GetTileHeight();

	chaoGO->AddComponent(Chao);
	objectArray.emplace_back(chaoGO);


	///////////////////////////////
	//			LIXO			//
	/////////////////////////////
	auto LixoGO = new GameObject();

	if (SetAtkForte == false) {
		LixoSprite = new Sprite(*LixoGO, "./assets/img/Level0/lixo2.png");
	}
	else {
		LixoSprite = new Sprite(*LixoGO, "./assets/img/Level0/lixo1.png");
	}

	LixoGO->box.x = (1) * tileSet->GetTileWidth() + chaoGO->box.x;
	LixoGO->box.y = (-11.605) * tileSet->GetTileHeight() + chaoGO->box.y;

	LixoGO->AddComponent(LixoSprite);
	objectArray.emplace_back(LixoGO);

	/*
	AtkFortGO->initialX = HPbarGO->box.Center().x + 35.5;
	AtkFortGO->initialY = HPbarGO->box.Center().y + 17;
	auto AtkFortCamFollower = new CameraFollower(*AtkFortGO);
	AtkFortGO->AddComponent(AtkFortCamFollower);
	AtkFortGO->AddComponent(AtkFortSprite);
	objectArray.emplace_back(AtkFortGO);
	*/

	///////////////////////////////

	///////////////////////////////
	//		MAXIMUM EFFORT		//
	/////////////////////////////
	auto Tile00_ColunaGO = new GameObject();
	Tile00_ColunaGO->box.x = (0) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile00_ColunaGO->box.y = (-22) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile00_Coluna = new TileMap(*Tile00_ColunaGO, "./assets/map/Level0/Tile00_Coluna.txt", tileSet);
	tileMap_Tile00_Coluna->colide = true;

	Tile00_ColunaGO->box.w = tileMap_Tile00_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile00_ColunaGO->box.h = tileMap_Tile00_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile00_ColunaGO->AddComponent(tileMap_Tile00_Coluna);
	objectArray.emplace_back(Tile00_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile01_ColunaGO = new GameObject();
	Tile01_ColunaGO->box.x = (19) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile01_ColunaGO->box.y = (-22) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile01_Coluna = new TileMap(*Tile01_ColunaGO, "./assets/map/Level0/Tile01_Coluna.txt", tileSet);
	tileMap_Tile01_Coluna->colide = true;

	Tile01_ColunaGO->box.w = tileMap_Tile01_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile01_ColunaGO->box.h = tileMap_Tile01_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile01_ColunaGO->AddComponent(tileMap_Tile01_Coluna);
	objectArray.emplace_back(Tile01_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile02_ColunaGO = new GameObject();
	Tile02_ColunaGO->box.x = (33) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile02_ColunaGO->box.y = (-13) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile02_Coluna = new TileMap(*Tile02_ColunaGO, "./assets/map/Level0/Tile02_Coluna.txt", tileSet);
	tileMap_Tile02_Coluna->colide = true;

	Tile02_ColunaGO->box.w = tileMap_Tile02_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile02_ColunaGO->box.h = tileMap_Tile02_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile02_ColunaGO->AddComponent(tileMap_Tile02_Coluna);
	objectArray.emplace_back(Tile02_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile03_ColunaGO = new GameObject();
	Tile03_ColunaGO->box.x = (42) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile03_ColunaGO->box.y = (-13) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile03_Coluna = new TileMap(*Tile03_ColunaGO, "./assets/map/Level0/Tile03_Coluna.txt", tileSet);
	tileMap_Tile03_Coluna->colide = true;

	Tile03_ColunaGO->box.w = tileMap_Tile03_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile03_ColunaGO->box.h = tileMap_Tile03_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile03_ColunaGO->AddComponent(tileMap_Tile03_Coluna);
	objectArray.emplace_back(Tile03_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile04_ColunaGO = new GameObject();
	Tile04_ColunaGO->box.x = (50) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile04_ColunaGO->box.y = (-16) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile04_Coluna = new TileMap(*Tile04_ColunaGO, "./assets/map/Level0/Tile04_Coluna.txt", tileSet);
	tileMap_Tile04_Coluna->colide = true;

	Tile04_ColunaGO->box.w = tileMap_Tile04_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile04_ColunaGO->box.h = tileMap_Tile04_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile04_ColunaGO->AddComponent(tileMap_Tile04_Coluna);
	objectArray.emplace_back(Tile04_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile05_ColunaGO = new GameObject();
	Tile05_ColunaGO->box.x = (51) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile05_ColunaGO->box.y = (-16) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile05_Coluna = new TileMap(*Tile05_ColunaGO, "./assets/map/Level0/Tile05_Coluna.txt", tileSet);
	tileMap_Tile05_Coluna->colide = true;

	Tile05_ColunaGO->box.w = tileMap_Tile05_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile05_ColunaGO->box.h = tileMap_Tile05_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile05_ColunaGO->AddComponent(tileMap_Tile05_Coluna);
	objectArray.emplace_back(Tile05_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile06_ColunaGO = new GameObject();
	Tile06_ColunaGO->box.x = (52) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile06_ColunaGO->box.y = (-16) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile06_Coluna = new TileMap(*Tile06_ColunaGO, "./assets/map/Level0/Tile06_Coluna.txt", tileSet);
	tileMap_Tile06_Coluna->colide = true;

	Tile06_ColunaGO->box.w = tileMap_Tile06_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile06_ColunaGO->box.h = tileMap_Tile06_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile06_ColunaGO->AddComponent(tileMap_Tile06_Coluna);
	objectArray.emplace_back(Tile06_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile07_ColunaGO = new GameObject();
	Tile07_ColunaGO->box.x = (53) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile07_ColunaGO->box.y = (-16) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile07_Coluna = new TileMap(*Tile07_ColunaGO, "./assets/map/Level0/Tile07_Coluna.txt", tileSet);
	tileMap_Tile07_Coluna->colide = true;

	Tile07_ColunaGO->box.w = tileMap_Tile07_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile07_ColunaGO->box.h = tileMap_Tile07_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile07_ColunaGO->AddComponent(tileMap_Tile07_Coluna);
	objectArray.emplace_back(Tile07_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile08_ColunaGO = new GameObject();
	Tile08_ColunaGO->box.x = (54) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile08_ColunaGO->box.y = (-16) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile08_Coluna = new TileMap(*Tile08_ColunaGO, "./assets/map/Level0/Tile08_Coluna.txt", tileSet);
	tileMap_Tile08_Coluna->colide = true;

	Tile08_ColunaGO->box.w = tileMap_Tile08_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile08_ColunaGO->box.h = tileMap_Tile08_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile08_ColunaGO->AddComponent(tileMap_Tile08_Coluna);
	objectArray.emplace_back(Tile08_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile09_ColunaGO = new GameObject();
	Tile09_ColunaGO->box.x = (55) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile09_ColunaGO->box.y = (-16) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile09_Coluna = new TileMap(*Tile09_ColunaGO, "./assets/map/Level0/Tile09_Coluna.txt", tileSet);
	tileMap_Tile09_Coluna->colide = true;

	Tile09_ColunaGO->box.w = tileMap_Tile09_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile09_ColunaGO->box.h = tileMap_Tile09_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile09_ColunaGO->AddComponent(tileMap_Tile09_Coluna);
	objectArray.emplace_back(Tile09_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile10_ColunaGO = new GameObject();
	Tile10_ColunaGO->box.x = (56) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile10_ColunaGO->box.y = (-16) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile10_Coluna = new TileMap(*Tile10_ColunaGO, "./assets/map/Level0/Tile10_Coluna.txt", tileSet);
	tileMap_Tile10_Coluna->colide = true;

	Tile10_ColunaGO->box.w = tileMap_Tile10_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile10_ColunaGO->box.h = tileMap_Tile10_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile10_ColunaGO->AddComponent(tileMap_Tile10_Coluna);
	objectArray.emplace_back(Tile10_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile11_ColunaGO = new GameObject();
	Tile11_ColunaGO->box.x = (57) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile11_ColunaGO->box.y = (-16) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile11_Coluna = new TileMap(*Tile11_ColunaGO, "./assets/map/Level0/Tile11_Coluna.txt", tileSet);
	tileMap_Tile11_Coluna->colide = true;

	Tile11_ColunaGO->box.w = tileMap_Tile11_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile11_ColunaGO->box.h = tileMap_Tile11_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile11_ColunaGO->AddComponent(tileMap_Tile11_Coluna);
	objectArray.emplace_back(Tile11_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile12_ColunaGO = new GameObject();
	Tile12_ColunaGO->box.x = (61) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile12_ColunaGO->box.y = (-21) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile12_Coluna = new TileMap(*Tile12_ColunaGO, "./assets/map/Level0/Tile12_Coluna.txt", tileSet);
	tileMap_Tile12_Coluna->colide = true;

	Tile12_ColunaGO->box.w = tileMap_Tile12_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile12_ColunaGO->box.h = tileMap_Tile12_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile12_ColunaGO->AddComponent(tileMap_Tile12_Coluna);
	objectArray.emplace_back(Tile12_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile13_ColunaGO = new GameObject();
	Tile13_ColunaGO->box.x = (69) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile13_ColunaGO->box.y = (-21) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile13_Coluna = new TileMap(*Tile13_ColunaGO, "./assets/map/Level0/Tile13_Coluna.txt", tileSet);
	tileMap_Tile13_Coluna->colide = true;

	Tile13_ColunaGO->box.w = tileMap_Tile13_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile13_ColunaGO->box.h = tileMap_Tile13_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile13_ColunaGO->AddComponent(tileMap_Tile13_Coluna);
	objectArray.emplace_back(Tile13_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile14_ColunaGO = new GameObject();
	Tile14_ColunaGO->box.x = (75) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile14_ColunaGO->box.y = (-19) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile14_Coluna = new TileMap(*Tile14_ColunaGO, "./assets/map/Level0/Tile14_Coluna.txt", tileSet);
	tileMap_Tile14_Coluna->colide = true;

	Tile14_ColunaGO->box.w = tileMap_Tile14_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile14_ColunaGO->box.h = tileMap_Tile14_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile14_ColunaGO->AddComponent(tileMap_Tile14_Coluna);
	objectArray.emplace_back(Tile14_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile15_ColunaGO = new GameObject();
	Tile15_ColunaGO->box.x = (83) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile15_ColunaGO->box.y = (-19) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile15_Coluna = new TileMap(*Tile15_ColunaGO, "./assets/map/Level0/Tile15_Coluna.txt", tileSet);
	tileMap_Tile15_Coluna->colide = true;

	Tile15_ColunaGO->box.w = tileMap_Tile15_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile15_ColunaGO->box.h = tileMap_Tile15_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile15_ColunaGO->AddComponent(tileMap_Tile15_Coluna);
	objectArray.emplace_back(Tile15_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile16_ColunaGO = new GameObject();
	Tile16_ColunaGO->box.x = (88) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile16_ColunaGO->box.y = (-29) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile16_Coluna = new TileMap(*Tile16_ColunaGO, "./assets/map/Level0/Tile16_Coluna.txt", tileSet);
	tileMap_Tile16_Coluna->colide = true;

	Tile16_ColunaGO->box.w = tileMap_Tile16_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile16_ColunaGO->box.h = tileMap_Tile16_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile16_ColunaGO->AddComponent(tileMap_Tile16_Coluna);
	objectArray.emplace_back(Tile16_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile17_LinhaGO = new GameObject();
	Tile17_LinhaGO->box.x = (89) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile17_LinhaGO->box.y = (-29) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile17_Linha = new TileMap(*Tile17_LinhaGO, "./assets/map/Level0/Tile17_Linha.txt", tileSet);
	tileMap_Tile17_Linha->colide = true;

	Tile17_LinhaGO->box.w = tileMap_Tile17_Linha->GetWidth() * tileSet->GetTileWidth();
	Tile17_LinhaGO->box.h = tileMap_Tile17_Linha->GetHeight() * tileSet->GetTileHeight();

	Tile17_LinhaGO->AddComponent(tileMap_Tile17_Linha);
	objectArray.emplace_back(Tile17_LinhaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile18_LinhaGO = new GameObject();
	Tile18_LinhaGO->box.x = (4) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile18_LinhaGO->box.y = (-22) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile18_Linha = new TileMap(*Tile18_LinhaGO, "./assets/map/Level0/Tile18_Linha.txt", tileSet);
	tileMap_Tile18_Linha->colide = true;

	Tile18_LinhaGO->box.w = tileMap_Tile18_Linha->GetWidth() * tileSet->GetTileWidth();
	Tile18_LinhaGO->box.h = tileMap_Tile18_Linha->GetHeight() * tileSet->GetTileHeight();

	Tile18_LinhaGO->AddComponent(tileMap_Tile18_Linha);
	objectArray.emplace_back(Tile18_LinhaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile19_LinhaGO = new GameObject();
	Tile19_LinhaGO->box.x = (62) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile19_LinhaGO->box.y = (-21) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile19_Linha = new TileMap(*Tile19_LinhaGO, "./assets/map/Level0/Tile19_Linha.txt", tileSet);
	tileMap_Tile19_Linha->colide = true;

	Tile19_LinhaGO->box.w = tileMap_Tile19_Linha->GetWidth() * tileSet->GetTileWidth();
	Tile19_LinhaGO->box.h = tileMap_Tile19_Linha->GetHeight() * tileSet->GetTileHeight();

	Tile19_LinhaGO->AddComponent(tileMap_Tile19_Linha);
	objectArray.emplace_back(Tile19_LinhaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile20_LinhaGO = new GameObject();
	Tile20_LinhaGO->box.x = (76) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile20_LinhaGO->box.y = (-19) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile20_Linha = new TileMap(*Tile20_LinhaGO, "./assets/map/Level0/Tile20_Linha.txt", tileSet);
	tileMap_Tile20_Linha->colide = true;

	Tile20_LinhaGO->box.w = tileMap_Tile20_Linha->GetWidth() * tileSet->GetTileWidth();
	Tile20_LinhaGO->box.h = tileMap_Tile20_Linha->GetHeight() * tileSet->GetTileHeight();

	Tile20_LinhaGO->AddComponent(tileMap_Tile20_Linha);
	objectArray.emplace_back(Tile20_LinhaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile21_LinhaGO = new GameObject();
	Tile21_LinhaGO->box.x = (34) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile21_LinhaGO->box.y = (-13) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile21_Linha = new TileMap(*Tile21_LinhaGO, "./assets/map/Level0/Tile21_Linha.txt", tileSet);
	tileMap_Tile21_Linha->colide = true;

	Tile21_LinhaGO->box.w = tileMap_Tile21_Linha->GetWidth() * tileSet->GetTileWidth();
	Tile21_LinhaGO->box.h = tileMap_Tile21_Linha->GetHeight() * tileSet->GetTileHeight();

	Tile21_LinhaGO->AddComponent(tileMap_Tile21_Linha);
	objectArray.emplace_back(Tile21_LinhaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile22_LinhaGO = new GameObject();
	Tile22_LinhaGO->box.x = (43) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile22_LinhaGO->box.y = (-10) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile22_Linha = new TileMap(*Tile22_LinhaGO, "./assets/map/Level0/Tile22_Linha.txt", tileSet);
	tileMap_Tile22_Linha->colide = true;

	Tile22_LinhaGO->box.w = tileMap_Tile22_Linha->GetWidth() * tileSet->GetTileWidth();
	Tile22_LinhaGO->box.h = tileMap_Tile22_Linha->GetHeight() * tileSet->GetTileHeight();

	Tile22_LinhaGO->AddComponent(tileMap_Tile22_Linha);
	objectArray.emplace_back(Tile22_LinhaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile23_LinhaGO = new GameObject();
	Tile23_LinhaGO->box.x = (34) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile23_LinhaGO->box.y = (-6) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile23_Linha = new TileMap(*Tile23_LinhaGO, "./assets/map/Level0/Tile23_Linha.txt", tileSet);
	tileMap_Tile23_Linha->colide = true;

	Tile23_LinhaGO->box.w = tileMap_Tile23_Linha->GetWidth() * tileSet->GetTileWidth();
	Tile23_LinhaGO->box.h = tileMap_Tile23_Linha->GetHeight() * tileSet->GetTileHeight();

	Tile23_LinhaGO->AddComponent(tileMap_Tile23_Linha);
	objectArray.emplace_back(Tile23_LinhaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile24_LinhaGO = new GameObject();
	Tile24_LinhaGO->box.x = (62) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile24_LinhaGO->box.y = (-6) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile24_Linha = new TileMap(*Tile24_LinhaGO, "./assets/map/Level0/Tile24_Linha.txt", tileSet);
	tileMap_Tile24_Linha->colide = true;

	Tile24_LinhaGO->box.w = tileMap_Tile24_Linha->GetWidth() * tileSet->GetTileWidth();
	Tile24_LinhaGO->box.h = tileMap_Tile24_Linha->GetHeight() * tileSet->GetTileHeight();

	Tile24_LinhaGO->AddComponent(tileMap_Tile24_Linha);
	objectArray.emplace_back(Tile24_LinhaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile25_LinhaGO = new GameObject();
	Tile25_LinhaGO->box.x = (76) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile25_LinhaGO->box.y = (-6) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile25_Linha = new TileMap(*Tile25_LinhaGO, "./assets/map/Level0/Tile25_Linha.txt", tileSet);
	tileMap_Tile25_Linha->colide = true;

	Tile25_LinhaGO->box.w = tileMap_Tile25_Linha->GetWidth() * tileSet->GetTileWidth();
	Tile25_LinhaGO->box.h = tileMap_Tile25_Linha->GetHeight() * tileSet->GetTileHeight();

	Tile25_LinhaGO->AddComponent(tileMap_Tile25_Linha);
	objectArray.emplace_back(Tile25_LinhaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

}

void GameState0::ChangePlayerHP() {
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