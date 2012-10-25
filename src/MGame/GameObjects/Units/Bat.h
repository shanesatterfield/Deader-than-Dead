#pragma once
#include "../Units/Unit.h"

class Bat : public Unit
{
public: 
	Bat(SDL_Surface* spriteSheet);

	void update(Uint32 timeElapsedMs);
	void handleMovement(Uint32 timeElapsedMs);
	void handleLook();

private:
	bool goLeft;
};