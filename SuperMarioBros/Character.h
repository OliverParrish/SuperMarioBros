#pragma once
#include "SDL.h"
#include "Commons.h"
#include "LevelMap.h"
#include "TileMap.h"
#include <iostream>
#include <string>

class Texture2D;

const float GravityValue = 350.0f;

class Character
{
public:

	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, TileMap* map);
	~Character();

	virtual void Render(int camX, int camY);
	virtual void Update(float deltaTime, SDL_Event e);

	virtual void UpdateFrame(float deltaTime);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	void Jump();
	void AddGravity(float deltaTime);
	bool IsJumping() { return mJumping; }
	void CancelJump();

	float GetCollisionRadius();
	Rect2D GetCollisionBox();

	void SetAlive(bool alive);
	bool GetAlive() { return mAlive; }

	TileMap* mCurrentTileMap;

protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	float mCollisionRadius;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	bool mMovingLeft;
	bool mMovingRight;

	bool mAlive;

	float movementSpeed = 200.0f;


	//Frame stuff for animation
	int mCurFrame;
	float mCurFrameTime;
	int mFrameCount;
	int mJumpFrame;

	//Jumping stuff
	bool mJumping;
	bool mCanJump;
	bool mCanMove;
	float mJumpForce;

	LevelMap* mCurrentLevelMap;


	FACING mFacingDirection;


};