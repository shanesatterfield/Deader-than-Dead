#include "KeyboardMouse.h"
#include <vector>
using namespace std;

bool KeyboardMouse::init(void)
{
	if(!Controller::init()) //base class init. Keyboard specific stuff goes below.
		return false; //something failed to initialize.

	curKeyState = SDL_GetKeyState(NULL);
	xCursor= 0; yCursor= 0;
	curMouseState = SDL_GetMouseState(&xCursor,&yCursor);

	//Initialization verification.
	if (curKeyState == NULL)
		return false; //Failed to initialize

	//Initialization successful!
	return true;
}

void KeyboardMouse::update(void)
{
	SDL_PumpEvents(); //updates the current keystate with the key state of the current frame.
	curMouseState = SDL_GetMouseState(&xCursor,&yCursor); //Gets the current mouse state.
	handleDirectionPresses(); //goes to base at controller.cpp 
	handleSelectionPresses();
}

float KeyboardMouse::detectLookAngle(int curPosX, int curPosY, int offsetX, int offsetY)
{
	//http://www.gamedev.net/topic/363179-how-do-i-work-out-the-angle-between-two-points-/
	float directionToLookX = xCursor - (curPosX - offsetX);
	float directionToLookY = yCursor - (curPosY - offsetY);

	return std::atan2(directionToLookY, directionToLookX) * 180.0f/PI_FLOAT;
}

//--- Key Presses mapped to input. ---
bool KeyboardMouse::keyReadUp(void)
{
	return curKeyState[SDLK_UP] || curKeyState[SDLK_w] != 0;;
}
bool KeyboardMouse::keyReadDown(void)
{
	return curKeyState[SDLK_DOWN] || curKeyState[SDLK_s] != 0;;
}
bool KeyboardMouse::keyReadLeft(void)
{
	return curKeyState[SDLK_LEFT] || curKeyState[SDLK_a] != 0;;
}
bool KeyboardMouse::keyReadRight(void)
{
	return curKeyState[SDLK_RIGHT] || curKeyState[SDLK_d] != 0;;
}
bool KeyboardMouse::keyReadPrimary(void)
{
	//http://pbeblog.wordpress.com/2009/06/23/getting-mouse-state-in-sdl/
	return SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(1);
}
bool KeyboardMouse::keyReadSecondary(void)
{
	//Secondary (ENTER, SPACE or Left-Click)
	return (
		curKeyState[SDLK_KP_ENTER] != 0 || 
		SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(3) != 0);
}
bool KeyboardMouse::keyReadToggle(void)
{
	return false; //TODO: Is toggle needed?
}
bool KeyboardMouse::keyReadCancel(void)
{
	return curKeyState[SDLK_ESCAPE] != 0;
}
bool KeyboardMouse::keyReadAbility1(void)
{
	return curKeyState[SDLK_SPACE] != 0;
}
bool KeyboardMouse::keyReadAbility2(void)
{
	return curKeyState[SDLK_LSHIFT] != 0;
}
bool KeyboardMouse::keyReadAbility3(void)
{
	return curKeyState[SDLK_3] != 0;
}
bool KeyboardMouse::keyReadAbility4(void)
{
	return curKeyState[SDLK_4] != 0;
}