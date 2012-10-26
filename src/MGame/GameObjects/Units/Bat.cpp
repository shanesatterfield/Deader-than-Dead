#include "Bat.h"
#include "../../Constants.h"

#define NUM_FRAMES_X	2
#define NUM_FRAMES_Y	2

Bat::Bat(SDL_Surface* spriteSheet) 
	: Unit(10, 382, STANDARD_FRAMESIZE_PIX, STANDARD_FRAMESIZE_PIX, 
	NUM_FRAMES_X, NUM_FRAMES_Y, STANDARD_FRAMESIZE_PIX, STANDARD_FRAMESIZE_PIX, spriteSheet)
{
	goLeft = false;
	this->type = (int)ObjectType::Enemy;
}

void Bat::update(Uint32 timeElapsedMs)
{
	saveCurPosToOldPos(); //Retains previous frame data before changes.
	
	handleMovement(timeElapsedMs); //movement handled by AI as opposed to a controller.
	if(collisionBox.x > 900)
	{
		collisionBox.x = 900;
		goLeft = true;
	}
	else if(collisionBox.x < 100)
	{
		collisionBox.x = 100;
		goLeft = false;
	}
		
	handleLook();
	sprite.update(timeElapsedMs);
}

void Bat::handleMovement(Uint32 timeElapsedMs)
{
	float totalSpeed = PLAYER_MOVEMENT_SPEED * timeElapsedMs/1000.0f;
	if(goLeft)
		moveBy(-totalSpeed, 0);
	else
		moveBy(totalSpeed,0);
}

void Bat::handleLook()
{
	if(goLeft)
		this->sprite.curRow = 0; //Magic Numbers T.T
	else
		this->sprite.curRow = 1; //Magic Numbers T.T
}
