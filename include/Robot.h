#pragma once

#ifndef ROBOT_H
#define ROBOT_H

#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Sound.h"
#include "Music.h"
#include "Collider.h"
#include "PenguinCannon.h"
#include "InputManager.h"
#include "Bullet.h"

#define ROBOT_MAX_LINEAR_SPEED 500	// em pixels/s
#define ROBOT_ACCELERATION 1000		// em pixels/s²
#define ROBOT_ATRICT 150			// em pixels/s²
#define ROBOT_ANGULAR_SPEED PI		// em rads/s
#define ROBOT_INITIAL_HP 4		// em hit points
#define ROBOT_TIME 0.5				// tempo em segundos
#define MAX_SPEED 400
#define SPEED_STEP 50
#define ROBOT_SPEED 400
#define ROBOT_JUMP 600
#define BULLET_SPEED 1000			// em pixels/s
#define BULLET_MAX_DAMAGE 20		// em hit points
#define BULLET_MAX_DISTANCE 1000	// em pixels
#define ROBOT_BULLET_DAMAGE 11		// dano em hitpoints

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
	Sound* runningSound;
	//Music* runningSound;

private:

	//std::weak_ptr<GameObject> pcannon;
	//Timer mudaDeLado;
	Timer changeSideTimer;
	Timer cooldownTimer;
	Timer parado;
	Vec2 speedH, speedV;
	float linearSpeed, verticalSpeed = 0, angle, gravity = 1.0, oppositeAccel, oppositeSpeed, initialX, initialY;
	bool Getspeed1 = false, Getspeed2 = false, Setrun = false, Setidle = true, Setjump = false,
		Wallgrab = false, tchfloor, airbone, doubleJump = false, tchCeiling = false, idleR = false, idleL = false;
	int hp, Stop = 0, Run = 0, Jump = 0, Fall = 1, chao = 0;

};

#endif	//ROBOT_H