#pragma once

#ifndef GAMESTATE2_H
#define GAMESTATE2_H

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
#include "GameState3.h"
#include "EndState.h"
#include "FinalBoss.h"
#include "Escudo.h"
#include "CanhaoVermelho.h"
#include "CanhaoAmarelo.h"

#define PI 3.14159265
#define ALIEN_NUMBER 3

class GameState2 : public State {
public:
	GameState2();
	~GameState2() override;
	void LoadAssets() override;
	void Update(float dt) override;
	void Render() override;
	void Start() override;
	void Pause() override;
	void Resume() override;


private:
	void ChangePlayerHP();
	void LoadLevel();

	Sprite* HPbarSprite, *BackGroundSprite;
	TileSet* tileSet;
	Music backgroundMusic;
	GameObject* HPbarGO;
	GameObject* surpriseGO;
	GameObject* playerGO;
	GameObject* coatGuyGO;
	GameObject* finalBossGO;
	GameObject* escudoGO;
	GameObject* canhaoVermelho1GO;
	GameObject* canhaoVermelho2GO;
	GameObject* canhaoVermelho3GO;
	GameObject* canhaoAmareloGO;
	GameObject* chaoGO;
	Player* player;
	CoatGuy* coatGuy;
	FinalBoss* finalBoss;
	Escudo* escudo;
	CanhaoVermelho* canhaoVermelho1;
	CanhaoVermelho* canhaoVermelho2;
	CanhaoVermelho* canhaoVermelho3;
	CanhaoAmarelo* canhaoAmarelo;

	bool dois = false, tres = false, quatro = false, cinco = false, meia = false, sete = false, oito = false, mostrando = false;
	bool cima1 = false, cima2 = false, baixo1 = false, baixo2 = false, esquerda1 = false, esquerda2 = false, direita1 = false, direita2 = false;

	Sprite  *CuraSprite, *AtkDistSprite, *AtkFortSprite;
	GameObject* CuraGO;
	GameObject* AtkDistGO;
	GameObject* AtkFortGO;
	bool SetCura = false, SetAtkForte = false, SetAtkDist = false;

};

#endif	//GAMESTATE2_H