#pragma once

#ifndef CANHAOVERMELHO_H
#define CANHAOVERMELHO_H

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

#define CANHAOVERMELHO_INITIAL_HP 4

class CanhaoVermelho : public Component {
public:
	CanhaoVermelho(GameObject& associated);
	~CanhaoVermelho();
	void Start() override;
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void NotifyCollision(GameObject& other) override;
	int GetHP();

	static CanhaoVermelho* canhaoVermelho;
	Sprite* sprite;
	Sound* CanhaoVermelhoSFX;

private:

	int hp;
	bool damaged;
	Timer LightRecoilTimer, HeavyRecoilTimer;
};

#endif	//CANHAOVERMELHO_H