#include "SDL.h"
#include <vector>
using namespace std;

class Controller
{
public:
	int xCursor;
	int yCursor;

	vector<int> moveDirection;
	float lookRadians;

	//Empty Constructor. Call the init() function to initialize. -JVL
	Controller(); 
	//Initializes all the states to false.
	bool init();
	//Saves the previous frame's state and updates the current frame's controller state.
	void update();

/*Taps*/
	//Taps ring true on the frame of the initial push and false on the next frame. Taps ring true after the button is released then pushed. -JVL
	bool tapUp(); 
	//Taps ring true on the frame of the initial push and false on the next frame. Taps ring true after the button is released then pushed. -JVL
	bool tapDown();
	//Taps ring true on the frame of the initial push and false on the next frame. Taps ring true after the button is released then pushed. -JVL
	bool tapLeft();
	//Taps ring true on the frame of the initial push and false on the next frame. Taps ring true after the button is released then pushed. -JVL
	bool tapRight();
	//Taps ring true on the frame of the initial push and false on the next frame. Taps ring true after the button is released then pushed. -JVL
	bool tapPrimary();
	//Taps ring true on the frame of the initial push and false on the next frame. Taps ring true after the button is released then pushed. -JVL
	bool tapSecondary();
	//Taps ring true on the frame of the initial push and false on the next frame. Taps ring true after the button is released then pushed. -JVL
	bool tapToggle();
	//Taps ring true on the frame of the initial push and false on the next frame. Taps ring true after the button is released then pushed. -JVL
	bool tapCancel();
	//Taps ring true on the frame of the initial push and false on the next frame. Taps ring true after the button is released then pushed. -JVL
	bool tapAbility1();
	//Taps ring true on the frame of the initial push and false on the next frame. Taps ring true after the button is released then pushed. -JVL
	bool tapAbility2();
	//Taps ring true on the frame of the initial push and false on the next frame. Taps ring true after the button is released then pushed. -JVL
	bool tapAbility3();
	//Taps ring true on the frame of the initial push and false on the next frame. Taps ring true after the button is released then pushed. -JVL
	bool tapAbility4();
	
/*Pushes*/
	//Push ring true on the frame with initial push and false as soon as it is released. -JVL
	bool pushUp();
	//Push ring true on the frame with initial push and false as soon as it is released. -JVL
	bool pushDown();
	//Push ring true on the frame with initial push and false as soon as it is released. -JVL
	bool pushLeft();
	//Push ring true on the frame with initial push and false as soon as it is released. -JVL
	bool pushRight();
	//Push ring true on the frame with initial push and false as soon as it is released. -JVL
	bool pushPrimary();
	//Push ring true on the frame with initial push and false as soon as it is released. -JVL
	bool pushSecondary();
	//Push ring true on the frame with initial push and false as soon as it is released. -JVL
	bool pushToggle();
	//Push ring true on the frame with initial push and false as soon as it is released. -JVL
	bool pushCancel();
	bool pushAbility1();
	bool pushAbility2();
	bool pushAbility3();
	bool pushAbility4();

/*Releases*/
	//Release rings true as soon as the button is released then false on the next frame. -JVL
	bool releaseUp(); 
	//Release rings true as soon as the button is released then false on the next frame. -JVL
	bool releaseDown();
	//Release rings true as soon as the button is released then false on the next frame. -JVL
	bool releaseLeft();
	//Release rings true as soon as the button is released then false on the next frame. -JVL
	bool releaseRight();
	//Release rings true as soon as the button is released then false on the next frame. -JVL
	bool releasePrimary();
	//Release rings true as soon as the button is released then false on the next frame. -JVL
	bool releaseSecondary();
	//Release rings true as soon as the button is released then false on the next frame. -JVL
	bool releaseToggle();
	//Release rings true as soon as the button is released then false on the next frame. -JVL
	bool releaseCancel();
	bool releaseAbility1();
	bool releaseAbility2();
	bool releaseAbility3();
	bool releaseAbility4();
	//It reads in the direction of of the controller/keys that dictate where the player is looking and returns a float in degrees. 0 degrees face north. -JVL
	float detectLookAngle(int xPosition, int yPosition, int offsetX, int offsetY);

protected:
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadUp(); 
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadDown();
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadLeft();
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadRight();
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadPrimary();
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadSecondary();
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadToggle();
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadCancel();
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadAbility1();
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadAbility2();
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadAbility3();
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadAbility4();

private:
	Uint8* curKeyState;
	Uint8 curMouseState;
	void initStates();
	void curToPrevStates();
	void updateStates();
	void handleDirectionPresses();
	void handleSelectionPresses();

	vector<int> updateMoveDirection();
	float updateLookDirection();

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