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

enum SCREENS
{
	SCREEN_INTRO = 0,
	SCRREN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};
