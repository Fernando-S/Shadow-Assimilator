#include "Music.h"
#include <string>
#include <iostream>

using std::cerr;

Music::Music() {
	music = nullptr;
}

Music::Music(const char* file) {
	music = nullptr;
	Open(file);
}

Music::~Music() {
	if (music) {
		Stop(200);									//200 ms
//		Mix_FreeMusic(music);
//		Mix_FreeMusic(music.get());
	}
}

void Music::Play(int times) {
	if (music) {
//		Mix_PlayMusic(music , times);				// se times for -1, a musica repete infinitamente. Se for 0, a musica nao toca
		Mix_PlayMusic(music.get(), times);				// se times for -1, a musica repete infinitamente. Se for 0, a musica nao toca
	}
	else {
		std::cerr << " ERROR: music is null" << std::endl;
		exit(1);
	}
}

void Music::Stop(int msToStop) {
	Mix_FadeOutMusic(msToStop);						// tenpo em ms
}

void Music::Open(const char* file) {
	music = Resources::GetMusic(file);

	if (!music) {
		std::cerr << " ERROR: impossible to load music" << std::endl;
		exit(1);
	}
}

bool Music::IsOpen() {
	return music != nullptr;
}
