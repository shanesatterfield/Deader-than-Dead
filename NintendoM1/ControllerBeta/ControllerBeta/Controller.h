#pragma once

#include "SDL.h"

using namespace std;

class Controller
{
public:
	int xCursor;
	int yCursor;

	//Empty Constructor. Call the init() function to initialize. -JVL
	Controller(); 
	//Initializes all the states to false.
	virtual bool init();
	//Saves the previous frame's state and updates the current frame's controller state.
	virtual void update();
	//It reads in the direction of of the controller/keys that dictate where the player is looking and returns a float in degrees. 0 degrees faces east. 180 degrees face west. -90 degrees faces north. 90 degrees face north. -JVL
	virtual float detectLookAngle(int xPosition, int yPosition, int offsetX, int offsetY)=0;


/*Taps*/
	//Taps ring true on the frame of the initial push and false on the next frame. Taps ring true after the button is released then pushed. -JVL
	bool tapUp(); 
	bool tapDown();
	bool tapLeft();
	bool tapRight();
	bool tapPrimary();
	bool tapSecondary();
	bool tapToggle();
	bool tapCancel();
	bool tapAbility1();
	bool tapAbility2();
	bool tapAbility3();
	bool tapAbility4();
	
/*Pushes*/
	//Push ring true on the frame with initial push and false as soon as it is released. -JVL
	bool pushUp();
	bool pushDown();
	bool pushLeft();
	bool pushRight();
	bool pushPrimary();
	bool pushSecondary();
	bool pushToggle();
	bool pushCancel();
	bool pushAbility1();
	bool pushAbility2();
	bool pushAbility3();
	bool pushAbility4();

/*Releases*/
	bool releaseUp(); 
	bool releaseDown();
	bool releaseLeft();
	bool releaseRight();
	bool releasePrimary();
	bool releaseSecondary();
	bool releaseToggle();
	bool releaseCancel();
	bool releaseAbility1();
	bool releaseAbility2();
	bool releaseAbility3();
	bool releaseAbility4();
	
protected: //Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	virtual bool keyReadUp();
	virtual bool keyReadDown();
	virtual bool keyReadLeft();
	virtual bool keyReadRight();
	virtual bool keyReadPrimary();
	virtual bool keyReadSecondary();
	virtual bool keyReadToggle();
	virtual bool keyReadCancel();
	virtual bool keyReadAbility1();
	virtual bool keyReadAbility2();
	virtual bool keyReadAbility3();
	virtual bool keyReadAbility4();

	void initStates();
	void curToPrevStates();
	void handleDirectionPresses();
	void handleSelectionPresses();

	float updateLookDirection();

private:
/*Currently pressed states*/
	//States whether the button is pressed in the current frame. -JVL
	bool curPressedUp; 
	//States whether the button is pressed in the current frame. -JVL
	bool curPressedDown;
	//States whether the button is pressed in the current frame. -JVL
	bool curPressedLeft;
	//States whether the button is pressed in the current frame. -JVL
	bool curPressedRight;
	//States whether the button is pressed in the current frame. -JVL
	bool curPressedPrimary;
	//States whether the button is pressed in the current frame. -JVL
	bool curPressedSecondary;
	//States whether the button is pressed in the current frame. -JVL
	bool curPressedToggle;
	//States whether the button is pressed in the current frame. -JVL
	bool curPressedCancel;
	//States whether the button is pressed in the current frame. -JVL
	bool curPressedAbility1;
	//States whether the button is pressed in the current frame. -JVL
	bool curPressedAbility2;
	//States whether the button is pressed in the current frame. -JVL
	bool curPressedAbility3;
	//States whether the button is pressed in the current frame. -JVL
	bool curPressedAbility4;
	
/*Previously pressed states*/	
	//States whether the button is pressed in the PREVIOUS frame. -JVL
	bool prevPressedUp;
	//States whether the button is pressed in the PREVIOUS frame. -JVL
	bool prevPressedDown;
	//States whether the button is pressed in the PREVIOUS frame. -JVL
	bool prevPressedLeft;
	//States whether the button is pressed in the PREVIOUS frame. -JVL
	bool prevPressedRight;
	//States whether the button is pressed in the PREVIOUS frame. -JVL
	bool prevPressedPrimary;
	//States whether the button is pressed in the PREVIOUS frame. -JVL
	bool prevPressedSecondary;
	//States whether the button is pressed in the PREVIOUS frame. -JVL
	bool prevPressedToggle;
	//States whether the button is pressed in the PREVIOUS frame. -JVL
	bool prevPressedCancel;
	//States whether the button is pressed in the PREVIOUS frame. -JVL
	bool prevPressedAbility1;
	//States whether the button is pressed in the PREVIOUS frame. -JVL
	bool prevPressedAbility2;
	//States whether the button is pressed in the PREVIOUS frame. -JVL
	bool prevPressedAbility3;
	//States whether the button is pressed in the PREVIOUS frame. -JVL
	bool prevPressedAbility4;
};