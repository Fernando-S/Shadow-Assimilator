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
	backgroundGO->box.y = -352;

	

	//auto tileSet = new TileSet(64, 64, "./assets/img/tileset.png");
	//auto tileMap = new TileMap(*chaoGO, "./assets/map/MEUtileMap.txt", tileSet);


	// TileSet de 40 por 40
//	auto tileSet = new TileSet(40, 40, "./assets/img/tilesetPRETOeLARANJA(40x40).png");
//	auto tileMap = new TileMap(*chaoGO, "./assets/map/tileMap40x40.txt", tileSet);


	// Teste do TileSet de 80 por 80 do chao
	auto tileSet = new TileSet(64, 64, "./assets/img/TileSetAzul.png");
	//auto tileSetEscuro = new TileSet(32, 32, "./assets/img/tileESCURO.png");
	auto tileSetEscuro = new TileSet(64, 64, "./assets/img/128sepa.png");

	auto Background = new TileMap(*backgroundGO, "./assets/map/tileMap_TUDAOBACKGROUNDOTIMIZADO.txt", tileSetEscuro);
	//auto Background = new TileMap(*backgroundGO, "./assets/map/tileMap_TUDAOBACKGROUND.txt", tileSet);
	//auto Colidem = new TileMap(*colidemGO, "./assets/map/TUDAO.txt", tileSet);
	//auto Colidem = new TileMap(*colidemGO, "./assets/map/TUDAOOTIMIZADO.txt", tileSet);
	//auto Chao = new TileMap(*chaoGO, "./assets/map/CHAOZAO.txt", tileSet);

	
	Background->colide = false;
	//Colidem->colide = false;
	//Chao->colide = true;

	//chaoGO->box.w = Chao->GetWidth() * tileSet->GetTileWidth();
	//chaoGO->box.h = Chao->GetHeight() * tileSet->GetTileHeight();

	//chaoGO->AddComponent(Chao);
	//objectArray.emplace_back(chaoGO);
	
	//colidemGO->AddComponent(Colidem);
	//objectArray.emplace_back(colidemGO);

	backgroundGO->AddComponent(Background);
	objectArray.emplace_back(backgroundGO);



	auto torre1LGO = new GameObject(); // declara a parede esquerda da torre
	torre1LGO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x; //declara onde a torre ficará no eixo x
	torre1LGO->box.y = (- 13 * tileSet->GetTileHeight()) + chaoGO->box.y; //declara onde a torre ficará no eixo y

	//auto torre1L = new TileMap(*torre1LGO, "./assets/map/torre1L.txt", tileSet);
	//torre1L->colide = true;

	//torre1LGO->box.w = torre1L->GetWidth() * tileSet->GetTileWidth();
	//torre1LGO->box.h = torre1L->GetHeight() * tileSet->GetTileHeight();

	//torre1LGO->AddComponent(torre1L);
	//objectArray.emplace_back(torre1LGO);





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
	robotGO->box.x = 2000;
	robotGO->box.y = 800 - robotGO->box.h;

	objectArray.emplace_back(robotGO);



