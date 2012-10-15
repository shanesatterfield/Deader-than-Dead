#include "SDL/SDL.h"

#ifndef BUTTON_H
#define BUTTON_H

class Button{
public:
	~Button();
	SDL_Surface* message;
	SDL_Rect box;
	bool check_click(int x, int y);
};

#endif