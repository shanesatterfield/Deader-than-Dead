#include "Controller.h"

//empty constructor. Call the init function to initialize.-JVL
Controller::Controller(){} 


bool Controller::init()
{
	curKeyState = SDL_GetKeyState(NULL);
	xCursor= 0; yCursor= 0;
	curMouseState = SDL_GetMouseState(&xCursor,&yCursor);
	initStates();

	//Initialization verification.
	if (curKeyState == NULL)
		return false; //Failed to initialize
	
	return true;
}

void Controller::initStates()
{
	//Whether the button is down. Note, if any of the keys corresponding with the button is down, then it will register as down all the time.
	 curPressedUp= false; 
	 curPressedDown= false;
	 curPressedLeft= false;
	 curPressedRight= false;
	 curPressedPrimary= false;
	 curPressedSecondary= false;
	 curPressedToggle= false;
	 curPressedCancel= false;
	//whether the button is up.
	 prevPressedUp= false;
	 prevPressedDown= false;
	 prevPressedLeft= false;
	 prevPressedRight= false;
	 prevPressedPrimary= false;
	 prevPressedSecondary= false;
	 prevPressedToggle= false;
	 prevPressedCancel= false;

	vector<int> moveDirection = vector<int>(0,0);
	vector<int> lookDirection = vector<int>(0,0);
}

void Controller::update()
{
	curToPrevStates(); //Sets the current states to previous states.
	SDL_PumpEvents(); //updates the current keystate with the key state of the current frame.

	//handle direction presses
	handleDirectionPresses();
	handleSelectionPresses();
}

void Controller::curToPrevStates()
{
	 prevPressedUp = curPressedUp;
	 prevPressedDown = curPressedDown;
	 prevPressedLeft = curPressedLeft;
	 prevPressedRight = curPressedRight;
	 prevPressedPrimary = curPressedPrimary;
	 prevPressedSecondary = curPressedSecondary;
	 prevPressedToggle = curPressedToggle;
	 prevPressedCancel = curPressedCancel;
}


void Controller::handleDirectionPresses()
{
	//up
	if(curKeyState[SDLK_UP])
		curPressedUp = true;
	else
		curPressedUp = false;

	//down
	if(curKeyState[SDLK_DOWN])
		curPressedDown = true;
	else
		curPressedDown = false;

	//left
	if(curKeyState[SDLK_LEFT])
		curPressedLeft = true;
	else
		curPressedLeft = false;

	//right
	if(curKeyState[SDLK_RIGHT])
		curPressedRight = true;
	else
		curPressedRight = false;
}

void Controller::handleSelectionPresses()
{
	//Secondary (ENTER, SPACE or Left-Click)
	if(curKeyState[SDLK_KP_ENTER] || curKeyState[SDLK_SPACE] || curMouseState&SDL_BUTTON(SDL_BUTTON_LEFT))
		curPressedPrimary = true;
	else
		curPressedPrimary = false;

	//Secondary  (Right-Click)
	//http://pbeblog.wordpress.com/2009/06/23/getting-mouse-state-in-sdl/
	if(curMouseState&SDL_BUTTON(SDL_BUTTON_RIGHT))
		curPressedSecondary = true;
	else
		curPressedSecondary = false;

	//Toggle
	if(curKeyState[SDLK_TAB] || curKeyState[1])
		curPressedToggle = true;
	else
		curPressedToggle = false;

	//Cancel
	if(curKeyState[SDLK_ESCAPE])
		curPressedCancel = true;
	else
		curPressedCancel = false;
}
bool Controller::tapUp(){return !prevPressedUp && curPressedUp;}
bool Controller::tapDown(){return !prevPressedDown && curPressedDown;}
bool Controller::tapLeft(){return !prevPressedLeft && curPressedLeft;}
bool Controller::tapRight(){return !prevPressedRight && curPressedRight;}
bool Controller::tapPrimary(){return !prevPressedPrimary && curPressedPrimary;}
bool Controller::tapSecondary(){return !prevPressedSecondary && curPressedSecondary;}
bool Controller::tapToggle(){return !prevPressedToggle && curPressedToggle;}
bool Controller::tapCancel(){return !prevPressedCancel && curPressedCancel;}
bool Controller::pushUp(){return curPressedUp;}
bool Controller::pushDown(){return curPressedDown;}
bool Controller::pushLeft(){return curPressedLeft;}
bool Controller::pushRight(){return curPressedRight;}
bool Controller::pushPrimary(){return curPressedPrimary;}
bool Controller::pushSecondary(){return curPressedSecondary;}
bool Controller::pushToggle(){return curPressedToggle;}
bool Controller::pushCancel(){return curPressedCancel;}
bool Controller::releaseUp(){return prevPressedUp && !curPressedUp;} 
bool Controller::releaseDown(){return prevPressedDown && !curPressedDown;} 
bool Controller::releaseLeft(){return prevPressedLeft && !curPressedLeft;} 
bool Controller::releaseRight(){return prevPressedRight && !curPressedRight;} 
bool Controller::releasePrimary(){return prevPressedPrimary && !curPressedPrimary;} 
bool Controller::releaseSecondary(){return prevPressedSecondary && !curPressedSecondary;} 
bool Controller::releaseToggle(){return prevPressedToggle && !curPressedToggle;} 
bool Controller::releaseCancel(){return prevPressedCancel && !curPressedCancel;} 


//bool Controller::releaseLeft()
//{
//	if(prevKeyState[SDLK_LEFT] && !curKeyState[SDLK_LEFT])
//		return true;
//	return false;
//}