
#pragma once

#ifndef ROBOT_H
#define ROBOT_H

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


#define ROBOT_MAX_LINEAR_SPEED 500		// em pixels/s
#define ROBOT_ACCELERATION 1000		// em pixels/s²
#define ROBOT_ATRICT 150				// em pixels/s²
#define ROBOT_ANGULAR_SPEED PI			// em rads/s
#define ROBOT_INITIAL_HP 4			// em hit points
#define ONETILESQUARE 64				// tamanho de 1 tile
#define ROBOT_LASER_DAMAGE 0			// em hit points
#define MAX_SPEED 400
#define SPEED_STEP 50
#define ROBOT_SPEED 100
#define ROBOT_JUMP 600

/*
class Robot : public Component {
public:
	Robot(GameObject& associated);
	~Robot();
	void Start() override;
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void NotifyCollision(GameObject& other) override;
	Vec2 GetCenter();			// Funcao para poder pegar a posicao do robot
	void Shoot(Vec2 target);
	int GetHP();

	static Robot* robot;
	Sprite* sprite;
	bool damaged = false, isAtacking = false, ultrapassou = false;
	Sound *runSFX, *jumpSFX, *DjumpSFX, *landSFX, *LightAttackSFX, *HeavyAttackSFX, *robotSFX;

private:
	//std::weak_ptr<GameObject> pcannon;
	Timer WallJumpTimer, DeathTimer;
	Timer ShootCooldownTimer, DashCooldownTimer;
	Vec2 speedH, speedV, speedD;
	float linearSpeed = 0, verticalSpeed = 0, diagonalSpeed = 0, angle, gravity = 1.0, oppositeAccel, oppositeSpeed;
	bool Getspeed1 = false, Getspeed2 = false, Setrun = false, Setidle = true, WallgrabL = false, WallgrabR = false,
		 tchfloor, airbone, doubleJump = false, tchCeiling = false, facingR = true, facingL = false, WallJump = false,
		 SetJump = false, runningSound = false, wallSlideSound = false, dead = false;
	int hp, Stop = 0, Run = 0, Jump = 0, Fall = 0, wallAUX = 0, wallX = 0, Ground = 0, DJ = 0, BuzzL = 0;
	int contadorW1 = 0, contadorW2 = 0;

};
*/














class Robot : public Component {
public:
	Robot(GameObject& associated);
	~Robot();
	void Start() override;
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void NotifyCollision(GameObject& other) override;
	Vec2 GetCenter();			// Funcao para poder pegar a posicao do robot
	void Shoot(Vec2 target);
	int GetHP();

	static Robot* robot;
	//float secondsToSelfDestruction = 1.5;
	Sprite* sprite;
	bool damaged = false, isAtacking = false, ultrapassou = false;
	Sound* robotSFX;

private:
	//std::weak_ptr<GameObject> pcannon;
	Timer WallJumpTimer, DeathTimer, DJTimer;
	Timer ShootCooldownTimer, DashCooldownTimer;
	Timer changeSideTimer, recoilTimer;
	Vec2 speedH, speedV, speedD;
	float linearSpeed = 0, verticalSpeed = 0, diagonalSpeed = 0, angle, gravity = 1.0, oppositeAccel, oppositeSpeed, initialX, initialY;

	bool Getspeed1 = false, Getspeed2 = false, Setrun = false, Setidle = true, WallgrabL = false, WallgrabR = false,
		tchfloor, airbone, doubleJump = false, tchCeiling = false, facingR = true, facingL = false, WallJump = false,
		SetJump = false, runningSound = false, wallSlideSound = false, deathSound = false, dead = false, notDJ = false, pouso = false, foguete = false,
		jumped = false, gforce = false, moveDireita = false, moveEsquerda = false, idle = false, shooting = false, alreadyShot = false, patrol = false,
		deadSpriteSet = false;

	int hp, Stop = 0, Run = 0, Jump = 0, Fall = 0, wallAUX = 0, wallX = 0, Ground = 0, DJ = 0, BuzzL = 0;
	int contadorW1 = 0, contadorW2 = 0;

};


















#endif	//ROBOT_H