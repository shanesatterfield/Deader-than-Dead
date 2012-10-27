#pragma once
#include "../GameObject.h"
#include "../../Animation.h"

class PowerUp : public GameObject
{
public:
	Animation sprite; 	//This is the sprite object handler. -JVL

	//Argument constructor. -JVL
	PowerUp(int xPosInit, int yPosInit, int widthCollision, int heightCollision, int numSheetColumns , int numSheetRows, int frameWidth, int frameHeight, int objType, SDL_Surface * spriteSheet);
	~PowerUp();//Deconstructor
	//The update function checks and does attribute/state changes. Reads in the amount of milleseconds elapsed since the last update cycle. -JVL
	virtual void update(Uint32);
	//This update will blit the object on the screen. -JVL
	virtual void draw(SDL_Surface*, int xOffset, int yOffset);

	//Takes in the otherobject, read the type and then makes state changes.
	virtual void checkCollisionWith(GameObject * otherObject);
protected:
	int invTimeElapsed; //The amount of time the unit has before it disappears
};