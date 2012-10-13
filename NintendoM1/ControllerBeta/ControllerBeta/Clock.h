//http://stackoverflow.com/questions/86582/singleton-how-should-it-be-used

#pragma once
#include "SDL.h"

#define TIME_FOR_60_FPS 16.6666

class Clock
{
public:
	//Constructor
	Clock();
	//Initializes the SDL_Timer. If it was already initialized, the instructions still runs. It doesn't seem to blow up the game.
	bool init();
	//Determines whether enough time has passed to allow the update/draw cycle to execute. When true, it resets the raw counter.
	bool allowTick();
	//States how much time has elpased since the prevous allowed update cycle; overriden when allowTick would be true.
	Uint32 timeElapsed;
	void update();

private:
	Uint32 curTimeStamp;
	Uint32 prevTimeStamp;
	Uint32 totalMsCount; //The raw count. This will reset to 0 so that it can count the ticks.
};