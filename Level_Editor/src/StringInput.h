#ifndef STRING_INPUT_H
#define STRING_INPUT_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include "SDLBase.h"

class StringInput: public SDLBase{
private:
	std::string str;
public:
	StringInput();
	~StringInput();
	int get_input(SDL_Event event);
	void display(int SCREEN_WIDTH, int SCREEN_HEGHT, int yOffset, SDL_Surface* screen);
	SDL_Surface* textInput;
	std::string getStr();
};

#endif