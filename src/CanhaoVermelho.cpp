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
	//	associated.angleDeg = angle * 180 / PI;
}

CanhaoVermelho::~CanhaoVermelho() {
	canhaoVermelho = nullptr;
}

void CanhaoVermelho::Start() {

}

void CanhaoVermelho::Update(float dt) {
	// todo - englobar tudo num if de se a o canhao ainda pode ser utilizado (variavel da GameData)

	reloadingRedTimer.Update(dt);
	/*
	if (!doMeio) {
		if (reloadingRedTimer.Get() > 1.0) {
		}
		else if (reloadRedTimer.Get() > 0.9) {
		}
		else if (reloadRedTimer.Get() > 0.8) {
		}
		else if (reloadRedTimer.Get() > 0.7) {
		}
		else if (reloadRedTimer.Get() > 0.6) {
		}
		else if (reloadRedTimer.Get() > 0.5) {
		}
		else if (reloadRedTimer.Get() > 0.4) {
		}
		else if (reloadRedTimer.Get() > 0.3) {
		}
		else if (reloadRedTimer.Get() > 0.2) {
		}
		else if (reloadRedTimer.Get() > 0.1) {
		}
	}
	else {

	}
	*/


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
	/*
	auto laser = (Laser*)other.GetComponent("Laser");
	auto player1 = (Player*)other.GetComponent("Player");
	auto coatGuy = (CoatGuy*)other.GetComponent("CoatGuy");

	// Prosfere dano ao boss se o tiro for do jogador
	if (laser && (laser->playerLaser || laser->coatGuyLaser)) {
		//std::cout << "Vida do Boss: " << hp << std::endl;
		hp -= laser->GetDamage();
	}
	else if (player1 && (Player::player->isAtacking || CoatGuy::coatGuy->isAtacking)) {
		//cout << "Deu dano no boss\n";
		hp -= 2;		// Prosfere dano ao boss se ele sofrer um ataque melee do jogador
	}
	*/
}

/*
int CanhaoVermelho::GetHP() {
	return hp;
}
*/
