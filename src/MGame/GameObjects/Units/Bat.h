#pragma once
#include "../Units/Unit.h"
#include "../PowerUps/HealthPowerUp.h"
#include "../../../MGame.h"

#include <cmath>
class Bat : public Unit
{
public: 
	Bat(SDL_Surface* spriteSheet);
	Bat(SDL_Surface* spriteSheet, GameObject * target);
	void update(Uint32 timeElapsedMs);
	void handleMovement(Uint32 timeElapsedMs);
	void handleLook();
	void changeRandomDirection();
	void checkCollisionWith(GameObject * otherObject);

private:
	bool randomMovement;
	Uint32 actionTimer;
	float xVelocity; float yVelocity;
};