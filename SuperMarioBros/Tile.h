#pragma once
#include "Texture2D.h"

class Tile
{
public:

	Vector2D mPosition;
	char C;
	Texture2D* mTexture;
	bool canCollide;

	SDL_Renderer* mRenderer;

	Tile(Vector2D _position, char _c, Texture2D* _texture, bool _collide, SDL_Renderer* _renderer)
	{
		mPosition = _position;
		C = _c;
		mTexture = new Texture2D(mRenderer);
		canCollide = _collide;
		mRenderer = _renderer;

	}
};
