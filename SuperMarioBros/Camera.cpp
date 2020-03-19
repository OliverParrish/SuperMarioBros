#include "Camera.h"

// Initialise static variables
Camera* Camera::instance = 0;
SDL_Rect Camera::mCamera = { 0, 0, 0, 0 };


void Camera::SetPosition(Vector2D newposition)
{
	mCamera.x = newposition.x;
	mCamera.y = newposition.y;
}


Camera::~Camera()
{
	delete instance;
	instance = nullptr;
}