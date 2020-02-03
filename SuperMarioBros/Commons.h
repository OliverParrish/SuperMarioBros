#pragma once

struct Vector2D
{
	float x;
	float y;

	Vector2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

};

struct Rect2D
{
	float x;
	float y;

	float height;
	float width;

	Rect2D()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Rect2D(float _x, float _y, float height, float width)
	{
		x = _x;
		y = _y;

		height = height;
		width = width;
	}




};

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCRREN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING
{

	FACING_LEFT = 0,
	FACING_RIGHT

};
