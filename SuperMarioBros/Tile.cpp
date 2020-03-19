#include "Tile.h"
#include <iostream>


Tile::Tile(SDL_Renderer* renderer, std::string imagePath, Vector2D position, CollisionType type)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mPosition = position;
	mCollisionType = type;

	if (!mTexture->LoadFromFile(imagePath))
	{
		std::cerr << "could not load image from " << imagePath << std::endl;
	}
}

Tile::~Tile()
{
	delete mRenderer;
	mRenderer = nullptr;

	delete mTexture;
	mTexture = nullptr;

}

void Tile::Render(int camX, int camY)
{
	mTexture->Render(Vector2D(mPosition.x - camX, mPosition.y - camY), nullptr, 0.0, nullptr, SDL_FLIP_NONE);
}
