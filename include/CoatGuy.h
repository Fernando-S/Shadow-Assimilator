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
#include "InputManager.h"


#define COATGUY_ACCELERATION 1000			// em pixels/s²
#define COATGUY_ATRICT 150					// em pixels/s²
#define COATGUY_INITIAL_HP 28				// em hit points
#define ONETILESQUARE 64					// tamanho de 1 tile
#define COATGUY_LASER_DAMAGE 2				// em hit points
#define LASER_SPEED 1000					// em pixels/s
#define LASER_MAX_DISTANCE 1000				// em pixels
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
	bool damaged = false, isAtacking = false, gotHit = false;;
	Sound* coatGuySFX;

private:
	Timer DeathTimer, ATKTimer;
	Timer FinishHimTimer, LoopTimer;
	Vec2 speedH, speedV;
	float linearSpeed = 0, verticalSpeed = 0, oppositeSpeed, initialX, initialY;
	bool Getspeed1 = false, Getspeed2 = false, Setrun = false, WallgrabL = false, WallgrabR = false, tchfloor, airbone,	tchCeiling = false,
		facingR = true, facingL = false, SetJump = false, runningSound = false,	wallSlideSound = false,	deathSound = false,	dead = false,
		foguete = false, FinishHimEneable = false, StartLoop = false, kill = false, Atk0 = false,	moveDireita = false, moveEsquerda = false;
	int hp, Stop = 0, Run = 0, Jump = 0, Fall = 0, Ground = 0, BuzzL = 0, contadorW1 = 0, contadorW2 = 0, falsehp = 1, Atk1 = 0;

};

#endif	//COATGUY_H
