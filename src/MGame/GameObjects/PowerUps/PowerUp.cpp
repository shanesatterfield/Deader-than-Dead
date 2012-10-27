#include "PowerUp.h"

PowerUp::PowerUp(int xPosInit , int yPosInit , int widthCollision , int heightCollision, 
	int numSheetColumns , int numSheetRows , int frameWidth , int frameHeight , int objType, SDL_Surface * spriteSheet) 
		: GameObject(xPosInit, yPosInit, widthCollision, heightCollision, 
		(int)abs((widthCollision-frameWidth)/2), (int)abs((heightCollision-frameHeight)/2),
		NULL)
{
	this->sprite.init(numSheetColumns, numSheetRows, frameWidth, frameHeight, spriteSheet);
	this->type = objType;
}
PowerUp::~PowerUp(){/*Please override*/}

void PowerUp::checkCollisionWith(GameObject * otherObject){/*Please override*/}

void PowerUp::update(Uint32 timeElapsedMs)
{
	this->sprite.update(timeElapsedMs);
}

void PowerUp::draw(SDL_Surface *destination, int xOffset, int yOffset)
{
	this->sprite.draw(this->pos.x - xOffset, this->pos.y - yOffset, destination);
}