#pragma once

#ifndef ALIEN_H
#define ALIEN_H

#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include "Minion.h"
#include "Camera.h"
#include "InputManager.h"
#include <vector>
#include <queue>


#define ALIEN_SPEED 300					// em pixels/s
#define ALIEN_ANGULAR_SPEED -20			// em angleDeg
#define ALIEN_MAX_HP 60					// em hit points (3 tiros necessarios para matar)
#define ALIEN_RESTING_TIME 3			// em segundos

class Alien : public Component{
public:
	Alien(GameObject& associated, int nMinions, float timeOffset = 0);
	~Alien();
	void Start() override;
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	void NotifyCollision(GameObject& other) override;

	static int alienCount;

private:
	int hp;
	Vec2 speed;
	std::vector<std::weak_ptr<GameObject>> minionArray;
	int Minions;
	enum AlienState {MOVING, RESTING};
	AlienState state;
	Timer restTimer;
	Vec2 destination;

};

#endif	//ALIEN_H