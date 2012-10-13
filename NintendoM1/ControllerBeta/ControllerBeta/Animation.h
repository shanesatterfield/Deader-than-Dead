#pragma once
#include "SDL.h"
#include "SDL_image.h"

using namespace std;

const int FRAMES_PER_MS = 300;

class Animation
{
private:
	SDL_Rect * spriteClip;
	SDL_Surface * spriteSheet; //1-dimmensional sprite array simulating a 2d array.
	SDL_Rect accessFrame(int row, int col); //Calculates the frame in the one dimmensional array.

	int frameWidth;
	int frameHeight;
	int numRows;
	int numColumns;
	Uint32 timeElapsed;

public:
	int curRow;			//usually reflects the current state of the character
	int curColumn;		//indicates the current frame of what it's animating through
	bool enable;		//Turn's the animation on or off

	Animation();
	void switchRow(int rowNumber);	//Sets the animation to display a new row at the beginning. Does not error check for out of bounds.
	bool init(int numColumns, int numRows, int frameWidth, int frameHeight, SDL_Surface * spriteSheet);		//Initializes 
	bool update(Uint32 timeElapsedMs);		//returns a boolean when it has reached the final frame. 
	void draw(int xPos, int yPos, SDL_Surface* destination);

	enum AnimStates
	{
		Idle = 0,
		Down = 1,
		Right = 2,
		Up = 3,
		Left = 4,
		Attack1Down = 5,
		Attack1Right = 6,
		Attack1Up = 7,
		Attack1Left = 8,
		Flinch = 8,
		Dying = 9,
		Dead = 10
	};
};