#include "Laser.h"


Laser::Laser(GameObject& associated, float angle, float speed, int damage, float maxDistance,
				const char* sprite, int frameCount, float frameTime) : Component(associated) {

	this->speed = { speed, 0 };
	this->distanceLeft = maxDistance;
	this->damage = damage;
	this->speedMagnitude = speed;

	associated.AddComponent(new Sprite(associated, sprite, frameCount, frameTime));
	associated.AddComponent(new Collider(associated));
	associated.angleDeg = (180 / PI)*angle;				// Corrige o angulo do Tiro
	this->speed = this->speed.GetRotated(angle);		// Corrige a direcao do Tiro
}

void Laser::Update(float dt) {
	distanceLeft -= speedMagnitude * dt;

	if (distanceLeft <= 0)
		associated.RequestDelete();
	else
		associated.box += speed * dt;
}

void Laser::Render() {

}

bool Laser::Is(std::string type) {
	if (type == "Laser")
		return true;
	else
		return false;
}

int Laser::GetDamage() {
	return damage;
}

void Laser::NotifyCollision(GameObject& other) {
	auto player = (Player*)other.GetComponent("Player");
	auto robot = (Robot*)other.GetComponent("Robot");
	auto coatGuy = (CoatGuy*)other.GetComponent("CoatGuy");
	auto tileMap = (TileMap*)other.GetComponent("TileMap");

	// Deleta o tiro apenas se colidir com o inimigo do atirador
	if (player && (this->robotLaser || this->coatGuyLaser))
		associated.RequestDelete();
	else if ((robot || coatGuy) && this->playerLaser)
		associated.RequestDelete();
	else if(tileMap && tileMap->colide)
		associated.RequestDelete();
}
