#include "GameState0.h"
#include "Game.h"
#include "GameData.h"


auto surpriseGO = new GameObject();

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
	auto chaoGO = new GameObject();
	chaoGO->box.x = 0;
	chaoGO->box.y = 800;

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
	auto tileMap_Chao = new TileMap(*chaoGO, "./assets/map/tileMap_CHAOZAO.txt", tileSet);
	
	tileMap_Background->colide = false;
	tileMap_Colidem->colide = false;
	tileMap_Chao->colide = true;

	chaoGO->box.w = tileMap_Chao->GetWidth() * tileSet->GetTileWidth();
	chaoGO->box.h = tileMap_Chao->GetHeight() * tileSet->GetTileHeight();

	chaoGO->AddComponent(tileMap_Chao);
	objectArray.emplace_back(chaoGO);

	colidemGO->AddComponent(tileMap_Colidem);
	objectArray.emplace_back(colidemGO);

	backgroundGO->AddComponent(tileMap_Background);
	objectArray.emplace_back(backgroundGO);












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
	robotGO->box.PlaceCenter(Vec2(3000, 800 - robotGO->box.h));

	objectArray.emplace_back(robotGO);



///////////////////////////////////
//		Carrega a Personagem	//
/////////////////////////////////
	auto playerGO = new GameObject();
	auto player = new Player(*playerGO);

	playerGO->AddComponent(player);
	playerGO->box.PlaceCenter(Vec2(1600, 600 - playerGO->box.h));
	//playerGO->box.PlaceCenter(Vec2(1600, -59));

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

}

void GameState0::Update(float dt){
	unsigned i, j;
	auto inputManager = InputManager::GetInstance();
	
	// Faz o update na camera e na box do mapa
	Camera::Update(dt);

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

