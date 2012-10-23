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
	TTF_Font* font;
	SDL_Color textColor;
	bool loaded;
	SDL_Color setColor(Uint8 r, Uint8 g, Uint8 b);
public:
	StringInput();
	~StringInput();
	int get_input(SDL_Event event);
	void display(int SCREEN_WIDTH, int SCREEN_HEGHT, int yOffset, SDL_Surface* screen);
	SDL_Surface* textInput;
	std::string getStr();
	bool is_loaded();
};

#endif