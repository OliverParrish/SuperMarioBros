#pragma once
#include "SDL.h"
#include "Commons.h"
#include "Texture2D.h"

class Flag
{
	public:

		Flag(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, SCREENS* changeScreen);
		~Flag();

		void Render(int camX, int camY);
		void Update(float deltaTime);

		const Vector2D GetPosition() { return mPosition; }

		const Rect2D GetBoxCollision() { return mBoxCollision; }

		SCREENS* mChangeScreen;

	private:

		SDL_Renderer* mRenderer;
		Vector2D mPosition;
		Texture2D* mTexture;
		Rect2D mBoxCollision;


};
