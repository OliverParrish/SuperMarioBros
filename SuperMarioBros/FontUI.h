#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Commons.h"
#include <string>

class FontUI
{
public:
	FontUI(SDL_Renderer* renderer, const char* text, SDL_Color color);
	~FontUI();

	void Draw();

	void SetPosition(Vector2D* newPos);
	void SetText(const char* text);

	void UpdateSurface();
	void UpdateTexture();



private:

	SDL_Rect mRect;
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
	SDL_Surface* mSurface;
	SDL_Color mColor;
	TTF_Font* mFont;
	const char* mText;
	Vector2D* mPositon;
};

