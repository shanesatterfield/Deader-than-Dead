#include "Controller.h"

//constructor. Call the init function to initialize.-JVL
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
	curMouseState = SDL_GetMouseState(&xCursor,&yCursor);

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
	 prevPressedAbility1 = curPressedAbility1;
	 prevPressedAbility2 = curPressedAbility2;
	 prevPressedAbility3 = curPressedAbility3;
	 prevPressedAbility4 = curPressedAbility4;
}


void Controller::handleDirectionPresses()
{
	//up
	if(Controller::keyReadUp())
		curPressedUp = true;
	else
		curPressedUp = false;

	//down
	if(Controller::keyReadDown())
		curPressedDown = true;
	else
		curPressedDown = false;

	//left
	if(Controller::keyReadLeft())
		curPressedLeft = true;
	else
		curPressedLeft = false;

	//right
	if(Controller::keyReadRight())
		curPressedRight = true;
	else
		curPressedRight = false;
}

float Controller::detectLookAngle(int curPosX, int curPosY, int offsetX, int offsetY)
{
	//http://www.gamedev.net/topic/363179-how-do-i-work-out-the-angle-between-two-points-/
	float directionToLookX = xCursor - (curPosX - offsetX);
	float directionToLookY = yCursor - (curPosY - offsetY);

	return std::atan2(directionToLookY, directionToLookX) * 180.0f/PI_FLOAT;
}


void Controller::handleSelectionPresses()
{
	//Primary (ENTER, SPACE or Left-Click)
	if(curKeyState[SDLK_KP_ENTER] || curKeyState[SDLK_SPACE] || curMouseState&SDL_BUTTON(SDL_BUTTON_LEFT))
		curPressedPrimary = true;
	else
		curPressedPrimary = false;

	//Secondary  (Right-Click)
	if(Controller::keyReadSecondary())
		curPressedSecondary = true;
	else
		curPressedSecondary = false;

	//Toggle
	if(Controller::keyReadToggle())
		curPressedToggle = true;
	else
		curPressedToggle = false;

	//Cancel
	if(Controller::keyReadCancel())
		curPressedCancel = true;
	else
		curPressedCancel = false;

	//KeyAbility1
	if(Controller::keyReadAbility1())
		curPressedAbility1 = true;
	else
		curPressedAbility1 = false;

	//KeyAbility2
	if(Controller::keyReadAbility2())
		curPressedAbility2 = true;
	else
		curPressedAbility2 = false;

	//KeyAbility3
	if(Controller::keyReadAbility3())
		curPressedAbility3 = true;
	else
		curPressedAbility3 = false;

	//KeyAbility4
	if(Controller::keyReadAbility4())
		curPressedAbility4 = true;
	else
		curPressedAbility4 = false;
}

//==Overridable Functions==//
bool Controller::keyReadUp()
{
	return curKeyState[SDLK_UP] || curKeyState[SDLK_w];
}
bool Controller::keyReadDown()
{
	return curKeyState[SDLK_DOWN] || curKeyState[SDLK_s];
}
bool Controller::keyReadLeft()
{
	return curKeyState[SDLK_LEFT] || curKeyState[SDLK_a];
}
bool Controller::keyReadRight()
{
	return curKeyState[SDLK_RIGHT] || curKeyState[SDLK_d];
}
bool Controller::keyReadPrimary()
{
	//http://pbeblog.wordpress.com/2009/06/23/getting-mouse-state-in-sdl/
	return SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(1);
}
bool Controller::keyReadSecondary()
{
	//Secondary (ENTER, SPACE or Left-Click)
	return (
		curKeyState[SDLK_KP_ENTER] || 
		SDL_GetMouseState(NULL,NULL)&SDL_BUTTON(3));
}
bool Controller::keyReadToggle()
{
	return false; //TODO: Is toggle needed?
}
bool Controller::keyReadCancel()
{
	return curKeyState[SDLK_ESCAPE];
}
bool Controller::keyReadAbility1()
{
	return curKeyState[SDLK_SPACE];
}
bool Controller::keyReadAbility2()
{
	return curKeyState[SDLK_LSHIFT];
}
bool Controller::keyReadAbility3()
{
	return curKeyState[SDLK_3];
}
bool Controller::keyReadAbility4()
{
	return curKeyState[SDLK_4];
}

bool Controller::tapUp(){return !prevPressedUp && curPressedUp;}
bool Controller::tapDown(){return !prevPressedDown && curPressedDown;}
bool Controller::tapLeft(){return !prevPressedLeft && curPressedLeft;}
bool Controller::tapRight(){return !prevPressedRight && curPressedRight;}
bool Controller::tapPrimary(){return !prevPressedPrimary && curPressedPrimary;}
bool Controller::tapSecondary(){return !prevPressedSecondary && curPressedSecondary;}
bool Controller::tapToggle(){return !prevPressedToggle && curPressedToggle;}
bool Controller::tapCancel(){return !prevPressedCancel && curPressedCancel;}
bool Controller::tapAbility1(){return !prevPressedAbility1 && curPressedAbility1;}
bool Controller::tapAbility2(){return !prevPressedAbility2 && curPressedAbility2;}
bool Controller::tapAbility3(){return !prevPressedAbility3 && curPressedAbility3;}
bool Controller::tapAbility4(){return !prevPressedAbility4 && curPressedAbility4;}

bool Controller::pushUp(){return curPressedUp;}
bool Controller::pushDown(){return curPressedDown;}
bool Controller::pushLeft(){return curPressedLeft;}
bool Controller::pushRight(){return curPressedRight;}
bool Controller::pushPrimary(){return curPressedPrimary;}
bool Controller::pushSecondary(){return curPressedSecondary;}
bool Controller::pushToggle(){return curPressedToggle;}
bool Controller::pushCancel(){return curPressedCancel;}
bool Controller::pushAbility1(){return curPressedAbility1;}
bool Controller::pushAbility2(){return curPressedAbility2;}
bool Controller::pushAbility3(){return curPressedAbility3;}
bool Controller::pushAbility4(){return curPressedAbility4;}

bool Controller::releaseUp(){return prevPressedUp && !curPressedUp;} 
bool Controller::releaseDown(){return prevPressedDown && !curPressedDown;} 
bool Controller::releaseLeft(){return prevPressedLeft && !curPressedLeft;} 
bool Controller::releaseRight(){return prevPressedRight && !curPressedRight;} 
bool Controller::releasePrimary(){return prevPressedPrimary && !curPressedPrimary;} 
bool Controller::releaseSecondary(){return prevPressedSecondary && !curPressedSecondary;} 
bool Controller::releaseToggle(){return prevPressedToggle && !curPressedToggle;} 
bool Controller::releaseCancel(){return prevPressedCancel && !curPressedCancel;} 
bool Controller::releaseAbility1(){return prevPressedAbility1 && !curPressedAbility1;}
bool Controller::releaseAbility2(){return prevPressedAbility2 && !curPressedAbility2;}
bool Controller::releaseAbility3(){return prevPressedAbility3 && !curPressedAbility3;}
bool Controller::releaseAbility4(){return prevPressedAbility4 && !curPressedAbility4;}