#pragma once

#ifndef CREDITSSTATE_H
#define CREDITSSTATE_H

#include "State.h"
#include "CameraFollower.h"
#include "Sprite.h"
#include "InputManager.h"
#include "GameState0.h"
#include "TitleState.h"
#include "Text.h"
#include "Camera.h"

class CreditsState : public State{
public:
	CreditsState();
	~CreditsState();
	void LoadAssets() override;
	void Update(float dt) override;
	void Render() override;
	void Start() override;
	void Pause() override;
	void Resume() override;
	
};

#endif	//CREDITSSTATE_H
