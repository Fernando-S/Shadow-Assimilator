#pragma once

#ifndef SOUND_H
#define SOUND_H

//#define INCLUDE_SDL_MIXER
//#include "SDL_include.h"
#include "SDL_mixer.h"							// Comentar e usar SDL_include.h para enviar
#include "GameObject.h"
#include "Resources.h"
#include <iostream>

class Sound : public Component{
public:
	Sound(GameObject& associated);
	Sound(GameObject& associated, const char* file);
	~Sound() override;
	void Play(int times = 1);
	void Stop();
	void Open(const char* file);
	bool IsOpen();
	void Update(float dt) override;
	void Render() override;
	bool Is(std::string type) override;
	bool IsPlaying();

private:
	Mix_Chunk *chunk;
	//std::shared_ptr<Mix_Chunk> chunk;
	int channel;
};

#endif	//SOUND_H
