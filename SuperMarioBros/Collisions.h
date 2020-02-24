#pragma once

#include "Character.h"
#include "Commons.h"

class Collisions
{
public:

	~Collisions();

	static Collisions* Instance();

	bool Circle(Character* Character1, Character* Character2);
	bool Box(Rect2D rect1, Rect2D rect2);

private:

	static Collisions* mInstance;
};