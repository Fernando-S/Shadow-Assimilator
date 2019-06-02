#pragma once

#ifndef PENGUINBODY_H
#define PENGUINBODY_H

#include "Component.h"
#include "Vec2.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Collider.h"
#include "PenguinCannon.h"
#include "InputManager.h"

#define PENGUIN_MAX_LINEAR_SPEED 500	// em pixels/s
#define PENGUIN_ACCELERATION 1000		// em pixels/s²
#define PENGUIN_ATRICT 150				// em pixels/s²
#define PENGUIN_ANGULAR_SPEED PI		// em rads/s
#define PENGUIN_INITIAL_HP 100			// em hit points

class PenguinBody : public Component{
public:
	PenguinBody(GameObject& associated);
	~PenguinBody();
	void Start() override;
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void NotifyCollision(GameObject& other) override;
	Vec2 GetCenter();			// Funcao para poder pegar a posicao do penguin

	static PenguinBody* player;
	//float secondsToSelfDestruction = 1.5;
	Sprite* sprite;

private:
	void SetSprite(const char* file, int frameCount, float frameTime);

	//std::weak_ptr<GameObject> pcannon;
	Vec2 speed;
	float linearSpeed, angle, gravity = 1.0;
	int hp;
	bool setaNovoSprite = false, moving = false;

};

#endif	//PENGUINBODY_H