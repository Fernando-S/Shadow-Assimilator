#include "CanhaoAmarelo.h"
#include "Game.h"
#include "Sound.h"
#include <iostream>

using namespace std;

CanhaoAmarelo* CanhaoAmarelo::canhaoAmarelo = nullptr;

CanhaoAmarelo::CanhaoAmarelo(GameObject& associated) : Component(associated) {
	canhaoAmarelo = this;

	hp = FINALBOSS_INITIAL_HP;

	// Carrega o sprite do boss final e do escudodele
	sprite = new Sprite(associated, "./assets/img/Boss Final/Boss_final.png");

	// Carrega som do boss Final
	CanhaoAmareloSFX = new Sound(associated);

	associated.AddComponent(CanhaoAmareloSFX);
	associated.AddComponent(sprite);
	associated.AddComponent(new Collider(associated));
	//	associated.angleDeg = angle * 180 / PI;
}

CanhaoAmarelo::~CanhaoAmarelo() {
	canhaoAmarelo = nullptr;
}

void CanhaoAmarelo::Start() {

}

void CanhaoAmarelo::Update(float dt) {
	auto inputManager = InputManager::GetInstance();
	double angleVariation = 0;

	if (inputManager.KeyPress(NUMPAD_ZERO_KEY)) {
		hp = 0;
		damaged = true;
	}


	if (hp <= 0) {
		// Deleta o CanhaoAmarelo se o hp dele acabou
		associated.RequestDelete();


	}
	else {
		//LightRecoilTimer.Update(dt);
		//HeavyRecoilTimer.Update(dt);
	}
}

void CanhaoAmarelo::Render() {

}

bool CanhaoAmarelo::Is(string type) {
	if (type == "CanhaoAmarelo")
		return true;
	else
		return false;
}

void CanhaoAmarelo::NotifyCollision(GameObject& other) {
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

int CanhaoAmarelo::GetHP() {
	return hp;
}

/*
void CanhaoAmarelo::LightShoot(Vec2 target) {
	LightRecoilTimer.Restart();
	associated.RemoveComponent(sprite);
	if (Player::player->GetCenter().x > this->associated.box.x) {
		//sprite = new Sprite(associated, "./assets/img/Robot/001A1BOM.png", 6, 0.2);
	}
	else if (Player::player->GetCenter().x < this->associated.box.x) {
		//	sprite = new Sprite(associated, "./assets/img/Robot/001A2BOM.png", 6, 0.2);
	}
	associated.AddComponent(sprite);
}
void CanhaoAmarelo::HeavyShoot(Vec2 target) {
	HeavyRecoilTimer.Restart();
	associated.RemoveComponent(sprite);
	if (Player::player->GetCenter().x > this->associated.box.x) {
		//	sprite = new Sprite(associated, "./assets/img/Robot/001A1BOM.png", 6, 0.2);
	}
	else if (Player::player->GetCenter().x < this->associated.box.x) {
		//	sprite = new Sprite(associated, "./assets/img/Robot/001A2BOM.png", 6, 0.2);
	}
	associated.AddComponent(sprite);
}
*/