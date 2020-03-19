#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>



Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}

Texture2D::~Texture2D()
{
	Free();

	mRenderer = NULL;
}

bool Texture2D::LoadFromFile(std::string path)
{
	Free();

	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{
		SDL_SetColorKey(pSurface, SDL_TRUE, SDL_MapRGB(pSurface->format, 0, 0xFF, 0xFF));

		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		if (mTexture == NULL)
		{
			std::cout << "Unable to create texture from surface. Error: " << SDL_GetError() << std::endl;
		}
		mWidth = pSurface->w;
		mHeight = pSurface->h;
	}
	else
	{
		std::cout << "Unable to Create texture from surface. Error: " << IMG_GetError() << std::endl;
	}
	SDL_FreeSurface(pSurface);

	return mTexture != NULL;
}

void Texture2D::Free()
{
	if (mTexture !=NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
	
}

void Texture2D::Render(Vector2D newpoition, SDL_RendererFlip flip, double angle)
{
	SDL_Rect renderLocation = { newpoition.x, newpoition.y, mWidth, mHeight };
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, flip);
}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}

void Texture2D::Render(Vector2D newposition, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_Rect renderLocation = { newposition.x, newposition.y, mWidth, mHeight };

	if (clip != NULL)
	{
		mWidth = clip->w;
		mHeight = clip->h;
	}

	SDL_RenderCopyEx(mRenderer, mTexture, clip, &renderLocation, angle, center, flip);
}
