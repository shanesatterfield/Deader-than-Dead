#include "MGame.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "SDLBase.h"
#include "GameScreen.h"

#include <iostream>

//Screen attributes
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int SCREEN_BPP = 32;
const int SPATIAL_HASHING_CELL_SIZE = 128;
const int SPEED = 400; //pixels per second
//The color of the font
SDL_Color textColor = { 0, 0, 0 };

bool MGame::main(){
	bool quit = false;
	
	if(load_files() == false){
		return 1;
	}

	while(!quit){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				quit = true;
			}
		}

		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255,255,255));

		apply_surface(100,100,stuff, gScreen);
		apply_surface(0,0,gScreen, screen);

		if(SDL_Flip(screen) == -1){
			return 1;
		}
	}

	return !quit;
}

//Loading Files
bool MGame::load_files(){
	gScreen = load_image("res/background.png");
	if(gScreen == NULL)
		return false;
	return true;
}

//Constructor
MGame::MGame(SDL_Event &tEvent){
	event = tEvent;
	stuff == NULL;
	stuff = load_image("res/pumpkin.png");
	if(stuff == NULL)
		std::cout << "Hey" << std::endl;
}

//Deconstructor
MGame::~MGame(){
	SDL_FreeSurface(stuff);
}