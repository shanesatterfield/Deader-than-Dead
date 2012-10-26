#include "GameScreen.h"
#include "SDLBase.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

GameScreen::GameScreen(){
	gScreen = NULL;
	screen = SDL_GetVideoSurface();
}

GameScreen::~GameScreen(){
	SDL_FreeSurface(gScreen);
}