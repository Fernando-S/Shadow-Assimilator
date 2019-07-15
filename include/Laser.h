#pragma once

#ifndef LASER_H
#define LASER_H

#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Collider.h"
#include "Player.h"
#include "Robot.h"
#include "CoatGuy.h"
#include "TileMap.h"

class Laser : public Component{
public:
	Laser(GameObject& associated , float angle, float speed, int damage, float maxDistance,
		   const char* sprite, int frameCount, float frameTime);
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void NotifyCollision(GameObject& other) override;
	int GetDamage();

	bool playerLaser = false, coatGuyLaser = false, robotLaser = false;
		
private:
	Vec2 speed;
	float distanceLeft;
	int damage;
	float speedMagnitude;

};

#endif	//LASER_H