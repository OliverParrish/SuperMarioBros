#pragma once
#include "SDL.h"
#include "Commons.h"
#include <iostream>
#include <string>

class Texture2D;

const float MovementSpeed = 200.0f;
const float GravityValue = 300.0f;

class Character
{
public:

	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();

	void Jump();
	void AddGravity(float deltaTime);

	float GetCollisionRadius();


protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	float mCollisionRadius;

	bool mMovingLeft;
	bool mMovingRight;

private:

	FACING mFacingDirection;
	bool mJumping;
	bool mCanJump;
	float mJumpForce;

};