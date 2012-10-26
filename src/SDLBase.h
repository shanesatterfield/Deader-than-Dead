#ifndef SDLBASE_H
#define SDLBASE_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>

class SDLBase{
protected:
	SDL_Surface* load_image(std::string filename);
	void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface *destination);
	//std::string convert_path(std::string filename);
	SDL_Color setColor(Uint8 r, Uint8 g, Uint8 b);
};

#endif