#ifndef GAMESCREEN_H 
#define GAMESCREEN_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "SDLBase.h"

class GameScreen: public SDLBase{
protected:
	SDL_Surface* gScreen;
	GameScreen();
	~GameScreen();
};

#endif