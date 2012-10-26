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
	bool keyReadDown(void);
	bool keyReadLeft(void);
	bool keyReadRight(void);
	bool keyReadPrimary(void);
	bool keyReadSecondary(void);
	bool keyReadToggle(void);
	bool keyReadCancel(void);
	bool keyReadAbility1(void);
	bool keyReadAbility2(void);
	bool keyReadAbility3(void);
	bool keyReadAbility4(void);

private:
	Uint8* curKeyState;
	Uint8 curMouseState;
};