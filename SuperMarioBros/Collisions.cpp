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

bool Collisions::Circle(Circle2D circle1, Circle2D circle2)
{
	Vector2D vec = Vector2D((circle1.position.x - circle2.position.x), circle1.position.y - circle2.position.y);

	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	double combinedDistance = ((double)circle1.circleRadius + (double)circle2.circleRadius);

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



