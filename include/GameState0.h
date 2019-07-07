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
	void LoadLevel();

	Sprite* HPbarSprite;
	TileSet* tileSet;
	Music backgroundMusic;
	GameObject* HPbarGO;
	GameObject* surpriseGO;
	GameObject* playerGO;
	GameObject* chaoGO;
	Player* player;

	bool dois = false, tres = false, quatro = false, cinco = false, meia = false, sete = false, oito = false, mostrando = false;
	bool cima1 = false, cima2 = false, baixo1 = false, baixo2 = false, esquerda1 = false, esquerda2 = false, direita1 = false, direita2 = false;
	
};

#endif	//GAMESTATE0_H
