#ifndef SPRITES_H
#define SPRITES_H

#include "SDL/SDL.h"
#include <string>

class Sprites{
public:
	Sprites();
	~Sprites();
	SDL_Surface* spriteSurface;
	SDL_Rect box;
	SDL_Rect clip;
	std::string type;
	std::string fromFile;
};

#endif     