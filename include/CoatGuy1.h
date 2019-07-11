#pragma once

#ifndef COATGUY_H
#define COATGUY_H

#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Sound.h"
#include "Music.h"
#include "Collider.h"
#include "InputManager.h"
#include "Laser.h"

#define COATGUY_MAX_LINEAR_SPEED 500	// em pixels/s
#define COATGUY_ACCELERATION 1000		// em pixels/s²
#define COATGUY_ATRICT 150			// em pixels/s²
#define COATGUY_ANGULAR_SPEED PI		// em rads/s
#define COATGUY_INITIAL_HP 4			// em hit points
#define COATGUY_TIME 0.5				// tempo em segundos
#define MAX_SPEED 400
#define SPEED_STEP 50
#define COATGUY_SPEED 400
#define COATGUY_JUMP 600
#define LASER_SPEED 1000			// em pixels/s
#define LASER_MAX_DAMAGE 20			// em hit points
#define LASER_MAX_DISTANCE 1000		// em pixels
#define COATGUY_LASER_DAMAGE 0		// dano em hitpoints
#define ONETILESQUARE 64			// tamanho de 1 tile

class CoatGuy : public Component {
public:
	CoatGuy(GameObject& associated);
	~CoatGuy();
	void Start() override;
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void NotifyCollision(GameObject& other) override;
	Vec2 GetCenter();
	void Shoot(Vec2 target);

	static CoatGuy* robot;
	Sprite* sprite;
	Sound* runningSound;

private:

	//std::weak_ptr<GameObject> pcannon;
	Timer changeSideTimer;
	Timer cooldownTimer;
	Timer parado;
	Vec2 speedH, speedV;
	float linearSpeed, verticalSpeed = 0, angle, gravity = 1.0, oppositeAccel, oppositeSpeed, initialX, initialY;
	bool Getspeed1 = false, Getspeed2 = false, Setrun = false, Setidle = true, Setjump = false, facingR = false, facingL = false,
		Wallgrab = false, tchfloor, airbone, doubleJump = false, tchCeiling = false, idleR = false, idleL = false,
		moveDireita = false, moveEsquerda = false;

	int hp, Stop = 0, Run = 0, Jump = 0, Fall = 1, chao = 0;

};

#endif	//COATGUY_H