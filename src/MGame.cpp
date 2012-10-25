#include "MGame.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "SDLBase.h"
#include "GameScreen.h"

#include <iostream>

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

bool MGame::load_files(){
	gScreen = load_image("res/background.png");
	if(gScreen == NULL)
		return false;
	return true;
}

MGame::MGame(SDL_Event &tEvent){
	event = tEvent;
	stuff == NULL;
	stuff = load_image("res/pumpkin.png");
	if(stuff == NULL)
		std::cout << "Hey" << std::endl;
}

MGame::~MGame(){
	SDL_FreeSurface(stuff);
}