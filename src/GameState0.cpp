#include "GameState0.h"
#include "Game.h"
#include "GameData.h"


auto surpriseGO = new GameObject();

bool dois = false, tres = false, quatro = false, cinco = false, meia = false, sete = false, oito = false;
bool cima1 = false, cima2 = false, baixo1 = false, baixo2 = false, esquerda1 = false, esquerda2 = false;
bool direita1 = false, direita2 = false, mostrando = false;

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
	//auto bg = new Sprite(*bgGO, "./assets/img/Art_logo_mono3x.png");
	//auto bg = new Sprite(*bgGO, "./assets/img/ocean.jpg");
	//auto bg = new Sprite(*bgGO, "./assets/img/teste.jpg");
	//auto bg = new Sprite(*bgGO, "./assets/img/cinza.jpg");
	auto bg = new Sprite(*bgGO, "./assets/img/background.png");
	//bg->background = true;				// Seta a flag de que eh o background que vai ser seguido	
	
	// Seta a escala e posiciona no centro da tela
	//bg->SetScale(0.2789, 0.2416);	// (resolution width / image width) * escala que queremos, (resolution height / image height) * escala que queremos
	bg->SetScale(1, 1.3333);	// (resolution width / image width) * escala que queremos, (resolution height / image height) * escala que queremos

	//bgGO->box.x = (Game::GetInstance().GetWidth() - bg->GetWidth()) / 2;
	//bgGO->box.y = (Game::GetInstance().GetHeight() - bg->GetHeight()) / 4;

	auto bgCamFollower = new CameraFollower(*bgGO);
	bgGO->AddComponent(bgCamFollower);


	bgGO->box.h = bg->GetHeight();
	bgGO->box.w = bg->GetWidth();

	bgGO->AddComponent(bg);
	objectArray.emplace_back(bgGO);

	// Chama funcao que carrega todas as contrucoes (chaos e predios) 
	LoadBuildings();
	

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
//		Carrega a Personagem	//
/////////////////////////////////
	auto playerGO = new GameObject();
	auto player = new Player(*playerGO);

	playerGO->AddComponent(player);
	//playerGO->box.PlaceCenter(Vec2(704, 741));
	//playerGO->box.PlaceCenter(Vec2(704, 500));
	playerGO->box.PlaceCenter(Vec2(1600, -59));

	//playerGO->box.w = 80;
	std::cout << "largura da personagem: " << playerGO->box.w << std::endl;
	std::cout << "altura da personagem: " << playerGO->box.h << std::endl;

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


	//Build(*chaoGO, *predioSimplesGO, *tileSet, *tileMap_PredioSimples, true, false, false, false, false,
		//chaoGO->box.y - (tileMap_Chao->GetHeight() * tileSet->GetTileHeight()), 30 * tileMap_Chao->GetWidth());

	predioSimplesGO->AddComponent(tileMap_PredioSimples);
	objectArray.emplace_back(predioSimplesGO);



///////////////////////////////
//	  Carrega o Lixao		//
/////////////////////////////
	auto lixaoGO = new GameObject();
	auto lixaoTetoGO = new GameObject();
	auto lixaoParedeEsquerdaGO = new GameObject();

	// todo - usaremos o mesmo tileSet por enquanto, nao temos um tileSet soh do chao
	//auto tileSet = new TileSet(80, 80, "./assets/img/tilesetPRETOeLARANJA(40x40).png");
	auto tileMap_Lixao = new TileMap(*lixaoGO, "./assets/map/tileMap_Lixao80x80.txt", tileSet);
	auto tileMap_LixaoTeto = new TileMap(*lixaoTetoGO, "./assets/map/tileMap_LixaoTeto80x80.txt", tileSet);
	auto tileMap_LixaoParedeEsquerda = new TileMap(*lixaoParedeEsquerdaGO, "./assets/map/tileMap_LixaoParedeEsquerda80x80.txt", tileSet);
	//tileMap_Lixao->colide = true;
	//tileMap_LixaoTeto->floor = true;
	tileMap_LixaoTeto->colide = true;
	tileMap_LixaoParedeEsquerda->colide = true;

	// hitbox que envolve o lixao
	lixaoGO->box.w = tileMap_Lixao->GetWidth() * tileSet->GetTileWidth();
	lixaoGO->box.h = tileMap_Lixao->GetHeight() * tileSet->GetTileHeight();
	lixaoGO->box.y = chaoGO->box.y - (tileMap_Lixao->GetHeight() * tileSet->GetTileHeight());
	lixaoGO->box.x = chaoGO->box.x;

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

	lixaoGO->AddComponent(tileMap_Lixao);
	lixaoTetoGO->AddComponent(tileMap_LixaoTeto);
	lixaoParedeEsquerdaGO->AddComponent(tileMap_LixaoParedeEsquerda);

	objectArray.emplace_back(lixaoGO);
	objectArray.emplace_back(lixaoTetoGO);
	objectArray.emplace_back(lixaoParedeEsquerdaGO);


}

