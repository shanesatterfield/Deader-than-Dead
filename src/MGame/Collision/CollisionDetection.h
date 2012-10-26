#pragma once
#include "SDL.h"
#include "../GameObjects/GameObject.h"

//Contains static methods used for basic collision detection
class CollisionDetection
{
public:
	static bool rectangleIntersecting(SDL_Rect rect1, SDL_Rect rect2);
	static bool rectangleIntersecting(GameObject * g1, GameObject * g2);
};