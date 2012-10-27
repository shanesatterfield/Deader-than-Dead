#include "Death.h"
#include "../../Camera.h"
#include "../../Constants.h"

#define NUM_FRAMES_X	3
#define NUM_FRAMES_Y	4
#define INIT_HIT_POINTS 3
#define INVINCE_TIME_MS 900

Death::Death(int xPos, int yPos, SDL_Surface* spriteSheet, Controller* controller)
	: Unit(xPos, yPos, STANDARD_FRAMESIZE_PIX / 2, STANDARD_FRAMESIZE_PIX, 
	NUM_FRAMES_X, NUM_FRAMES_Y, STANDARD_FRAMESIZE_PIX, STANDARD_FRAMESIZE_PIX, spriteSheet, INIT_HIT_POINTS)
{
	this->controller = controller;
	this->type = (int)ObjectType::Death;
	this->hitPoints = 3;
	this->invincible = false;
	this->invTimeElapsed = 0;
}

void Death::update(Uint32 timeElapsedMs)
{
	saveCurPosToOldPos(); //Retains previous frame data before changes.
	updateInvincibilityState(timeElapsedMs); //Counts down the amount of time the unit is invincible.

	handleMovement(timeElapsedMs);
	handleLook();
	sprite.update(timeElapsedMs);
}

void Death::handleMovement(Uint32 timeElapsedMs)
{
	float totalSpeed = PLAYER_MOVEMENT_SPEED * timeElapsedMs/1000.0f;
	if(controller->pushRight())
		Death::moveBy(totalSpeed, 0);
	if(controller->pushLeft())
		Death::moveBy(-totalSpeed, 0);
	if(controller->pushUp())
		Death::moveBy(0,-totalSpeed);
	if(controller->pushDown())
		Death::moveBy(0,totalSpeed);
}

void Death::handleLook()
{
	int offsetX =  Camera::boxPosAndSize.x;
	int offsetY = Camera::boxPosAndSize.y;

	//test - float angle
	float angle = controller->detectLookAngle(this->centerX(), this->centerY(), offsetX, offsetY);
		if(angle < -45.0f)
			if(angle < -135.0f)
				this->sprite.curRow = Animation::AnimStates::Left; //angle (-180 thru -135)
			else
				this->sprite.curRow = Animation::AnimStates::Up; //angle (-135 thru -45)
		else
			if(angle > 135)
				this->sprite.curRow = Animation::AnimStates::Left; //agnle (180 thru 135)
			else if(angle > 45)
				this->sprite.curRow = Animation::AnimStates::Down; //angle (135 thru 45)
			else
				this->sprite.curRow = Animation::AnimStates::Right; //angle (45 thru -45)
}

void Death::checkCollisionWith(GameObject * otherObject)
{
	switch(otherObject->type)
	{
	case ObjectType::Enemy:
		if(!isInvincible())
		{
			invTimeElapsed = INVINCE_TIME_MS; //Start the timer
			hitPoints--;
		}
		break;
	default:
		break;
	}
}