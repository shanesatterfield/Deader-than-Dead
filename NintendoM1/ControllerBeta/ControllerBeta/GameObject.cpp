#include "GameObject.h"

//Precondition: the position, width and height of the collisionBox. 
//Postcondition: A gameobject is created with a collision box.
GameObject::GameObject(int xPos, int yPos, int widthCollision, 
	int heightCollision, int boxOffsetX, int boxOffsetY)
{
	//Gather the position
	pos.x = xPos;
	pos.y = yPos;
	pos.w = boxOffsetX;
	pos.h = boxOffsetY;

	//Construct the collision box.
	collisionBox.x = xPos + boxOffsetX;
	collisionBox.y = yPos + boxOffsetY;
	collisionBox.w = widthCollision;
	collisionBox.h = heightCollision;
	
	//Flag is false; you just created this object!
	deallocate = false;
}

int GameObject::centerX()
{ 
	return collisionBox.x + collisionBox.w/2; 
}
int GameObject::centerY()
{
	return collisionBox.y + collisionBox.h/2;
}
void GameObject::moveBox(int xShift, int yShift)
{
	collisionBox.x += xShift;
	collisionBox.y += yShift;
	pos.x += xShift;
	pos.y += yShift;
}
void GameObject::setBoxPosition(int xShift, int yShift)
{
	pos.x = xShift;
	pos.y = yShift;
	collisionBox.x = xShift + pos.w;
	collisionBox.y = yShift + pos.h;
}