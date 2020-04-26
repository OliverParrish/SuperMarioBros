#include "TileMap.h"
#include "Camera.h"


TileMap::TileMap(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	mMap = nullptr;
}

TileMap::~TileMap()
{
	delete mRenderer;
	mRenderer = nullptr;
}

void TileMap::Render()
{
	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			Tile* t = GetTileAt(x, y);
			if (t != nullptr)
				t->Render(Camera::GetInstance()->GetPosition().x, Camera::GetInstance()->GetPosition().y);
		}
		
	}
}

void TileMap::GenerateTileMap(char** map, int rows, int columns)
{
	mMap = new char* [rows];
	for (unsigned int i = 0; i < rows; i++)
		mMap[i] = new char[columns];

	mWidth = columns;
	mHeight = rows;

	mTiles = new std::vector<std::vector<Tile*>>(rows, std::vector<Tile*>(columns));

	for (unsigned int row = 0; row < rows; row++)
	{
		for (unsigned int column = 0; column < columns; column++)
		{
			mMap[row][column] = map[row][column];

			char type = mMap[row][column];

			switch (type)
			{
			case '1':
				(*mTiles)[row][column] = new Tile(mRenderer, "Images/Ground.png", Vector2D(column * 32, row * 32), CollisionType::SOLID);
				break;
			case '2':
				(*mTiles)[row][column] = new Tile(mRenderer, "Images/Platform.png", Vector2D(column * 32, row * 32), CollisionType::SOLID);
				break;
			case '3':
				(*mTiles)[row][column] = new Tile(mRenderer, "Images/PipeTopLeft.png", Vector2D(column * 32, row * 32), CollisionType::SOLID);
				break;
			case '4':
				(*mTiles)[row][column] = new Tile(mRenderer, "Images/PipeTopRight.png", Vector2D(column * 32, row * 32), CollisionType::SOLID);
				break;
			case '5':
				(*mTiles)[row][column] = new Tile(mRenderer, "Images/PipeBottomLeft.png", Vector2D(column * 32, row * 32), CollisionType::SOLID);
				break;
			case '6':
				(*mTiles)[row][column] = new Tile(mRenderer, "Images/PipeBottomRight.png", Vector2D(column * 32, row * 32), CollisionType::SOLID);
				break;
			case '7':
				(*mTiles)[row][column] = new Tile(mRenderer, "Images/Step.png", Vector2D(column * 32, row * 32), CollisionType::SOLID);
				break;
			case '8':
				mCoins.push_back(new Coin(mRenderer, "Images/Coins.png", Vector2D(column * 32, row * 32)));
				break;
			case '9':
				mFlag = new Flag(mRenderer, "Images/Flag.png", Vector2D((column * 32) - 19, (row * 32) - 198), nullptr);
				break;
			case 'k':
				mKoopa.push_back(new CharacterKoopa(mRenderer, "Images/Koopa.png", this, Vector2D(column * 32, row * 32), 80.0f, FACING_LEFT));
				break;
			}
			
		}
	}
	
}

Tile* TileMap::GetTileAt(int x, int y)
{
	if (x >= GetWidth() || x < 0) return nullptr;
	if (y >= GetHeight() || y < 0) return nullptr;

	Tile* tile = mTiles->at(y).at(x);

	if (tile != nullptr)
		return tile;

	return nullptr;
}
