#include "StartScreen.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <iostream>

bool StartScreen::main(){
	bool quit = false;

	if(load_files() == false)
		return 1;

	while(!quit){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT)
				quit = true;
			if(event.type == SDL_KEYDOWN){
				if(event.key.keysym.sym == SDLK_RETURN){
					quit = true;
				}
			}
		}
		
		apply_surface((SCREEN_WIDTH - messages[0]->w)/2, SCREEN_HEIGHT/3, messages[0], screen);
		apply_surface((SCREEN_WIDTH - messages[1]->w)/2, 2*SCREEN_HEIGHT/3, messages[1], screen);

		if(SDL_Flip(screen) == -1)
			return 1;

	}
	cleanup();
	return 0;
}

StartScreen::StartScreen(SDL_Event &event, const int SCREEN_WIDTH, const int SCREEN_HEIGHT){
	this->event = event;
	messages[0] = NULL;
	messages[1] = NULL;
	titleFont = NULL;
	optionFont = NULL;
	textColor = setColor(255,255,255);
	this->SCREEN_WIDTH = SCREEN_WIDTH;
	this->SCREEN_HEIGHT = SCREEN_HEIGHT;
}

bool StartScreen::load_files(){
	titleFont = TTF_OpenFont("res/bloodcrow.ttf", 75);
	if(titleFont == NULL)
		return false;

	optionFont = TTF_OpenFont("res/bloodcrow.ttf", 28);
	if(optionFont == NULL)
		return false;

	messages[0] = TTF_RenderText_Solid(titleFont, "Deader-than-Dead", textColor);
	if(messages[0] == NULL)
		return false;

	messages[1] = TTF_RenderText_Solid(optionFont, "Press Enter", textColor);
	if(messages[1] == false)
		return false;

	return true;
}

void StartScreen::cleanup(){
	for(int i = 0; i < 2; i++){
		SDL_FreeSurface(messages[i]);
	}

	TTF_CloseFont(titleFont);
	TTF_CloseFont(optionFont);
}