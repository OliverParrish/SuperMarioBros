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
	if (rect1.x < rect2.x + rect2.width &&
		rect1.x + rect1.width > rect2.x &&
		rect1.y < rect2.y + rect2.height &&
		rect1.y + rect1.height > rect2.y)
	{
		return true;
	}

	return false;
}



