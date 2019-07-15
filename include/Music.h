#pragma once

#ifndef MUSIC_H
#define MUSIC_H

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
//#include "SDL_mixer.h"							// Comentar e usar SDL_include.h para enviar
#include "Resources.h"
#include <string>

class Music {
public:
	Music();
	Music(const char* file);
	void Play(int times = -1);
	void Stop(int msToStop = 1500);
	void Open(const char* file);
	bool IsOpen();
	~Music();

private:
//	Mix_Music* music;
	std::shared_ptr<Mix_Music> music;

};

#endif	//MUSIC_H