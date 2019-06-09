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

#define PLAYER_MAX_LINEAR_SPEED 500	// em pixels/s
#define PLAYER_ACCELERATION 1000		// em pixels/s²
#define PLAYER_ATRICT 150				// em pixels/s²
#define PLAYER_ANGULAR_SPEED PI		// em rads/s
#define PLAYER_INITIAL_HP 100			// em hit points

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
	//Vec2 GetFloor();			// Função para achar a distância do personagem pro chao

	static Player* player;
	//float secondsToSelfDestruction = 1.5;
	Sprite* sprite;

private:

	//std::weak_ptr<GameObject> pcannon;
	Vec2 speedH, speedV;
	float linearSpeed, verticalSpeed = 0, angle, gravity = 1.0, oppositeAccel, oppositeSpeed;
	bool Getspeed1 = false, Getspeed2 = false, Setrun = false, Setidle = true, Setjump = false,
		Wallgrab = false,/*Floorgrab = false, Quedalivre = true,*/ tchfloor = false, airbone = true, doubleJump = false;
	int hp, Stop = 0, Run = 0, Jump = 0, Fall = 1, chao = 0;

};

#endif	//PLAYER_H