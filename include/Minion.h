#pragma once

#ifndef MINION_H
#define MINION_H

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Bullet.h"

#define ANGULAR_SPEED (PI/2)				// em rad/s
#define RADIUS 150							// em pixels
#define BULLET_SPEED 1000					// em pixels/s
#define BULLET_MAX_DAMAGE 20				// em hit points
#define BULLET_MAX_DISTANCE 1000			// em pixels

class Minion : public Component{
public:
	Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter/*, Alien* bigAlien*/, float arcOffsetDeg = 0);
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void Shoot(Vec2 target);
	void NotifyCollision(GameObject& other) override;
		
private:
//	GameObject& alienCenter;
	std::weak_ptr<GameObject> alienCenter;	// mudei para poder usar weak_ptr
	float arc;

};

#endif	//MINION_H