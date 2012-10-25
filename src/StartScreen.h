#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include "GameScreen.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class StartScreen: public GameScreen{
private:
	SDL_Event event;
	SDL_Surface* messages[2];
	TTF_Font* titleFont;
	TTF_Font* optionFont;
	SDL_Color textColor;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	bool load_files();
	void cleanup();
public:
	bool main();
	StartScreen(SDL_Event &event, const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
};

#endif