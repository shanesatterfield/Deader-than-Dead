#ifndef SDLBASE_H
#define SDLBASE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>

class SDLBase{
public:
	SDL_Surface* load_image(std::string filename);
	void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface *destination);
};

#endif