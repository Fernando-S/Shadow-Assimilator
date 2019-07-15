#include "Escudo.h"
#include "Game.h"
#include "Sound.h"
#include <iostream>

using namespace std;

Escudo* Escudo::escudo = nullptr;

Escudo::Escudo(GameObject& associated) : Component(associated) {
	escudo = this;

	hp = FINALBOSS_INITIAL_HP;

	// Carrega o sprite do boss final e do escudodele
	//sprite = new Sprite(associated, "./assets/img/Boss Final/escudo.png");
	sprite = new Sprite(associated, "./assets/img/Boss Final/escudo1.png");

	// Carrega som do boss Final
	EscudoSFX = new Sound(associated);

	associated.AddComponent(EscudoSFX);
	associated.AddComponent(sprite);
	associated.AddComponent(new Collider(associated));
}

Escudo::~Escudo() {
	escudo = nullptr;
}

void Escudo::Start() {

}

void Escudo::Update(float dt) {
	auto inputManager = InputManager::GetInstance();

	if (0) {
		hp = 0;
		damaged = true;
	}


	if (hp <= 0) {
		// Deleta o Escudo se o hp dele acabou
		associated.RequestDelete();


	}
	else {
		//LightRecoilTimer.Update(dt);
		//HeavyRecoilTimer.Update(dt);
	}
}

void Escudo::Render() {

}

bool Escudo::Is(string type) {
	if (type == "Escudo")
		return true;
	else
		return false;
}

void Escudo::NotifyCollision(GameObject& other) {
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

int Escudo::GetHP() {
	return hp;
}
