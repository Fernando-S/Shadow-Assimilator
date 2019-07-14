#include "GameState2.h"
#include "Game.h"
#include "GameData.h"


GameState2::GameState2() {
	playerGO = new GameObject();
	coatGuyGO = new GameObject();
	finalBossGO = new GameObject();
	escudoGO = new GameObject();
	chaoGO = new GameObject();
	canhaoVermelho1GO = new GameObject();
	canhaoVermelho2GO = new GameObject();
	canhaoVermelho3GO = new GameObject();
	canhaoAmareloGO = new GameObject();

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
	auto backGO = new GameObject();
	tileSet = new TileSet(64, 64, "./assets/img/tile003.png");

	auto background = new TileMap(*backGO, "./assets/map/Level3/Mapa_4.txt", tileSet);

	background->colide = false;

	backGO->box.x = 0;
	backGO->box.y = -4 * ONETILESQUARE;

	backGO->box.w = background->GetWidth() * tileSet->GetTileWidth();
	backGO->box.h = background->GetHeight() * tileSet->GetTileHeight();

	backGO->AddComponent(background);
	objectArray.emplace_back(backGO);


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

	if (SetAtkForte == true) {
		AtkFortSprite = new Sprite(*AtkFortGO, "./assets/img/Protagonista/icones/icone_ark_forte.png");
	}
	else {
		AtkFortSprite = new Sprite(*AtkFortGO, "./assets/img/Protagonista/icones/icone_ark_forte.png");
	}

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

	if (SetAtkDist == true) {
		AtkDistSprite = new Sprite(*AtkDistGO, "./assets/img/Protagonista/icones/icone_atk_distancia.png");
	}
	else {
		AtkDistSprite = new Sprite(*AtkDistGO, "./assets/img/Protagonista/icones/icone_atk_distancia.png");
	}

	AtkDistGO->initialX = HPbarGO->box.Center().x + 63.2;
	AtkDistGO->initialY = HPbarGO->box.Center().y + 17;
	auto AtkDistCamFollower = new CameraFollower(*AtkDistGO);
	AtkDistGO->AddComponent(AtkDistCamFollower);

	AtkDistGO->AddComponent(AtkDistSprite);
	objectArray.emplace_back(AtkDistGO);
	//////////////////

	////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////
	//		Carrega o Final BOSS	//
	/////////////////////////////////
	finalBoss = new FinalBoss(*finalBossGO);

	finalBossGO->AddComponent(finalBoss);
	finalBossGO->box.x = 1160;
	finalBossGO->box.y = 800 - finalBossGO->box.h;
	objectArray.emplace_back(finalBossGO);


	///////////////////////////////////////////////
	//		Carrega o escudo do Final BOSS		//
	/////////////////////////////////////////////
	escudo = new Escudo(*escudoGO);

	escudoGO->AddComponent(escudo);
	escudoGO->box.x = finalBossGO->box.x - finalBoss->sprite->GetWidth() + 78;
	escudoGO->box.y = 800 - escudoGO->box.h;
	objectArray.emplace_back(escudoGO);


	///////////////////////////////////////////////
	//		Carrega os Canhoes Vermelhos		//
	/////////////////////////////////////////////

	int baseC = 192 + ONETILESQUARE;

	// Base 1
	auto baseVermelha1GO = new GameObject();
	auto baseVermelha1Sprite = new Sprite(*baseVermelha1GO, "./assets/img/Boss Final/torre2/base_torre2.png");

	baseVermelha1GO->AddComponent(baseVermelha1Sprite);
	baseVermelha1GO->box.x = 350;
	baseVermelha1GO->box.y = finalBossGO->box.y - baseC;

	objectArray.emplace_back(baseVermelha1GO);

	// Canhao 1
	canhaoVermelho1 = new CanhaoVermelho(*canhaoVermelho1GO);
	canhaoVermelho1GO->AddComponent(canhaoVermelho1);
	canhaoVermelho1GO->box.x = baseVermelha1GO->box.x + 5;
	canhaoVermelho1GO->box.y = baseVermelha1GO->box.y + baseVermelha1Sprite->GetHeight() - 30;

	objectArray.emplace_back(canhaoVermelho1GO);


	// Base 2
	auto baseVermelha2GO = new GameObject();
	auto baseVermelha2Sprite = new Sprite(*baseVermelha2GO, "./assets/img/Boss Final/torre2/base_torre2.png");

	baseVermelha2GO->AddComponent(baseVermelha2Sprite);
	baseVermelha2GO->box.x = 600;
	baseVermelha2GO->box.y = finalBossGO->box.y - baseC;

	objectArray.emplace_back(baseVermelha2GO);

	// Canhao 2
	canhaoVermelho2 = new CanhaoVermelho(*canhaoVermelho2GO);
	canhaoVermelho2GO->AddComponent(canhaoVermelho2);
	canhaoVermelho2GO->box.x = baseVermelha2GO->box.x + 5;
	canhaoVermelho2GO->box.y = baseVermelha2GO->box.y + baseVermelha2Sprite->GetHeight() - 30;
	canhaoVermelho2->doMeio = true;

	objectArray.emplace_back(canhaoVermelho2GO);


	// Base 3
	auto baseVermelha3GO = new GameObject();
	auto baseVermelha3Sprite = new Sprite(*baseVermelha3GO, "./assets/img/Boss Final/torre2/base_torre2.png");

	baseVermelha3GO->AddComponent(baseVermelha3Sprite);
	baseVermelha3GO->box.x = 850;
	baseVermelha3GO->box.y = finalBossGO->box.y - baseC;

	objectArray.emplace_back(baseVermelha3GO);

	// Canhao 3
	canhaoVermelho3 = new CanhaoVermelho(*canhaoVermelho3GO);
	canhaoVermelho3GO->AddComponent(canhaoVermelho3);
	canhaoVermelho3GO->box.x = baseVermelha3GO->box.x + 5;
	canhaoVermelho3GO->box.y = baseVermelha3GO->box.y + baseVermelha3Sprite->GetHeight() - 30;

	objectArray.emplace_back(canhaoVermelho3GO);



	///////////////////////////////////////////
	//		Carrega os Canhoao Amarelo		//
	/////////////////////////////////////////

	// Base
	auto baseAmarelaGO = new GameObject();
	auto baseAmarelaSprite = new Sprite(*baseAmarelaGO, "./assets/img/Boss Final/torre1/base_torre1.png");

	baseAmarelaGO->AddComponent(baseAmarelaSprite);
	baseAmarelaGO->box.x = finalBossGO->box.x + finalBoss->sprite->GetWidth() - baseAmarelaSprite->GetWidth();
	baseAmarelaGO->box.y = finalBossGO->box.y + 3 * ONETILESQUARE;

	objectArray.emplace_back(baseAmarelaGO);
	
	// Canhao
	canhaoAmarelo = new CanhaoAmarelo(*canhaoAmareloGO);
	canhaoAmareloGO->AddComponent(canhaoAmarelo);
	canhaoAmareloGO->box.x = baseAmarelaGO->box.x + 5;
	canhaoAmareloGO->box.y = baseAmarelaGO->box.y + baseVermelha3Sprite->GetHeight() - 30;
	
	objectArray.emplace_back(canhaoAmareloGO);
	

	///////////////////////////////////
	//		Carrega o CoatGuy		//
	/////////////////////////////////
	coatGuy = new CoatGuy(*coatGuyGO);

	coatGuyGO->AddComponent(coatGuy);
	coatGuyGO->box.x = 60 * ONETILESQUARE;
	coatGuyGO->box.y = 800 - coatGuyGO->box.h - 100;

	//objectArray.emplace_back(coatGuyGO);


	///////////////////////////////////
	//		Carrega a Personagem	//
	/////////////////////////////////
	player = new Player(*playerGO);

	playerGO->AddComponent(player);
	playerGO->box.x = 400;
	playerGO->box.y = 800 - playerGO->box.h;

	objectArray.emplace_back(playerGO);
	Camera::Follow(playerGO);			// Coloca a camera para seguir o Penguin

	//Camera::Unfollow();

}