// Loucura loucura
void GameState0::Build(GameObject chaoGO, GameObject go, TileSet tileSet, TileMap tileMap, bool background, bool chao, bool teto, bool paredeEsquerda, bool paredeDireita, int ntilesX, int ntilesY) {
	
	if (background && !chao && !teto && !paredeEsquerda && !paredeDireita) {
		/*
		go->box.w = tileMap->GetWidth() * tileSet->GetTileWidth();
		go->box.h = tileMap->GetHeight() * tileSet->GetTileHeight();
		//go->box.y = chaoGO->box.y - (tileMap->GetHeight() * tileSet->GetTileHeight());
		//go->box.x = 30 * tileMap->GetWidth();
		go->box.y = ntilesY;
		go->box.x = ntilesX;

		go->AddComponent(tileMap);
		*/

		go.box.w = tileMap.GetWidth() * tileSet.GetTileWidth();
		go.box.h = tileMap.GetHeight() * tileSet.GetTileHeight();
		//go->box.y = chaoGO->box.y - (tileMap->GetHeight() * tileSet->GetTileHeight());
		//go->box.x = 30 * tileMap->GetWidth();
		go.box.y = ntilesY;
		go.box.x = ntilesX;

		go.AddComponent(&tileMap);
	}
	else if (background && chao && !teto && !paredeEsquerda && !paredeDireita) {

	}
	else if (background && !chao && teto && !paredeEsquerda && !paredeDireita) {

	}
	else if (background && !chao && !teto && paredeEsquerda && !paredeDireita) {

	}
	else if (background && !chao && !teto && !paredeEsquerda && paredeDireita) {

	}
	else if (background && chao && teto && !paredeEsquerda && !paredeDireita) {

	}
	else if (background && chao && !teto && paredeEsquerda && !paredeDireita) {

	}
	else if (background && chao && !teto && !paredeEsquerda && paredeDireita) {

	}
	else if (background && chao && teto && paredeEsquerda && !paredeDireita) {

	}
	else if (background && chao && teto && !paredeEsquerda && paredeDireita) {

	}
	else if (background && chao && teto && paredeEsquerda && !paredeDireita) {

	}
	else if (!background && !chao && !teto && !paredeEsquerda && !paredeDireita) {	// Nao faz sentido existir esse daqui

	}
	else if (!background && chao && !teto && !paredeEsquerda && !paredeDireita) {

	}
	else if (!background && !chao && teto && !paredeEsquerda && !paredeDireita) {

	}
	else if (!background && !chao && !teto && paredeEsquerda && !paredeDireita) {

	}
	else if (!background && !chao && !teto && !paredeEsquerda && paredeDireita) {

	}
	else if (!background && chao && teto && !paredeEsquerda && !paredeDireita) {

	}
	else if (!background && chao && !teto && paredeEsquerda && !paredeDireita) {

	}
	else if (!background && chao && !teto && !paredeEsquerda && paredeDireita) {

	}
	else if (!background && chao && teto && paredeEsquerda && !paredeDireita) {

	}
	else if (!background && chao && teto && !paredeEsquerda && paredeDireita) {

	}
	else if (!background && chao && teto && paredeEsquerda && !paredeDireita) {

	}

	
}