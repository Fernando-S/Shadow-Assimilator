#pragma once

#ifndef GAMESTATE1_H
#define GAMESTATE1_H

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
#include "GameState2.h"
#include "EndState.h"
#include "FinalBoss.h"

#define PI 3.14159265
#define ALIEN_NUMBER 3
#define FINALBOSS_INITIAL_HP 2

class GameState1 : public State{
public:	
	GameState1();
	~GameState1() override;
	void LoadAssets() override;
	void Update(float dt) override;
	void Render() override;
	void Start() override;
	void Pause() override;
	void Resume() override;
	

private:
	void ChangePlayerHP(), ChangeCoatGuyHP();
	void LoadLevel();

	Sprite* HPbarSprite, *DetalheSprite;
	Sprite *HPbarCoatGuySprite;
	TileSet* tileSet;
	Music backgroundMusic;
	GameObject* HPbarGO;
	GameObject* HPbarCoatGuyGO;
	GameObject* surpriseGO;
	GameObject* playerGO;
	GameObject* coatGuyGO;
	GameObject* chaoGO;
	Player* player;
	CoatGuy* coatGuy;

	Timer playerHitTimer, coatGuyHitTimer;

	bool dois = false, tres = false, quatro = false, cinco = false, meia = false, sete = false, oito = false, mostrando = false;
	bool cima1 = false, cima2 = false, baixo1 = false, baixo2 = false, esquerda1 = false, esquerda2 = false, direita1 = false, direita2 = false;
	
	Sprite  *CuraSprite, *AtkDistSprite, *AtkFortSprite;
	GameObject* CuraGO;
	GameObject* AtkDistGO;
	GameObject* AtkFortGO;
	bool SetCura = false, SetAtkForte = false, SetAtkDist = false;

};

#endif	//GAMESTATE1_H
