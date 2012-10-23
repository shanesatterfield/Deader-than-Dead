#pragma once
#include "TestMonster.h"

#define NUM_FRAMES_X	3
#define NUM_FRAMES_Y	5

TestMonster::TestMonster(SDL_Surface* spriteSheet) 
	: Unit(10, 382, GIRAFFE_FRAMESIZE_PIX, GIRAFFE_FRAMESIZE_PIX, 
	NUM_FRAMES_X, NUM_FRAMES_Y, GIRAFFE_FRAMESIZE_PIX, GIRAFFE_FRAMESIZE_PIX, spriteSheet)
{
	goLeft = false;
	this->type = (int)ObjectType::Enemy;
}

void TestMonster::update(Uint32 timeElapsedMs)
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

void TestMonster::handleMovement(Uint32 timeElapsedMs)
{
	float totalSpeed = PLAYER_MOVEMENT_SPEED * timeElapsedMs/1000.0f;
	if(goLeft)
		moveBy(-totalSpeed, 0);
	else
		moveBy(totalSpeed,0);
}

void TestMonster::handleLook()
{
	if(goLeft)
		this->sprite.curRow = Animation::AnimStates::Left;
	else
		this->sprite.curRow = Animation::AnimStates::Right;
}
