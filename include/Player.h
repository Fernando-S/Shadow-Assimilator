#pragma once

#ifndef PLAYER_H
#define PLAYER_H

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
#include "InputManager.h"


#define PLAYER_ACCELERATION 1000		// em pixels/s�
#define PLAYER_ATRICT 150				// em pixels/s�
#define PLAYER_INITIAL_HP 22			// em hit points
#define ONETILESQUARE 64				// tamanho de 1 tile
#define PLAYER_LASER_DAMAGE 2			// em hit points
#define LASER_SPEED 1000				// em pixels/s
#define LASER_MAX_DISTANCE 1000			// em pixels


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
	Sprite* sprite;
	bool damaged = false, isAtacking = false, gotHit = false;
	Sound* playerSFX;

private:
	Timer WallJumpTimer, DeathTimer, DJTimer, HPRegenTimer;
	Timer ShootCooldownTimer, DashCooldownTimer, ATK1CooldownTimer;
	Vec2 speedH, speedV;
	float linearSpeed = 0, verticalSpeed = 0, oppositeSpeed, hp, froze = 0;
	bool Getspeed1 = false, Getspeed2 = false, Setrun = false, WallgrabL = false, WallgrabR = false,
		tchfloor, airbone, doubleJump = false, tchCeiling = false, facingR = true, facingL = false,
		SetJump = false, runningSound = false, wallSlideSound = false, deathSound = false, dead = false,
		foguete = false, Atk0 = false, Neon = false, atakL = false, atakR = false;
	int Stop = 0, Run = 0, Jump = 0, Fall = 0, wallAUX = 0, wallX = 0, Ground = 0, DJ = 0, BuzzL = 0, Atk1 = 0, Atk2 = 0,
		contadorW1 = 0, contadorW2 = 0, Atk2delay = 0, shootaux = 0, regen = 0;

};

#endif	//PLAYER_H