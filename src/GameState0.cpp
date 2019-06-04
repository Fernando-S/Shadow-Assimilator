#include "GameState0.h"
#include "Game.h"
#include "GameData.h"




auto surpriseGO = new GameObject();

bool dois = false, tres = false, quatro = false, cinco = false, meia = false, sete = false, oito = false;
bool cima1 = false, cima2 = false, baixo1 = false, baixo2 = false, esquerda1 = false, esquerda2 = false;
bool direita1 = false, direita2 = false, mostrando = false;

GameState0::GameState0() {
//	started = false;
//	quitRequested = false;
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
	auto bg = new Sprite(*bgGO, "./assets/img/Art_logo_mono3x.png");
//	auto bg = new Sprite(*bgGO, "./assets/img/ocean.jpg");
	bg->background = true;				// Seta a flag de que eh o background que vai ser seguido	
	
	// Seta a escala e posiciona no centro da tela
	bg->SetScale(0.2789, 0.2416);	// (resolution width / image width) * escala que queremos, (resolution height / image height) * escala que queremos

	

	auto bgCamFollower = new CameraFollower(*bgGO/*, true*/);
	bgGO->AddComponent(bgCamFollower);

	//bgGO->box.x = (Game::GetInstance().GetWidth() - bg->GetWidth()) / 2;
	//bgGO->box.y = (Game::GetInstance().GetHeight() - bg->GetHeight()) / 4;

	bgGO->box.h = bg->GetHeight();
	bgGO->box.w = bg->GetWidth();

	bgGO->AddComponent(bg);
	objectArray.emplace_back(bgGO);
	

///////////////////////////
//	  Carrega o Mapa	//
/////////////////////////
	auto mapGO = new GameObject();
	mapGO->box.x = 0;					// todo - resolver posicao
	mapGO->box.y = 0;					// todo - resolver posicao
	//mapGO->box.PlaceCenter(Vec2(0, 800));				// todo - resolver posicao

	//auto tileSet = new TileSet(64, 64, "./assets/img/tileset.png");
	//auto tileMap = new TileMap(*mapGO, "./assets/map/MEUtileMap.txt", tileSet);

	// TileSet de 40 por 40
//	auto tileSet = new TileSet(40, 40, "./assets/img/tilesetPRETOeLARANJA(40x40).png");
//	auto tileMap = new TileMap(*mapGO, "./assets/map/tileMap40x40.txt", tileSet);
	

	// TileSet de 80 por 80
	auto tileSet = new TileSet(80, 80, "./assets/img/tilesetPRETOeLARANJA(40x40).png");
	//auto tileMap = new TileMap(*mapGO, "./assets/map/tileMap80x80.txt", tileSet);
	auto tileMap = new TileMap(*mapGO, "./assets/map/tileMap80x802.txt", tileSet);

	mapGO->box.w = tileMap->GetWidth() * tileSet->GetTileHeight();
	mapGO->box.h = tileMap->GetHeight() * tileSet->GetTileHeight();
	//mapGO->box.h = 3 * tileSet->GetTileHeight();

	std::cout << "largura do tileMap: " << tileMap->GetWidth() << "; altura do tileMap: " << tileMap->GetHeight() << std::endl;
	std::cout << "largura do mapGO: " << mapGO->box.w << "; altura do mapGO: " << mapGO->box.h << std::endl;
	std::cout << "x do mapGO: " << mapGO->box.x << "; y do mapGO: " << mapGO->box.y << std::endl;


	//auto mapCameraFollower = new CameraFollower(*mapGO);
	//mapGO->AddComponent(mapCameraFollower);


	mapGO->AddComponent(tileMap);
	objectArray.emplace_back(mapGO);


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
//		Carrega o Penguin		//
/////////////////////////////////
	auto penguinGO = new GameObject();
	auto penguin = new PenguinBody(*penguinGO);

	penguinGO->AddComponent(penguin);
	//penguinGO->box.PlaceCenter(Vec2(704, 741));
	penguinGO->box.PlaceCenter(Vec2(704, -68));
	objectArray.emplace_back(penguinGO);

	Camera::Follow(penguinGO);			// Coloca a camera para seguir o Penguin

///////////////////////////////////
//		Collider do Chao		//
/////////////////////////////////
	//auto chaoGO = new GameObject();
	


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

		if (direita2 && inputManager.KeyPress(SPACE_KEY)) {
			mostrando = true;
			surpriseGO->render = true;
			std::cout << "mostrando = true" << std::endl;
		}
		else if (mostrando && inputManager.MouseRelease(LEFT_MOUSE_BUTTON)) {
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

		//if (oito && inputManager.KeyPress(SPACE_KEY)) {
		if (oito && inputManager.MouseRelease(LEFT_MOUSE_BUTTON)) {
			mostrando = true;
			surpriseGO->render = true;
			std::cout << "mostrando = true" << std::endl;
		}
		//else if (mostrando && inputManager.KeyPress(A_KEY)) {
		else if (mostrando && inputManager.MouseRelease(RIGHT_MOUSE_BUTTON)) {
			mostrando = false;
			surpriseGO->render = false;
			std::cout << "mostrando = false" << std::endl;
		}
	}










	std::vector<Collider*> colliders(objectArray.size(), nullptr);
	bool collidersArrayFilled = false;

	// todo - ver se precisa mudar esse reconhecimento de colisao

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
	if (!PenguinBody::player) {
		GameData::playerVictory = false;
		popRequested = true;

		// todo - pensar melhor em como mudar de tela apenas apos o termino da animacao de explosao
//		TimeToEndPlayerAnimation.Update(dt);
//		if (PenguinBody::secondsToSelfDestruction/*, selfDestructCount.Get() > secondsToSelfDestruct/)
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
