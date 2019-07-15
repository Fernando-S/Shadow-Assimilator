#include "FinalBoss.h"
#include "Game.h"
#include "Sound.h"
#include <iostream>

using namespace std;

FinalBoss* FinalBoss::finalBoss = nullptr;

FinalBoss::FinalBoss(GameObject& associated) : Component(associated) {
	finalBoss = this;

	hp = FINALBOSS_INITIAL_HP;

	// Carrega o sprite do boss final e do escudodele
	//sprite = new Sprite(associated, "./assets/img/Boss Final/Boss_final.png");
	sprite = new Sprite(associated, "./assets/img/Boss Final/Boss_final1.png");

	// Carrega som do boss Final
	FinalBossSFX = new Sound(associated);

	associated.AddComponent(FinalBossSFX);
	associated.AddComponent(sprite);
	associated.AddComponent(new Collider(associated));
}

FinalBoss::~FinalBoss() {
	finalBoss = nullptr;
}

void FinalBoss::Start() {

}

void FinalBoss::Update(float dt) {
	auto inputManager = InputManager::GetInstance();

	if (inputManager.KeyPress(NUMPAD_ZERO_KEY)) {
		hp = 0;
		damaged = true;
	}


	if (hp <= 0) {
		// Deleta o FinalBoss se o hp dele acabou
		associated.RequestDelete();


	}
	else {
		//LightRecoilTimer.Update(dt);
		//HeavyRecoilTimer.Update(dt);
	}
}

void FinalBoss::Render() {

}

bool FinalBoss::Is(string type) {
	if (type == "FinalBoss")
		return true;
	else
		return false;
}

void FinalBoss::NotifyCollision(GameObject& other) {
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

int FinalBoss::GetHP() {
	return hp;
}
