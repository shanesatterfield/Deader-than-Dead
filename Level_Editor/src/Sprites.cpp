#include "Sprites.h"
#include "SDL/SDL.h"
#include <string>

Sprites::Sprites(){
	spriteSurface = NULL;
	type = "";
	fromFile = "";
	box.x = 0;
	box.y = 0;
	box.w = 0;
	box.h = 0;

	clip.x = 0;
	clip.y = 0;
	clip.w = 0;
	clip.h = 0;
}
Sprites::~Sprites(){
	SDL_FreeSurface(spriteSurface);
}