#pragma once
#include "HealthPowerUp.h"
#include "../ObjectType.h"
#include "../Units/Death.h"
#include <memory>

#define NUM_FRAMES_X	1
#define NUM_FRAMES_Y	1

HealthPowerUp::HealthPowerUp(int xPosInit, int yPosInit, SDL_Surface * spriteSheet)
	:PowerUp(xPosInit, yPosInit, STANDARD_FRAMESIZE_PIX, STANDARD_FRAMESIZE_PIX,
	NUM_FRAMES_X, NUM_FRAMES_Y, STANDARD_FRAMESIZE_PIX, STANDARD_FRAMESIZE_PIX,
	ObjectType::HealthCandyCorn, spriteSheet)
{
}

//http://stackoverflow.com/questions/4089726/how-do-i-cast-a-parent-class-as-the-child-class
void HealthPowerUp::checkCollisionWith(GameObject * otherObject)
{
	if(otherObject->type == ObjectType::Death)
	{
		deallocate = true;
	}
}