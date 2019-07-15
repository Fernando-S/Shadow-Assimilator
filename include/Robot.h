
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
#include "InputManager.h"
#include "GameData.h"


#define ROBOT_ACCELERATION 1000		// em pixels/s²
#define ROBOT_ATRICT 150				// em pixels/s²
#define ROBOT_INITIAL_HP 4			// em hit points
#define ONETILESQUARE 64				// tamanho de 1 tile
#define ROBOT_LASER_DAMAGE 2			// em hit points
#define ROBOT_SPEED 100

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
	bool damaged = false, isAtacking = false, gotHit = false;;
	Sound* robotSFX;

private:
	Timer DeathTimer;
	Timer ShootCooldownTimer;
	Timer changeSideTimer, recoilTimer;
	Vec2 speedH;
	float linearSpeed = 0, verticalSpeed = 0, oppositeSpeed, initialX, initialY;

	bool Getspeed1 = false, Getspeed2 = false, Setrun = false, WallgrabL = false, WallgrabR = false,
		tchfloor, airbone, tchCeiling = false, facingR = true, facingL = false,	runningSound = false,
		deathSound = false, dead = false, moveDireita = false, moveEsquerda = false, idle = false,
		shooting = false, alreadyShot = false, patrol = false, deadSpriteSet = false;

	int hp, Stop = 0, Run = 0, Jump = 0, Fall = 0, Ground = 0, BuzzL = 0, contadorW1 = 0, contadorW2 = 0;

};


















#endif	//ROBOT_H