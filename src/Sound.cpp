#include "Sound.h"

Sound::Sound(GameObject& associated) : Component(associated) {
	chunk = nullptr;
}

Sound::Sound(GameObject& associated, const char* file) : Component(associated) {			// mudei para const char*		a
	Sound(this->associated);
	Open(file);
}

void Sound::Play(int times) {
	channel = Mix_PlayChannel(-1, chunk, times - 1);
	//channel = Mix_PlayChannel(-1, chunk.get(), times - 1);
	if (channel < 0) {
		std::cerr << " Impossible to play sound; ERROR: " << Mix_GetError() << std::endl;
		exit(1);
	}
}

void Sound::Stop() {
	if (chunk != nullptr)
		Mix_HaltChannel(channel);
}

void Sound::Open(const char* file) {					// mudei para const char*
	chunk = Mix_LoadWAV(file);
	//chunk = Resources::GetSound(file);

	if (!chunk) {
		std::cerr << " Couldn't open sound file; ERROR: " << Mix_GetError() << std::endl;
		exit(1);
	}
}

Sound::~Sound() {
	if (chunk != nullptr) {
		Mix_HaltChannel(channel);
		Mix_FreeChunk(chunk);
		//Mix_FreeChunk(chunk.get());
	}
}

bool Sound::IsOpen() {
	if (chunk != nullptr)
		return true;
	else
		return false;
}

void Sound::Update(float dt) {

}

void Sound::Render() {

}	

bool Sound::Is(std::string type) {
	if (type == "Sound")
		return true;
	else
		return false;
}

bool Sound::IsPlaying() {
	if (channel < 0)						 // sem canal para o som
		return false;
	else if (Mix_Playing(channel) != 0)
		return true;
	else
		return false;
}










