#pragma once
#include "GameObject.h"
#include "Animation.h"

class Unit : public GameObject
{
public:
	Animation sprite; 	//This is the sprite object handler. -JVL
	//Argument constructor. Everything is set to 0/NULL if parameter is not provided -JVL
	Unit(int xPosInit, int yPosInit, int widthCollision, int heightCollision, int numSheetColumns , int numSheetRows, int frameWidth, int frameHeight, SDL_Surface * spriteSheet);
	//The update function checks and does attribute/state changes. Reads in the amount of milleseconds elapsed since the last update cycle. -JVL
	virtual void update(Uint32);
	//This update will blit the object on the screen. -JVL
	virtual void draw(SDL_Surface*);
	//Sets the position of the gameObject to exactly where the parameters specify. It also moves the collision box. -JVL
	void setPosition(int xPosNew, int yPosNew);
	//Moves the x/y position and the collision box by the amount specified
	void moveBy(int xMoveBy, int yMoveBy);
	//Sets the x and y position to the xPosOld and yPosOld attributes. Use right before any changes to the current xPos and yPos.
	void saveCurPosToOldPos();
	//Compares the old and current position to see if has changed position. Best if used after oldPos and xPos are updated fully in the frame
	bool stayedInSamePosition();
	//Getters; a method of making attributes read-only. -JVL
	int getXPos() const;
	int getYPos() const;
protected:
	int xPosOld; //The unit's x position at the previous frame. -JVL
	int yPosOld; //the unit's y position at the previous frame. -JVL
};