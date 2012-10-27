#pragma once
#include "../Units/Unit.h"

class Bat : public Unit
{
public: 
	Bat(SDL_Surface* spriteSheet);
	Bat(SDL_Surface* spriteSheet, GameObject * target);
	void update(Uint32 timeElapsedMs);
	void handleMovement(Uint32 timeElapsedMs);
	void handleLook();

private:
	bool goLeft;
};