void GameState2::Update(float dt) {
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
	auto Chao = new TileMap(*chaoGO, "./assets/map/Level3/Tile_Chao.txt", tileSet);

	Chao->colide = true;

	//chaoGO->box.w = Chao->GetWidth() * tileSet->GetTileWidth();
	//chaoGO->box.h = Chao->GetHeight() * tileSet->GetTileHeight();

	chaoGO->box.w = Chao->GetWidth() * tileSet->GetTileWidth();
	chaoGO->box.h = Chao->GetHeight() * tileSet->GetTileHeight();

	chaoGO->AddComponent(Chao);
	objectArray.emplace_back(chaoGO);
	///////////////////////////////////////////////////////////////

	///////////////////////////////
	//			FUNDO			//
	/////////////////////////////

	auto BackGroundGO = new GameObject();

	BackGroundSprite = new Sprite(*BackGroundGO, "./assets/img/Level1/objeto_mapa2.png");

	BackGroundGO->box.x = (0) * tileSet->GetTileWidth() + chaoGO->box.x;
	BackGroundGO->box.y = (-32) * tileSet->GetTileHeight() + chaoGO->box.y;

	BackGroundGO->AddComponent(BackGroundSprite);
	objectArray.emplace_back(BackGroundGO);

	////////////////////////////////


	///////////////////////////////
	//		MAXIMUM EFFORT		//
	/////////////////////////////
	auto Tile00_ColunaGO = new GameObject();
	Tile00_ColunaGO->box.x = (0) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile00_ColunaGO->box.y = (-14) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile00_Coluna = new TileMap(*Tile00_ColunaGO, "./assets/map/Level3/Tile00_Coluna.txt", tileSet);
	tileMap_Tile00_Coluna->colide = true;

	Tile00_ColunaGO->box.w = tileMap_Tile00_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile00_ColunaGO->box.h = tileMap_Tile00_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile00_ColunaGO->AddComponent(tileMap_Tile00_Coluna);
	objectArray.emplace_back(Tile00_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile01_ColunaGO = new GameObject();
	Tile01_ColunaGO->box.x = (21) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile01_ColunaGO->box.y = (-14) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile01_Coluna = new TileMap(*Tile01_ColunaGO, "./assets/map/Level3/Tile01_Coluna.txt", tileSet);
	tileMap_Tile01_Coluna->colide = true;

	Tile01_ColunaGO->box.w = tileMap_Tile01_Coluna->GetWidth() * tileSet->GetTileWidth();
	Tile01_ColunaGO->box.h = tileMap_Tile01_Coluna->GetHeight() * tileSet->GetTileHeight();

	Tile01_ColunaGO->AddComponent(tileMap_Tile01_Coluna);
	objectArray.emplace_back(Tile01_ColunaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 




	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile03_LinhaGO = new GameObject();
	Tile03_LinhaGO->box.x = (4) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile03_LinhaGO->box.y = (-4) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile03_Linha = new TileMap(*Tile03_LinhaGO, "./assets/map/Level3/Tile03_Linha.txt", tileSet);
	tileMap_Tile03_Linha->colide = true;

	Tile03_LinhaGO->box.w = tileMap_Tile03_Linha->GetWidth() * tileSet->GetTileWidth();
	Tile03_LinhaGO->box.h = tileMap_Tile03_Linha->GetHeight() * tileSet->GetTileHeight();

	Tile03_LinhaGO->AddComponent(tileMap_Tile03_Linha);
	objectArray.emplace_back(Tile03_LinhaGO);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile04_LinhaGO = new GameObject();
	Tile04_LinhaGO->box.x = (12) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile04_LinhaGO->box.y = (-4) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Tile04_Linha = new TileMap(*Tile04_LinhaGO, "./assets/map/Level3/Tile04_Linha.txt", tileSet);
	tileMap_Tile04_Linha->colide = true;

	Tile04_LinhaGO->box.w = tileMap_Tile04_Linha->GetWidth() * tileSet->GetTileWidth();
	Tile04_LinhaGO->box.h = tileMap_Tile04_Linha->GetHeight() * tileSet->GetTileHeight();

	Tile04_LinhaGO->AddComponent(tileMap_Tile04_Linha);
	objectArray.emplace_back(Tile04_LinhaGO);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 

	auto TileAUX = new GameObject();
	TileAUX->box.x = (18) * tileSet->GetTileWidth() + chaoGO->box.x;
	TileAUX->box.y = (-11) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_TileAUX = new TileMap(*TileAUX, "./assets/map/Level3/Tile_AUX.txt", tileSet);
	tileMap_TileAUX->colide = true;

	TileAUX->box.w = tileMap_TileAUX->GetWidth() * tileSet->GetTileWidth();
	TileAUX->box.h = tileMap_TileAUX->GetHeight() * tileSet->GetTileHeight();

	TileAUX->AddComponent(tileMap_TileAUX);
	objectArray.emplace_back(TileAUX);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	auto Tile_TetoGO = new GameObject();
	Tile_TetoGO->box.x = (0) * tileSet->GetTileWidth() + chaoGO->box.x;
	Tile_TetoGO->box.y = (-16) * tileSet->GetTileHeight() + chaoGO->box.y;

	auto tileMap_Teto = new TileMap(*Tile_TetoGO, "./assets/map/Level3/Tile_Teto.txt", tileSet);
	tileMap_Teto->colide = true;

	Tile_TetoGO->box.w = tileMap_Teto->GetWidth() * tileSet->GetTileWidth();
	Tile_TetoGO->box.h = tileMap_Teto->GetHeight() * tileSet->GetTileHeight();

	Tile_TetoGO->AddComponent(tileMap_Teto);
	objectArray.emplace_back(Tile_TetoGO);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 


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