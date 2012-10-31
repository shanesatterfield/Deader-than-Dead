#include "MGame.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "SDLBase.h"
#include "GameScreen.h"

#include <iostream>

//Screen attributes
const int FRAMES_PER_SECOND = 30;
const int SCREEN_WIDTH = 800; //TODO: This was already defined in Deader-Than-Dead.cpp
const int SCREEN_HEIGHT = 600;//TODO: This was already defined in Deader-Than-Dead.cpp
const int SCREEN_BPP = 32;
const int SPATIAL_HASHING_CELL_SIZE = 128;
const int SPEED = 400; //pixels per second
//The color of the font
SDL_Color textColor = { 0, 0, 0 };

SpatialHashing MGame::spatialHashing(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SPATIAL_HASHING_CELL_SIZE);
GameObjectManager MGame::gameObjectManager;
Camera * MGame::camera;
SDL_Surface * MGame::batImage;
SDL_Surface * MGame::deathImage;
SDL_Surface * MGame::stuff;
SDL_Surface * MGame::projectileImage;

//Loading Files (Sprites, Fonts, Music).
bool MGame::load_files(){
	gScreen = load_image("res/background.png");
	stuff = load_image("res/objectsSpriteSheet.png");
	this->deathImage = load_image("res/deathSprites.png");
	this->batImage = load_image("res/enemySprites.png");
	projectileImage = NULL;
	this->projectileImage = load_image("res/spiritProjectile.png");
	if(gScreen == NULL || stuff == NULL || 
		deathImage == NULL || batImage == NULL ||
		projectileImage == NULL)
		return false;

	font = TTF_OpenFont("res/bloodcrow.ttf", 28);
	if(font == NULL) return false;

	return true;
}

//Object initialization. Passes in loaded files.
bool MGame::init_all_objects()
{
	//Initialize controller
	if(false) 
	{} //TODO: Use conditioning to determine whether to use keyboard, gamepad or other input. -JVL
	else 
		controller = new KeyboardMouse;

	if(!controller->init()) return false;

	//Initialize Player Death and add to master gameobject list.
	deathPlayer = new Death(800, 600, deathImage, controller);
	gameObjectManager.addGameObject(deathPlayer);

	//Load Monsters/Tiles here.
	const int NUMBER_OF_MONSTERS = 3;
	for(int index = 0; index < NUMBER_OF_MONSTERS; index++)
	{
		Unit * newTest = new Bat(batImage, deathPlayer);
		newTest->setPosition((32 * index) % 1600, (index * 25) % (768 * 2) % 1200);
		gameObjectManager.addGameObject(newTest);
	}

	//Distributes the stuff.
	const int X_GAP = 392;
	const int Y_GAP = 292;
	for(int x = 0; x < SCREEN_WIDTH * 2; x++)
	{
		for(int y = 0; y < SCREEN_HEIGHT * 2; y++)
		{
			gameObjectManager.addGameObject(
				new HealthPowerUp(x, y, stuff));
			y += Y_GAP;
		}
		x += X_GAP;
	}

	//Camera!
	camera = new Camera(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0,
		200, deathPlayer);

	return true;
}

//Constructor
MGame::MGame(SDL_Event &tEvent){
	event = tEvent;
}

//Deconstructor
MGame::~MGame(){
	delete controller;
	delete camera;
	SDL_FreeSurface(batImage);
	SDL_FreeSurface(deathImage);
	SDL_FreeSurface(stuff);
	SDL_FreeSurface(projectileImage);
	//TTF_CloseFont(font); //Causes Crash upon exe termination. 
}

bool MGame::main(){
	bool quit = false;

	if(load_files() == false){return 1;}
	if(!init_all_objects()){return 1;}

	while(!quit)
	{
		clock.update();
		if(clock.allowTick())
		{
			while(SDL_PollEvent(&event)){
				if(event.type == SDL_QUIT){
					quit = true;
				}
			}
			//Fill/Reset the screen 
			SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xCD, 0x85, 0x3F ) );

			controller->update();	
			//**********Gameobject/memory handling*********************
			gameObjectManager.update(clock.timeElapsed);
			spatialHashing.update(gameObjectManager.getAllObjectsList());
			
			//Ensure Death does not go off the map.
			if(deathPlayer->pos.x < 0)
				deathPlayer->setPosition(0, deathPlayer->pos.y);
			else if(deathPlayer->pos.x + deathPlayer->collisionBox.w > SCREEN_WIDTH * 2)
				deathPlayer->setPosition(SCREEN_WIDTH * 2 - deathPlayer->collisionBox.w, deathPlayer->pos.y);
			if(deathPlayer->collisionBox.y < 0)
				deathPlayer->setPosition(deathPlayer->pos.x, 0);
			else if(deathPlayer->collisionBox.y + deathPlayer->collisionBox.h > SCREEN_HEIGHT * 2)
				deathPlayer->setPosition(deathPlayer->pos.x, SCREEN_HEIGHT * 2 - deathPlayer->collisionBox.h);

			//*********************************************************
			camera->followObject();

			gameObjectManager.draw(screen, camera->getX(), camera->getY());

			//Render the Health
			std::string s;
			std::stringstream out1;
			out1 << deathPlayer->hitPoints;
			string resultCursorStr = "Health: " + out1.str();
			SDL_Surface *message = TTF_RenderText_Solid( font, resultCursorStr.c_str(), textColor );
			//Render the Kills
			std::stringstream out2;
			out2 << deathPlayer->killCount;
			resultCursorStr = "Score: " + out2.str();
			SDL_Surface *message2 = TTF_RenderText_Solid( font, resultCursorStr.c_str(), textColor );


			//If there was an error in rendering the text
			if( message == NULL )
				return 1;    

			//Apply the images to the screen. Detect end of game.
			if(deathPlayer->hitPoints > 0)
			{
				apply_surface( 0, 100, message, screen );
				apply_surface( 500, 100, message2, screen);
			}
			else
				quit = true;

			if(SDL_Flip(screen) == -1){return 1;}

			//Free any surfaces or anything that may be tacked again
			SDL_FreeSurface( message );
			SDL_FreeSurface( message2 );
		}//end clock
	}//Screen Loop End


	return !quit; //End of Game!
}