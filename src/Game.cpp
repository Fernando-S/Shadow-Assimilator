#include "Game.h"


Game* Game::instance = nullptr;

Game::~Game() {
	if (storedState)
		delete storedState;				// Deleta o State guardado caso exista

	while (!stateStack.empty()) {
		stateStack.pop();				// pop no state da pilha
	}

	/* Fecha tudo */
	TTF_Quit();
	Mix_Quit();
	Mix_CloseAudio();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::Run() {
	if (!storedState)
		std::cout << "There was not a state set. Nothing to show..." << std::endl;
	else {
		stateStack.emplace(storedState);
		storedState->Start();
		storedState = nullptr;
		State *currentState = &GetCurrentState();

		while (!currentState->QuitRequested() && !stateStack.empty()) {
			
			// Checa se o estado atual quer ser deletado
			if (currentState->PopRequested()) {
				stateStack.pop();				// Dsemepilha o estado atual

				// Limpa os Resources desse estado que foi desempilhado
				Resources::ClearImages();
				Resources::ClearMusics();
				Resources::ClearSounds();
				Resources::ClearFonts();

				// Checa se a pilha de estados ficou vazia depois de desempilhar o antigo estado atual
				if (!stateStack.empty()) {
					currentState = &GetCurrentState();		// Pega o estado do topo da pilha e torna esse o estado atual
					currentState->Resume();					// Resume o novo estado atual no topo da pilha
				}
				else   
					break;				// Se a pilha de estados ficou vazia, sai do laco 
			}

			// Checa se ha algum estado guardado
			if (storedState) {
				currentState->Pause();						// Pausa o estado atual se houver

				stateStack.emplace(storedState);			// Empilha o estado guardado
				storedState->Start();						// Da Start() nesse estado
				storedState = nullptr;						// Esvazia o ponteiro para estados guardados
				currentState = &GetCurrentState();			// Estado que estava guardado e foi empilhado se torna o atual
			}


			// Roda (Renderiza e faz os updates) do jogo normalmente
			SDL_RenderClear(renderer);						// Renderiza a cor de fundo antes de renderizar os outros assets	
			CalculateDeltaTime();							// Atualiza o calculo de tempo
			InputManager::GetInstance().Update();			// Mantem atualizacao dos inputs
			currentState->Update(dt);						// Atualiza o estado
			currentState->Render();							// Renderiza o estado
			SDL_RenderPresent(renderer);
			SDL_Delay(33);									// tempo em ms para algo proximo de 30 fps
		}
	}

}

SDL_Renderer* Game::GetRenderer() {
	return renderer;
}

Game& Game::GetInstance() {	
	if (instance != nullptr)
		return *instance;		// retorna a instancia se ja existir uma
	else {
		instance = new Game("Shadow Assimilator", 1280, 640);		// instancia um novo jogo
		return *instance;		// retorna a nova instancia instancia
	}
}

Game::Game(const char* title, int width, int height) {
	frameStart = 0;
	dt = 0.0;

	// Checa se ja existe uma instancia	
	if (instance != nullptr) {
		std::cerr << "ERROR: Can't instantiate the game. Game already running" << std::endl;
		exit(1);
	}

	instance = this;
	this->width = width;
	this->height = height;

	// Inicializando as bibliotecas 
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
		std::cerr << "SDL_Init ERROR: " << SDL_GetError() << std::endl;
		exit(1);
	}

	if (!Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3)) {
		std::cerr << "ERROR: SDL_Mixer couldn't be initialized" << std::endl;
		exit(1);						// Erro de versao. Monitor Francisco sugeriu para comentar
	}

	if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)) {
		std::cerr << "ERROR: SDL_Image couldn't be initialized" << std::endl;
		exit(1);
	}
	
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)) {		// MIX_DEFAULT_ para todos e 1024 no hcunksize
		std::cerr << "ERROR: Mix_OpenAudio returned ERROR " << Mix_GetError() << std::endl;
		exit(1);
	}

	if (Mix_AllocateChannels(32) != 32) {				// 32 canais de audio
		std::cerr << "ERROR: impossible to allocate 32 audios channels" << std::endl;
		exit(1);
	}

	if (TTF_Init() == -1) {
		std::cerr << "TTF couldn't be initialized! ERROR: " << TTF_GetError() << std::endl;
		exit(1);
	}
	
	// Cria uma nova janela
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);		// title, pos x, pos y, width, height, fullscreen
	if (!window) {
		std::cerr << "ERROR: impossible to create window" << std::endl;
		exit(1);
	}

	// Cria um novo renderer e seta uma cor de fundo
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);		// -1 = SLD escolhe o melhor renderizador e ACCELERATED requisita OpenGL ou Direct 3D
	if (!renderer) {
		std::cerr << "ERROR: impossible to create render" << std::endl;
		exit(1);
	}
	SDL_SetRenderDrawColor(renderer, 25, 0, 51, 0);		// Seta a cor de fundo Red, Green, Blue, Alpha


	storedState = nullptr;
}

float Game::GetDeltaTime() {
	return dt;
}

void Game::CalculateDeltaTime() {
	int temp = SDL_GetTicks();

	dt = (temp - frameStart) / (float)1000;
	frameStart = temp;
}

int Game::GetWidth() {
	return width;
}

int Game::GetHeight() {
	return height;
}

State& Game::GetCurrentState() {
	State& topo = *((std::unique_ptr<State>&)stateStack.top());
	return topo;		// Retorna o topo da pilha de States
}

void Game::Push(State *state) {
	storedState = state;	// Retorna o ponteiro para o estado a ser empilhado
}
