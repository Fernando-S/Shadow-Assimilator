#include "CanhaoVermelho.h"
#include "Game.h"
#include "Sound.h"
#include "FinalBoss.h"
#include <iostream>

using namespace std;

CanhaoVermelho* CanhaoVermelho::canhaoVermelho = nullptr;

CanhaoVermelho::CanhaoVermelho(GameObject& associated) : Component(associated) {
	canhaoVermelho = this;

	hp = FINALBOSS_INITIAL_HP;

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
	auto inputManager = InputManager::GetInstance();
	double angleVariation = 0;

	if (0) {
		hp = 0;
		damaged = true;
	}


	if (hp <= 0) {
		// Deleta o CanhaoVermelho se o hp dele acabou
		associated.RequestDelete();


	}
	else {
		//LightRecoilTimer.Update(dt);
		//HeavyRecoilTimer.Update(dt);
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

}

int CanhaoVermelho::GetHP() {
	return hp;
}
