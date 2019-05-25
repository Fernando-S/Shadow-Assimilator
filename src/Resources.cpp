#include "Resources.h"
#include "Game.h"


std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;


std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file) {
	auto search = imageTable.find(file);

	if (search != imageTable.end())				// continua a procurar a imagem se ainda nao esta no final do vetor
		return search->second;
	else {										// tenta carregar a imagem se chegou ao final do vetor
		auto texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

		if (!texture) {
			std::cerr << " IMG_LoadTexture returned ERROR: " << SDL_GetError() << std::endl;
			exit(1);
		}

		std::shared_ptr<SDL_Texture> sharedTexture(texture, [](SDL_Texture *p) -> void {
			SDL_DestroyTexture(p);
		});

		imageTable[file] = sharedTexture;

		return sharedTexture;
	}
}

void Resources::ClearImages() {
	for (auto it = imageTable.begin(); it != imageTable.end();) {
		if ((it->second).unique())
			it = imageTable.erase(it);				// destroi cada imagem
		else
			it++;									// avanca no vetor
	}
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file) {
	auto search = musicTable.find(file);

	if (search != musicTable.end())				// continua a procurar a musica se ainda nao esta no final do vetor
		return search->second;
	else {										// tenta carregar a musica se chegou ao final do vetor
		auto music = Mix_LoadMUS(file.c_str());

		if (!music) {
			std::cerr << " Mix_LoadMUS returned ERROR: " << Mix_GetError() << std::endl;
			exit(1);
		}
		
		std::shared_ptr<Mix_Music> sharedMusic(music, [](Mix_Music *p) -> void {
			Mix_FreeMusic(p);
		});

		musicTable[file] = sharedMusic;

		return sharedMusic;
	}
}

void Resources::ClearMusics() {
	for (auto it = musicTable.begin(); it != musicTable.end();) {
		if ((it->second).unique())
			it = musicTable.erase(it);					// destroi cada musica				
		else
			it++;										// avanca no vetor
	}
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file) {
	auto search = soundTable.find(file);

	if (search != soundTable.end())				// continua a procurar a msuica se ainda nao esta no final do vetor
		return search->second;
	else {										// tenta carregar o som se chegou ao final do vetor
		auto sound = Mix_LoadWAV(file.c_str());

		if (!sound) {
			std::cerr << " IMG_LoadTexture returned ERROR: " << Mix_GetError() << std::endl;
			exit(1);
		}

		std::shared_ptr<Mix_Chunk> sharedSound(sound, [](Mix_Chunk *p) -> void {
			Mix_FreeChunk(p);
		});

		soundTable[file] = sharedSound;

		return sharedSound;
	}
}

void Resources::ClearSounds() {
	for (auto it = soundTable.begin(); it != soundTable.end();) {
		if ((it->second).unique())
			it = soundTable.erase(it);					// destroi cada som
		else 
			it++;										// avanca no vetor
	}
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int fontSize) {
	auto key = file + std::to_string(fontSize);

	auto search = fontTable.find(key);

	if (search != fontTable.end())				// continua a procurar a fonte se ainda nao esta no final do vetor
		return search->second;
	else {										// tenta carregar a musica se chegou ao final do vetor
		auto font = TTF_OpenFont(file.c_str(), fontSize);

		if (!font) {
			std::cerr << "TTF_OpenFont returned ERROR: " << TTF_GetError() << std::endl;
			exit(1);
		}

		std::shared_ptr<TTF_Font> sharedFont(font, [](TTF_Font *p) -> void {
			TTF_CloseFont(p);
		});

		fontTable[key] = sharedFont;

		return sharedFont;
	}
}

void Resources::ClearFonts() {
	for (auto it = fontTable.begin(); it != fontTable.end();) {
		if ((it->second).unique())
			it = fontTable.erase(it);					// destroi cada fonte
		else
			it++;										// avanca no vetor
	}
}
