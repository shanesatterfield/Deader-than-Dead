#pragma once
#include "SDL.h"

class GameObject
{
public:
	//Constructor used to define the collision box of this gameobject. Sadly they are all boxes...
	GameObject(int xPos, int yPos, int collisionX, int collisionY, int boxOffestX, int boxOffsetY);
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

	//The update function checks and does attribute/state changes. Reads in the amount of milleseconds elapsed since the last update cycle. -JVL
	virtual void update(Uint32);
	//This update will blit the object on the screen. -JVL
	virtual void draw(SDL_Surface*);
	//Cleans any surfaces or allocated memory
	virtual void cleanLoop();
	//This function will deallcoate as much memory as possible. Best when called to destroy itself.
	virtual void cleanUp();
};