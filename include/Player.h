
#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Collider.h"
#include "PenguinCannon.h"
#include "InputManager.h"
#include "Music.h"
#include "Sound.h"


#define PLAYER_MAX_LINEAR_SPEED 500		// em pixels/s
#define PLAYER_ACCELERATION 1000		// em pixels/s²
#define PLAYER_ATRICT 150				// em pixels/s²
#define PLAYER_ANGULAR_SPEED PI			// em rads/s
#define PLAYER_INITIAL_HP 22			// em hit points
#define ONETILESQUARE 64				// tamanho de 1 tile
#define PLAYER_BULLET_DAMAGE 2			// em hit points

class Player : public Component {
public:
	Player(GameObject& associated);
	~Player();
	void Start() override;
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void NotifyCollision(GameObject& other) override;
	Vec2 GetCenter();			// Funcao para poder pegar a posicao do player
	void Shoot(Vec2 target);
	int GetHP();

	static Player* player;
	//float secondsToSelfDestruction = 1.5;
	Sprite* sprite;
	bool damaged = false, isAtacking = false, ultrapassou = false;
	Sound *runSFX, *jumpSFX, *DjumpSFX, *landSFX, *LightAttackSFX, *HeavyAttackSFX, *playerSFX;

private:
	//std::weak_ptr<GameObject> pcannon;
	Timer WallJumpTimer, DeathTimer, DJTimer;
	Timer ShootCooldownTimer, DashCooldownTimer;
	Vec2 speedH, speedV, speedD;
	float linearSpeed = 0, verticalSpeed = 0, diagonalSpeed = 0, angle, gravity = 1.0, oppositeAccel, oppositeSpeed;
	bool Getspeed1 = false, Getspeed2 = false, Setrun = false, Setidle = true, WallgrabL = false, WallgrabR = false,
		tchfloor, airbone, doubleJump = false, tchCeiling = false, facingR = true, facingL = false, WallJump = false,
		SetJump = false, runningSound = false, wallSlideSound = false, dead = false, notDJ = false;
	int hp, Stop = 0, Run = 0, Jump = 0, Fall = 0, wallAUX = 0, wallX = 0, Ground = 0, DJ = 0, BuzzL = 0;
	int contadorW1 = 0, contadorW2 = 0;

};
#endif	//PLAYER_H













/*
#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Collider.h"
#include "PenguinCannon.h"
#include "InputManager.h"
#include "Music.h"


#define PLAYER_MAX_LINEAR_SPEED 500		// em pixels/s
#define PLAYER_ACCELERATION 1000		// em pixels/s²
#define PLAYER_ATRICT 150				// em pixels/s²
#define PLAYER_ANGULAR_SPEED PI			// em rads/s
#define PLAYER_INITIAL_HP 22			// em hit points
#define ONETILESQUARE 64				// tamanho de 1 tile

class Player : public Component {
public:
	Player(GameObject& associated);
	~Player();
	void Start() override;
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void NotifyCollision(GameObject& other) override;
	Vec2 GetCenter();			// Funcao para poder pegar a posicao do player
	void Shoot(Vec2 target);
	int GetHP();

	static Player* player;
	//float secondsToSelfDestruction = 1.5;
	Sprite* sprite;
	bool damaged = false;

private:
	//std::weak_ptr<GameObject> pcannon;
	Timer WallJumpTimer;
	Timer ShootCooldownTimer;
	Vec2 speedH, speedV, speedD;
	float linearSpeed = 0, verticalSpeed = 0, diagonalSpeed = 0, angle, gravity = 1.0, oppositeAccel, oppositeSpeed;
	bool Getspeed1 = false, Getspeed2 = false, Setrun = false, Setidle = true, WallgrabL = false, WallgrabR = false,
		tchfloor, airbone, doubleJump = false, tchCeiling = false, facingR = true, facingL = false, WallJump = false,
		SetJump = false;
	int hp, Stop = 0, Run = 0, Jump = 0, Fall = 0, wallAUX = 0, wallX = 0, Ground = 0;

};

#endif	//PLAYER_H
*/