#include "Camera.h"

SDL_Rect Camera::boxPosAndSize;

Camera::Camera(int mapWidthLimit, int mapHeightLimit, int screenWidth, int screenHeight,
		int xPos, int yPos, int sizeOfCameraBox, GameObject * playerObject)
{
	//Map screen info
	widthOfEntireMap = mapWidthLimit;
	heightOfEntireMap = mapHeightLimit;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	//Camera attributes
	boxPosAndSize.x = xPos;
	boxPosAndSize.y = yPos;
	boxPosAndSize.w = sizeOfCameraBox;
	boxPosAndSize.h = sizeOfCameraBox;

	//The thing that the camera will be following.
	objectToFollow = playerObject;
}

Camera::~Camera(){}

void Camera::followObject()
{
	SDL_Rect middleBox;
	middleBox.x = boxPosAndSize.x + (screenWidth - boxPosAndSize.w)/2;
	middleBox.y = boxPosAndSize.y + (screenHeight - boxPosAndSize.h)/2;
	middleBox.w = boxPosAndSize.w; middleBox.h = boxPosAndSize.h;

	//Check x axis displacement
	int xShift = objectToFollow->collisionBox.x - middleBox.x;
	if(xShift > 0) //not a left push
	{
		//then the box is pushing right?
		xShift = (objectToFollow->collisionBox.x + objectToFollow->collisionBox.w) -
		(middleBox.x + middleBox.w);

		if(xShift < 0)
			xShift = 0; //No shift in the x axis. Definitely y axis pushing!
			
	}

	//Check y axis displacement
	int yShift = objectToFollow->collisionBox.y - middleBox.y;
	if(yShift > 0) //not a upper push, then the box is pushing downward.
	{
		yShift = (objectToFollow->collisionBox.y + objectToFollow->collisionBox.h) -
		(middleBox.y + middleBox.h);

		if(yShift < 0)
			yShift = 0;//No shift in the y axis
	}
	//Moves the camera while taking into account edges.
	shift(xShift, yShift);
}

void Camera::shift(int xShift, int yShift)
{
	boxPosAndSize.x += xShift;
	boxPosAndSize.y += yShift;

	//Check left/right borders
	if(boxPosAndSize.x < 0)
		boxPosAndSize.x = 0;
	else if(boxPosAndSize.x > widthOfEntireMap - screenWidth)
		boxPosAndSize.x = widthOfEntireMap - screenWidth;

	//Check top/down borders
	if(boxPosAndSize.y < 0)
		boxPosAndSize.y = 0;
	else if(boxPosAndSize.y > heightOfEntireMap - screenHeight)
		boxPosAndSize.y = heightOfEntireMap - screenHeight;
}

//Gets the x position of the camera (for shifting purposes)
int Camera::getX() const{return boxPosAndSize.x;} 
//gets the y position of the camera (for shifting purposes)
int Camera::getY() const{return boxPosAndSize.y;} 