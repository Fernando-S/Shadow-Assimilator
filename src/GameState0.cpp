#include "GameState0.h"
#include "Game.h"
#include "GameData.h"


auto surpriseGO = new GameObject();
auto HPbarGO = new GameObject();
auto playerGO = new GameObject();
auto player = new Player(*playerGO);
auto chaoGO = new GameObject();


bool dois = false, tres = false, quatro = false, cinco = false, meia = false, sete = false, oito = false, mostrando = false;
bool cima1 = false, cima2 = false, baixo1 = false, baixo2 = false, esquerda1 = false, esquerda2 = false, direita1 = false, direita2 = false;

GameState0::GameState0() {
}

void GameState0::LoadAssets() {
	int i;

/////////////////////////////////////////////
//	  Carrega a Musica e aperta o play	  //
///////////////////////////////////////////
	//backgroundMusic = *new Music("./assets/audio/Basshunter_DotA.mp3");
	backgroundMusic = *new Music("./assets/audio/Shadow_Assimilator_-_Theme_1.mp3");
	backgroundMusic.Play();


/////////////////////////////////
//	  Carrega o Background	  //
///////////////////////////////
	
	auto bgGO = new GameObject();
	auto bg = new Sprite(*bgGO, "./assets/img/background.png");
	//bg->background = true;				// Seta a flag de que eh o background que vai ser seguido	
	
	// Seta a escala e posiciona no centro da tela
	bg->SetScale(1.3333, 1.3333);	// (resolution width / image width) * escala que queremos, (resolution height / image height) * escala que queremos

	auto bgCamFollower = new CameraFollower(*bgGO);
	bgGO->AddComponent(bgCamFollower);


	bgGO->box.h = bg->GetHeight();
	bgGO->box.w = bg->GetWidth();

	bgGO->AddComponent(bg);
	objectArray.emplace_back(bgGO);






	// Chama funcao que carrega todas as contrucoes (chaos e predios) 
	//LoadBuildings();

	
	
	// Teste do novo TileSet
	chaoGO->box.x = 0;
	chaoGO->box.y = 800;
	LoadTest();
	
	auto colidemGO = new GameObject();
	colidemGO->box.x = 0;
	//colidemGO->box.y = -1056;
	colidemGO->box.y = -288;

	auto backgroundGO = new GameObject();
	backgroundGO->box.x = 0;
	//backgroundGO->box.y = -1056;
	backgroundGO->box.y = -288;

	

	//auto tileSet = new TileSet(64, 64, "./assets/img/tileset.png");
	//auto tileMap = new TileMap(*chaoGO, "./assets/map/MEUtileMap.txt", tileSet);


	// TileSet de 40 por 40
//	auto tileSet = new TileSet(40, 40, "./assets/img/tilesetPRETOeLARANJA(40x40).png");
//	auto tileMap = new TileMap(*chaoGO, "./assets/map/tileMap40x40.txt", tileSet);


	// Teste do TileSet de 80 por 80 do chao
	auto tileSet = new TileSet(64, 64, "./assets/img/TileSetAzul.png");
	//auto tileSetEscuro = new TileSet(32, 32, "./assets/img/tileESCURO.png");
	auto tileSetEscuro = new TileSet(64, 64, "./assets/img/128sepa.png");

	auto tileMap_Background = new TileMap(*backgroundGO, "./assets/map/tileMap_TUDAOBACKGROUNDOTIMIZADO.txt", tileSetEscuro);
	//auto tileMap_Background = new TileMap(*backgroundGO, "./assets/map/tileMap_TUDAOBACKGROUND.txt", tileSet);
	//auto tileMap_Colidem = new TileMap(*colidemGO, "./assets/map/tileMap_TUDAO.txt", tileSet);
	auto tileMap_Colidem = new TileMap(*colidemGO, "./assets/map/tileMap_TUDAOOTIMIZADO.txt", tileSet);
	//auto tileMap_Chao = new TileMap(*chaoGO, "./assets/map/tileMap_CHAOZAO.txt", tileSet);

	
	tileMap_Background->colide = false;
	tileMap_Colidem->colide = false;
	//tileMap_Chao->colide = true;

	//chaoGO->box.w = tileMap_Chao->GetWidth() * tileSet->GetTileWidth();
	//chaoGO->box.h = tileMap_Chao->GetHeight() * tileSet->GetTileHeight();

	//chaoGO->AddComponent(tileMap_Chao);
	//objectArray.emplace_back(chaoGO);
	
	colidemGO->AddComponent(tileMap_Colidem);
	//objectArray.emplace_back(colidemGO);

	backgroundGO->AddComponent(tileMap_Background);
	//objectArray.emplace_back(backgroundGO);



	auto torre1LGO = new GameObject(); // declara a parede esquerda da torre
	torre1LGO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x; //declara onde a torre ficará no eixo x
	torre1LGO->box.y = (- 13 * tileSet->GetTileHeight()) + chaoGO->box.y; //declara onde a torre ficará no eixo y

	auto tileMap_torre1L = new TileMap(*torre1LGO, "./assets/map/tileMap_torre1L.txt", tileSet);
	tileMap_torre1L->colide = true;

	torre1LGO->box.w = tileMap_torre1L->GetWidth() * tileSet->GetTileWidth();
	torre1LGO->box.h = tileMap_torre1L->GetHeight() * tileSet->GetTileHeight();

	torre1LGO->AddComponent(tileMap_torre1L);
	objectArray.emplace_back(torre1LGO);





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
	//robotGO->box.PlaceCenter(Vec2(3000, /*800 - robotGO->box.h*/300));
	robotGO->box.x = 3000;
	robotGO->box.y = 300;

	objectArray.emplace_back(robotGO);



///////////////////////////////////
//		Carrega a Personagem	//
/////////////////////////////////
	//auto playerGO = new GameObject();
	//auto player = new Player(*playerGO);
	playerGO->AddComponent(player);
	//playerGO->box.PlaceCenter(Vec2(1600, /*400 - playerGO->box.h*/ 300));
	playerGO->box.x = 1500;
	playerGO->box.y = 800-playerGO->box.h;

	objectArray.emplace_back(playerGO);

	Camera::Follow(playerGO);			// Coloca a camera para seguir o Penguin
	


/*
	// Carrega o Alien com 3 minions
	auto alienGO = new GameObject();

	auto alien = new Alien(*alienGO, 3);
	alienGO->box = {512, 300};
	alienGO->box.Centralize();

	alienGO->AddComponent(alien);
	objectArray.emplace_back(alienGO);
*/
	
/*
	for (i = 0; i < ALIEN_NUMBER; i++) {
		auto alienGO = new GameObject();

		auto alien = new Alien(*alienGO, 3, (std::rand() % (ALIEN_RESTING_TIME * 100)) / 100.f);

		alienGO->AddComponent(alien);
		alienGO->box.PlaceCenter({ float(std::rand() % 1408),float(std::rand() % 1280) });

		objectArray.emplace_back(alienGO);
	}
*/



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

	ChangePlayerHP();
	
	quitRequested = inputManager.QuitRequested();			// Seta o quitRequested ao fechar o jogo
	popRequested = inputManager.KeyPress(ESCAPE_KEY);		// Seta o popRequested para retornar a TitleSet ao apertar ESC
	UpdateArray(dt);										// Faz o update de cada GameObject no objectArray

	/*
	// KONAMI CODE
	// todo - Apertar 2 teclas seguidas nao funciona (reconhece as duas apertando soh uma vez). Usar um timer pra resolver isso
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

	std::cout << "chaoGO.x = " << chaoGO->box.x << std::endl;
	std::cout << "chaoGO.y = " << chaoGO->box.y << std::endl;

	std::cout << "playerGO.x = " << playerGO->box.x << std::endl;
	std::cout << "playerGO.y = " << playerGO->box.y << std::endl;




	// PENSADOR CODE
	if (surpriseGO) {
		if ( (inputManager.KeyRelease(TWO_KEY) || inputManager.KeyRelease(NUMPAD_TWO_KEY)) && !dois) {
			dois = true;
			tres = quatro = cinco = meia = sete = oito = false;
			std::cout << "dois = true" << std::endl;
		}
		if ( (inputManager.KeyRelease(THREE_KEY) || inputManager.KeyRelease(NUMPAD_THREE_KEY)) && dois) {
			tres = true;
			dois = quatro = cinco = meia = sete = oito = false;
			std::cout << "tres = true" << std::endl;
		}
		if ( (inputManager.KeyRelease(FOUR_KEY) || inputManager.KeyRelease(NUMPAD_FOUR_KEY)) && tres) {
			quatro = true;
			dois = tres = cinco = meia = sete = oito = false;
			std::cout << "quatro = true" << std::endl;
		}
		if ( (inputManager.KeyRelease(FIVE_KEY) || inputManager.KeyRelease(NUMPAD_FIVE_KEY)) && quatro) {
			cinco = true;
			dois = tres = quatro = meia = sete = oito = false;
			std::cout << "cinco = true" << std::endl;
		}
		if ( (inputManager.KeyRelease(SIX_KEY) || inputManager.KeyRelease(NUMPAD_SIX_KEY)) && cinco) {
			meia = true;
			dois = tres = quatro = cinco = sete = oito = false;
			std::cout << "meia = true" << std::endl;
		}
		if ( (inputManager.KeyRelease(SEVEN_KEY) || inputManager.KeyRelease(NUMPAD_SEVEN_KEY)) && meia) {
			sete = true;
			dois = tres = quatro = cinco = meia = oito = false;
			std::cout << "sete = true" << std::endl;
		}
		if ((inputManager.KeyRelease(EIGHT_KEY) || inputManager.KeyRelease(NUMPAD_EIGHT_KEY)) && sete) {
			oito = true;
			dois = tres = quatro = cinco = meia = sete = false;
			std::cout << "oito = true" << std::endl;
		}

		if (oito && inputManager.KeyPress(Z_KEY)) {
		//if (oito && inputManager.MouseRelease(LEFT_MOUSE_BUTTON)) {
			mostrando = true;
			surpriseGO->render = true;
			std::cout << "mostrando = true" << std::endl;
		}
		else if (mostrando && inputManager.KeyPress(X_KEY)) {
		//else if (mostrando && inputManager.MouseRelease(RIGHT_MOUSE_BUTTON)) {
			mostrando = false;
			surpriseGO->render = false;
			std::cout << "mostrando = false" << std::endl;
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

	/*
	
	// Tela de GAME OVER
	if (!Player::player) {
		GameData::playerVictory = false;
		popRequested = true;

		// todo - pensar melhor em como mudar de tela apenas apos o termino da animacao de explosao
//		TimeToEndPlayerAnimation.Update(dt);
//		if (Player::secondsToSelfDestruction/*, selfDestructCount.Get() > secondsToSelfDestruct/)
//		if (TimeToEndPlayerAnimation.Get() > secondsToEndPlayerAnimation)
			Game::GetInstance().Push(new EndState());
	}	// Tela de WIN
	else if (Alien::alienCount == 0) {
		GameData::playerVictory = true;
		popRequested = true;

		// todo - pensar melhor em como mudar de tela apenas apos o termino da animacao de explosao
//		TimeToEndAlienAnimation.Update(dt);
//		if(TimeToEndAlienAnimation.Get() > secondsToEndAlienAnimation)
			Game::GetInstance().Push(new EndState());
	}

	*/

}

