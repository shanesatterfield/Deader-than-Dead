#include "SDL/SDL.h"
#include "Button.h"

bool Button::check_click(int x, int y){
	bool bl = false;
	if(x >= box.x && x <= box.x + box.w){
		if(y >= box.y && y <= box.y + box.h){
			bl = true;
		}
	}
	return bl;
}

Button::~Button(){
	SDL_FreeSurface(message);
}