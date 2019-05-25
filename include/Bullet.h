#pragma once

#ifndef BULLET_H
#define BULLET_H

#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Collider.h"
#include "PenguinBody.h"
#include "Alien.h"

class Bullet : public Component{
public:
	Bullet(GameObject& associated , float angle, float speed, int damage, float maxDistance,
		   const char* sprite, int frameCount, float frameTime);
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void NotifyCollision(GameObject& other) override;
	int GetDamage();

	bool targetsPlayer, playerBullet = false, alienBullet = false;
		
private:
	Vec2 speed;
	float distanceLeft;
	int damage;
	float speedMagnitude;

};

#endif	//BULLET_H