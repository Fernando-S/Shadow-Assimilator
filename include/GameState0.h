#pragma once

#ifndef GAMESTATE0_H
#define GAMESTATE0_H

#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "TileSet.h"
#include "TileMap.h"
#include "CameraFollower.h"
#include "Camera.h"
#include "Alien.h"
#include "Player.h"
#include "Robot.h"
#include "Collision.h"
#include "State.h"
#include "EndState.h"

#define PI 3.14159265
#define ALIEN_NUMBER 3

class GameState0 : public State{
public:	
	GameState0();
	~GameState0() override;
	void LoadAssets() override;
	void Update(float dt) override;
	void Render() override;
	void Start() override;
	void Pause() override;
	void Resume() override;
	

private:
	void ChangePlayerHP();
	void LoadMap();
	void LoadLevel();

	Sprite* HPbarSprite;
	TileSet* tileSet;
	Music backgroundMusic;
	
	// todo - mexer melhor nisso para mudar de tela apenas apos o fim das animacoes de explosao
	Timer TimeToEndPlayerAnimation, TimeToEndAlienAnimation;
	float secondsToEndPlayerAnimation = 1.5, secondsToEndAlienAnimation = 1.2;
	
};

#endif	//GAMESTATE0_H
