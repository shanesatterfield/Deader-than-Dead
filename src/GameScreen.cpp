#include "GameScreen.h"
#include "SDLBase.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

GameScreen::GameScreen(){
	gScreen = NULL;
	screen = SDL_GetVideoSurface();
}

GameScreen::~GameScreen(){
	SDL_FreeSurface(gScreen);
}