#pragma once

#ifndef TEXT_H
#define TEXT_H

//#define INCLUDE_SDL
//#define INCLUDE_SDL_TTF
//#include "SDL_include.h"
#include "SDL_ttf.h"					// Comentar e usar SDL_include.h para enviar
#include "Component.h"
#include "Timer.h"
#include "Camera.h"
#include "Rect.h"

class Text : public Component{
public:
	enum TextStyle { SOLID, SHADED, BLENDED };
	Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
	~Text();
	void Update(float dt);
	void Render();
	bool Is(std::string type);
	void SetText(std::string text);
	void SetColor(SDL_Color color);
	void SetStyle(TextStyle style);
	void SetFontFile(std::string fontFile);
	void SetFontSize(int fontSize);
	SDL_Color GetSDLColor(Uint8 a, Uint8 r, Uint8 g, Uint8 b);

private:
	void RemakeTexture();

//	TTF_Font* font;
	std::shared_ptr<TTF_Font> font;
	SDL_Texture* texture;
	std::string text;
	TextStyle style;
	std::string fontFile;
	int fontSize;
	SDL_Color color;

	// todo - dar uma olhada melhor nisso depois
	Timer intermittenceCount;
	float intermittenceSeconds;

};

#endif	//TEXT_H
