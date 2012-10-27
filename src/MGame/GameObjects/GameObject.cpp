#include "GameObject.h"

GameObject::GameObject(int xPos, int yPos, int widthCollision, 
	int heightCollision, int boxOffsetX, int boxOffsetY, GameObject * gameObject)
{
	*this = GameObject::GameObject(xPos, yPos, widthCollision, 
	heightCollision, boxOffsetX, boxOffsetY); //Calls regular constructor
	this->target = gameObject; //Assigns a target to do stuff with.
}

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
	this->target = NULL;
}

GameObject::~GameObject(){/*Override when it contains allocated stuff!*/}

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
	setBoxPosition(pos.x+=xShift, pos.y+=yShift);
}
void GameObject::setBoxPosition(int xNew, int yNew)
{
	pos.x = xNew;
	pos.y = yNew;
	collisionBox.x = xNew + pos.w;
	collisionBox.y = yNew + pos.h;
}

//----overridable functions-----//
//The update function checks and does attribute/state changes. Reads in the amount of milleseconds elapsed since the last update cycle. -JVL
void GameObject::update(Uint32){/*Please Override*/};
//This update will blit the object on the screen. -JVL
void GameObject::draw(SDL_Surface*, int xOffset, int yOffset){/*Please Override*/};
//Cleans any surfaces or allocated memory
void GameObject::cleanLoop(){/*Please Override*/};
//Takes in the otherobject, read the type and then makes state changes.
void GameObject::checkCollisionWith(GameObject*){/*Please Override*/};
