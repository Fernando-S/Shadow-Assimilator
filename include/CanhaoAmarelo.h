#pragma once

#ifndef CANHAOAMARELO_H
#define CANHAOAMARELO_H

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

#define CANHAOAMARELO_INITIAL_HP 4

class CanhaoAmarelo : public Component {
public:
	CanhaoAmarelo(GameObject& associated);
	~CanhaoAmarelo();
	void Start() override;
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void NotifyCollision(GameObject& other) override;
	/*
	void LightShoot(Vec2 target);
	void HeavyShoot(Vec2 target);
	*/
	int GetHP();

	static CanhaoAmarelo* canhaoAmarelo;
	Sprite* sprite;
	Sound* CanhaoAmareloSFX;

private:

	int hp;
	bool damaged;
	Timer LightRecoilTimer, HeavyRecoilTimer;
};

#endif	//CANHAOAMARELO_H