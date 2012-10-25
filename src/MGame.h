#ifndef MGAME_H
#define MGAME_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "GameScreen.h"

class MGame: public GameScreen{
private:
	SDL_Event event;
	SDL_Surface* stuff;
	bool load_files();
public:
	MGame(SDL_Event &event);
	~MGame();
	bool main();
};

#endif