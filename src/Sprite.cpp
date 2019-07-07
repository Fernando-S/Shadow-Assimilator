#include "Game.h"
#include "Sprite.h"


Sprite::Sprite(GameObject &associated) : Component(associated) {
	texture = nullptr;
	width = 0;
	height = 0;
	scale = {1, 1};
	frameCount = 1;
	currentFrame = 0;
	timeElapsed = 0;

}

Sprite::Sprite(GameObject &associated, const char* file, int frameCount, float frameTime,
			   float secondsToSelfDestruct) : Component(associated) {
	Sprite(this->associated);
	texture = nullptr;
	width = 0;
	height = 0;
	scale = {1, 1};
	timeElapsed = 0;
	this->secondsToSelfDestruct = secondsToSelfDestruct;

	Open(file);	
	SetFrameCount(frameCount);
	SetFrameTime(frameTime);
	
}

Sprite::~Sprite() {
}

void Sprite::Open(const char* file) {
	if (texture)
		//SDL_DestroyTexture(texture);
		SDL_DestroyTexture(texture.get());

	texture = Resources::GetImage(file);

	if (!texture) {
		std::cerr << " IMG_LoadTexture  returned ERROR: " << SDL_GetError() << std::endl;
		exit(1);
	}

	//SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
	SetClip(0, 0, width, height);									// seta o clip para textura inteira

	// Passa as dimensoes
	this->associated.box.w = (float)width;
	this->associated.box.h = (float)height;
}

void Sprite::SetClip(int x, int y, int w, int h) {
	clipRect = {x, y, w, h};
}

void Sprite::Render() {
	//if (background)					// renderiza na posicao da camera se for background
		//Render((int)this->associated.box.x, (int)this->associated.box.y);
		//Render((int)(Game::GetInstance().GetWidth() - width) / 2, (int)(Game::GetInstance().GetHeight() - height) / 4);
	//	Render((int)Game::GetInstance().GetWidth()/3 - 30, (int)(Game::GetInstance().GetHeight()/* + height*/) / 12);
	//else							// renderiza na posicao no mundo se nao for
		Render((int)(this->associated.box.x - Camera::pos.x), (int)(this->associated.box.y - Camera::pos.y));
}

void Sprite::Update(float dt) {
	if (secondsToSelfDestruct > 0) {
		selfDestructCount.Update(dt);

		if (selfDestructCount.Get() > secondsToSelfDestruct)
			associated.RequestDelete();
		else if (frameCount > 1) { // esse processo so faz sentido para sprites com mais de um frame (nao estaticas)
			timeElapsed += dt;

			if (timeElapsed > frameTime) {
				timeElapsed -= frameTime;
				currentFrame++;
				SetFrame(currentFrame);
			}
		}
	}
	else if (frameCount > 1) { // esse processo so faz sentido para sprites com mais de um frame (nao estaticas)
		timeElapsed += dt;

		if (timeElapsed > frameTime) {
			timeElapsed -= frameTime;
			currentFrame++;
			SetFrame(currentFrame);
		}
	}
}

bool Sprite::Is(std::string type) {
	if (type == "Sprite")
		return true;
	else
		return false;
}

int Sprite::GetWidth() {
	return (int)(clipRect.w*scale.x);
}

int Sprite::GetHeight() {
	return  (int)(clipRect.h*scale.y);
}

bool Sprite::IsOpen() {
	if (texture != nullptr)
		return true;
	else
		return false;
}

void Sprite::Render(int x, int y) {

	SDL_Rect dstRect{x, y, (int)clipRect.w*scale.x, (int)clipRect.h*scale.y};

//	if (SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture, &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE) != 0) {
	if (SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(), &clipRect, &dstRect, associated.angleDeg, nullptr, SDL_FLIP_NONE) != 0) {
		std::cerr << "SDL_RenderCopy returned ERROR: " << SDL_GetError() << std::endl;
		exit(1);
	}	  
}

void Sprite::SetScale(float scaleX, float scaleY) {
	// Escala em X
	if (scaleX)
		scale.x = scaleX;
	else
		scale.x = scale.x;
	
	// Escala em Y
	if (scaleY)
		scale.y = scaleY;
	else
		scale.y = scale.y;

	auto lastCenter = associated.box.Center();

	associated.box.w = GetWidth();
	associated.box.h = GetHeight();

	associated.box += (lastCenter - associated.box.Center());
}

Vec2 Sprite::GetScale() {
	return scale;
}


void Sprite::SetFrame(int frame) {
	currentFrame = frame;			// Seta o frame atual

	// Checa se o frame atual eh menor que a contagem de frames do spritesheet
	if (currentFrame < frameCount) 
		SetClip(currentFrame *clipRect.w, 0, clipRect.w, clipRect.h);
	else {
		currentFrame = 0;
		SetClip(0, 0, clipRect.w, clipRect.h);
	}

}

void Sprite::SetFrameCount(int frameCount) {
	this->frameCount = frameCount;			// Seta o frameCount
	clipRect.w /= frameCount;				// Divide o tamanho do clip para um Sprite do Spritesheet
	associated.box.w = GetWidth();			// A box recebe a largura do novo frame
	associated.box.PlaceCenter(associated.box.Center());	// Alinha o centro da box om o centro do novo frame
	SetFrame(0);							// Reseta o frame inicial
}

void Sprite::SetFrameTime(float frameTime) {
	this->frameTime = frameTime;		// Seta o frameTime
}