GameState0::~GameState0() {
	objectArray.clear();				// Esvazia o vetor de objetos
}

void GameState0::Render() {
	RenderArray();					// Renderiza cada GameObject no objectArray
}

void GameState0::Start() {
	LoadAssets();
	StartArray();					// Da Start em cada GameObject no objectArray
}

void GameState0::Pause() {

}

void GameState0::Resume() {

}


void GameState0::LoadTest() {
	/*
	auto chaoGO = new GameObject();
	chaoGO->box.x = 0;
	chaoGO->box.y = 800;*/

	auto tileSet = new TileSet(64, 64, "./assets/img/TileSetAzul.png");
	auto tileMap_Chao = new TileMap(*chaoGO, "./assets/map/tileMap_CHAOZAO.txt", tileSet);


	tileMap_Chao->colide = true;

	chaoGO->box.w = tileMap_Chao->GetWidth() * tileSet->GetTileWidth();
	chaoGO->box.h = tileMap_Chao->GetHeight() * tileSet->GetTileHeight();

	chaoGO->AddComponent(tileMap_Chao);
	objectArray.emplace_back(chaoGO);


	//////////////////////////////////////////////
	// Comeco dos paranaues

	auto Tile00GO = new GameObject();
	Tile00GO->box.x = /*tileSet->GetTileWidth() * ONETILESQUARE +*/ chaoGO->box.x;
	Tile00GO->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile00 = new TileMap(*Tile00GO, "./assets/map/tileMap_Tile00.txt", tileSet);
	tileMap_Tile00->colide = true;

	Tile00GO->box.w = tileMap_Tile00->GetWidth() * tileSet->GetTileWidth();
	Tile00GO->box.h = tileMap_Tile00->GetHeight() * tileSet->GetTileHeight();

	Tile00GO->AddComponent(tileMap_Tile00);
	objectArray.emplace_back(Tile00GO);

	// Segunda parede

	auto Tile00GO1 = new GameObject();
	Tile00GO1->box.x = 9 * ONETILESQUARE + chaoGO->box.x;
	Tile00GO1->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;
	auto tileMap_Tile001 = new TileMap(*Tile00GO1, "./assets/map/tileMap_Tile00.txt", tileSet);
	tileMap_Tile001->colide = true;
	Tile00GO1->box.w = tileMap_Tile001->GetWidth() * tileSet->GetTileWidth();
	Tile00GO1->box.h = tileMap_Tile001->GetHeight() * tileSet->GetTileHeight();
	Tile00GO1->AddComponent(tileMap_Tile001);
	objectArray.emplace_back(Tile00GO1);



	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile01GO = new GameObject();
	Tile01GO->box.x =  1 * ONETILESQUARE + chaoGO->box.x;
	Tile01GO->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile01 = new TileMap(*Tile01GO, "./assets/map/tileMap_Tile01.txt", tileSet);
	tileMap_Tile01->colide = true;

	Tile01GO->box.w = tileMap_Tile01->GetWidth() * tileSet->GetTileWidth();
	Tile01GO->box.h = tileMap_Tile01->GetHeight() * tileSet->GetTileHeight();

	Tile01GO->AddComponent(tileMap_Tile01);
	objectArray.emplace_back(Tile01GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile02GO = new GameObject();
	Tile02GO->box.x =  2 * ONETILESQUARE + chaoGO->box.x;
	Tile02GO->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile02 = new TileMap(*Tile02GO, "./assets/map/tileMap_Tile02.txt", tileSet);
	tileMap_Tile02->colide = true;

	Tile02GO->box.w = tileMap_Tile02->GetWidth() * tileSet->GetTileWidth();
	Tile02GO->box.h = tileMap_Tile02->GetHeight() * tileSet->GetTileHeight();

	Tile02GO->AddComponent(tileMap_Tile02);
	objectArray.emplace_back(Tile02GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile03GO = new GameObject();
	Tile03GO->box.x =  3 * ONETILESQUARE + chaoGO->box.x;
	Tile03GO->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile03 = new TileMap(*Tile03GO, "./assets/map/tileMap_Tile03.txt", tileSet);
	tileMap_Tile03->colide = true;

	Tile03GO->box.w = tileMap_Tile03->GetWidth() * tileSet->GetTileWidth();
	Tile03GO->box.h = tileMap_Tile03->GetHeight() * tileSet->GetTileHeight();

	Tile03GO->AddComponent(tileMap_Tile03);
	objectArray.emplace_back(Tile03GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile04GO = new GameObject();
	Tile04GO->box.x =  4 * ONETILESQUARE + chaoGO->box.x;
	Tile04GO->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile04 = new TileMap(*Tile04GO, "./assets/map/tileMap_Tile04.txt", tileSet);
	tileMap_Tile04->colide = true;

	Tile04GO->box.w = tileMap_Tile04->GetWidth() * tileSet->GetTileWidth();
	Tile04GO->box.h = tileMap_Tile04->GetHeight() * tileSet->GetTileHeight();

	Tile04GO->AddComponent(tileMap_Tile04);
	objectArray.emplace_back(Tile04GO);




	//// PLATAFORMA WOLOLO

	auto TileWOLOLOGO = new GameObject();
	TileWOLOLOGO->box.x = 10 * ONETILESQUARE + chaoGO->box.x;
	TileWOLOLOGO->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_TileWOLOLO = new TileMap(*TileWOLOLOGO, "./assets/map/tileMap_TileWOLOLO.txt", tileSet);
	tileMap_TileWOLOLO->colide = true;

	TileWOLOLOGO->box.w = tileMap_TileWOLOLO->GetWidth() * tileSet->GetTileWidth();
	TileWOLOLOGO->box.h = tileMap_TileWOLOLO->GetHeight() * tileSet->GetTileHeight();

	TileWOLOLOGO->AddComponent(tileMap_TileWOLOLO);
	objectArray.emplace_back(TileWOLOLOGO);



	//// PLATAFORMA WOLOLO 2

	auto TileWOLOLOGO2 = new GameObject();
	TileWOLOLOGO2->box.x = 26 * ONETILESQUARE + chaoGO->box.x;
	TileWOLOLOGO2->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_TileWOLOLO2 = new TileMap(*TileWOLOLOGO2, "./assets/map/tileMap_TileWOLOLO.txt", tileSet);
	tileMap_TileWOLOLO2->colide = true;

	TileWOLOLOGO2->box.w = tileMap_TileWOLOLO2->GetWidth() * tileSet->GetTileWidth();
	TileWOLOLOGO2->box.h = tileMap_TileWOLOLO2->GetHeight() * tileSet->GetTileHeight();

	TileWOLOLOGO2->AddComponent(tileMap_TileWOLOLO2);
	objectArray.emplace_back(TileWOLOLOGO2);



	//// PLATAFORMA WOLOLO 3

	auto TileWOLOLOGO3 = new GameObject();
	TileWOLOLOGO3->box.x = 40 * ONETILESQUARE + chaoGO->box.x;
	TileWOLOLOGO3->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_TileWOLOLO3 = new TileMap(*TileWOLOLOGO3, "./assets/map/tileMap_TileWOLOLO.txt", tileSet);
	tileMap_TileWOLOLO3->colide = true;

	TileWOLOLOGO3->box.w = tileMap_TileWOLOLO3->GetWidth() * tileSet->GetTileWidth();
	TileWOLOLOGO3->box.h = tileMap_TileWOLOLO3->GetHeight() * tileSet->GetTileHeight();

	TileWOLOLOGO3->AddComponent(tileMap_TileWOLOLO3);
	objectArray.emplace_back(TileWOLOLOGO3);



	// Terceira parede

	auto Tile00GO2 = new GameObject();
	Tile00GO2->box.x = 26 * ONETILESQUARE + chaoGO->box.x;
	Tile00GO2->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;
	auto tileMap_Tile002 = new TileMap(*Tile00GO2, "./assets/map/tileMap_Tile00.txt", tileSet);
	tileMap_Tile002->colide = true;
	Tile00GO2->box.w = tileMap_Tile002->GetWidth() * tileSet->GetTileWidth();
	Tile00GO2->box.h = tileMap_Tile002->GetHeight() * tileSet->GetTileHeight();
	Tile00GO2->AddComponent(tileMap_Tile002);
	objectArray.emplace_back(Tile00GO2);



	// Quarta parede

	auto Tile00GO3 = new GameObject();
	Tile00GO3->box.x = 48 * ONETILESQUARE + chaoGO->box.x;
	Tile00GO3->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;
	auto tileMap_Tile003 = new TileMap(*Tile00GO3, "./assets/map/tileMap_Tile00.txt", tileSet);
	tileMap_Tile003->colide = true;
	Tile00GO3->box.w = tileMap_Tile003->GetWidth() * tileSet->GetTileWidth();
	Tile00GO3->box.h = tileMap_Tile003->GetHeight() * tileSet->GetTileHeight();
	Tile00GO3->AddComponent(tileMap_Tile003);
	objectArray.emplace_back(Tile00GO3);




	/*
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile05GO = new GameObject();
	Tile05GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile05GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile05 = new TileMap(*Tile05GO, "./assets/map/tileMap_Tile05.txt", tileSet);
	tileMap_Tile05->colide = true;

	Tile05GO->box.w = tileMap_Tile05->GetWidth() * tileSet->GetTileWidth();
	Tile05GO->box.h = tileMap_Tile05->GetHeight() * tileSet->GetTileHeight();

	Tile05GO->AddComponent(tileMap_Tile05);
	objectArray.emplace_back(Tile05GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile06GO = new GameObject();
	Tile06GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile06GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile06 = new TileMap(*Tile06GO, "./assets/map/tileMap_Tile06.txt", tileSet);
	tileMap_Tile06->colide = true;

	Tile06GO->box.w = tileMap_Tile06->GetWidth() * tileSet->GetTileWidth();
	Tile06GO->box.h = tileMap_Tile06->GetHeight() * tileSet->GetTileHeight();

	Tile06GO->AddComponent(tileMap_Tile06);
	objectArray.emplace_back(Tile06GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile07GO = new GameObject();
	Tile07GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile07GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile07 = new TileMap(*Tile07GO, "./assets/map/tileMap_Tile07.txt", tileSet);
	tileMap_Tile07->colide = true;

	Tile07GO->box.w = tileMap_Tile07->GetWidth() * tileSet->GetTileWidth();
	Tile07GO->box.h = tileMap_Tile07->GetHeight() * tileSet->GetTileHeight();

	Tile07GO->AddComponent(tileMap_Tile07);
	objectArray.emplace_back(Tile07GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile08GO = new GameObject();
	Tile08GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile08GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile08 = new TileMap(*Tile08GO, "./assets/map/tileMap_Tile08.txt", tileSet);
	tileMap_Tile08->colide = true;

	Tile08GO->box.w = tileMap_Tile08->GetWidth() * tileSet->GetTileWidth();
	Tile08GO->box.h = tileMap_Tile08->GetHeight() * tileSet->GetTileHeight();

	Tile08GO->AddComponent(tileMap_Tile08);
	objectArray.emplace_back(Tile08GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile09GO = new GameObject();
	Tile09GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile09GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile09 = new TileMap(*Tile09GO, "./assets/map/tileMap_Tile09.txt", tileSet);
	tileMap_Tile09->colide = true;

	Tile09GO->box.w = tileMap_Tile09->GetWidth() * tileSet->GetTileWidth();
	Tile09GO->box.h = tileMap_Tile09->GetHeight() * tileSet->GetTileHeight();

	Tile09GO->AddComponent(tileMap_Tile09);
	objectArray.emplace_back(Tile09GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile10GO = new GameObject();
	Tile10GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile10GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile10 = new TileMap(*Tile10GO, "./assets/map/tileMap_Tile10.txt", tileSet);
	tileMap_Tile10->colide = true;

	Tile10GO->box.w = tileMap_Tile10->GetWidth() * tileSet->GetTileWidth();
	Tile10GO->box.h = tileMap_Tile10->GetHeight() * tileSet->GetTileHeight();

	Tile10GO->AddComponent(tileMap_Tile10);
	objectArray.emplace_back(Tile10GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile11GO = new GameObject();
	Tile11GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile11GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile11 = new TileMap(*Tile11GO, "./assets/map/tileMap_Tile11.txt", tileSet);
	tileMap_Tile11->colide = true;

	Tile11GO->box.w = tileMap_Tile11->GetWidth() * tileSet->GetTileWidth();
	Tile11GO->box.h = tileMap_Tile11->GetHeight() * tileSet->GetTileHeight();

	Tile11GO->AddComponent(tileMap_Tile11);
	objectArray.emplace_back(Tile11GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile12GO = new GameObject();
	Tile12GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile12GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile12 = new TileMap(*Tile12GO, "./assets/map/tileMap_Tile12.txt", tileSet);
	tileMap_Tile12->colide = true;

	Tile12GO->box.w = tileMap_Tile12->GetWidth() * tileSet->GetTileWidth();
	Tile12GO->box.h = tileMap_Tile12->GetHeight() * tileSet->GetTileHeight();

	Tile12GO->AddComponent(tileMap_Tile12);
	objectArray.emplace_back(Tile12GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile13GO = new GameObject();
	Tile13GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile13GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile13 = new TileMap(*Tile13GO, "./assets/map/tileMap_Tile13.txt", tileSet);
	tileMap_Tile13->colide = true;

	Tile13GO->box.w = tileMap_Tile13->GetWidth() * tileSet->GetTileWidth();
	Tile13GO->box.h = tileMap_Tile13->GetHeight() * tileSet->GetTileHeight();

	Tile13GO->AddComponent(tileMap_Tile13);
	objectArray.emplace_back(Tile13GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile14GO = new GameObject();
	Tile14GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile14GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile14 = new TileMap(*Tile14GO, "./assets/map/tileMap_Tile14.txt", tileSet);
	tileMap_Tile14->colide = true;

	Tile14GO->box.w = tileMap_Tile14->GetWidth() * tileSet->GetTileWidth();
	Tile14GO->box.h = tileMap_Tile14->GetHeight() * tileSet->GetTileHeight();

	Tile14GO->AddComponent(tileMap_Tile14);
	objectArray.emplace_back(Tile14GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile15GO = new GameObject();
	Tile15GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile15GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile15 = new TileMap(*Tile15GO, "./assets/map/tileMap_Tile15.txt", tileSet);
	tileMap_Tile15->colide = true;

	Tile15GO->box.w = tileMap_Tile15->GetWidth() * tileSet->GetTileWidth();
	Tile15GO->box.h = tileMap_Tile15->GetHeight() * tileSet->GetTileHeight();

	Tile15GO->AddComponent(tileMap_Tile15);
	objectArray.emplace_back(Tile15GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile16GO = new GameObject();
	Tile16GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile16GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile16 = new TileMap(*Tile16GO, "./assets/map/tileMap_Tile16.txt", tileSet);
	tileMap_Tile16->colide = true;

	Tile16GO->box.w = tileMap_Tile16->GetWidth() * tileSet->GetTileWidth();
	Tile16GO->box.h = tileMap_Tile16->GetHeight() * tileSet->GetTileHeight();

	Tile16GO->AddComponent(tileMap_Tile16);
	objectArray.emplace_back(Tile16GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile17GO = new GameObject();
	Tile17GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile17GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile17 = new TileMap(*Tile17GO, "./assets/map/tileMap_Tile17.txt", tileSet);
	tileMap_Tile17->colide = true;

	Tile17GO->box.w = tileMap_Tile17->GetWidth() * tileSet->GetTileWidth();
	Tile17GO->box.h = tileMap_Tile17->GetHeight() * tileSet->GetTileHeight();

	Tile17GO->AddComponent(tileMap_Tile17);
	objectArray.emplace_back(Tile17GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile18GO = new GameObject();
	Tile18GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile18GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile18 = new TileMap(*Tile18GO, "./assets/map/tileMap_Tile18.txt", tileSet);
	tileMap_Tile18->colide = true;

	Tile18GO->box.w = tileMap_Tile18->GetWidth() * tileSet->GetTileWidth();
	Tile18GO->box.h = tileMap_Tile18->GetHeight() * tileSet->GetTileHeight();

	Tile18GO->AddComponent(tileMap_Tile18);
	objectArray.emplace_back(Tile18GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile19GO = new GameObject();
	Tile19GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile19GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile19 = new TileMap(*Tile19GO, "./assets/map/tileMap_Tile19.txt", tileSet);
	tileMap_Tile19->colide = true;

	Tile19GO->box.w = tileMap_Tile19->GetWidth() * tileSet->GetTileWidth();
	Tile19GO->box.h = tileMap_Tile19->GetHeight() * tileSet->GetTileHeight();

	Tile19GO->AddComponent(tileMap_Tile19);
	objectArray.emplace_back(Tile19GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile20GO = new GameObject();
	Tile20GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile20GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile20 = new TileMap(*Tile20GO, "./assets/map/tileMap_Tile20.txt", tileSet);
	tileMap_Tile20->colide = true;

	Tile20GO->box.w = tileMap_Tile20->GetWidth() * tileSet->GetTileWidth();
	Tile20GO->box.h = tileMap_Tile20->GetHeight() * tileSet->GetTileHeight();

	Tile20GO->AddComponent(tileMap_Tile20);
	objectArray.emplace_back(Tile20GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile21GO = new GameObject();
	Tile21GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile21GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile21 = new TileMap(*Tile21GO, "./assets/map/tileMap_Tile21.txt", tileSet);
	tileMap_Tile21->colide = true;

	Tile21GO->box.w = tileMap_Tile21->GetWidth() * tileSet->GetTileWidth();
	Tile21GO->box.h = tileMap_Tile21->GetHeight() * tileSet->GetTileHeight();

	Tile21GO->AddComponent(tileMap_Tile21);
	objectArray.emplace_back(Tile21GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile22GO = new GameObject();
	Tile22GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile22GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile22 = new TileMap(*Tile22GO, "./assets/map/tileMap_Tile22.txt", tileSet);
	tileMap_Tile22->colide = true;

	Tile22GO->box.w = tileMap_Tile22->GetWidth() * tileSet->GetTileWidth();
	Tile22GO->box.h = tileMap_Tile22->GetHeight() * tileSet->GetTileHeight();

	Tile22GO->AddComponent(tileMap_Tile22);
	objectArray.emplace_back(Tile22GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile23GO = new GameObject();
	Tile23GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile23GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile23 = new TileMap(*Tile23GO, "./assets/map/tileMap_Tile23.txt", tileSet);
	tileMap_Tile23->colide = true;

	Tile23GO->box.w = tileMap_Tile23->GetWidth() * tileSet->GetTileWidth();
	Tile23GO->box.h = tileMap_Tile23->GetHeight() * tileSet->GetTileHeight();

	Tile23GO->AddComponent(tileMap_Tile23);
	objectArray.emplace_back(Tile23GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile24GO = new GameObject();
	Tile24GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile24GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile24 = new TileMap(*Tile24GO, "./assets/map/tileMap_Tile24.txt", tileSet);
	tileMap_Tile24->colide = true;

	Tile24GO->box.w = tileMap_Tile24->GetWidth() * tileSet->GetTileWidth();
	Tile24GO->box.h = tileMap_Tile24->GetHeight() * tileSet->GetTileHeight();

	Tile24GO->AddComponent(tileMap_Tile24);
	objectArray.emplace_back(Tile24GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile25GO = new GameObject();
	Tile25GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile25GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile25 = new TileMap(*Tile25GO, "./assets/map/tileMap_Tile25.txt", tileSet);
	tileMap_Tile25->colide = true;

	Tile25GO->box.w = tileMap_Tile25->GetWidth() * tileSet->GetTileWidth();
	Tile25GO->box.h = tileMap_Tile25->GetHeight() * tileSet->GetTileHeight();

	Tile25GO->AddComponent(tileMap_Tile25);
	objectArray.emplace_back(Tile25GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile26GO = new GameObject();
	Tile26GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile26GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile26 = new TileMap(*Tile26GO, "./assets/map/tileMap_Tile26.txt", tileSet);
	tileMap_Tile26->colide = true;

	Tile26GO->box.w = tileMap_Tile26->GetWidth() * tileSet->GetTileWidth();
	Tile26GO->box.h = tileMap_Tile26->GetHeight() * tileSet->GetTileHeight();

	Tile26GO->AddComponent(tileMap_Tile26);
	objectArray.emplace_back(Tile26GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile27GO = new GameObject();
	Tile27GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile27GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile27 = new TileMap(*Tile27GO, "./assets/map/tileMap_Tile27.txt", tileSet);
	tileMap_Tile27->colide = true;

	Tile27GO->box.w = tileMap_Tile27->GetWidth() * tileSet->GetTileWidth();
	Tile27GO->box.h = tileMap_Tile27->GetHeight() * tileSet->GetTileHeight();

	Tile27GO->AddComponent(tileMap_Tile27);
	objectArray.emplace_back(Tile27GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile28GO = new GameObject();
	Tile28GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile28GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile28 = new TileMap(*Tile28GO, "./assets/map/tileMap_Tile28.txt", tileSet);
	tileMap_Tile28->colide = true;

	Tile28GO->box.w = tileMap_Tile28->GetWidth() * tileSet->GetTileWidth();
	Tile28GO->box.h = tileMap_Tile28->GetHeight() * tileSet->GetTileHeight();

	Tile28GO->AddComponent(tileMap_Tile28);
	objectArray.emplace_back(Tile28GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile29GO = new GameObject();
	Tile29GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile29GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile29 = new TileMap(*Tile29GO, "./assets/map/tileMap_Tile29.txt", tileSet);
	tileMap_Tile29->colide = true;

	Tile29GO->box.w = tileMap_Tile29->GetWidth() * tileSet->GetTileWidth();
	Tile29GO->box.h = tileMap_Tile29->GetHeight() * tileSet->GetTileHeight();

	Tile29GO->AddComponent(tileMap_Tile29);
	objectArray.emplace_back(Tile29GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile30GO = new GameObject();
	Tile30GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile30GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile30 = new TileMap(*Tile30GO, "./assets/map/tileMap_Tile30.txt", tileSet);
	tileMap_Tile30->colide = true;

	Tile30GO->box.w = tileMap_Tile30->GetWidth() * tileSet->GetTileWidth();
	Tile30GO->box.h = tileMap_Tile30->GetHeight() * tileSet->GetTileHeight();

	Tile30GO->AddComponent(tileMap_Tile30);
	objectArray.emplace_back(Tile30GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile31GO = new GameObject();
	Tile31GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile31GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile31 = new TileMap(*Tile31GO, "./assets/map/tileMap_Tile31.txt", tileSet);
	tileMap_Tile31->colide = true;

	Tile31GO->box.w = tileMap_Tile31->GetWidth() * tileSet->GetTileWidth();
	Tile31GO->box.h = tileMap_Tile31->GetHeight() * tileSet->GetTileHeight();

	Tile31GO->AddComponent(tileMap_Tile31);
	objectArray.emplace_back(Tile31GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile32GO = new GameObject();
	Tile32GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile32GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile32 = new TileMap(*Tile32GO, "./assets/map/tileMap_Tile32.txt", tileSet);
	tileMap_Tile32->colide = true;

	Tile32GO->box.w = tileMap_Tile32->GetWidth() * tileSet->GetTileWidth();
	Tile32GO->box.h = tileMap_Tile32->GetHeight() * tileSet->GetTileHeight();

	Tile32GO->AddComponent(tileMap_Tile32);
	objectArray.emplace_back(Tile32GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile33GO = new GameObject();
	Tile33GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile33GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile33 = new TileMap(*Tile33GO, "./assets/map/tileMap_Tile33.txt", tileSet);
	tileMap_Tile33->colide = true;

	Tile33GO->box.w = tileMap_Tile33->GetWidth() * tileSet->GetTileWidth();
	Tile33GO->box.h = tileMap_Tile33->GetHeight() * tileSet->GetTileHeight();

	Tile33GO->AddComponent(tileMap_Tile33);
	objectArray.emplace_back(Tile33GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile34GO = new GameObject();
	Tile34GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile34GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile34 = new TileMap(*Tile34GO, "./assets/map/tileMap_Tile34.txt", tileSet);
	tileMap_Tile34->colide = true;

	Tile34GO->box.w = tileMap_Tile34->GetWidth() * tileSet->GetTileWidth();
	Tile34GO->box.h = tileMap_Tile34->GetHeight() * tileSet->GetTileHeight();

	Tile34GO->AddComponent(tileMap_Tile34);
	objectArray.emplace_back(Tile34GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile35GO = new GameObject();
	Tile35GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile35GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile35 = new TileMap(*Tile35GO, "./assets/map/tileMap_Tile35.txt", tileSet);
	tileMap_Tile35->colide = true;

	Tile35GO->box.w = tileMap_Tile35->GetWidth() * tileSet->GetTileWidth();
	Tile35GO->box.h = tileMap_Tile35->GetHeight() * tileSet->GetTileHeight();

	Tile35GO->AddComponent(tileMap_Tile35);
	objectArray.emplace_back(Tile35GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile36GO = new GameObject();
	Tile36GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile36GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile36 = new TileMap(*Tile36GO, "./assets/map/tileMap_Tile36.txt", tileSet);
	tileMap_Tile36->colide = true;

	Tile36GO->box.w = tileMap_Tile36->GetWidth() * tileSet->GetTileWidth();
	Tile36GO->box.h = tileMap_Tile36->GetHeight() * tileSet->GetTileHeight();

	Tile36GO->AddComponent(tileMap_Tile36);
	objectArray.emplace_back(Tile36GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile37GO = new GameObject();
	Tile37GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile37GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile37 = new TileMap(*Tile37GO, "./assets/map/tileMap_Tile37.txt", tileSet);
	tileMap_Tile37->colide = true;

	Tile37GO->box.w = tileMap_Tile37->GetWidth() * tileSet->GetTileWidth();
	Tile37GO->box.h = tileMap_Tile37->GetHeight() * tileSet->GetTileHeight();

	Tile37GO->AddComponent(tileMap_Tile37);
	objectArray.emplace_back(Tile37GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile38GO = new GameObject();
	Tile38GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile38GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile38 = new TileMap(*Tile38GO, "./assets/map/tileMap_Tile38.txt", tileSet);
	tileMap_Tile38->colide = true;

	Tile38GO->box.w = tileMap_Tile38->GetWidth() * tileSet->GetTileWidth();
	Tile38GO->box.h = tileMap_Tile38->GetHeight() * tileSet->GetTileHeight();

	Tile38GO->AddComponent(tileMap_Tile38);
	objectArray.emplace_back(Tile38GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile39GO = new GameObject();
	Tile39GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile39GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile39 = new TileMap(*Tile39GO, "./assets/map/tileMap_Tile39.txt", tileSet);
	tileMap_Tile39->colide = true;

	Tile39GO->box.w = tileMap_Tile39->GetWidth() * tileSet->GetTileWidth();
	Tile39GO->box.h = tileMap_Tile39->GetHeight() * tileSet->GetTileHeight();

	Tile39GO->AddComponent(tileMap_Tile39);
	objectArray.emplace_back(Tile39GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile40GO = new GameObject();
	Tile40GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile40GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile40 = new TileMap(*Tile40GO, "./assets/map/tileMap_Tile40.txt", tileSet);
	tileMap_Tile40->colide = true;

	Tile40GO->box.w = tileMap_Tile40->GetWidth() * tileSet->GetTileWidth();
	Tile40GO->box.h = tileMap_Tile40->GetHeight() * tileSet->GetTileHeight();

	Tile40GO->AddComponent(tileMap_Tile40);
	objectArray.emplace_back(Tile40GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile41GO = new GameObject();
	Tile41GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile41GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile41 = new TileMap(*Tile41GO, "./assets/map/tileMap_Tile41.txt", tileSet);
	tileMap_Tile41->colide = true;

	Tile41GO->box.w = tileMap_Tile41->GetWidth() * tileSet->GetTileWidth();
	Tile41GO->box.h = tileMap_Tile41->GetHeight() * tileSet->GetTileHeight();

	Tile41GO->AddComponent(tileMap_Tile41);
	objectArray.emplace_back(Tile41GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile42GO = new GameObject();
	Tile42GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile42GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile42 = new TileMap(*Tile42GO, "./assets/map/tileMap_Tile42.txt", tileSet);
	tileMap_Tile42->colide = true;

	Tile42GO->box.w = tileMap_Tile42->GetWidth() * tileSet->GetTileWidth();
	Tile42GO->box.h = tileMap_Tile42->GetHeight() * tileSet->GetTileHeight();

	Tile42GO->AddComponent(tileMap_Tile42);
	objectArray.emplace_back(Tile42GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile43GO = new GameObject();
	Tile43GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile43GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile43 = new TileMap(*Tile43GO, "./assets/map/tileMap_Tile43.txt", tileSet);
	tileMap_Tile43->colide = true;

	Tile43GO->box.w = tileMap_Tile43->GetWidth() * tileSet->GetTileWidth();
	Tile43GO->box.h = tileMap_Tile43->GetHeight() * tileSet->GetTileHeight();

	Tile43GO->AddComponent(tileMap_Tile43);
	objectArray.emplace_back(Tile43GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile44GO = new GameObject();
	Tile44GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile44GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile44 = new TileMap(*Tile44GO, "./assets/map/tileMap_Tile44.txt", tileSet);
	tileMap_Tile44->colide = true;

	Tile44GO->box.w = tileMap_Tile44->GetWidth() * tileSet->GetTileWidth();
	Tile44GO->box.h = tileMap_Tile44->GetHeight() * tileSet->GetTileHeight();

	Tile44GO->AddComponent(tileMap_Tile44);
	objectArray.emplace_back(Tile44GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile45GO = new GameObject();
	Tile45GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile45GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile45 = new TileMap(*Tile45GO, "./assets/map/tileMap_Tile45.txt", tileSet);
	tileMap_Tile45->colide = true;

	Tile45GO->box.w = tileMap_Tile45->GetWidth() * tileSet->GetTileWidth();
	Tile45GO->box.h = tileMap_Tile45->GetHeight() * tileSet->GetTileHeight();

	Tile45GO->AddComponent(tileMap_Tile45);
	objectArray.emplace_back(Tile45GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile46GO = new GameObject();
	Tile46GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile46GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile46 = new TileMap(*Tile46GO, "./assets/map/tileMap_Tile46.txt", tileSet);
	tileMap_Tile46->colide = true;

	Tile46GO->box.w = tileMap_Tile46->GetWidth() * tileSet->GetTileWidth();
	Tile46GO->box.h = tileMap_Tile46->GetHeight() * tileSet->GetTileHeight();

	Tile46GO->AddComponent(tileMap_Tile46);
	objectArray.emplace_back(Tile46GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile47GO = new GameObject();
	Tile47GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile47GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile47 = new TileMap(*Tile47GO, "./assets/map/tileMap_Tile47.txt", tileSet);
	tileMap_Tile47->colide = true;

	Tile47GO->box.w = tileMap_Tile47->GetWidth() * tileSet->GetTileWidth();
	Tile47GO->box.h = tileMap_Tile47->GetHeight() * tileSet->GetTileHeight();

	Tile47GO->AddComponent(tileMap_Tile47);
	objectArray.emplace_back(Tile47GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile48GO = new GameObject();
	Tile48GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile48GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile48 = new TileMap(*Tile48GO, "./assets/map/tileMap_Tile48.txt", tileSet);
	tileMap_Tile48->colide = true;

	Tile48GO->box.w = tileMap_Tile48->GetWidth() * tileSet->GetTileWidth();
	Tile48GO->box.h = tileMap_Tile48->GetHeight() * tileSet->GetTileHeight();

	Tile48GO->AddComponent(tileMap_Tile48);
	objectArray.emplace_back(Tile48GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile49GO = new GameObject();
	Tile49GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile49GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile49 = new TileMap(*Tile49GO, "./assets/map/tileMap_Tile49.txt", tileSet);
	tileMap_Tile49->colide = true;

	Tile49GO->box.w = tileMap_Tile49->GetWidth() * tileSet->GetTileWidth();
	Tile49GO->box.h = tileMap_Tile49->GetHeight() * tileSet->GetTileHeight();

	Tile49GO->AddComponent(tileMap_Tile49);
	objectArray.emplace_back(Tile49GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile50GO = new GameObject();
	Tile50GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile50GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile50 = new TileMap(*Tile50GO, "./assets/map/tileMap_Tile50.txt", tileSet);
	tileMap_Tile50->colide = true;

	Tile50GO->box.w = tileMap_Tile50->GetWidth() * tileSet->GetTileWidth();
	Tile50GO->box.h = tileMap_Tile50->GetHeight() * tileSet->GetTileHeight();

	Tile50GO->AddComponent(tileMap_Tile50);
	objectArray.emplace_back(Tile50GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile51GO = new GameObject();
	Tile51GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile51GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile51 = new TileMap(*Tile51GO, "./assets/map/tileMap_Tile51.txt", tileSet);
	tileMap_Tile51->colide = true;

	Tile51GO->box.w = tileMap_Tile51->GetWidth() * tileSet->GetTileWidth();
	Tile51GO->box.h = tileMap_Tile51->GetHeight() * tileSet->GetTileHeight();

	Tile51GO->AddComponent(tileMap_Tile51);
	objectArray.emplace_back(Tile51GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile52GO = new GameObject();
	Tile52GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile52GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile52 = new TileMap(*Tile52GO, "./assets/map/tileMap_Tile52.txt", tileSet);
	tileMap_Tile52->colide = true;

	Tile52GO->box.w = tileMap_Tile52->GetWidth() * tileSet->GetTileWidth();
	Tile52GO->box.h = tileMap_Tile52->GetHeight() * tileSet->GetTileHeight();

	Tile52GO->AddComponent(tileMap_Tile52);
	objectArray.emplace_back(Tile52GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile53GO = new GameObject();
	Tile53GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile53GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile53 = new TileMap(*Tile53GO, "./assets/map/tileMap_Tile53.txt", tileSet);
	tileMap_Tile53->colide = true;

	Tile53GO->box.w = tileMap_Tile53->GetWidth() * tileSet->GetTileWidth();
	Tile53GO->box.h = tileMap_Tile53->GetHeight() * tileSet->GetTileHeight();

	Tile53GO->AddComponent(tileMap_Tile53);
	objectArray.emplace_back(Tile53GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile54GO = new GameObject();
	Tile54GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile54GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile54 = new TileMap(*Tile54GO, "./assets/map/tileMap_Tile54.txt", tileSet);
	tileMap_Tile54->colide = true;

	Tile54GO->box.w = tileMap_Tile54->GetWidth() * tileSet->GetTileWidth();
	Tile54GO->box.h = tileMap_Tile54->GetHeight() * tileSet->GetTileHeight();

	Tile54GO->AddComponent(tileMap_Tile54);
	objectArray.emplace_back(Tile54GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile55GO = new GameObject();
	Tile55GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile55GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile55 = new TileMap(*Tile55GO, "./assets/map/tileMap_Tile55.txt", tileSet);
	tileMap_Tile55->colide = true;

	Tile55GO->box.w = tileMap_Tile55->GetWidth() * tileSet->GetTileWidth();
	Tile55GO->box.h = tileMap_Tile55->GetHeight() * tileSet->GetTileHeight();

	Tile55GO->AddComponent(tileMap_Tile55);
	objectArray.emplace_back(Tile55GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile56GO = new GameObject();
	Tile56GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile56GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile56 = new TileMap(*Tile56GO, "./assets/map/tileMap_Tile56.txt", tileSet);
	tileMap_Tile56->colide = true;

	Tile56GO->box.w = tileMap_Tile56->GetWidth() * tileSet->GetTileWidth();
	Tile56GO->box.h = tileMap_Tile56->GetHeight() * tileSet->GetTileHeight();

	Tile56GO->AddComponent(tileMap_Tile56);
	objectArray.emplace_back(Tile56GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile57GO = new GameObject();
	Tile57GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile57GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile57 = new TileMap(*Tile57GO, "./assets/map/tileMap_Tile57.txt", tileSet);
	tileMap_Tile57->colide = true;

	Tile57GO->box.w = tileMap_Tile57->GetWidth() * tileSet->GetTileWidth();
	Tile57GO->box.h = tileMap_Tile57->GetHeight() * tileSet->GetTileHeight();

	Tile57GO->AddComponent(tileMap_Tile57);
	objectArray.emplace_back(Tile57GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile58GO = new GameObject();
	Tile58GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile58GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile58 = new TileMap(*Tile58GO, "./assets/map/tileMap_Tile58.txt", tileSet);
	tileMap_Tile58->colide = true;

	Tile58GO->box.w = tileMap_Tile58->GetWidth() * tileSet->GetTileWidth();
	Tile58GO->box.h = tileMap_Tile58->GetHeight() * tileSet->GetTileHeight();

	Tile58GO->AddComponent(tileMap_Tile58);
	objectArray.emplace_back(Tile58GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile59GO = new GameObject();
	Tile59GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile59GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile59 = new TileMap(*Tile59GO, "./assets/map/tileMap_Tile59.txt", tileSet);
	tileMap_Tile59->colide = true;

	Tile59GO->box.w = tileMap_Tile59->GetWidth() * tileSet->GetTileWidth();
	Tile59GO->box.h = tileMap_Tile59->GetHeight() * tileSet->GetTileHeight();

	Tile59GO->AddComponent(tileMap_Tile59);
	objectArray.emplace_back(Tile59GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile60GO = new GameObject();
	Tile60GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile60GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile60 = new TileMap(*Tile60GO, "./assets/map/tileMap_Tile60.txt", tileSet);
	tileMap_Tile60->colide = true;

	Tile60GO->box.w = tileMap_Tile60->GetWidth() * tileSet->GetTileWidth();
	Tile60GO->box.h = tileMap_Tile60->GetHeight() * tileSet->GetTileHeight();

	Tile60GO->AddComponent(tileMap_Tile60);
	objectArray.emplace_back(Tile60GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile61GO = new GameObject();
	Tile61GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile61GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile61 = new TileMap(*Tile61GO, "./assets/map/tileMap_Tile61.txt", tileSet);
	tileMap_Tile61->colide = true;

	Tile61GO->box.w = tileMap_Tile61->GetWidth() * tileSet->GetTileWidth();
	Tile61GO->box.h = tileMap_Tile61->GetHeight() * tileSet->GetTileHeight();

	Tile61GO->AddComponent(tileMap_Tile61);
	objectArray.emplace_back(Tile61GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile62GO = new GameObject();
	Tile62GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile62GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile62 = new TileMap(*Tile62GO, "./assets/map/tileMap_Tile62.txt", tileSet);
	tileMap_Tile62->colide = true;

	Tile62GO->box.w = tileMap_Tile62->GetWidth() * tileSet->GetTileWidth();
	Tile62GO->box.h = tileMap_Tile62->GetHeight() * tileSet->GetTileHeight();

	Tile62GO->AddComponent(tileMap_Tile62);
	objectArray.emplace_back(Tile62GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile63GO = new GameObject();
	Tile63GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile63GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile63 = new TileMap(*Tile63GO, "./assets/map/tileMap_Tile63.txt", tileSet);
	tileMap_Tile63->colide = true;

	Tile63GO->box.w = tileMap_Tile63->GetWidth() * tileSet->GetTileWidth();
	Tile63GO->box.h = tileMap_Tile63->GetHeight() * tileSet->GetTileHeight();

	Tile63GO->AddComponent(tileMap_Tile63);
	objectArray.emplace_back(Tile63GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile64GO = new GameObject();
	Tile64GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile64GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile64 = new TileMap(*Tile64GO, "./assets/map/tileMap_Tile64.txt", tileSet);
	tileMap_Tile64->colide = true;

	Tile64GO->box.w = tileMap_Tile64->GetWidth() * tileSet->GetTileWidth();
	Tile64GO->box.h = tileMap_Tile64->GetHeight() * tileSet->GetTileHeight();

	Tile64GO->AddComponent(tileMap_Tile64);
	objectArray.emplace_back(Tile64GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile65GO = new GameObject();
	Tile65GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile65GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile65 = new TileMap(*Tile65GO, "./assets/map/tileMap_Tile65.txt", tileSet);
	tileMap_Tile65->colide = true;

	Tile65GO->box.w = tileMap_Tile65->GetWidth() * tileSet->GetTileWidth();
	Tile65GO->box.h = tileMap_Tile65->GetHeight() * tileSet->GetTileHeight();

	Tile65GO->AddComponent(tileMap_Tile65);
	objectArray.emplace_back(Tile65GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile66GO = new GameObject();
	Tile66GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile66GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile66 = new TileMap(*Tile66GO, "./assets/map/tileMap_Tile66.txt", tileSet);
	tileMap_Tile66->colide = true;

	Tile66GO->box.w = tileMap_Tile66->GetWidth() * tileSet->GetTileWidth();
	Tile66GO->box.h = tileMap_Tile66->GetHeight() * tileSet->GetTileHeight();

	Tile66GO->AddComponent(tileMap_Tile66);
	objectArray.emplace_back(Tile66GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile67GO = new GameObject();
	Tile67GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile67GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile67 = new TileMap(*Tile67GO, "./assets/map/tileMap_Tile67.txt", tileSet);
	tileMap_Tile67->colide = true;

	Tile67GO->box.w = tileMap_Tile67->GetWidth() * tileSet->GetTileWidth();
	Tile67GO->box.h = tileMap_Tile67->GetHeight() * tileSet->GetTileHeight();

	Tile67GO->AddComponent(tileMap_Tile67);
	objectArray.emplace_back(Tile67GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile68GO = new GameObject();
	Tile68GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile68GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile68 = new TileMap(*Tile68GO, "./assets/map/tileMap_Tile68.txt", tileSet);
	tileMap_Tile68->colide = true;

	Tile68GO->box.w = tileMap_Tile68->GetWidth() * tileSet->GetTileWidth();
	Tile68GO->box.h = tileMap_Tile68->GetHeight() * tileSet->GetTileHeight();

	Tile68GO->AddComponent(tileMap_Tile68);
	objectArray.emplace_back(Tile68GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile69GO = new GameObject();
	Tile69GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile69GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto tileMap_Tile69 = new TileMap(*Tile69GO, "./assets/map/tileMap_Tile69.txt", tileSet);
	tileMap_Tile69->colide = true;

	Tile69GO->box.w = tileMap_Tile69->GetWidth() * tileSet->GetTileWidth();
	Tile69GO->box.h = tileMap_Tile69->GetHeight() * tileSet->GetTileHeight();

	Tile69GO->AddComponent(tileMap_Tile69);
	objectArray.emplace_back(Tile69GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	*/
}


void GameState0::LoadBuildings() {
	/*
/////////////////
//	  Chao	  //
///////////////
	auto chaoGO = new GameObject();
	chaoGO->box.x = 0;
	chaoGO->box.y = 800;

	//auto tileSet = new TileSet(64, 64, "./assets/img/tileset.png");
	//auto tileMap = new TileMap(*chaoGO, "./assets/map/MEUtileMap.txt", tileSet);


	// TileSet de 40 por 40
//	auto tileSet = new TileSet(40, 40, "./assets/img/tilesetPRETOeLARANJA(40x40).png");
//	auto tileMap = new TileMap(*chaoGO, "./assets/map/tileMap40x40.txt", tileSet);


	// TileSet de 80 por 80 do chao
	auto tileSet = new TileSet(80, 80, "./assets/img/tilesetPRETOeLARANJA(40x40).png");
	//auto tileMap = new TileMap(*chaoGO, "./assets/map/tileMap80x80.txt", tileSet);
	//auto tileMap_Chao = new TileMap(*chaoGO, "./assets/map/tileMap_Chao80x80.txt", tileSet);
	auto tileMap_Chao = new TileMap(*chaoGO, "./assets/map/tileMap_ChaoInfinito80x80.txt", tileSet);
	//tileMap_Chao->floor = true;
	tileMap_Chao->colide = true;

	chaoGO->box.w = tileMap_Chao->GetWidth() * tileSet->GetTileWidth();
	chaoGO->box.h = tileMap_Chao->GetHeight() * tileSet->GetTileHeight();

	chaoGO->AddComponent(tileMap_Chao);
	objectArray.emplace_back(chaoGO);



///////////////////////////////
//	  Conjunto de Predios	//
/////////////////////////////
	auto prediosGO = new GameObject();

	// todo - usaremos o mesmo tileSet por enquanto, nao temos um tileSet soh do chao
	//auto tileSet = new TileSet(80, 80, "./assets/img/tilesetPRETOeLARANJA(40x40).png");
	auto tileMap_Predios = new TileMap(*prediosGO, "./assets/map/tileMap_Predios80x80.txt", tileSet);
	tileMap_Predios->colide = true;

	// hitbox que envolve TODOS os predios
	prediosGO->box.w = tileMap_Predios->GetWidth() * tileSet->GetTileWidth();
	prediosGO->box.h = tileMap_Predios->GetHeight() * tileSet->GetTileHeight();
	prediosGO->box.y = chaoGO->box.y - (tileMap_Predios->GetHeight() * tileSet->GetTileHeight());
	prediosGO->box.x = 0;

	prediosGO->AddComponent(tileMap_Predios);
	//objectArray.emplace_back(prediosGO);

		auto testeGO = new GameObject();
	auto tileMap_teste = new TileMap(*testeGO, "./assets/map/TESTE.txt", tileSet);

	// hitbox do background
	//testeGO->box.w = tileMap_teste->GetWidth() * tileSet->GetTileWidth();
	//testeGO->box.h = tileMap_teste->GetHeight() * tileSet->GetTileHeight();
	testeGO->box.y = chaoGO->box.y - (tileMap_teste->GetHeight() * tileSet->GetTileHeight());
	testeGO->box.x = chaoGO->box.x;

	testeGO->AddComponent(tileMap_teste);
	//objectArray.emplace_back(testeGO);



/////////////////////////////////
//	  Predio Mais Simples	  //
///////////////////////////////
	auto predioSimplesGO = new GameObject();

	// todo - usaremos o mesmo tileSet por enquanto, nao temos um tileSet soh do chao
	//auto tileSet = new TileSet(80, 80, "./assets/img/tilesetPRETOeLARANJA(40x40).png");
	auto tileMap_PredioSimples = new TileMap(*predioSimplesGO, "./assets/map/tileMap_PredioSimples80x80.txt", tileSet);
	//tileMap_PredioSimples->floor = true;
	tileMap_PredioSimples->colide = true;

	// posicao em relacao ao tileMap_Chao e tamanho da hitbox do predio
	predioSimplesGO->box.w = tileMap_PredioSimples->GetWidth() * tileSet->GetTileWidth();
	predioSimplesGO->box.h = tileMap_PredioSimples->GetHeight() * tileSet->GetTileHeight();
	predioSimplesGO->box.y = chaoGO->box.y - (tileMap_Chao->GetHeight() * tileSet->GetTileHeight());
	predioSimplesGO->box.x = 30 * tileMap_Chao->GetWidth();


	predioSimplesGO->AddComponent(tileMap_PredioSimples);
	objectArray.emplace_back(predioSimplesGO);


	*/
///////////////////////
//	   Lixao		//
/////////////////////
	auto lixaoGO = new GameObject();
//	auto lixaoTetoGO = new GameObject();
//	auto lixaoParedeEsquerdaGO = new GameObject();

	// todo - usaremos o mesmo tileSet por enquanto, nao temos um tileSet soh do chao
	auto tileSet = new TileSet(80, 80, "./assets/img/tilesetPRETOeLARANJA(40x40).png");
	auto tileMap_Lixao = new TileMap(*lixaoGO, "./assets/map/tileMap_Lixao80x80.txt", tileSet);
/*	auto tileMap_LixaoTeto = new TileMap(*lixaoTetoGO, "./assets/map/tileMap_LixaoTeto80x80.txt", tileSet);
//	auto tileMap_LixaoParedeEsquerda = new TileMap(*lixaoParedeEsquerdaGO, "./assets/map/tileMap_LixaoParedeEsquerda80x80.txt", tileSet);
	//tileMap_Lixao->colide = true;
	//tileMap_LixaoTeto->floor = true;
//	tileMap_LixaoTeto->colide = true;
//	tileMap_LixaoParedeEsquerda->colide = true;

	// hitbox que envolve o lixao
	lixaoGO->box.w = tileMap_Lixao->GetWidth() * tileSet->GetTileWidth();
	lixaoGO->box.h = tileMap_Lixao->GetHeight() * tileSet->GetTileHeight();
	lixaoGO->box.y = /*chaoGO->box.y/ 800 - (tileMap_Lixao->GetHeight() * tileSet->GetTileHeight());
	lixaoGO->box.x = /*chaoGO->box.x/0;
	

	// hitbox do teto do lixao
	lixaoTetoGO->box.w = tileMap_LixaoTeto->GetWidth() * tileSet->GetTileWidth();
	lixaoTetoGO->box.h = tileMap_LixaoTeto->GetHeight() * tileSet->GetTileHeight();
	lixaoTetoGO->box.y = lixaoGO->box.y;
	lixaoTetoGO->box.x = lixaoGO->box.x + 4 * tileSet->GetTileWidth();

	// hitbox da parede esquerda do lixao
	lixaoParedeEsquerdaGO->box.w = tileMap_LixaoParedeEsquerda->GetWidth() * tileSet->GetTileWidth();
	lixaoParedeEsquerdaGO->box.h = tileMap_LixaoParedeEsquerda->GetHeight() * tileSet->GetTileHeight();
	lixaoParedeEsquerdaGO->box.y = lixaoGO->box.y;
	lixaoParedeEsquerdaGO->box.x = lixaoGO->box.x;
*/
	lixaoGO->AddComponent(tileMap_Lixao);
//	lixaoTetoGO->AddComponent(tileMap_LixaoTeto);
//	lixaoParedeEsquerdaGO->AddComponent(tileMap_LixaoParedeEsquerda);

	objectArray.emplace_back(lixaoGO);
/*	objectArray.emplace_back(lixaoTetoGO);
/	objectArray.emplace_back(lixaoParedeEsquerdaGO);



///////////////////////////////////
//	Plataforma de 3 quadrados	//
/////////////////////////////////
	auto plataformaGO = new GameObject();
	auto tileMap_Plataforma = new TileMap(*plataformaGO, "./assets/map/tileMap_Plataforma80x80.txt", tileSet);
	tileMap_Plataforma->colide = true;


	// hitbox da plataforma
	plataformaGO->box.w = tileMap_Plataforma->GetWidth() * tileSet->GetTileWidth();
	plataformaGO->box.h = tileMap_Plataforma->GetHeight() * tileSet->GetTileHeight();
	plataformaGO->box.y = predioSimplesGO->box.y - 3 * tileSet->GetTileHeight();
	plataformaGO->box.x = predioSimplesGO->box.x - 5 * tileSet->GetTileWidth();

	plataformaGO->AddComponent(tileMap_Plataforma);
	objectArray.emplace_back(plataformaGO);



///////////////////////////////////////////
//	SEGUNDA Plataforma de 3 quadrados	//
/////////////////////////////////////////
	auto segundaPlataformaGO = new GameObject();
	auto tileMap_SegundaPlataforma = new TileMap(*segundaPlataformaGO, "./assets/map/tileMap_Plataforma80x80.txt", tileSet);
	tileMap_SegundaPlataforma->colide = true;


	// hitbox da plataforma
	segundaPlataformaGO->box.w = tileMap_SegundaPlataforma->GetWidth() * tileSet->GetTileWidth();
	segundaPlataformaGO->box.h = tileMap_SegundaPlataforma->GetHeight() * tileSet->GetTileHeight();
	segundaPlataformaGO->box.y = predioSimplesGO->box.y /*-  1 * tileSet->GetTileHeight()/;
	segundaPlataformaGO->box.x = predioSimplesGO->box.x - 5 * tileSet->GetTileWidth();

	segundaPlataformaGO->AddComponent(tileMap_SegundaPlataforma);
	objectArray.emplace_back(segundaPlataformaGO);



///////////////////////////////////
//	 Plataforma de 3 quadrados	//
/////////////////////////////////
	auto terceiraPlataformaGO = new GameObject();
	auto tileMap_TerceiraPlataforma = new TileMap(*terceiraPlataformaGO, "./assets/map/tileMap_Plataforma80x80.txt", tileSet);
	tileMap_TerceiraPlataforma->colide = true;


	// hitbox da plataforma
	terceiraPlataformaGO->box.w = tileMap_TerceiraPlataforma->GetWidth() * tileSet->GetTileWidth();
	terceiraPlataformaGO->box.h = tileMap_TerceiraPlataforma->GetHeight() * tileSet->GetTileHeight();
	terceiraPlataformaGO->box.y = predioSimplesGO->box.y + 1 * tileSet->GetTileHeight();
	terceiraPlataformaGO->box.x = predioSimplesGO->box.x + 10 * tileSet->GetTileWidth();

	terceiraPlataformaGO->AddComponent(tileMap_TerceiraPlataforma);
	objectArray.emplace_back(terceiraPlataformaGO);
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

