#include "Bat.h"

#define NUM_FRAMES_X	2
#define NUM_FRAMES_Y	2
#define INIT_HIT_POINTS 1
#define CHANGE_TO_RANDOM_MOVEMENT 200
#define CHANGE_TO_CHASE 800
#define INVINCE_TIME_MS 200

Bat::Bat(SDL_Surface* spriteSheet, GameObject * target) 
	: Unit(10, 382, STANDARD_FRAMESIZE_PIX, STANDARD_FRAMESIZE_PIX, 
	NUM_FRAMES_X, NUM_FRAMES_Y, STANDARD_FRAMESIZE_PIX, STANDARD_FRAMESIZE_PIX, spriteSheet, INIT_HIT_POINTS, target)
{
	randomMovement = false;
	this->type = (int)ObjectType::Enemy;
}

Bat::Bat(SDL_Surface* spriteSheet) 
	: Unit(10, 382, STANDARD_FRAMESIZE_PIX, STANDARD_FRAMESIZE_PIX, 
	NUM_FRAMES_X, NUM_FRAMES_Y, STANDARD_FRAMESIZE_PIX, STANDARD_FRAMESIZE_PIX, spriteSheet, INIT_HIT_POINTS)
{
	randomMovement = false;
	this->type = (int)ObjectType::Enemy;
}

void Bat::update(Uint32 timeElapsedMs)
{
	//Counts down the amount of time the unit is invincible.
	updateInvincibilityState(timeElapsedMs); 

	//Get distance of bat to player
	int xDiff = target->centerX() - this->centerX();
	int yDiff = target->centerY() - this->centerY();
	int distance = sqrt(float(xDiff*xDiff + yDiff * yDiff));
	
	//if bat is close enough, randomize movement. else, chase player.
	if(!randomMovement && distance < CHANGE_TO_RANDOM_MOVEMENT)
	{
		randomMovement = true;
		xVelocity = pos.x - xPosOld;//Preserve current vector approach
		yVelocity = pos.y - yPosOld;//Preserve current vector approach
		float normalization = this->findNormalizationDenominator(xVelocity, yVelocity);
		xVelocity /= normalization;
		yVelocity /= normalization;
	}
	else if(randomMovement && distance > CHANGE_TO_CHASE)
		randomMovement = false;

	saveCurPosToOldPos(); //Retains previous frame data before changes.

	handleMovement(timeElapsedMs); //movement handled by AI as opposed to a controller.
	
	handleLook();
	sprite.update(timeElapsedMs);
}

void Bat::handleMovement(Uint32 timeElapsedMs)
{
	if(!randomMovement)
		this->chaseTarget(timeElapsedMs, PLAYER_MOVEMENT_SPEED);
	else
	{
		//Determine whether the velocity vector should be randomized.
		actionTimer += timeElapsedMs;
		const int TIME_TO_CHANGE_MOVEMENT_PATTERN = 1000;
		if(actionTimer > TIME_TO_CHANGE_MOVEMENT_PATTERN)
		{
			changeRandomDirection(); 
			actionTimer = 0;
		}

		//Apply the single direction movement.
		this->moveBy(xVelocity * PLAYER_MOVEMENT_SPEED * timeElapsedMs/1000.0f,
			yVelocity * PLAYER_MOVEMENT_SPEED * timeElapsedMs/1000.0f );
	}
}

//http://www.cplusplus.com/reference/clibrary/cstdlib/rand/
//http://www.daniweb.com/software-development/cpp/threads/1769/c-random-numbers
void Bat::changeRandomDirection()
{
	int unNormalizedX = (rand() % 200) - 100;
	int unNormalizedY = (rand() % 200) - 100;
	float normalizationDenominator; 
	abs(unNormalizedX) > abs(unNormalizedY) ? 
		normalizationDenominator = abs(unNormalizedX) : 
		normalizationDenominator = abs(unNormalizedY);

	xVelocity = unNormalizedX / normalizationDenominator;
	yVelocity = unNormalizedY / normalizationDenominator;
}

void Bat::handleLook()
{
	if(pos.x < xPosOld)
		this->sprite.curRow = 0; //Magic Numbers T.T
	else
		this->sprite.curRow = 1; //Magic Numbers T.T
}

void Bat::checkCollisionWith(GameObject * otherObject)
{
	switch(otherObject->type)
	{
	case ObjectType::Death:
		if(!isInvincible())
		{
			invTimeElapsed = INVINCE_TIME_MS; //Start the timer
			hitPoints--;

			if(hitPoints <= 0)
			{
				GameObjectManager::queuedNewGameObjects.push_back(new HealthPowerUp(pos.x, pos.y, MGame::stuff));
				deallocate = true;
			}

		}
		break;
	default:
		break;
	}
}