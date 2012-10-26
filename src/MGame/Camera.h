#pragma once
#include "SDL.h"
#include "GameObjects\GameObject.h"
#include "Collision\CollisionDetection.h"

class Camera
{
private:
	int widthOfEntireMap;
	int heightOfEntireMap;
	int screenWidth;
	int screenHeight;
	
public:
	//The Box represents the camera borders. If the player goes beyond the invisible box, the box position will shift to keep the character in the box.
	static SDL_Rect boxPosAndSize;
	//The position of the object will be regularly pinged so that the camera can follow it. Be careful when deallocating this object elsewhere.
	GameObject * objectToFollow;

	Camera(int mapWidthLimit, int mapHeightLimit, int screenWidth, int ScreenHeight,
		int xPos, int yPos, int sizeOfCameraBox, GameObject * playerObject); //constructor
	~Camera(); //destructor (is it necessary?)
	void followObject(); //Pings the objectToFollow's position and makes shifts accordingly.
	void shift(int xShift, int yShift); //Shifts the camera while preventing the camera from going beyond the edge of the map.
	int getX() const; //Gets the x position of the camera (for shifting purposes)
	int getY() const; //gets the y position of the camera (for shifting purposes)
};