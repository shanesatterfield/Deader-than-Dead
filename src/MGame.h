#ifndef MGAME_H
#define MGAME_H
#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "GameScreen.h"

//Game logic Added By Joshua Liong Below.
#include "MGame/Animation.h"
#include "MGame/Camera.h"
#include "MGame/Clock.h"
#include "MGame/GameObjectManager.h"
#include "MGame/Collision/SpatialHashing.h"
#include "MGame/Controller/Controller.h"
#include "MGame/Controller/KeyboardMouse.h"
#include "MGame/GameObjects/Units/Bat.h"
#include "MGame/GameObjects/Units/Death.h"
#include "MGame/GameObjects/Units/TestMonster.h"
#include "MGame/GameObjects/PowerUps/HealthPowerUp.h"
#include <string>
#include <stdlib.h>
#include <sstream>
#include <vector>

class MGame: public GameScreen{
private:
	SDL_Event event;
	Clock clock;
	bool load_files();
	bool init_all_objects();

public:
	MGame(SDL_Event &event);
	~MGame();
	bool main();

	Controller * controller;
	Death * deathPlayer;
	static SpatialHashing spatialHashing;
	static GameObjectManager gameObjectManager;
	static Camera * camera;
	static SDL_Surface * batImage;
	static SDL_Surface * deathImage;
	static SDL_Surface * stuff;
	static SDL_Surface * projectileImage;
	TTF_Font *font;
};

#endif