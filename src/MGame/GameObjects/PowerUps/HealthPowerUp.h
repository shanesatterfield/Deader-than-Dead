#pragma once
#include "PowerUp.h"

class HealthPowerUp : public PowerUp
{
public:
	HealthPowerUp(int xPosInit, int yPosInit, SDL_Surface * spriteSheet);
	//~HealthPowerUp(); //Deconstructor

	//Takes in the otherobject, read the type and then makes state changes.
	virtual void checkCollisionWith(GameObject * otherObject);
};