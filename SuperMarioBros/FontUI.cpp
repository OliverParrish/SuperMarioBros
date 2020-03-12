#include "FontUI.h"


FontUI::FontUI(SDL_Renderer* renderer, const char* text, SDL_Color color)
{
	mRenderer = renderer;
	mFont = TTF_OpenFont("Font/SuperMario256.ttf", 24);
	mText = text;
	mColor = color;

	mSurface = TTF_RenderText_Solid(mFont, mText, mColor);

	mTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);
}

FontUI::~FontUI()
{
	delete mText;
	mText = nullptr;
	
	delete mFont;
	mFont = nullptr;

	delete mSurface;
	mSurface = nullptr;

	delete mTexture;
	mTexture = nullptr;

	delete mRenderer;
	mRenderer = nullptr;
}

void FontUI::Draw()
{
	mRect.x = mPositon->x;
	mRect.y = mPositon->y;

	mRect.w = 100;
	mRect.h = 25;

	SDL_RenderCopy(mRenderer, mTexture, NULL, &mRect);
}

void FontUI::SetPosition(Vector2D* newPos)
{
	mPositon = newPos;
}

void FontUI::SetText(const char* text)
{
	mText = text;
}

void FontUI::UpdateSurface()
{
	mSurface = TTF_RenderText_Solid(mFont, mText, mColor);
}

void FontUI::UpdateTexture()
{
	mTexture = SDL_CreateTextureFromSurface(mRenderer, mSurface);
}
