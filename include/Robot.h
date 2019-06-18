#pragma once

#ifndef ROBOT_H
#define ROBOT_H

#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Collider.h"
#include "PenguinCannon.h"
#include "InputManager.h"
#include "Bullet.h"

#define ROBOT_MAX_LINEAR_SPEED 500	// em pixels/s
#define ROBOT_ACCELERATION 1000		// em pixels/s�
#define ROBOT_ATRICT 150			// em pixels/s�
#define ROBOT_ANGULAR_SPEED PI		// em rads/s
#define ROBOT_INITIAL_HP 100		// em hit points
#define ROBOT_TIME 0.5				// tempo em segundos

class Robot : public Component {
public:
	Robot(GameObject& associated);
	~Robot();
	void Start() override;
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void NotifyCollision(GameObject& other) override;
	Vec2 GetCenter();
	void Shoot(Vec2 target);

	static Robot* robot;
	//float secondsToSelfDestruction = 1.5;
	Sprite* sprite;

private:

	//std::weak_ptr<GameObject> pcannon;
	//Timer mudaDeLado;
	Timer cooldownTimer;
	Vec2 speedH, speedV;
	float linearSpeed, verticalSpeed = 0, angle, gravity = 1.0, oppositeAccel, oppositeSpeed, initialX, initialY;
	bool Getspeed1 = false, Getspeed2 = false, Setrun = false, Setidle = true, Setjump = false,
		Wallgrab = false,/*Floorgrab = false, Quedalivre = true,*/ tchfloor = false, airbone = true, doubleJump = false, encostouTeto = false;
	int hp, Stop = 0, Run = 0, Jump = 0, Fall = 1, chao = 0;

};

#endif	//ROBOT_H