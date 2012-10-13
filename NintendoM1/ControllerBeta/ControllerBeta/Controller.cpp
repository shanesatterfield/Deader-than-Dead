#include "Controller.h"

//constructor. Call the init function to initialize.-JVL
Controller::Controller(){} 

bool Controller::init()
{
	initStates();
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
     curPressedAbility1 = false;
	 curPressedAbility2 = false;
	 curPressedAbility3 = false;
	 curPressedAbility4 = false;
	//whether the button is up.
	 prevPressedUp= false;
	 prevPressedDown= false;
	 prevPressedLeft= false;
	 prevPressedRight= false;
	 prevPressedPrimary= false;
	 prevPressedSecondary= false;
	 prevPressedToggle= false;
	 prevPressedCancel = false;
	 prevPressedAbility1 = false;
	 prevPressedAbility2 = false;
	 prevPressedAbility3 = false;
	 prevPressedAbility4 = false;
}

void Controller::update()
{
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
	curPressedUp = keyReadUp(); 
	curPressedDown = keyReadDown();
	curPressedLeft = keyReadLeft();
	curPressedRight = keyReadRight();

	//Tony's code. Keep and study for later. -JVL
	//curPressedUp = &Controller::keyReadUp;
	//curPressedDown = &Controller::keyReadDown;
	//curPressedLeft = &Controller::keyReadLeft;
	//curPressedRight = &Controller::keyReadRight;
}

void Controller::handleSelectionPresses()
{
	curPressedPrimary = keyReadPrimary();
	curPressedSecondary = keyReadSecondary();
	curPressedToggle = keyReadToggle();
	curPressedCancel = keyReadCancel();
	curPressedAbility1 = keyReadAbility1();
	curPressedAbility2 = keyReadAbility2();
	curPressedAbility3 = keyReadAbility3();
	curPressedAbility4 = keyReadAbility4();
}

//Cheap workaround to abstraction. I had linker issues that I couldn't fix. -JVL
bool Controller::keyReadUp(){return false;}
bool Controller::keyReadDown(){return false;}
bool Controller::keyReadLeft(){return false;}
bool Controller::keyReadRight(){return false;}
bool Controller::keyReadPrimary(){return false;}
bool Controller::keyReadSecondary(){return false;}
bool Controller::keyReadToggle(){return false;}
bool Controller::keyReadCancel(){return false;}
bool Controller::keyReadAbility1(){return false;}
bool Controller::keyReadAbility2(){return false;}
bool Controller::keyReadAbility3(){return false;}
bool Controller::keyReadAbility4(){return false;}

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