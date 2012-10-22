#include "Death.h"
#include "../../Constants.h"

#define NUM_FRAMES_X	3
#define NUM_FRAMES_Y	5

Death::Death(int xPos, int yPos, SDL_Surface* spriteSheet, Controller* controller)
	: Unit(xPos, yPos, STANDARD_FRAMESIZE_PIX, STANDARD_FRAMESIZE_PIX, 
	NUM_FRAMES_X, NUM_FRAMES_Y, STANDARD_FRAMESIZE_PIX, STANDARD_FRAMESIZE_PIX, spriteSheet)
{
	this->controller = controller;
	this->type = (int)ObjectType::Death;
}

void Death::update(Uint32 timeElapsedMs)
{
	saveCurPosToOldPos(); //Retains previous frame data before changes.
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
	if(stayedInSamePosition())
		this->sprite.curRow = Animation::AnimStates::Idle;
	else
	{
		//temporary variable. 
		const int OFFSET = 0;

		//test - float angle
		float angle = controller->detectLookAngle(this->centerX(), this->centerY(), OFFSET, OFFSET);
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
}

void Death::checkCollisionWith(GameObject * otherObject)
{
	switch(otherObject->type)
	{
	case ObjectType::Enemy:
		otherObject->setBoxPosition(100, 368);
		break;
	default:
		break;
	}
}

