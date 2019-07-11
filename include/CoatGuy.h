#pragma once

#ifndef COATGUY_H
#define COATGUY_H

#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Collider.h"
#include "Laser.h"
#include "TileMap.h"
#include "Camera.h"
//#include "PenguinCannon.h"
#include "InputManager.h"


#define COATGUY_MAX_LINEAR_SPEED 500		// em pixels/s
#define COATGUY_ACCELERATION 1000			// em pixels/s²
#define COATGUY_ATRICT 150					// em pixels/s²
#define COATGUY_ANGULAR_SPEED PI			// em rads/s
#define COATGUY_INITIAL_HP 4				// em hit points
#define ONETILESQUARE 64					// tamanho de 1 tile
#define COATGUY_LASER_DAMAGE 2				// em hit points
#define LASER_SPEED 1000					// em pixels/s
#define LASER_MAX_DAMAGE 20					// em hit points
#define LASER_MAX_DISTANCE 1000				// em pixels
#define MAX_SPEED 400
#define SPEED_STEP 50
#define COATGUY_SPEED 400
#define COATGUY_JUMP 600


class CoatGuy : public Component {
public:
	CoatGuy(GameObject& associated);
	~CoatGuy();
	void Start() override;
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void NotifyCollision(GameObject& other) override;
	Vec2 GetCenter();			// Funcao para poder pegar a posicao do coatGuy
	void Shoot(Vec2 target);
	int GetHP();

	static CoatGuy* coatGuy;
	Sprite* sprite;
	bool damaged = false, isAtacking = false, ultrapassou = false, gotHit = false;;
	Sound* coatGuySFX;

private:
	//std::weak_ptr<GameObject> pcannon;
	Timer WallJumpTimer, DeathTimer, DJTimer, ATKTimer;
	Timer ShootCooldownTimer, DashCooldownTimer, FinishHimTimer, LoopTimer;
	Vec2 speedH, speedV, speedD;
	float linearSpeed = 0, verticalSpeed = 0, diagonalSpeed = 0, angle, gravity = 1.0, oppositeAccel, oppositeSpeed;
	bool Getspeed1 = false, Getspeed2 = false, Setrun = false, Setidle = true, WallgrabL = false, WallgrabR = false,
		tchfloor, airbone, doubleJump = false, tchCeiling = false, facingR = true, facingL = false, WallJump = false,
		SetJump = false, runningSound = false, wallSlideSound = false, deathSound = false, dead = false, notDJ = false, pouso = false, foguete = false,
		spriteAlreadyIdleR = false, spriteAlreadyIdleL = false, spriteAlreadyRunR = false, spriteAlreadyRunL = false,
		spriteAlreadyJumpR = false, spriteAlreadyJumpL = false, spriteAlreadyDJL = false, spriteAlreadyDJR = false,
		jumped = false, gforce = false, FinishHimEneable = false, StartLoop = false, kill = false, Atk0 = false;
	int hp, Stop = 0, Run = 0, Jump = 0, Fall = 0, wallAUX = 0, wallX = 0, Ground = 0, DJ = 0, BuzzL = 0;
	int contadorW1 = 0, contadorW2 = 0, loopaux = 0, falsehp = 1, Atk1 = 0;

};

#endif	//COATGUY_H
