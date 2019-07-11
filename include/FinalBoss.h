#pragma once

#ifndef FINALBOSS_H
#define FINALBOSS_h

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

#define FINALBOSS_INITIAL_HP 4

class FinalBoss : public Component {
public:
	FinalBoss(GameObject& associated);
	~FinalBoss();
	void Start() override;
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void NotifyCollision(GameObject& other) override;
	void LightShoot(Vec2 target);
	void HeavyShoot(Vec2 target);
	int GetHP();

	static FinalBoss* finalBoss;
	Sprite* sprite;
	Sound* FinalBossSFX;

private:

	int hp;
	bool damaged;
	Timer LightRecoilTimer, HeavyRecoilTimer;
};

#endif	//FINALBOSS