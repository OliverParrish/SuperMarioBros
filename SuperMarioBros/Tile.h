#pragma once
#include "Texture2D.h"
#include "Commons.h"

class Tile
{
public:
	
	Tile(SDL_Renderer* renderer, std::string imagePath, Vector2D position, CollisionType type);
	~Tile();

	static const int width = 32;
	static const int height = 32;

	CollisionType GetCollisionType() { return mCollisionType; }

	Vector2D GetPosition() { return mPosition; }

	void Render(int x, int y);

private:

	CollisionType mCollisionType;
	
	Texture2D* mTexture;

	Vector2D mPosition;

	SDL_Renderer* mRenderer;

};

