#pragma once

#ifndef SPRITE_H
#define SPRITE_H


//#define INCLUDE_SDL_IMAGE
//#include "SDL_include.h"
#include <iostream>
#include "SDL_image.h"							// Comentar e usar SDL_include.h para enviar
#include "Component.h"
#include "GameObject.h"
#include "Resources.h"
#include "Timer.h"


class Sprite: public Component {
public:
	Sprite(GameObject& associated);
	Sprite(GameObject& associated, const char* file, int frameCount = 1, float frameTime = 1,
		   float secondsToSelfDestruct = 0);		// mudei para const char*
	~Sprite() override;
	void Open(const char* file);
	void SetClip(int x, int y, int w, int h);
	void Render() override;
	void Update(float dt) override;
	bool Is(std::string type) override;
	int GetWidth();
	int GetHeight();
	bool IsOpen();
	void Render(int x, int y);
	void SetScale(float scaleX, float scaleY);
	Vec2 GetScale();
	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);
	
	bool background = false;

private:
//	SDL_Texture* texture;
	std::shared_ptr<SDL_Texture> texture;
	int width, height, frameCount, currentFrame;
	SDL_Rect clipRect;
	Vec2 scale;
	float timeElapsed, frameTime;
	Timer selfDestructCount;
	float secondsToSelfDestruct;

};

#endif	//SPRITE_H
