#include "../GameObject.h"
#include "../../Animation.h"

class ProjectileDeath: public GameObject
{
public:
	ProjectileDeath(int xPosInit, int yPosInit, int xDirection, int yDirection, SDL_Surface* spriteSheet);
	void update(Uint32 timeElapsedMs);
	void checkCollisionWith(GameObject * otherObject);
	void draw(SDL_Surface*, int xOffset, int yOffset);

private:
	Animation sprite;
	int timeToLive;
	int xVelocity; int yVelocity;
};