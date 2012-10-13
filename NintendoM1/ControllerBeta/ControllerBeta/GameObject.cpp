#include "GameObject.h"

//Precondition: the position, width and height of the collisionBox. 
//Postcondition: A gameobject is created with a collision box.
GameObject::GameObject(int xPos, int yPos, int widthCollision, int heightCollision)
{
	//Construct the collision box.
	collisionBox.x = xPos;
	collisionBox.y = yPos;
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
}
void GameObject::setBoxPosition(int xShift, int yShift)
{
	collisionBox.x = xShift;
	collisionBox.y = yShift;
}