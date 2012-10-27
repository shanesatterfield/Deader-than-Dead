#include "Unit.h"
#include "../../Controller/Controller.h"

class Death : public Unit
{
public:
	Death(int xPos, int yPos, SDL_Surface* spriteSheet, Controller * controller);
	void update(Uint32 timeElapsedMs);
	void checkCollisionWith(GameObject * otherObject);
	bool invincible;

private:
	Controller * controller; //A reference to the controller. This pointer will be used to update the state of Death.
	void handleMovement(Uint32 timeElapsed);
	void handleLook();
};