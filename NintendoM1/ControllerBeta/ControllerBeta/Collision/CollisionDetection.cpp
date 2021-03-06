#include "CollisionDetection.h"

bool CollisionDetection::rectangleIntersecting(SDL_Rect rect1, SDL_Rect rect2)
{
	//x axis check
	if((rect1.x + rect1.w) < rect2.x || (rect2.x + rect2.w) < rect1.x)
		return false;
	else if((rect1.y + rect1.h) < rect2.y || (rect2.y + rect2.h) < rect1.y) //y axis check
		return false;
	else
		return true;
}

bool CollisionDetection::rectangleIntersecting(GameObject * g1, GameObject * g2)
{
	//Get the rectangles and then go thru rectangle intersection check.
	return CollisionDetection::rectangleIntersecting(g1->collisionBox, g2->collisionBox);
}