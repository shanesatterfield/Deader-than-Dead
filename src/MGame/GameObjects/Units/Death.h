#pragma once
#include "Unit.h"
#include "../../Controller/Controller.h"

#define NUMBER_OF_COOLDOWNS 3

class Death : public Unit
{
public:
	Death(int xPos, int yPos, SDL_Surface* spriteSheet, Controller * controller);
	int cooldowns[NUMBER_OF_COOLDOWNS];
	void update(Uint32 timeElapsedMs);
	void checkCollisionWith(GameObject * otherObject);
	bool invincible;
	static int killCount;

private:
	Controller * controller; //A reference to the controller. This pointer will be used to update the state of Death.
	int attackState;
	int abilityCooldown;
	void handleMovement(Uint32 timeElapsed);
	void handleLook();
	void handleAttack();
	void cooldownAllAbilities(Uint32 timeElapsed);
	bool switchToNewStandby(int newMode); //returns true if switch is complete. False if there is still a cooldown.

	enum AttackMode
	{
		//Standby
		MeleeStandby = 0,
		RangedStandby = 1,
		AoEStandby = 2,

		//Attacks in progress (Values are Standby + 10)
		MeleeAttack = 10,
		RangedAttack = 11,
		AoEAttack = 12
	};
};