///////////////////////////////////
//		Carrega a Personagem	//
/////////////////////////////////
	//auto playerGO = new GameObject();
	//auto player = new Player(*playerGO);
	playerGO->AddComponent(player);
	//playerGO->box.PlaceCenter(Vec2(1600, /*400 - playerGO->box.h*/ 300));
	playerGO->box.x = 1500;
	playerGO->box.y = 800 - playerGO->box.h;

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
	auto Chao = new TileMap(*chaoGO, "./assets/map/tileMap_CHAOZAO.txt", tileSet);


	Chao->colide = true;

	chaoGO->box.w = Chao->GetWidth() * tileSet->GetTileWidth();
	chaoGO->box.h = Chao->GetHeight() * tileSet->GetTileHeight();

	chaoGO->AddComponent(Chao);
	objectArray.emplace_back(chaoGO);


	//////////////////////////////////////////////
	// Comeco dos paranaues
	/*
	auto Tile00GO = new GameObject();
	Tile00GO->box.x =  chaoGO->box.x;
	Tile00GO->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile00 = new TileMap(*Tile00GO, "./assets/map/Tile00.txt", tileSet);
	Tile00->colide = true;

	Tile00GO->box.w = Tile00->GetWidth() * tileSet->GetTileWidth();
	Tile00GO->box.h = Tile00->GetHeight() * tileSet->GetTileHeight();

	Tile00GO->AddComponent(Tile00);
	objectArray.emplace_back(Tile00GO);

	// Segunda parede

	auto Tile00GO1 = new GameObject();
	Tile00GO1->box.x = 9 * ONETILESQUARE + chaoGO->box.x;
	Tile00GO1->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;
	auto Tile001 = new TileMap(*Tile00GO1, "./assets/map/Tile00.txt", tileSet);
	Tile001->colide = true;
	Tile00GO1->box.w = Tile001->GetWidth() * tileSet->GetTileWidth();
	Tile00GO1->box.h = Tile001->GetHeight() * tileSet->GetTileHeight();
	Tile00GO1->AddComponent(Tile001);
	objectArray.emplace_back(Tile00GO1);



	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile01GO = new GameObject();
	Tile01GO->box.x =  1 * ONETILESQUARE + chaoGO->box.x;
	Tile01GO->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile01 = new TileMap(*Tile01GO, "./assets/map/Tile01.txt", tileSet);
	Tile01->colide = true;

	Tile01GO->box.w = Tile01->GetWidth() * tileSet->GetTileWidth();
	Tile01GO->box.h = Tile01->GetHeight() * tileSet->GetTileHeight();

	Tile01GO->AddComponent(Tile01);
	objectArray.emplace_back(Tile01GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile02GO = new GameObject();
	Tile02GO->box.x =  2 * ONETILESQUARE + chaoGO->box.x;
	Tile02GO->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile02 = new TileMap(*Tile02GO, "./assets/map/Tile02.txt", tileSet);
	Tile02->colide = true;

	Tile02GO->box.w = Tile02->GetWidth() * tileSet->GetTileWidth();
	Tile02GO->box.h = Tile02->GetHeight() * tileSet->GetTileHeight();

	Tile02GO->AddComponent(Tile02);
	objectArray.emplace_back(Tile02GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile03GO = new GameObject();
	Tile03GO->box.x =  3 * ONETILESQUARE + chaoGO->box.x;
	Tile03GO->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile03 = new TileMap(*Tile03GO, "./assets/map/Tile03.txt", tileSet);
	Tile03->colide = true;

	Tile03GO->box.w = Tile03->GetWidth() * tileSet->GetTileWidth();
	Tile03GO->box.h = Tile03->GetHeight() * tileSet->GetTileHeight();

	Tile03GO->AddComponent(Tile03);
	objectArray.emplace_back(Tile03GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile04GO = new GameObject();
	Tile04GO->box.x =  4 * ONETILESQUARE + chaoGO->box.x;
	Tile04GO->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile04 = new TileMap(*Tile04GO, "./assets/map/Tile04.txt", tileSet);
	Tile04->colide = true;

	Tile04GO->box.w = Tile04->GetWidth() * tileSet->GetTileWidth();
	Tile04GO->box.h = Tile04->GetHeight() * tileSet->GetTileHeight();

	Tile04GO->AddComponent(Tile04);
	objectArray.emplace_back(Tile04GO);




	//// PLATAFORMA WOLOLO

	auto TileWOLOLOGO = new GameObject();
	TileWOLOLOGO->box.x = 10 * ONETILESQUARE + chaoGO->box.x;
	TileWOLOLOGO->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto TileWOLOLO = new TileMap(*TileWOLOLOGO, "./assets/map/TileWOLOLO.txt", tileSet);
	TileWOLOLO->colide = true;

	TileWOLOLOGO->box.w = TileWOLOLO->GetWidth() * tileSet->GetTileWidth();
	TileWOLOLOGO->box.h = TileWOLOLO->GetHeight() * tileSet->GetTileHeight();

	TileWOLOLOGO->AddComponent(TileWOLOLO);
	objectArray.emplace_back(TileWOLOLOGO);



	//// PLATAFORMA WOLOLO 2

	auto TileWOLOLOGO2 = new GameObject();
	TileWOLOLOGO2->box.x = 26 * ONETILESQUARE + chaoGO->box.x;
	TileWOLOLOGO2->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto TileWOLOLO2 = new TileMap(*TileWOLOLOGO2, "./assets/map/TileWOLOLO.txt", tileSet);
	TileWOLOLO2->colide = true;

	TileWOLOLOGO2->box.w = TileWOLOLO2->GetWidth() * tileSet->GetTileWidth();
	TileWOLOLOGO2->box.h = TileWOLOLO2->GetHeight() * tileSet->GetTileHeight();

	TileWOLOLOGO2->AddComponent(TileWOLOLO2);
	objectArray.emplace_back(TileWOLOLOGO2);



	//// PLATAFORMA WOLOLO 3

	auto TileWOLOLOGO3 = new GameObject();
	TileWOLOLOGO3->box.x = 40 * ONETILESQUARE + chaoGO->box.x;
	TileWOLOLOGO3->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto TileWOLOLO3 = new TileMap(*TileWOLOLOGO3, "./assets/map/TileWOLOLO.txt", tileSet);
	TileWOLOLO3->colide = true;

	TileWOLOLOGO3->box.w = TileWOLOLO3->GetWidth() * tileSet->GetTileWidth();
	TileWOLOLOGO3->box.h = TileWOLOLO3->GetHeight() * tileSet->GetTileHeight();

	TileWOLOLOGO3->AddComponent(TileWOLOLO3);
	objectArray.emplace_back(TileWOLOLOGO3);



	// Terceira parede

	auto Tile00GO2 = new GameObject();
	Tile00GO2->box.x = 26 * ONETILESQUARE + chaoGO->box.x;
	Tile00GO2->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;
	auto Tile002 = new TileMap(*Tile00GO2, "./assets/map/Tile00.txt", tileSet);
	Tile002->colide = true;
	Tile00GO2->box.w = Tile002->GetWidth() * tileSet->GetTileWidth();
	Tile00GO2->box.h = Tile002->GetHeight() * tileSet->GetTileHeight();
	Tile00GO2->AddComponent(Tile002);
	objectArray.emplace_back(Tile00GO2);



	// Quarta parede

	auto Tile00GO3 = new GameObject();
	Tile00GO3->box.x = 48 * ONETILESQUARE + chaoGO->box.x;
	Tile00GO3->box.y = (-6 * tileSet->GetTileHeight()) + chaoGO->box.y;
	auto Tile003 = new TileMap(*Tile00GO3, "./assets/map/Tile00.txt", tileSet);
	Tile003->colide = true;
	Tile00GO3->box.w = Tile003->GetWidth() * tileSet->GetTileWidth();
	Tile00GO3->box.h = Tile003->GetHeight() * tileSet->GetTileHeight();
	Tile00GO3->AddComponent(Tile003);
	objectArray.emplace_back(Tile00GO3);




	/*
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile05GO = new GameObject();
	Tile05GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile05GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile05 = new TileMap(*Tile05GO, "./assets/map/Tile05.txt", tileSet);
	Tile05->colide = true;

	Tile05GO->box.w = Tile05->GetWidth() * tileSet->GetTileWidth();
	Tile05GO->box.h = Tile05->GetHeight() * tileSet->GetTileHeight();

	Tile05GO->AddComponent(Tile05);
	objectArray.emplace_back(Tile05GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile06GO = new GameObject();
	Tile06GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile06GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile06 = new TileMap(*Tile06GO, "./assets/map/Tile06.txt", tileSet);
	Tile06->colide = true;

	Tile06GO->box.w = Tile06->GetWidth() * tileSet->GetTileWidth();
	Tile06GO->box.h = Tile06->GetHeight() * tileSet->GetTileHeight();

	Tile06GO->AddComponent(Tile06);
	objectArray.emplace_back(Tile06GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile07GO = new GameObject();
	Tile07GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile07GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile07 = new TileMap(*Tile07GO, "./assets/map/Tile07.txt", tileSet);
	Tile07->colide = true;

	Tile07GO->box.w = Tile07->GetWidth() * tileSet->GetTileWidth();
	Tile07GO->box.h = Tile07->GetHeight() * tileSet->GetTileHeight();

	Tile07GO->AddComponent(Tile07);
	objectArray.emplace_back(Tile07GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile08GO = new GameObject();
	Tile08GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile08GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile08 = new TileMap(*Tile08GO, "./assets/map/Tile08.txt", tileSet);
	Tile08->colide = true;

	Tile08GO->box.w = Tile08->GetWidth() * tileSet->GetTileWidth();
	Tile08GO->box.h = Tile08->GetHeight() * tileSet->GetTileHeight();

	Tile08GO->AddComponent(Tile08);
	objectArray.emplace_back(Tile08GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile09GO = new GameObject();
	Tile09GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile09GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile09 = new TileMap(*Tile09GO, "./assets/map/Tile09.txt", tileSet);
	Tile09->colide = true;

	Tile09GO->box.w = Tile09->GetWidth() * tileSet->GetTileWidth();
	Tile09GO->box.h = Tile09->GetHeight() * tileSet->GetTileHeight();

	Tile09GO->AddComponent(Tile09);
	objectArray.emplace_back(Tile09GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile10GO = new GameObject();
	Tile10GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile10GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile10 = new TileMap(*Tile10GO, "./assets/map/Tile10.txt", tileSet);
	Tile10->colide = true;

	Tile10GO->box.w = Tile10->GetWidth() * tileSet->GetTileWidth();
	Tile10GO->box.h = Tile10->GetHeight() * tileSet->GetTileHeight();

	Tile10GO->AddComponent(Tile10);
	objectArray.emplace_back(Tile10GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile11GO = new GameObject();
	Tile11GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile11GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile11 = new TileMap(*Tile11GO, "./assets/map/Tile11.txt", tileSet);
	Tile11->colide = true;

	Tile11GO->box.w = Tile11->GetWidth() * tileSet->GetTileWidth();
	Tile11GO->box.h = Tile11->GetHeight() * tileSet->GetTileHeight();

	Tile11GO->AddComponent(Tile11);
	objectArray.emplace_back(Tile11GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile12GO = new GameObject();
	Tile12GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile12GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile12 = new TileMap(*Tile12GO, "./assets/map/Tile12.txt", tileSet);
	Tile12->colide = true;

	Tile12GO->box.w = Tile12->GetWidth() * tileSet->GetTileWidth();
	Tile12GO->box.h = Tile12->GetHeight() * tileSet->GetTileHeight();

	Tile12GO->AddComponent(Tile12);
	objectArray.emplace_back(Tile12GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile13GO = new GameObject();
	Tile13GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile13GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile13 = new TileMap(*Tile13GO, "./assets/map/Tile13.txt", tileSet);
	Tile13->colide = true;

	Tile13GO->box.w = Tile13->GetWidth() * tileSet->GetTileWidth();
	Tile13GO->box.h = Tile13->GetHeight() * tileSet->GetTileHeight();

	Tile13GO->AddComponent(Tile13);
	objectArray.emplace_back(Tile13GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile14GO = new GameObject();
	Tile14GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile14GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile14 = new TileMap(*Tile14GO, "./assets/map/Tile14.txt", tileSet);
	Tile14->colide = true;

	Tile14GO->box.w = Tile14->GetWidth() * tileSet->GetTileWidth();
	Tile14GO->box.h = Tile14->GetHeight() * tileSet->GetTileHeight();

	Tile14GO->AddComponent(Tile14);
	objectArray.emplace_back(Tile14GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile15GO = new GameObject();
	Tile15GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile15GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile15 = new TileMap(*Tile15GO, "./assets/map/Tile15.txt", tileSet);
	Tile15->colide = true;

	Tile15GO->box.w = Tile15->GetWidth() * tileSet->GetTileWidth();
	Tile15GO->box.h = Tile15->GetHeight() * tileSet->GetTileHeight();

	Tile15GO->AddComponent(Tile15);
	objectArray.emplace_back(Tile15GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile16GO = new GameObject();
	Tile16GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile16GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile16 = new TileMap(*Tile16GO, "./assets/map/Tile16.txt", tileSet);
	Tile16->colide = true;

	Tile16GO->box.w = Tile16->GetWidth() * tileSet->GetTileWidth();
	Tile16GO->box.h = Tile16->GetHeight() * tileSet->GetTileHeight();

	Tile16GO->AddComponent(Tile16);
	objectArray.emplace_back(Tile16GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile17GO = new GameObject();
	Tile17GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile17GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile17 = new TileMap(*Tile17GO, "./assets/map/Tile17.txt", tileSet);
	Tile17->colide = true;

	Tile17GO->box.w = Tile17->GetWidth() * tileSet->GetTileWidth();
	Tile17GO->box.h = Tile17->GetHeight() * tileSet->GetTileHeight();

	Tile17GO->AddComponent(Tile17);
	objectArray.emplace_back(Tile17GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile18GO = new GameObject();
	Tile18GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile18GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile18 = new TileMap(*Tile18GO, "./assets/map/Tile18.txt", tileSet);
	Tile18->colide = true;

	Tile18GO->box.w = Tile18->GetWidth() * tileSet->GetTileWidth();
	Tile18GO->box.h = Tile18->GetHeight() * tileSet->GetTileHeight();

	Tile18GO->AddComponent(Tile18);
	objectArray.emplace_back(Tile18GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile19GO = new GameObject();
	Tile19GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile19GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile19 = new TileMap(*Tile19GO, "./assets/map/Tile19.txt", tileSet);
	Tile19->colide = true;

	Tile19GO->box.w = Tile19->GetWidth() * tileSet->GetTileWidth();
	Tile19GO->box.h = Tile19->GetHeight() * tileSet->GetTileHeight();

	Tile19GO->AddComponent(Tile19);
	objectArray.emplace_back(Tile19GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile20GO = new GameObject();
	Tile20GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile20GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile20 = new TileMap(*Tile20GO, "./assets/map/Tile20.txt", tileSet);
	Tile20->colide = true;

	Tile20GO->box.w = Tile20->GetWidth() * tileSet->GetTileWidth();
	Tile20GO->box.h = Tile20->GetHeight() * tileSet->GetTileHeight();

	Tile20GO->AddComponent(Tile20);
	objectArray.emplace_back(Tile20GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile21GO = new GameObject();
	Tile21GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile21GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile21 = new TileMap(*Tile21GO, "./assets/map/Tile21.txt", tileSet);
	Tile21->colide = true;

	Tile21GO->box.w = Tile21->GetWidth() * tileSet->GetTileWidth();
	Tile21GO->box.h = Tile21->GetHeight() * tileSet->GetTileHeight();

	Tile21GO->AddComponent(Tile21);
	objectArray.emplace_back(Tile21GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile22GO = new GameObject();
	Tile22GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile22GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile22 = new TileMap(*Tile22GO, "./assets/map/Tile22.txt", tileSet);
	Tile22->colide = true;

	Tile22GO->box.w = Tile22->GetWidth() * tileSet->GetTileWidth();
	Tile22GO->box.h = Tile22->GetHeight() * tileSet->GetTileHeight();

	Tile22GO->AddComponent(Tile22);
	objectArray.emplace_back(Tile22GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile23GO = new GameObject();
	Tile23GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile23GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile23 = new TileMap(*Tile23GO, "./assets/map/Tile23.txt", tileSet);
	Tile23->colide = true;

	Tile23GO->box.w = Tile23->GetWidth() * tileSet->GetTileWidth();
	Tile23GO->box.h = Tile23->GetHeight() * tileSet->GetTileHeight();

	Tile23GO->AddComponent(Tile23);
	objectArray.emplace_back(Tile23GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile24GO = new GameObject();
	Tile24GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile24GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile24 = new TileMap(*Tile24GO, "./assets/map/Tile24.txt", tileSet);
	Tile24->colide = true;

	Tile24GO->box.w = Tile24->GetWidth() * tileSet->GetTileWidth();
	Tile24GO->box.h = Tile24->GetHeight() * tileSet->GetTileHeight();

	Tile24GO->AddComponent(Tile24);
	objectArray.emplace_back(Tile24GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile25GO = new GameObject();
	Tile25GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile25GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile25 = new TileMap(*Tile25GO, "./assets/map/Tile25.txt", tileSet);
	Tile25->colide = true;

	Tile25GO->box.w = Tile25->GetWidth() * tileSet->GetTileWidth();
	Tile25GO->box.h = Tile25->GetHeight() * tileSet->GetTileHeight();

	Tile25GO->AddComponent(Tile25);
	objectArray.emplace_back(Tile25GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile26GO = new GameObject();
	Tile26GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile26GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile26 = new TileMap(*Tile26GO, "./assets/map/Tile26.txt", tileSet);
	Tile26->colide = true;

	Tile26GO->box.w = Tile26->GetWidth() * tileSet->GetTileWidth();
	Tile26GO->box.h = Tile26->GetHeight() * tileSet->GetTileHeight();

	Tile26GO->AddComponent(Tile26);
	objectArray.emplace_back(Tile26GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile27GO = new GameObject();
	Tile27GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile27GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile27 = new TileMap(*Tile27GO, "./assets/map/Tile27.txt", tileSet);
	Tile27->colide = true;

	Tile27GO->box.w = Tile27->GetWidth() * tileSet->GetTileWidth();
	Tile27GO->box.h = Tile27->GetHeight() * tileSet->GetTileHeight();

	Tile27GO->AddComponent(Tile27);
	objectArray.emplace_back(Tile27GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile28GO = new GameObject();
	Tile28GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile28GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile28 = new TileMap(*Tile28GO, "./assets/map/Tile28.txt", tileSet);
	Tile28->colide = true;

	Tile28GO->box.w = Tile28->GetWidth() * tileSet->GetTileWidth();
	Tile28GO->box.h = Tile28->GetHeight() * tileSet->GetTileHeight();

	Tile28GO->AddComponent(Tile28);
	objectArray.emplace_back(Tile28GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile29GO = new GameObject();
	Tile29GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile29GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile29 = new TileMap(*Tile29GO, "./assets/map/Tile29.txt", tileSet);
	Tile29->colide = true;

	Tile29GO->box.w = Tile29->GetWidth() * tileSet->GetTileWidth();
	Tile29GO->box.h = Tile29->GetHeight() * tileSet->GetTileHeight();

	Tile29GO->AddComponent(Tile29);
	objectArray.emplace_back(Tile29GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile30GO = new GameObject();
	Tile30GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile30GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile30 = new TileMap(*Tile30GO, "./assets/map/Tile30.txt", tileSet);
	Tile30->colide = true;

	Tile30GO->box.w = Tile30->GetWidth() * tileSet->GetTileWidth();
	Tile30GO->box.h = Tile30->GetHeight() * tileSet->GetTileHeight();

	Tile30GO->AddComponent(Tile30);
	objectArray.emplace_back(Tile30GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile31GO = new GameObject();
	Tile31GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile31GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile31 = new TileMap(*Tile31GO, "./assets/map/Tile31.txt", tileSet);
	Tile31->colide = true;

	Tile31GO->box.w = Tile31->GetWidth() * tileSet->GetTileWidth();
	Tile31GO->box.h = Tile31->GetHeight() * tileSet->GetTileHeight();

	Tile31GO->AddComponent(Tile31);
	objectArray.emplace_back(Tile31GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile32GO = new GameObject();
	Tile32GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile32GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile32 = new TileMap(*Tile32GO, "./assets/map/Tile32.txt", tileSet);
	Tile32->colide = true;

	Tile32GO->box.w = Tile32->GetWidth() * tileSet->GetTileWidth();
	Tile32GO->box.h = Tile32->GetHeight() * tileSet->GetTileHeight();

	Tile32GO->AddComponent(Tile32);
	objectArray.emplace_back(Tile32GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile33GO = new GameObject();
	Tile33GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile33GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile33 = new TileMap(*Tile33GO, "./assets/map/Tile33.txt", tileSet);
	Tile33->colide = true;

	Tile33GO->box.w = Tile33->GetWidth() * tileSet->GetTileWidth();
	Tile33GO->box.h = Tile33->GetHeight() * tileSet->GetTileHeight();

	Tile33GO->AddComponent(Tile33);
	objectArray.emplace_back(Tile33GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile34GO = new GameObject();
	Tile34GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile34GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile34 = new TileMap(*Tile34GO, "./assets/map/Tile34.txt", tileSet);
	Tile34->colide = true;

	Tile34GO->box.w = Tile34->GetWidth() * tileSet->GetTileWidth();
	Tile34GO->box.h = Tile34->GetHeight() * tileSet->GetTileHeight();

	Tile34GO->AddComponent(Tile34);
	objectArray.emplace_back(Tile34GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile35GO = new GameObject();
	Tile35GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile35GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile35 = new TileMap(*Tile35GO, "./assets/map/Tile35.txt", tileSet);
	Tile35->colide = true;

	Tile35GO->box.w = Tile35->GetWidth() * tileSet->GetTileWidth();
	Tile35GO->box.h = Tile35->GetHeight() * tileSet->GetTileHeight();

	Tile35GO->AddComponent(Tile35);
	objectArray.emplace_back(Tile35GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile36GO = new GameObject();
	Tile36GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile36GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile36 = new TileMap(*Tile36GO, "./assets/map/Tile36.txt", tileSet);
	Tile36->colide = true;

	Tile36GO->box.w = Tile36->GetWidth() * tileSet->GetTileWidth();
	Tile36GO->box.h = Tile36->GetHeight() * tileSet->GetTileHeight();

	Tile36GO->AddComponent(Tile36);
	objectArray.emplace_back(Tile36GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile37GO = new GameObject();
	Tile37GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile37GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile37 = new TileMap(*Tile37GO, "./assets/map/Tile37.txt", tileSet);
	Tile37->colide = true;

	Tile37GO->box.w = Tile37->GetWidth() * tileSet->GetTileWidth();
	Tile37GO->box.h = Tile37->GetHeight() * tileSet->GetTileHeight();

	Tile37GO->AddComponent(Tile37);
	objectArray.emplace_back(Tile37GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile38GO = new GameObject();
	Tile38GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile38GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile38 = new TileMap(*Tile38GO, "./assets/map/Tile38.txt", tileSet);
	Tile38->colide = true;

	Tile38GO->box.w = Tile38->GetWidth() * tileSet->GetTileWidth();
	Tile38GO->box.h = Tile38->GetHeight() * tileSet->GetTileHeight();

	Tile38GO->AddComponent(Tile38);
	objectArray.emplace_back(Tile38GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile39GO = new GameObject();
	Tile39GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile39GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile39 = new TileMap(*Tile39GO, "./assets/map/Tile39.txt", tileSet);
	Tile39->colide = true;

	Tile39GO->box.w = Tile39->GetWidth() * tileSet->GetTileWidth();
	Tile39GO->box.h = Tile39->GetHeight() * tileSet->GetTileHeight();

	Tile39GO->AddComponent(Tile39);
	objectArray.emplace_back(Tile39GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile40GO = new GameObject();
	Tile40GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile40GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile40 = new TileMap(*Tile40GO, "./assets/map/Tile40.txt", tileSet);
	Tile40->colide = true;

	Tile40GO->box.w = Tile40->GetWidth() * tileSet->GetTileWidth();
	Tile40GO->box.h = Tile40->GetHeight() * tileSet->GetTileHeight();

	Tile40GO->AddComponent(Tile40);
	objectArray.emplace_back(Tile40GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile41GO = new GameObject();
	Tile41GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile41GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile41 = new TileMap(*Tile41GO, "./assets/map/Tile41.txt", tileSet);
	Tile41->colide = true;

	Tile41GO->box.w = Tile41->GetWidth() * tileSet->GetTileWidth();
	Tile41GO->box.h = Tile41->GetHeight() * tileSet->GetTileHeight();

	Tile41GO->AddComponent(Tile41);
	objectArray.emplace_back(Tile41GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile42GO = new GameObject();
	Tile42GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile42GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile42 = new TileMap(*Tile42GO, "./assets/map/Tile42.txt", tileSet);
	Tile42->colide = true;

	Tile42GO->box.w = Tile42->GetWidth() * tileSet->GetTileWidth();
	Tile42GO->box.h = Tile42->GetHeight() * tileSet->GetTileHeight();

	Tile42GO->AddComponent(Tile42);
	objectArray.emplace_back(Tile42GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile43GO = new GameObject();
	Tile43GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile43GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile43 = new TileMap(*Tile43GO, "./assets/map/Tile43.txt", tileSet);
	Tile43->colide = true;

	Tile43GO->box.w = Tile43->GetWidth() * tileSet->GetTileWidth();
	Tile43GO->box.h = Tile43->GetHeight() * tileSet->GetTileHeight();

	Tile43GO->AddComponent(Tile43);
	objectArray.emplace_back(Tile43GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile44GO = new GameObject();
	Tile44GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile44GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile44 = new TileMap(*Tile44GO, "./assets/map/Tile44.txt", tileSet);
	Tile44->colide = true;

	Tile44GO->box.w = Tile44->GetWidth() * tileSet->GetTileWidth();
	Tile44GO->box.h = Tile44->GetHeight() * tileSet->GetTileHeight();

	Tile44GO->AddComponent(Tile44);
	objectArray.emplace_back(Tile44GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile45GO = new GameObject();
	Tile45GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile45GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile45 = new TileMap(*Tile45GO, "./assets/map/Tile45.txt", tileSet);
	Tile45->colide = true;

	Tile45GO->box.w = Tile45->GetWidth() * tileSet->GetTileWidth();
	Tile45GO->box.h = Tile45->GetHeight() * tileSet->GetTileHeight();

	Tile45GO->AddComponent(Tile45);
	objectArray.emplace_back(Tile45GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile46GO = new GameObject();
	Tile46GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile46GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile46 = new TileMap(*Tile46GO, "./assets/map/Tile46.txt", tileSet);
	Tile46->colide = true;

	Tile46GO->box.w = Tile46->GetWidth() * tileSet->GetTileWidth();
	Tile46GO->box.h = Tile46->GetHeight() * tileSet->GetTileHeight();

	Tile46GO->AddComponent(Tile46);
	objectArray.emplace_back(Tile46GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile47GO = new GameObject();
	Tile47GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile47GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile47 = new TileMap(*Tile47GO, "./assets/map/Tile47.txt", tileSet);
	Tile47->colide = true;

	Tile47GO->box.w = Tile47->GetWidth() * tileSet->GetTileWidth();
	Tile47GO->box.h = Tile47->GetHeight() * tileSet->GetTileHeight();

	Tile47GO->AddComponent(Tile47);
	objectArray.emplace_back(Tile47GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile48GO = new GameObject();
	Tile48GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile48GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile48 = new TileMap(*Tile48GO, "./assets/map/Tile48.txt", tileSet);
	Tile48->colide = true;

	Tile48GO->box.w = Tile48->GetWidth() * tileSet->GetTileWidth();
	Tile48GO->box.h = Tile48->GetHeight() * tileSet->GetTileHeight();

	Tile48GO->AddComponent(Tile48);
	objectArray.emplace_back(Tile48GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile49GO = new GameObject();
	Tile49GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile49GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile49 = new TileMap(*Tile49GO, "./assets/map/Tile49.txt", tileSet);
	Tile49->colide = true;

	Tile49GO->box.w = Tile49->GetWidth() * tileSet->GetTileWidth();
	Tile49GO->box.h = Tile49->GetHeight() * tileSet->GetTileHeight();

	Tile49GO->AddComponent(Tile49);
	objectArray.emplace_back(Tile49GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile50GO = new GameObject();
	Tile50GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile50GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile50 = new TileMap(*Tile50GO, "./assets/map/Tile50.txt", tileSet);
	Tile50->colide = true;

	Tile50GO->box.w = Tile50->GetWidth() * tileSet->GetTileWidth();
	Tile50GO->box.h = Tile50->GetHeight() * tileSet->GetTileHeight();

	Tile50GO->AddComponent(Tile50);
	objectArray.emplace_back(Tile50GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile51GO = new GameObject();
	Tile51GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile51GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile51 = new TileMap(*Tile51GO, "./assets/map/Tile51.txt", tileSet);
	Tile51->colide = true;

	Tile51GO->box.w = Tile51->GetWidth() * tileSet->GetTileWidth();
	Tile51GO->box.h = Tile51->GetHeight() * tileSet->GetTileHeight();

	Tile51GO->AddComponent(Tile51);
	objectArray.emplace_back(Tile51GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile52GO = new GameObject();
	Tile52GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile52GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile52 = new TileMap(*Tile52GO, "./assets/map/Tile52.txt", tileSet);
	Tile52->colide = true;

	Tile52GO->box.w = Tile52->GetWidth() * tileSet->GetTileWidth();
	Tile52GO->box.h = Tile52->GetHeight() * tileSet->GetTileHeight();

	Tile52GO->AddComponent(Tile52);
	objectArray.emplace_back(Tile52GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile53GO = new GameObject();
	Tile53GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile53GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile53 = new TileMap(*Tile53GO, "./assets/map/Tile53.txt", tileSet);
	Tile53->colide = true;

	Tile53GO->box.w = Tile53->GetWidth() * tileSet->GetTileWidth();
	Tile53GO->box.h = Tile53->GetHeight() * tileSet->GetTileHeight();

	Tile53GO->AddComponent(Tile53);
	objectArray.emplace_back(Tile53GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile54GO = new GameObject();
	Tile54GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile54GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile54 = new TileMap(*Tile54GO, "./assets/map/Tile54.txt", tileSet);
	Tile54->colide = true;

	Tile54GO->box.w = Tile54->GetWidth() * tileSet->GetTileWidth();
	Tile54GO->box.h = Tile54->GetHeight() * tileSet->GetTileHeight();

	Tile54GO->AddComponent(Tile54);
	objectArray.emplace_back(Tile54GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile55GO = new GameObject();
	Tile55GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile55GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile55 = new TileMap(*Tile55GO, "./assets/map/Tile55.txt", tileSet);
	Tile55->colide = true;

	Tile55GO->box.w = Tile55->GetWidth() * tileSet->GetTileWidth();
	Tile55GO->box.h = Tile55->GetHeight() * tileSet->GetTileHeight();

	Tile55GO->AddComponent(Tile55);
	objectArray.emplace_back(Tile55GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile56GO = new GameObject();
	Tile56GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile56GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile56 = new TileMap(*Tile56GO, "./assets/map/Tile56.txt", tileSet);
	Tile56->colide = true;

	Tile56GO->box.w = Tile56->GetWidth() * tileSet->GetTileWidth();
	Tile56GO->box.h = Tile56->GetHeight() * tileSet->GetTileHeight();

	Tile56GO->AddComponent(Tile56);
	objectArray.emplace_back(Tile56GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile57GO = new GameObject();
	Tile57GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile57GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile57 = new TileMap(*Tile57GO, "./assets/map/Tile57.txt", tileSet);
	Tile57->colide = true;

	Tile57GO->box.w = Tile57->GetWidth() * tileSet->GetTileWidth();
	Tile57GO->box.h = Tile57->GetHeight() * tileSet->GetTileHeight();

	Tile57GO->AddComponent(Tile57);
	objectArray.emplace_back(Tile57GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile58GO = new GameObject();
	Tile58GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile58GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile58 = new TileMap(*Tile58GO, "./assets/map/Tile58.txt", tileSet);
	Tile58->colide = true;

	Tile58GO->box.w = Tile58->GetWidth() * tileSet->GetTileWidth();
	Tile58GO->box.h = Tile58->GetHeight() * tileSet->GetTileHeight();

	Tile58GO->AddComponent(Tile58);
	objectArray.emplace_back(Tile58GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile59GO = new GameObject();
	Tile59GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile59GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile59 = new TileMap(*Tile59GO, "./assets/map/Tile59.txt", tileSet);
	Tile59->colide = true;

	Tile59GO->box.w = Tile59->GetWidth() * tileSet->GetTileWidth();
	Tile59GO->box.h = Tile59->GetHeight() * tileSet->GetTileHeight();

	Tile59GO->AddComponent(Tile59);
	objectArray.emplace_back(Tile59GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile60GO = new GameObject();
	Tile60GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile60GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile60 = new TileMap(*Tile60GO, "./assets/map/Tile60.txt", tileSet);
	Tile60->colide = true;

	Tile60GO->box.w = Tile60->GetWidth() * tileSet->GetTileWidth();
	Tile60GO->box.h = Tile60->GetHeight() * tileSet->GetTileHeight();

	Tile60GO->AddComponent(Tile60);
	objectArray.emplace_back(Tile60GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile61GO = new GameObject();
	Tile61GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile61GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile61 = new TileMap(*Tile61GO, "./assets/map/Tile61.txt", tileSet);
	Tile61->colide = true;

	Tile61GO->box.w = Tile61->GetWidth() * tileSet->GetTileWidth();
	Tile61GO->box.h = Tile61->GetHeight() * tileSet->GetTileHeight();

	Tile61GO->AddComponent(Tile61);
	objectArray.emplace_back(Tile61GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile62GO = new GameObject();
	Tile62GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile62GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile62 = new TileMap(*Tile62GO, "./assets/map/Tile62.txt", tileSet);
	Tile62->colide = true;

	Tile62GO->box.w = Tile62->GetWidth() * tileSet->GetTileWidth();
	Tile62GO->box.h = Tile62->GetHeight() * tileSet->GetTileHeight();

	Tile62GO->AddComponent(Tile62);
	objectArray.emplace_back(Tile62GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile63GO = new GameObject();
	Tile63GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile63GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile63 = new TileMap(*Tile63GO, "./assets/map/Tile63.txt", tileSet);
	Tile63->colide = true;

	Tile63GO->box.w = Tile63->GetWidth() * tileSet->GetTileWidth();
	Tile63GO->box.h = Tile63->GetHeight() * tileSet->GetTileHeight();

	Tile63GO->AddComponent(Tile63);
	objectArray.emplace_back(Tile63GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile64GO = new GameObject();
	Tile64GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile64GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile64 = new TileMap(*Tile64GO, "./assets/map/Tile64.txt", tileSet);
	Tile64->colide = true;

	Tile64GO->box.w = Tile64->GetWidth() * tileSet->GetTileWidth();
	Tile64GO->box.h = Tile64->GetHeight() * tileSet->GetTileHeight();

	Tile64GO->AddComponent(Tile64);
	objectArray.emplace_back(Tile64GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile65GO = new GameObject();
	Tile65GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile65GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile65 = new TileMap(*Tile65GO, "./assets/map/Tile65.txt", tileSet);
	Tile65->colide = true;

	Tile65GO->box.w = Tile65->GetWidth() * tileSet->GetTileWidth();
	Tile65GO->box.h = Tile65->GetHeight() * tileSet->GetTileHeight();

	Tile65GO->AddComponent(Tile65);
	objectArray.emplace_back(Tile65GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile66GO = new GameObject();
	Tile66GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile66GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile66 = new TileMap(*Tile66GO, "./assets/map/Tile66.txt", tileSet);
	Tile66->colide = true;

	Tile66GO->box.w = Tile66->GetWidth() * tileSet->GetTileWidth();
	Tile66GO->box.h = Tile66->GetHeight() * tileSet->GetTileHeight();

	Tile66GO->AddComponent(Tile66);
	objectArray.emplace_back(Tile66GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile67GO = new GameObject();
	Tile67GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile67GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile67 = new TileMap(*Tile67GO, "./assets/map/Tile67.txt", tileSet);
	Tile67->colide = true;

	Tile67GO->box.w = Tile67->GetWidth() * tileSet->GetTileWidth();
	Tile67GO->box.h = Tile67->GetHeight() * tileSet->GetTileHeight();

	Tile67GO->AddComponent(Tile67);
	objectArray.emplace_back(Tile67GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile68GO = new GameObject();
	Tile68GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile68GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile68 = new TileMap(*Tile68GO, "./assets/map/Tile68.txt", tileSet);
	Tile68->colide = true;

	Tile68GO->box.w = Tile68->GetWidth() * tileSet->GetTileWidth();
	Tile68GO->box.h = Tile68->GetHeight() * tileSet->GetTileHeight();

	Tile68GO->AddComponent(Tile68);
	objectArray.emplace_back(Tile68GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	auto Tile69GO = new GameObject();
	Tile69GO->box.x = tileSet->GetTileWidth() * ONETILESQUARE + chaoGO->box.x;
	Tile69GO->box.y = (-10 * tileSet->GetTileHeight()) + chaoGO->box.y;

	auto Tile69 = new TileMap(*Tile69GO, "./assets/map/Tile69.txt", tileSet);
	Tile69->colide = true;

	Tile69GO->box.w = Tile69->GetWidth() * tileSet->GetTileWidth();
	Tile69GO->box.h = Tile69->GetHeight() * tileSet->GetTileHeight();

	Tile69GO->AddComponent(Tile69);
	objectArray.emplace_back(Tile69GO);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

	*/



