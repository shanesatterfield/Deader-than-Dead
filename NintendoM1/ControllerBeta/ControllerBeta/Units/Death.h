#include "Unit.h"
#include "../Controller.h"

class Death : public Unit
{
public:
	//Argument constructor.
	Death(int xPos, int yPos, SDL_Surface* spriteSheet, Controller * controller);
	void update(Uint32 timeElapsedMs);

private:
	Controller * controller; //A reference to the controller. This pointer will be used to update the state of Death.

	void handleMovement(Uint32 timeElapsed);
	void handleLook();
};