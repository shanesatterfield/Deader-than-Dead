//The headers
#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Animation.h"
#include "Camera.h"
#include "Clock.h"
#include "GameObjectManager.h"
#include "Collision/SpatialHashing.h"
#include "Controller/Controller.h"
#include "Controller/KeyboardMouse.h"
#include "GameObjects/Units/Bat.h"
#include "GameObjects/Units/Death.h"
#include "GameObjects/Units/TestMonster.h"
#include <string>
#include <stdlib.h>
#include <sstream>
#include <vector>

using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int SCREEN_BPP = 32;
const int SPATIAL_HASHING_CELL_SIZE = 128;


const int SPEED = 400; //pixels per second

//The surfaces
SDL_Surface *dots = NULL;
SDL_Surface *screen = NULL;

//The event structure
SDL_Event event;

//The font that's going to be used
TTF_Font *font = NULL;

//The color of the font
SDL_Color textColor = { 0, 0, 0 };

//New features!
Controller * controller;
Animation * animationTest;
Death * deathPlayer;
Clock clock;
SDL_Surface *blackTest = NULL;
vector<GameObject*> listOfGameObjects;
static SpatialHashing spatialHashing(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SPATIAL_HASHING_CELL_SIZE);
static GameObjectManager gameObjectManager;
static Camera * camera;
static SDL_Surface * batImage;

SDL_Surface *load_image( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return the optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

	 //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        return false;    
    }


	//Initialize controller
	if(false) 
		{} //TODO: Use conditioning to determine whether to use keyboard, gamepad or other input. -JVL
	else 
		controller = new KeyboardMouse;

	if(!controller->init())
		return false;

	animationTest = new Animation();
	if(!animationTest->init(3, 5,64,64, load_image( "Sprites//giraffe.png" )))
		return false;

	if(!clock.init()) //initialize the clock.
		return false;

	//Initialize GameObjects
	deathPlayer = new Death(700, 700, load_image( "Sprites//deathSprites.png" ), controller);

	//Add gameobjects
	gameObjectManager.addGameObject(deathPlayer);
	const int NUMBER_OF_MONSTERS = 1000;
	batImage = load_image( "Sprites//enemySprites.png" );
	for(int index = 0; index < NUMBER_OF_MONSTERS; index++)
	{
		//There should probably be a central location to store the images instead of loading
		//the texture into each one...
		Unit * newTest = new Bat(batImage);
		newTest->setPosition((25 * index) % 2048, (index * 25) % (768 * 2));

		gameObjectManager.addGameObject(newTest);
	}

	//Camera!
	camera = new Camera(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0,
		300, deathPlayer);
	

    //Set the window caption
    SDL_WM_SetCaption( "Controller BETA Joshua Liong", NULL );

	//Other test stuff
	blackTest = load_image("Sprites//BlackTest.png");

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the sprite map
    dots = load_image( "dots.png" );

	//Open the font
    font = TTF_OpenFont( "lazy.ttf", 28 );

    //If there was an problem loading the sprite map
    if( dots == NULL || font == NULL)
    {
        return false;
    }

    //If eveything loaded fine
    return true;
}

void clean_up()
{
    //Free the sprite map
    SDL_FreeSurface( dots );

	//Free camera
	delete camera;

	//Close the font that was used
    TTF_CloseFont( font );
    
    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

/*
int main( int argc, char* args[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

 
	int i = 0;
	float xPos = 0;
	float yPos = 0;

    //Apply the sprites to the screen
	Uint8* keystates = SDL_GetKeyState(NULL);
	while(!quit) 		//While the user hasn't quit
	{
		clock.update();
		if(clock.allowTick()) //time based stuff goes in here.
		{
			//Fill/Reset the screen 
			SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xCD, 0x85, 0x3F ) );

			//Timer
			Uint32 timeElapsedMs = clock.timeElapsed;

			//While there's events to handle
			while( SDL_PollEvent( &event ) )
			{
				//If the user has Xed out the window
				if( event.type == SDL_QUIT )
				{
					//Quit the program
					quit = true;
				}
			}

			controller->update();		
			//**********Gameobject/memory handling*********************
			gameObjectManager.update(timeElapsedMs);
			spatialHashing.update(gameObjectManager.activeGameObjects);
			//*********************************************************
			camera->followObject();

			if(controller->releaseCancel())
			{
				quit = true; //ESC terminates the program
			}

			int numTotalObjects = listOfGameObjects.size();
			
			animationTest->update(timeElapsedMs);
			animationTest->draw(xPos,yPos, screen); 
			gameObjectManager.draw(screen, camera->getX(), camera->getY());

			if(false) //DEBUG BLOCK. It should have a square at the center of the sprite.
			{
				SDL_Rect playerLocation;
				SDL_Rect collisionBoxClip;
				collisionBoxClip.x = 0; 
				collisionBoxClip.y = 0; 
				collisionBoxClip.w = deathPlayer->collisionBox.w;
				collisionBoxClip.h = deathPlayer->collisionBox.h;
				playerLocation.x = deathPlayer->collisionBox.x;
				playerLocation.y = deathPlayer->collisionBox.y;
				SDL_BlitSurface(blackTest, &collisionBoxClip,
					screen, &playerLocation);
			}

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
		
			//Update the screen
			if( SDL_Flip( screen ) == -1 )
			{
				return 1;
			}

			//Free any surfaces or anything that may be tacked again
			SDL_FreeSurface( message );
    
		}//end clockTick check
	}
    //Free the images and quit SDL
    clean_up();

    return 0;
}
*/