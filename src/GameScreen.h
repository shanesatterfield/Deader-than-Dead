#ifndef GAMESCREEN_H 
#define GAMESCREEN_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "SDLBase.h"d

class GameScreen: public SDLBase{
protected:
	SDL_Surface* gScreen;
	SDL_Surface* screen;
	GameScreen();
	~GameScreen();
};

#endif