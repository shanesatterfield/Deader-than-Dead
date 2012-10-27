#pragma once
#include "SDL.h"
#include "ObjectType.h"
class GameObject
{
public:
	//Constructor used to define the collision box of this gameobject. Sadly they are all boxes...
	GameObject(int xPos, int yPos, int collisionX, int collisionY, int boxOffestX, int boxOffsetY);
	//Second Constructor used to define the collision box of this gameobject. Sadly they are all boxes...
	GameObject(int xPos, int yPos, int collisionX, int collisionY, int boxOffestX, int boxOffsetY, GameObject * targetObject);
	//Virtual deconstructor. Needed so that the child classes can be destroyed when in a generic list.
	virtual ~GameObject();
	//The collision box to be used for collision detection
	SDL_Rect collisionBox;
	//The position (used to draw the sprite) is stored in x,y. The offset for collision is stored in w,h.
	SDL_Rect pos;
	//A flag to indicate that this object must be destroyed by the next update cycle.
	bool deallocate;
	//Returns the X of the center of the collision box.
	int centerX();
	//Returns the Y of the center of the collision box.
	int centerY();
	//Shifts the x and y position of the box. Used to move the gameObject alongside with the collisionbox.
	void moveBox(int xShift, int yShift);
	//Sets the x and y position of the position and collision box.
	void setBoxPosition(int xShift, int yShift);
	//Enum Type of GameObject; defines what it is.
	int type;
	//Determines the target to attack, chase or modify, depending on Update AI.
	GameObject * target;
	//The update function checks and does attribute/state changes. Reads in the amount of milleseconds elapsed since the last update cycle. -JVL
	virtual void update(Uint32);
	//This update will blit the object on the screen. -JVL
	virtual void draw(SDL_Surface*, int xOffset, int yOffset);
	//Cleans any surfaces or allocated memory
	virtual void cleanLoop();

	//Takes in the otherobject, read the type and then makes state changes.
	virtual void checkCollisionWith(GameObject * otherObject);
};