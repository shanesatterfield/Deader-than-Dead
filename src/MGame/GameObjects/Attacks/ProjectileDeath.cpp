#include "ProjectileDeath.h"
#include "../Units/Unit.h"

#define PROJECTILE_COLLISION_SIZE 15
#define PROJECTILE_SPEED 800
#define COLLISION_OFFSET 0
#define TIME_TO_LIVE 500 //ms

ProjectileDeath::ProjectileDeath(int xPosInit, int yPosInit, int xDirection, int yDirection, SDL_Surface* spriteSheet)
	: GameObject(xPosInit, yPosInit, PROJECTILE_COLLISION_SIZE, PROJECTILE_COLLISION_SIZE, COLLISION_OFFSET, COLLISION_OFFSET)
{
	sprite.init(1,1,25,25,spriteSheet);
	timeToLive = TIME_TO_LIVE;
	xVelocity = xDirection;
	yVelocity = yDirection;
}

void ProjectileDeath::update(Uint32 timeElapsedMs)
{
	if((timeToLive -= timeElapsedMs) <= 0)
		deallocate = true;
	else
	{
		float normalizedValue = GameObject::findNormalizationDenominator(xVelocity, yVelocity);
		int xSpeed = xVelocity / normalizedValue * PROJECTILE_SPEED * timeElapsedMs/1000;
		int ySpeed = yVelocity / normalizedValue * PROJECTILE_SPEED * timeElapsedMs/1000;
		this->moveBox(xSpeed, ySpeed);
	}
}

void ProjectileDeath::draw(SDL_Surface* screen, int xOffset, int yOffset)
{
	sprite.draw(pos.x - xOffset, pos.y - yOffset, screen);
}

void ProjectileDeath::checkCollisionWith(GameObject * otherObject)
{
	int typeNum = otherObject->type;
	if(0 < typeNum && typeNum < 70)
	{
		Unit * thisUnit = dynamic_cast<Unit*>(otherObject);
		thisUnit->hitPoints--;
		if(thisUnit->hitPoints <= 0)
			thisUnit->deallocate = true;
	}
}