#pragma once

#ifndef TITLESTATE_H
#define TITLESTATE_H

#include "State.h"
#include "CameraFollower.h"
#include "Sprite.h"
#include "InputManager.h"
#include "GameState0.h"
#include "CreditsState.h"
#include "Text.h"
#include "Camera.h"

class TitleState : public State{
public:
	TitleState();
	~TitleState();
	void LoadAssets() override;
	void Update(float dt) override;
	void Render() override;
	void Start() override;
	void Pause() override;
	void Resume() override;
	
private:
	GameObject* startButtonGO;
	GameObject* creditsButtonGO;
	GameObject* bgGO;
	Vec2 mousePos = { 0, 0 };
	Music backgroundMusic;
	Sound* hoverSound;
	Sound* clickSound;
	bool startHoverSound = false, creditsHoverSound = false;

};

#endif	//TITLESTATE_H
