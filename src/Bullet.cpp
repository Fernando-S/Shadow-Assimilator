#include "Bullet.h"


Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance,
				const char* sprite, int frameCount, float frameTime) : Component(associated) {
	//esse
	this->speed = { speed, 0 };
	this->distanceLeft = maxDistance;
	this->damage = damage;
	// esse
	this->speedMagnitude = speed;

	associated.AddComponent(new Sprite(associated, sprite, frameCount, frameTime));
	associated.AddComponent(new Collider(associated));
	associated.angleDeg = (180 / PI)*angle;				// Corrige o angulo do Tiro
	this->speed = this->speed.GetRotated(angle);		// Corrige a direcao do Tiro
}

void Bullet::Update(float dt) {
	distanceLeft -= speedMagnitude * dt;

	if (distanceLeft <= 0)
		associated.RequestDelete();
	else
		associated.box += speed * dt;
}

void Bullet::Render() {

}

bool Bullet::Is(std::string type) {
	if (type == "Bullet")
		return true;
	else
		return false;
}

int Bullet::GetDamage() {
	return damage;
}

void Bullet::NotifyCollision(GameObject& other) {
	auto player = (Player*)other.GetComponent("Player");
	auto alien = (Alien*)other.GetComponent("Alien");
	auto minion = (Minion*)other.GetComponent("Minion");
	auto robot = (Robot*)other.GetComponent("Robot");
	auto tileMap = (TileMap*)other.GetComponent("TileMap");

	// Deleta o tiro apenas se colidir com o inimigo do atirador
	if (player && /*this->alienBullet*/ this->robotBullet)
		associated.RequestDelete();
	else if ( /*(alien /*|| minion)*/ robot && this->playerBullet)
		associated.RequestDelete();
	else if(tileMap && tileMap->colide)
		associated.RequestDelete();
}
