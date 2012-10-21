#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include <iostream>
#include <string>
#include <windows.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

SDL_Surface *screen = NULL;
SDL_Surface *background = NULL;
SDL_Event event;

bool init(){
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen == NULL)
		return false;

	SDL_WM_SetCaption("Deader than Dead", NULL);

	return true;
}

SDL_Surface* load_image(std::string filename){
	SDL_Surface *loadedImage = NULL;
	SDL_Surface *optimizedImage = NULL;

	loadedImage = IMG_Load(filename.c_str());
	if(loadedImage != NULL){
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	return optimizedImage;
}


bool load_files(){
	background = load_image("res/pumpkin.png");
	if(background == NULL)
		return false;
	return true;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface *destination){
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, NULL, destination, &offset);
}

void cleanup(){
	SDL_FreeSurface(background);
	SDL_Quit();
}

int main(int argc, char* argv[]){
	bool quit = false;
	if(init() == false)
		return 1;
	if(load_files() == false)
		return 1;

	while(!quit){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				quit = true;
			}
		}

		apply_surface(0,0,background, screen);

		if(SDL_Flip(screen) == -1)
			return 1;
	}

	cleanup();
	return 0;
}