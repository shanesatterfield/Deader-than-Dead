/*
Deader-than-Dead Main
Screen Manager

Project Manager:
	Shane Satterfield
Collaborators:
	Christopher Gomez
	Joshua Liong
*/
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include <iostream>
#include <string>

#include "src/MGame.h"
#include "src/GameScreen.h"
#include "src/StartScreen.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

SDL_Surface *screen = NULL;
SDL_Event event;

//Function Prototpyes
bool init();
void cleanup();

int main(int argc, char* argv[]){
	bool quit = false;
	if(init() == false)
		return 1;

	StartScreen starScream(event, SCREEN_WIDTH, SCREEN_HEIGHT);
	MGame mgame(event);

	while(!quit){
		if(starScream.main() == true){
			quit = true;
			break;
		}
		if(mgame.main() == false){
			quit = true;
			break;
		}
	}

	cleanup();
	return 0;
}

bool init(){
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if(screen == NULL)
		return false;

	if(TTF_Init() == -1)
		return false;

	SDL_WM_SetCaption("Deader than Dead", NULL);

	return true;
}

void cleanup(){
	TTF_Quit();
	SDL_Quit();
}