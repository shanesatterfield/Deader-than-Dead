#pragma once
#include "../Units/Unit.h"
#include "../../Constants.h"

class TestMonster : public Unit
{
public: 
	TestMonster(SDL_Surface* spriteSheet);

	void update(Uint32 timeElapsedMs);
	void handleMovement(Uint32 timeElapsedMs);
	void handleLook();

private:
	bool goLeft;
};