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

			SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 255,255,255));

			//Fill/Reset the screen 
			SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xCD, 0x85, 0x3F ) );

			controller->update();	
			if(controller->releaseCancel())
				quit = true; //ESC terminates the program
			//**********Gameobject/memory handling*********************
			gameObjectManager.update(clock.timeElapsed);
			spatialHashing.update(gameObjectManager.getAllObjectsList());
			//*********************************************************
			camera->followObject();

			gameObjectManager.draw(screen, camera->getX(), camera->getY());

			//Render the text
			std::string s;
			std::stringstream out1;
			std::stringstream out2;
			out1 << camera->getX();
			out2 << camera->getY();
			string resultCursorStr = "<" + out1.str() + " , " + out2.str() + ">";
			string text = resultCursorStr;

			SDL_Surface *message = TTF_RenderText_Solid( font, text.c_str(), textColor );

			//If there was an error in rendering the text
			if( message == NULL )
			{
				return 1;    
			}

			//Apply the images to the screen
			apply_surface( 0, 150, message, screen );

			if(SDL_Flip(screen) == -1){return 1;}

			//Free any surfaces or anything that may be tacked again
			SDL_FreeSurface( message );
		}//end clock

	}//Screen Loop End

	return !quit;
}

//Loading Files (Sprites, Fonts, Music).
bool MGame::load_files(){
	gScreen = load_image("res/background.png");
	stuff = load_image("res/pumpkin.png");
	this->deathImage = load_image("res/deathSprites.png");
	this->batImage = load_image("res/enemySprites.png");
	if(gScreen == NULL || stuff == NULL || 
		deathImage == NULL || batImage == NULL)
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
	deathPlayer = new Death(400, 300, deathImage, controller);
	gameObjectManager.addGameObject(deathPlayer);

	//Load Monsters/Tiles here.
	const int NUMBER_OF_MONSTERS = 1000;
	for(int index = 0; index < NUMBER_OF_MONSTERS; index++)
	{
		Unit * newTest = new Bat(batImage, deathPlayer);
		newTest->setPosition((32 * index) % 1600, (index * 25) % (768 * 2) % 1200);
		gameObjectManager.addGameObject(newTest);
	}

	//Camera!
	camera = new Camera(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0,
		500, deathPlayer);

	return true;
}

//Constructor
MGame::MGame(SDL_Event &tEvent){
	event = tEvent;
}

//Deconstructor
MGame::~MGame(){
	SDL_FreeSurface(stuff);
}