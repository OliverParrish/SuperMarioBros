#pragma once

#ifndef _TEXTURE2D_H
#define _TEXTURE2D_H

#include "SDL.h"
#include "Commons.h"
#include "SDL_image.h"
#include <string>

class Texture2D
{

public:

	Texture2D(SDL_Renderer* renderer);
	~Texture2D();

	bool LoadFromFile(std::string path);
	void Free();
	void Render(Vector2D newposition, SDL_RendererFlip flip, double angle = 0.0f);
	void Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle = 0.0f);
	void Render(Vector2D newposition, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip);

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }


private:

	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;

};
#endif //_TEXTURE2D_H