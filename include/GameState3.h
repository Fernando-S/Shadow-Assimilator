#pragma once

#ifndef GAMESTATE3_H
#define GAMESTATE3_H

#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "TileSet.h"
#include "TileMap.h"
#include "CameraFollower.h"
#include "Camera.h"
#include "Player.h"
#include "Robot.h"
#include "CoatGuy.h"
#include "Collision.h"
#include "State.h"
#include "EndState.h"
#include "FinalBoss.h"

#define PI 3.14159265
#define ALIEN_NUMBER 3

class GameState3 : public State{
public:	
	GameState3();
	~GameState3() override;
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
	GameObject* coatGuyGO;
	GameObject* chaoGO;
	Player* player;
	GameObject* finalBossGo;

	bool dois = false, tres = false, quatro = false, cinco = false, meia = false, sete = false, oito = false, mostrando = false;
	bool cima1 = false, cima2 = false, baixo1 = false, baixo2 = false, esquerda1 = false, esquerda2 = false, direita1 = false, direita2 = false;
	
};

#endif	//GAMESTATE3_H
