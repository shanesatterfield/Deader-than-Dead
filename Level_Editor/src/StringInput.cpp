#include "StringInput.h"
#include <string>
#include "SDLBase.h"
#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"


StringInput::StringInput(){
	textInput = NULL;
	str = "";
	SDL_EnableUNICODE(SDL_ENABLE);
}

StringInput::~StringInput(){
	SDL_FreeSurface(textInput);
	SDL_EnableUNICODE(SDL_DISABLE);
}

std::string StringInput::getStr(){
	return str;
}

int StringInput::get_input(SDL_Event event){
	if(event.type == SDL_KEYDOWN){
		std::string temp = str;
		if(str.size() < 20){

			if(event.key.keysym.unicode == (Uint16)'.'){
				str += (char)event.key.keysym.unicode;
			}
			else if(event.key.keysym.unicode == (Uint16)' '){
				str += (char)event.key.keysym.unicode;
			}
			else if(event.key.keysym.unicode >= (Uint16)'A' && event.key.keysym.unicode <= (Uint16)'Z'){
				str += (char)event.key.keysym.unicode;
			}
			else if(event.key.keysym.unicode >= (Uint16)'a' && event.key.keysym.unicode <= (Uint16)'z'){
				str += (char)event.key.keysym.unicode;
			}
			else if(event.key.keysym.unicode >= (Uint16)'0' && event.key.keysym.unicode <= (Uint16)'9'){
				str += (char)event.key.keysym.unicode;
			}
			else if(event.key.keysym.unicode == (Uint16)'/'){
				str += (char)event.key.keysym.unicode;
			}
		}
		if(event.key.keysym.unicode == SDLK_BACKSPACE && str.size() != 0){
			str.erase(str.size()-1);
		}
		if(event.key.keysym.unicode == SDLK_RETURN){
			return 2;
		}
		if(str != temp){
			/*
			if(textInput != NULL)
				SDL_FreeSurface(textInput);
			textInput = TTF_RenderText_Solid(font, "asdf", textColor);
			*/
			std::cout << str << std::endl;
			return 1;
		}
	}
	return 0;
}

void StringInput::display(int SCREEN_WIDTH, int SCREEN_HEGHT, int yOffset, SDL_Surface* screen){
	if(textInput != NULL){
		apply_surface((SCREEN_WIDTH - textInput->w)/2, (SCREEN_HEGHT - textInput->h)/2 + yOffset, textInput, screen);
	}
}
