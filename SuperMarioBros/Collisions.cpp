#include "Collisions.h"
#include "Character.h"

Collisions* Collisions::mInstance = NULL;

Collisions::~Collisions()
{
	mInstance = NULL;
}

Collisions* Collisions::Instance()
{
	if (!mInstance)
	{
		mInstance = new Collisions;
	}
	return mInstance;
}

bool Collisions::Circle(Character* Character1, Character* Character2)
{
	Vector2D vec = Vector2D((Character1->GetPosition().x - Character2->GetPosition().x), Character1->GetPosition().y - Character2->GetPosition().y);

	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	double combinedDistance = ((double)Character1->GetCollisionRadius() + (double)Character2->GetCollisionRadius());

	return distance < combinedDistance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	return false;
}



