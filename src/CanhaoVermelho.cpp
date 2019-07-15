#include "CanhaoVermelho.h"
#include "Game.h"
#include "Sound.h"
#include <iostream>

using namespace std;

CanhaoVermelho* CanhaoVermelho::canhaoVermelho = nullptr;

CanhaoVermelho::CanhaoVermelho(GameObject& associated) : Component(associated) {
	canhaoVermelho = this;

	//hp = FINALBOSS_INITIAL_HP;

	// Carrega o sprite do boss final e do escudodele
	sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_00.png");

	// Carrega som do boss Final
	CanhaoVermelhoSFX = new Sound(associated);

	associated.AddComponent(CanhaoVermelhoSFX);
	associated.AddComponent(sprite);
	associated.AddComponent(new Collider(associated));
}

CanhaoVermelho::~CanhaoVermelho() {
	canhaoVermelho = nullptr;
}

void CanhaoVermelho::Start() {

}

void CanhaoVermelho::Update(float dt) {
	// todo - englobar tudo num if de se a o canhao ainda pode ser utilizado (variavel da GameData)

	reloadingRedTimer.Update(dt);
	
	// Canhoes em cima das plataformas
	if (!doMeio) {
		// troca os sprites dos canhoes carregando
		if (reloadingRedTimer.Get() > 3.2) {
			reloadingRedTimer.Restart();
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_00.png");
			associated.AddComponent(sprite);
			loaded = false;
		}
		else if (reloadingRedTimer.Get() > 2.8) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_07.png");
			associated.AddComponent(sprite);
			loaded = true;
		}
		else if (reloadingRedTimer.Get() > 2.4) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_06.png");
			associated.AddComponent(sprite);
		}
		else if (reloadingRedTimer.Get() > 2.0) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_05.png");
			associated.AddComponent(sprite);
		}
		else if (reloadingRedTimer.Get() > 1.6) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_04.png");
			associated.AddComponent(sprite);
		}
		else if (reloadingRedTimer.Get() > 1.2) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_03.png");
			associated.AddComponent(sprite);
		}
		else if (reloadingRedTimer.Get() > 0.8) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_02.png");
			associated.AddComponent(sprite);
		}
		else if (reloadingRedTimer.Get() > 0.4) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_01.png");
			associated.AddComponent(sprite);
		}
	}
	// Canhao do meio 2x mais rapido
	else {
		// troca os sprites do canhao carregando
		if (reloadingRedTimer.Get() > 1.6) {
			reloadingRedTimer.Restart();
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_00.png");
			associated.AddComponent(sprite);
			loaded = false;
		}
		else if (reloadingRedTimer.Get() > 1.4) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_07.png");
			associated.AddComponent(sprite);
			loaded = true;
		}
		else if (reloadingRedTimer.Get() > 1.2) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_06.png");
			associated.AddComponent(sprite);
		}
		else if (reloadingRedTimer.Get() > 0.9) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_05.png");
			associated.AddComponent(sprite);
		}
		else if (reloadingRedTimer.Get() > 0.8) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_04.png");
			associated.AddComponent(sprite);
		}
		else if (reloadingRedTimer.Get() > 0.6) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_03.png");
			associated.AddComponent(sprite);
		}
		else if (reloadingRedTimer.Get() > 0.4) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_02.png");
			associated.AddComponent(sprite);
		}
		else if (reloadingRedTimer.Get() > 0.2) {
			associated.RemoveComponent(sprite);
			sprite = new Sprite(associated, "./assets/img/Boss Final/torre2/torre2_01.png");
			associated.AddComponent(sprite);
		}
	}
	


}

void CanhaoVermelho::Render() {

}

bool CanhaoVermelho::Is(string type) {
	if (type == "CanhaoVermelho")
		return true;
	else
		return false;
}

void CanhaoVermelho::NotifyCollision(GameObject& other) {

}