auto Tile00_ColunaGO = new GameObject();
Tile00_ColunaGO->box.x = (0) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile00_ColunaGO->box.y = (-7) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile00_Coluna = new TileMap(*Tile00_ColunaGO, "./assets/map/Tile00_Coluna.txt", tileSet);
tileMap_Tile00_Coluna->colide = true;

Tile00_ColunaGO->box.w = tileMap_Tile00_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile00_ColunaGO->box.h = tileMap_Tile00_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile00_ColunaGO->AddComponent(tileMap_Tile00_Coluna);
objectArray.emplace_back(Tile00_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile01_ColunaGO = new GameObject();
Tile01_ColunaGO->box.x = (8) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile01_ColunaGO->box.y = (-7) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile01_Coluna = new TileMap(*Tile01_ColunaGO, "./assets/map/Tile01_Coluna.txt", tileSet);
tileMap_Tile01_Coluna->colide = true;

Tile01_ColunaGO->box.w = tileMap_Tile01_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile01_ColunaGO->box.h = tileMap_Tile01_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile01_ColunaGO->AddComponent(tileMap_Tile01_Coluna);
objectArray.emplace_back(Tile01_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile02_ColunaGO = new GameObject();
Tile02_ColunaGO->box.x = (19) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile02_ColunaGO->box.y = (-6) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile02_Coluna = new TileMap(*Tile02_ColunaGO, "./assets/map/Tile02_Coluna.txt", tileSet);
tileMap_Tile02_Coluna->colide = true;

Tile02_ColunaGO->box.w = tileMap_Tile02_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile02_ColunaGO->box.h = tileMap_Tile02_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile02_ColunaGO->AddComponent(tileMap_Tile02_Coluna);
objectArray.emplace_back(Tile02_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile03_ColunaGO = new GameObject();
Tile03_ColunaGO->box.x = (20) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile03_ColunaGO->box.y = (-6) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile03_Coluna = new TileMap(*Tile03_ColunaGO, "./assets/map/Tile03_Coluna.txt", tileSet);
tileMap_Tile03_Coluna->colide = true;

Tile03_ColunaGO->box.w = tileMap_Tile03_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile03_ColunaGO->box.h = tileMap_Tile03_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile03_ColunaGO->AddComponent(tileMap_Tile03_Coluna);
objectArray.emplace_back(Tile03_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile04_ColunaGO = new GameObject();
Tile04_ColunaGO->box.x = (24) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile04_ColunaGO->box.y = (-5) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile04_Coluna = new TileMap(*Tile04_ColunaGO, "./assets/map/Tile04_Coluna.txt", tileSet);
tileMap_Tile04_Coluna->colide = true;

Tile04_ColunaGO->box.w = tileMap_Tile04_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile04_ColunaGO->box.h = tileMap_Tile04_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile04_ColunaGO->AddComponent(tileMap_Tile04_Coluna);
objectArray.emplace_back(Tile04_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile05_ColunaGO = new GameObject();
Tile05_ColunaGO->box.x = (26) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile05_ColunaGO->box.y = (-5) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile05_Coluna = new TileMap(*Tile05_ColunaGO, "./assets/map/Tile05_Coluna.txt", tileSet);
tileMap_Tile05_Coluna->colide = true;

Tile05_ColunaGO->box.w = tileMap_Tile05_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile05_ColunaGO->box.h = tileMap_Tile05_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile05_ColunaGO->AddComponent(tileMap_Tile05_Coluna);
objectArray.emplace_back(Tile05_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile06_ColunaGO = new GameObject();
Tile06_ColunaGO->box.x = (30) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile06_ColunaGO->box.y = (-8) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile06_Coluna = new TileMap(*Tile06_ColunaGO, "./assets/map/Tile06_Coluna.txt", tileSet);
tileMap_Tile06_Coluna->colide = true;

Tile06_ColunaGO->box.w = tileMap_Tile06_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile06_ColunaGO->box.h = tileMap_Tile06_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile06_ColunaGO->AddComponent(tileMap_Tile06_Coluna);
objectArray.emplace_back(Tile06_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile07_ColunaGO = new GameObject();
Tile07_ColunaGO->box.x = (32) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile07_ColunaGO->box.y = (-8) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile07_Coluna = new TileMap(*Tile07_ColunaGO, "./assets/map/Tile07_Coluna.txt", tileSet);
tileMap_Tile07_Coluna->colide = true;

Tile07_ColunaGO->box.w = tileMap_Tile07_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile07_ColunaGO->box.h = tileMap_Tile07_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile07_ColunaGO->AddComponent(tileMap_Tile07_Coluna);
objectArray.emplace_back(Tile07_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile08_ColunaGO = new GameObject();
Tile08_ColunaGO->box.x = (35) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile08_ColunaGO->box.y = (-7) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile08_Coluna = new TileMap(*Tile08_ColunaGO, "./assets/map/Tile08_Coluna.txt", tileSet);
tileMap_Tile08_Coluna->colide = true;

Tile08_ColunaGO->box.w = tileMap_Tile08_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile08_ColunaGO->box.h = tileMap_Tile08_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile08_ColunaGO->AddComponent(tileMap_Tile08_Coluna);
objectArray.emplace_back(Tile08_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile09_ColunaGO = new GameObject();
Tile09_ColunaGO->box.x = (39) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile09_ColunaGO->box.y = (-10) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile09_Coluna = new TileMap(*Tile09_ColunaGO, "./assets/map/Tile09_Coluna.txt", tileSet);
tileMap_Tile09_Coluna->colide = true;

Tile09_ColunaGO->box.w = tileMap_Tile09_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile09_ColunaGO->box.h = tileMap_Tile09_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile09_ColunaGO->AddComponent(tileMap_Tile09_Coluna);
objectArray.emplace_back(Tile09_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile10_ColunaGO = new GameObject();
Tile10_ColunaGO->box.x = (41) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile10_ColunaGO->box.y = (-10) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile10_Coluna = new TileMap(*Tile10_ColunaGO, "./assets/map/Tile10_Coluna.txt", tileSet);
tileMap_Tile10_Coluna->colide = true;

Tile10_ColunaGO->box.w = tileMap_Tile10_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile10_ColunaGO->box.h = tileMap_Tile10_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile10_ColunaGO->AddComponent(tileMap_Tile10_Coluna);
objectArray.emplace_back(Tile10_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile11_ColunaGO = new GameObject();
Tile11_ColunaGO->box.x = (45) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile11_ColunaGO->box.y = (-13) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile11_Coluna = new TileMap(*Tile11_ColunaGO, "./assets/map/Tile11_Coluna.txt", tileSet);
tileMap_Tile11_Coluna->colide = true;

Tile11_ColunaGO->box.w = tileMap_Tile11_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile11_ColunaGO->box.h = tileMap_Tile11_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile11_ColunaGO->AddComponent(tileMap_Tile11_Coluna);
objectArray.emplace_back(Tile11_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile12_ColunaGO = new GameObject();
Tile12_ColunaGO->box.x = (47) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile12_ColunaGO->box.y = (-13) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile12_Coluna = new TileMap(*Tile12_ColunaGO, "./assets/map/Tile12_Coluna.txt", tileSet);
tileMap_Tile12_Coluna->colide = true;

Tile12_ColunaGO->box.w = tileMap_Tile12_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile12_ColunaGO->box.h = tileMap_Tile12_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile12_ColunaGO->AddComponent(tileMap_Tile12_Coluna);
objectArray.emplace_back(Tile12_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile13_ColunaGO = new GameObject();
Tile13_ColunaGO->box.x = (49) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile13_ColunaGO->box.y = (-10) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile13_Coluna = new TileMap(*Tile13_ColunaGO, "./assets/map/Tile13_Coluna.txt", tileSet);
tileMap_Tile13_Coluna->colide = true;

Tile13_ColunaGO->box.w = tileMap_Tile13_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile13_ColunaGO->box.h = tileMap_Tile13_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile13_ColunaGO->AddComponent(tileMap_Tile13_Coluna);
objectArray.emplace_back(Tile13_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile14_ColunaGO = new GameObject();
Tile14_ColunaGO->box.x = (53) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile14_ColunaGO->box.y = (-13) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile14_Coluna = new TileMap(*Tile14_ColunaGO, "./assets/map/Tile14_Coluna.txt", tileSet);
tileMap_Tile14_Coluna->colide = true;

Tile14_ColunaGO->box.w = tileMap_Tile14_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile14_ColunaGO->box.h = tileMap_Tile14_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile14_ColunaGO->AddComponent(tileMap_Tile14_Coluna);
objectArray.emplace_back(Tile14_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile15_ColunaGO = new GameObject();
Tile15_ColunaGO->box.x = (56) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile15_ColunaGO->box.y = (-15) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile15_Coluna = new TileMap(*Tile15_ColunaGO, "./assets/map/Tile15_Coluna.txt", tileSet);
tileMap_Tile15_Coluna->colide = true;

Tile15_ColunaGO->box.w = tileMap_Tile15_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile15_ColunaGO->box.h = tileMap_Tile15_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile15_ColunaGO->AddComponent(tileMap_Tile15_Coluna);
objectArray.emplace_back(Tile15_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile16_ColunaGO = new GameObject();
Tile16_ColunaGO->box.x = (57) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile16_ColunaGO->box.y = (-15) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile16_Coluna = new TileMap(*Tile16_ColunaGO, "./assets/map/Tile16_Coluna.txt", tileSet);
tileMap_Tile16_Coluna->colide = true;

Tile16_ColunaGO->box.w = tileMap_Tile16_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile16_ColunaGO->box.h = tileMap_Tile16_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile16_ColunaGO->AddComponent(tileMap_Tile16_Coluna);
objectArray.emplace_back(Tile16_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile17_ColunaGO = new GameObject();
Tile17_ColunaGO->box.x = (61) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile17_ColunaGO->box.y = (-17) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile17_Coluna = new TileMap(*Tile17_ColunaGO, "./assets/map/Tile17_Coluna.txt", tileSet);
tileMap_Tile17_Coluna->colide = true;

Tile17_ColunaGO->box.w = tileMap_Tile17_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile17_ColunaGO->box.h = tileMap_Tile17_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile17_ColunaGO->AddComponent(tileMap_Tile17_Coluna);
objectArray.emplace_back(Tile17_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile18_ColunaGO = new GameObject();
Tile18_ColunaGO->box.x = (62) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile18_ColunaGO->box.y = (-17) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile18_Coluna = new TileMap(*Tile18_ColunaGO, "./assets/map/Tile18_Coluna.txt", tileSet);
tileMap_Tile18_Coluna->colide = true;

Tile18_ColunaGO->box.w = tileMap_Tile18_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile18_ColunaGO->box.h = tileMap_Tile18_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile18_ColunaGO->AddComponent(tileMap_Tile18_Coluna);
objectArray.emplace_back(Tile18_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile19_ColunaGO = new GameObject();
Tile19_ColunaGO->box.x = (66) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile19_ColunaGO->box.y = (-18) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile19_Coluna = new TileMap(*Tile19_ColunaGO, "./assets/map/Tile19_Coluna.txt", tileSet);
tileMap_Tile19_Coluna->colide = true;

Tile19_ColunaGO->box.w = tileMap_Tile19_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile19_ColunaGO->box.h = tileMap_Tile19_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile19_ColunaGO->AddComponent(tileMap_Tile19_Coluna);
objectArray.emplace_back(Tile19_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile20_ColunaGO = new GameObject();
Tile20_ColunaGO->box.x = (74) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile20_ColunaGO->box.y = (-18) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile20_Coluna = new TileMap(*Tile20_ColunaGO, "./assets/map/Tile20_Coluna.txt", tileSet);
tileMap_Tile20_Coluna->colide = true;

Tile20_ColunaGO->box.w = tileMap_Tile20_Coluna->GetWidth() * tileSet->GetTileWidth();
Tile20_ColunaGO->box.h = tileMap_Tile20_Coluna->GetHeight() * tileSet->GetTileHeight();

Tile20_ColunaGO->AddComponent(tileMap_Tile20_Coluna);
objectArray.emplace_back(Tile20_ColunaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile21_LinhaGO = new GameObject();
Tile21_LinhaGO->box.x = (67) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile21_LinhaGO->box.y = (-18) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile21_Linha = new TileMap(*Tile21_LinhaGO, "./assets/map/Tile21_Linha.txt", tileSet);
tileMap_Tile21_Linha->colide = true;

Tile21_LinhaGO->box.w = tileMap_Tile21_Linha->GetWidth() * tileSet->GetTileWidth();
Tile21_LinhaGO->box.h = tileMap_Tile21_Linha->GetHeight() * tileSet->GetTileHeight();

Tile21_LinhaGO->AddComponent(tileMap_Tile21_Linha);
objectArray.emplace_back(Tile21_LinhaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile22_LinhaGO = new GameObject();
Tile22_LinhaGO->box.x = (46) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile22_LinhaGO->box.y = (-13) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile22_Linha = new TileMap(*Tile22_LinhaGO, "./assets/map/Tile22_Linha.txt", tileSet);
tileMap_Tile22_Linha->colide = true;

Tile22_LinhaGO->box.w = tileMap_Tile22_Linha->GetWidth() * tileSet->GetTileWidth();
Tile22_LinhaGO->box.h = tileMap_Tile22_Linha->GetHeight() * tileSet->GetTileHeight();

Tile22_LinhaGO->AddComponent(tileMap_Tile22_Linha);
objectArray.emplace_back(Tile22_LinhaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile23_LinhaGO = new GameObject();
Tile23_LinhaGO->box.x = (54) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile23_LinhaGO->box.y = (-13) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile23_Linha = new TileMap(*Tile23_LinhaGO, "./assets/map/Tile23_Linha.txt", tileSet);
tileMap_Tile23_Linha->colide = true;

Tile23_LinhaGO->box.w = tileMap_Tile23_Linha->GetWidth() * tileSet->GetTileWidth();
Tile23_LinhaGO->box.h = tileMap_Tile23_Linha->GetHeight() * tileSet->GetTileHeight();

Tile23_LinhaGO->AddComponent(tileMap_Tile23_Linha);
objectArray.emplace_back(Tile23_LinhaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile24_LinhaGO = new GameObject();
Tile24_LinhaGO->box.x = (40) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile24_LinhaGO->box.y = (-10) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile24_Linha = new TileMap(*Tile24_LinhaGO, "./assets/map/Tile24_Linha.txt", tileSet);
tileMap_Tile24_Linha->colide = true;

Tile24_LinhaGO->box.w = tileMap_Tile24_Linha->GetWidth() * tileSet->GetTileWidth();
Tile24_LinhaGO->box.h = tileMap_Tile24_Linha->GetHeight() * tileSet->GetTileHeight();

Tile24_LinhaGO->AddComponent(tileMap_Tile24_Linha);
objectArray.emplace_back(Tile24_LinhaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile25_LinhaGO = new GameObject();
Tile25_LinhaGO->box.x = (48) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile25_LinhaGO->box.y = (-10) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile25_Linha = new TileMap(*Tile25_LinhaGO, "./assets/map/Tile25_Linha.txt", tileSet);
tileMap_Tile25_Linha->colide = true;

Tile25_LinhaGO->box.w = tileMap_Tile25_Linha->GetWidth() * tileSet->GetTileWidth();
Tile25_LinhaGO->box.h = tileMap_Tile25_Linha->GetHeight() * tileSet->GetTileHeight();

Tile25_LinhaGO->AddComponent(tileMap_Tile25_Linha);
objectArray.emplace_back(Tile25_LinhaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile26_LinhaGO = new GameObject();
Tile26_LinhaGO->box.x = (31) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile26_LinhaGO->box.y = (-8) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile26_Linha = new TileMap(*Tile26_LinhaGO, "./assets/map/Tile26_Linha.txt", tileSet);
tileMap_Tile26_Linha->colide = true;

Tile26_LinhaGO->box.w = tileMap_Tile26_Linha->GetWidth() * tileSet->GetTileWidth();
Tile26_LinhaGO->box.h = tileMap_Tile26_Linha->GetHeight() * tileSet->GetTileHeight();

Tile26_LinhaGO->AddComponent(tileMap_Tile26_Linha);
objectArray.emplace_back(Tile26_LinhaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile27_LinhaGO = new GameObject();
Tile27_LinhaGO->box.x = (1) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile27_LinhaGO->box.y = (-7) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile27_Linha = new TileMap(*Tile27_LinhaGO, "./assets/map/Tile27_Linha.txt", tileSet);
tileMap_Tile27_Linha->colide = true;

Tile27_LinhaGO->box.w = tileMap_Tile27_Linha->GetWidth() * tileSet->GetTileWidth();
Tile27_LinhaGO->box.h = tileMap_Tile27_Linha->GetHeight() * tileSet->GetTileHeight();

Tile27_LinhaGO->AddComponent(tileMap_Tile27_Linha);
objectArray.emplace_back(Tile27_LinhaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile28_LinhaGO = new GameObject();
Tile28_LinhaGO->box.x = (33) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile28_LinhaGO->box.y = (-7) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile28_Linha = new TileMap(*Tile28_LinhaGO, "./assets/map/Tile28_Linha.txt", tileSet);
tileMap_Tile28_Linha->colide = true;

Tile28_LinhaGO->box.w = tileMap_Tile28_Linha->GetWidth() * tileSet->GetTileWidth();
Tile28_LinhaGO->box.h = tileMap_Tile28_Linha->GetHeight() * tileSet->GetTileHeight();

Tile28_LinhaGO->AddComponent(tileMap_Tile28_Linha);
objectArray.emplace_back(Tile28_LinhaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile29_LinhaGO = new GameObject();
Tile29_LinhaGO->box.x = (36) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile29_LinhaGO->box.y = (-6) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile29_Linha = new TileMap(*Tile29_LinhaGO, "./assets/map/Tile29_Linha.txt", tileSet);
tileMap_Tile29_Linha->colide = true;

Tile29_LinhaGO->box.w = tileMap_Tile29_Linha->GetWidth() * tileSet->GetTileWidth();
Tile29_LinhaGO->box.h = tileMap_Tile29_Linha->GetHeight() * tileSet->GetTileHeight();

Tile29_LinhaGO->AddComponent(tileMap_Tile29_Linha);
objectArray.emplace_back(Tile29_LinhaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile30_LinhaGO = new GameObject();
Tile30_LinhaGO->box.x = (25) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile30_LinhaGO->box.y = (-5) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile30_Linha = new TileMap(*Tile30_LinhaGO, "./assets/map/Tile30_Linha.txt", tileSet);
tileMap_Tile30_Linha->colide = true;

Tile30_LinhaGO->box.w = tileMap_Tile30_Linha->GetWidth() * tileSet->GetTileWidth();
Tile30_LinhaGO->box.h = tileMap_Tile30_Linha->GetHeight() * tileSet->GetTileHeight();

Tile30_LinhaGO->AddComponent(tileMap_Tile30_Linha);
objectArray.emplace_back(Tile30_LinhaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

auto Tile31_LinhaGO = new GameObject();
Tile31_LinhaGO->box.x = (13) * tileSet->GetTileWidth() + chaoGO->box.x;
Tile31_LinhaGO->box.y = (-4) * tileSet->GetTileHeight() + chaoGO->box.y;

auto tileMap_Tile31_Linha = new TileMap(*Tile31_LinhaGO, "./assets/map/Tile31_Linha.txt", tileSet);
tileMap_Tile31_Linha->colide = true;

Tile31_LinhaGO->box.w = tileMap_Tile31_Linha->GetWidth() * tileSet->GetTileWidth();
Tile31_LinhaGO->box.h = tileMap_Tile31_Linha->GetHeight() * tileSet->GetTileHeight();

Tile31_LinhaGO->AddComponent(tileMap_Tile31_Linha);
objectArray.emplace_back(Tile31_LinhaGO);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////// 






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
	//auto Chao = new TileMap(*chaoGO, "./assets/map/Chao80x80.txt", tileSet);
	auto Chao = new TileMap(*chaoGO, "./assets/map/ChaoInfinito80x80.txt", tileSet);
	//Chao->floor = true;
	Chao->colide = true;

	chaoGO->box.w = Chao->GetWidth() * tileSet->GetTileWidth();
	chaoGO->box.h = Chao->GetHeight() * tileSet->GetTileHeight();

	chaoGO->AddComponent(Chao);
	objectArray.emplace_back(chaoGO);



///////////////////////////////
//	  Conjunto de Predios	//
/////////////////////////////
	auto prediosGO = new GameObject();

	// todo - usaremos o mesmo tileSet por enquanto, nao temos um tileSet soh do chao
	//auto tileSet = new TileSet(80, 80, "./assets/img/tilesetPRETOeLARANJA(40x40).png");
	auto Predios = new TileMap(*prediosGO, "./assets/map/Predios80x80.txt", tileSet);
	Predios->colide = true;

	// hitbox que envolve TODOS os predios
	prediosGO->box.w = Predios->GetWidth() * tileSet->GetTileWidth();
	prediosGO->box.h = Predios->GetHeight() * tileSet->GetTileHeight();
	prediosGO->box.y = chaoGO->box.y - (Predios->GetHeight() * tileSet->GetTileHeight());
	prediosGO->box.x = 0;

	prediosGO->AddComponent(Predios);
	//objectArray.emplace_back(prediosGO);

		auto testeGO = new GameObject();
	auto teste = new TileMap(*testeGO, "./assets/map/TESTE.txt", tileSet);

	// hitbox do background
	//testeGO->box.w = teste->GetWidth() * tileSet->GetTileWidth();
	//testeGO->box.h = teste->GetHeight() * tileSet->GetTileHeight();
	testeGO->box.y = chaoGO->box.y - (teste->GetHeight() * tileSet->GetTileHeight());
	testeGO->box.x = chaoGO->box.x;

	testeGO->AddComponent(teste);
	//objectArray.emplace_back(testeGO);



/////////////////////////////////
//	  Predio Mais Simples	  //
///////////////////////////////
	auto predioSimplesGO = new GameObject();

	// todo - usaremos o mesmo tileSet por enquanto, nao temos um tileSet soh do chao
	//auto tileSet = new TileSet(80, 80, "./assets/img/tilesetPRETOeLARANJA(40x40).png");
	auto PredioSimples = new TileMap(*predioSimplesGO, "./assets/map/PredioSimples80x80.txt", tileSet);
	//PredioSimples->floor = true;
	PredioSimples->colide = true;

	// posicao em relacao ao Chao e tamanho da hitbox do predio
	predioSimplesGO->box.w = PredioSimples->GetWidth() * tileSet->GetTileWidth();
	predioSimplesGO->box.h = PredioSimples->GetHeight() * tileSet->GetTileHeight();
	predioSimplesGO->box.y = chaoGO->box.y - (Chao->GetHeight() * tileSet->GetTileHeight());
	predioSimplesGO->box.x = 30 * Chao->GetWidth();


	predioSimplesGO->AddComponent(PredioSimples);
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
	//auto Lixao = new TileMap(*lixaoGO, "./assets/map/Lixao80x80.txt", tileSet);
/*	auto LixaoTeto = new TileMap(*lixaoTetoGO, "./assets/map/LixaoTeto80x80.txt", tileSet);
//	auto LixaoParedeEsquerda = new TileMap(*lixaoParedeEsquerdaGO, "./assets/map/LixaoParedeEsquerda80x80.txt", tileSet);
	//Lixao->colide = true;
	//LixaoTeto->floor = true;
//	LixaoTeto->colide = true;
//	LixaoParedeEsquerda->colide = true;

	// hitbox que envolve o lixao
	lixaoGO->box.w = Lixao->GetWidth() * tileSet->GetTileWidth();
	lixaoGO->box.h = Lixao->GetHeight() * tileSet->GetTileHeight();
	lixaoGO->box.y = /*chaoGO->box.y/ 800 - (Lixao->GetHeight() * tileSet->GetTileHeight());
	lixaoGO->box.x = /*chaoGO->box.x/0;
	

	// hitbox do teto do lixao
	lixaoTetoGO->box.w = LixaoTeto->GetWidth() * tileSet->GetTileWidth();
	lixaoTetoGO->box.h = LixaoTeto->GetHeight() * tileSet->GetTileHeight();
	lixaoTetoGO->box.y = lixaoGO->box.y;
	lixaoTetoGO->box.x = lixaoGO->box.x + 4 * tileSet->GetTileWidth();

	// hitbox da parede esquerda do lixao
	lixaoParedeEsquerdaGO->box.w = LixaoParedeEsquerda->GetWidth() * tileSet->GetTileWidth();
	lixaoParedeEsquerdaGO->box.h = LixaoParedeEsquerda->GetHeight() * tileSet->GetTileHeight();
	lixaoParedeEsquerdaGO->box.y = lixaoGO->box.y;
	lixaoParedeEsquerdaGO->box.x = lixaoGO->box.x;
*/
	//lixaoGO->AddComponent(Lixao);
//	lixaoTetoGO->AddComponent(LixaoTeto);
//	lixaoParedeEsquerdaGO->AddComponent(LixaoParedeEsquerda);

	//objectArray.emplace_back(lixaoGO);
/*	objectArray.emplace_back(lixaoTetoGO);
/	objectArray.emplace_back(lixaoParedeEsquerdaGO);



///////////////////////////////////
//	Plataforma de 3 quadrados	//
/////////////////////////////////
	auto plataformaGO = new GameObject();
	auto Plataforma = new TileMap(*plataformaGO, "./assets/map/Plataforma80x80.txt", tileSet);
	Plataforma->colide = true;


	// hitbox da plataforma
	plataformaGO->box.w = Plataforma->GetWidth() * tileSet->GetTileWidth();
	plataformaGO->box.h = Plataforma->GetHeight() * tileSet->GetTileHeight();
	plataformaGO->box.y = predioSimplesGO->box.y - 3 * tileSet->GetTileHeight();
	plataformaGO->box.x = predioSimplesGO->box.x - 5 * tileSet->GetTileWidth();

	plataformaGO->AddComponent(Plataforma);
	objectArray.emplace_back(plataformaGO);



///////////////////////////////////////////
//	SEGUNDA Plataforma de 3 quadrados	//
/////////////////////////////////////////
	auto segundaPlataformaGO = new GameObject();
	auto SegundaPlataforma = new TileMap(*segundaPlataformaGO, "./assets/map/Plataforma80x80.txt", tileSet);
	SegundaPlataforma->colide = true;


	// hitbox da plataforma
	segundaPlataformaGO->box.w = SegundaPlataforma->GetWidth() * tileSet->GetTileWidth();
	segundaPlataformaGO->box.h = SegundaPlataforma->GetHeight() * tileSet->GetTileHeight();
	segundaPlataformaGO->box.y = predioSimplesGO->box.y /*-  1 * tileSet->GetTileHeight()/;
	segundaPlataformaGO->box.x = predioSimplesGO->box.x - 5 * tileSet->GetTileWidth();

	segundaPlataformaGO->AddComponent(SegundaPlataforma);
	objectArray.emplace_back(segundaPlataformaGO);



///////////////////////////////////
//	 Plataforma de 3 quadrados	//
/////////////////////////////////
	auto terceiraPlataformaGO = new GameObject();
	auto TerceiraPlataforma = new TileMap(*terceiraPlataformaGO, "./assets/map/Plataforma80x80.txt", tileSet);
	TerceiraPlataforma->colide = true;


	// hitbox da plataforma
	terceiraPlataformaGO->box.w = TerceiraPlataforma->GetWidth() * tileSet->GetTileWidth();
	terceiraPlataformaGO->box.h = TerceiraPlataforma->GetHeight() * tileSet->GetTileHeight();
	terceiraPlataformaGO->box.y = predioSimplesGO->box.y + 1 * tileSet->GetTileHeight();
	terceiraPlataformaGO->box.x = predioSimplesGO->box.x + 10 * tileSet->GetTileWidth();

	terceiraPlataformaGO->AddComponent(TerceiraPlataforma);
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

