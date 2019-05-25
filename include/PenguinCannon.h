#pragma once

#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H

#include "Component.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include "Collider.h"
#include "InputManager.h"
#include "Camera.h"
#include "Bullet.h"

#define PENGUIN_BULLET_SPEED 600				// em pixels/s
#define PENGUIN_BULLET_MAX_DAMAGE 30			// em hit points
#define PENGUIN_BULLET_MAX_DISTANCE 1000		// em pixels
#define PENGUIN_SHOOTING_COLLDOWN 1				// em segundos

class PenguinCannon : public Component{
public:
	PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody);
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void Shoot();
	void NotifyCollision(GameObject& other) override;
		
private:
	std::weak_ptr<GameObject> pbody;
	float angle;
	Timer cooldownTimer;

};

#endif	//PENGUINCANNON_H