#pragma once
#include "Controller.h"
#include "SDL.h"
using namespace std;
#define PI_FLOAT	3.14159f

class KeyboardMouse : public Controller
{
public:
	bool init(void);
	void update(void);
	float detectLookAngle(int,int,int,int);

protected:
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadUp(void); 
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadDown(void);
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadLeft(void);
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadRight(void);
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadPrimary(void);
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadSecondary(void);
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadToggle(void);
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadCancel(void);
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadAbility1(void);
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadAbility2(void);
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadAbility3(void);
	//Reads the SDL Keys from the physical controller and returns whether the keys pressed correspond to the action desired. -JVL
	bool keyReadAbility4(void);

private:
	Uint8* curKeyState;
	Uint8 curMouseState;
};