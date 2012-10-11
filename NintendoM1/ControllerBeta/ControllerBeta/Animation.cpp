#include "Animation.h"

Animation::Animation(){}

bool Animation::init(int numColumns, int numRows, int frameWidth, int frameHeight, SDL_Surface * spriteSheet)
{
	this->spriteSheet = spriteSheet;
	if(spriteSheet == NULL)
		return false; //Failed to initialize.

	this->spriteClip = new SDL_Rect[numRows*numColumns];
	this->numRows = numRows;
	this->numColumns = numColumns;

	curRow = 0;
	curColumn = 0;

	int curFrame = 0;

	for(int y = 0; y < numRows; y++)
	{
		for(int x = 0; x < numColumns; x++)
		{
			//Define the rectangle of the frame.
			spriteClip[curFrame].x = x * frameWidth;
			spriteClip[curFrame].y = y * frameHeight;
			spriteClip[curFrame].w = frameWidth;
			spriteClip[curFrame].h = frameHeight;
			
			//increment to the next frame in the one dimm array.
			curFrame++;
		}
	}

	this->timeElapsed = 0;

	//Initialization complete!
	return true;
}

bool Animation::update(Uint32 timeElapsedMs)
{
	bool frameCycleCompleted = false;
	if(enable)
	{
		timeElapsed += timeElapsedMs; //Increment the timer.
		if(timeElapsed >= FRAMES_PER_MS)
		{
			//Increment to next frame within the row.
			this->curColumn = ((curColumn +1) % numColumns);
			
			//Check if it's the final frame.
			if(this->curColumn >= numColumns - 1)
				frameCycleCompleted = true;

			//Reset the timer
			timeElapsed = 0;
		}
	}
	return frameCycleCompleted; //Returns when the final frame was hit. Useful for single-run thru rows.
}

SDL_Rect Animation::accessFrame(int row, int col)
{
	return spriteClip[row * numColumns + col];
}

void Animation::switchRow(int rowNumber)
{
	curRow = rowNumber;
	curColumn = 0;
}

void Animation::draw(int xPos, int yPos, SDL_Surface* destination)
{
	SDL_Rect drawPos; //declaration
	drawPos.x = xPos;
	drawPos.y = yPos;

	//SDL_BlitSurface(The whole sheet, the section to display, the screen, where to draw on the screen);
	SDL_BlitSurface(spriteSheet, &accessFrame(curRow, curColumn), destination, &drawPos );
}
