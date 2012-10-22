#pragma once
#include "SDL.h"

//Contains static methods used for basic collision detection
class CollisionDetection
{
public:
	static bool rectangleIntersecting(SDL_Rect rect1, SDL_Rect rect2);
};