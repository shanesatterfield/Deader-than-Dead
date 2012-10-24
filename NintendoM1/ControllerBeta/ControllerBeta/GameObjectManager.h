#pragma once
#include "GameObjects\GameObject.h"
#include <vector>

using namespace std;

//Manages allocation, deallocation, updates and draws of all game objects in the world.
//This object should be a static object; it's public functions accessible everywhere. -JVL
class GameObjectManager
{
public:
	//Contains the addresses of newly created objects to be added to the world
	static vector<GameObject*> queuedNewGameObjects;
	//Contains the addresses of active game objects updating/drawing in the world.
	vector<GameObject*> activeGameObjects;

	//Manages deallocation, allocation and updates of gameObjects in the world.
	void update(Uint32 timeElapsedMs);
	//Updates all the gameObjects in the world
	void updateAllGameObjects(Uint32 timeElapsedMs); 
	//Draws all the gameobjects in the world.
	void draw(SDL_Surface *destination, int xOffset, int yOffset);
	//Deallocates all the gameobjects in the world and in the queue.
	void cleanUp();
	//Adds a gameObject to the queue so that it may be running by the next frame.
	void addGameObject(GameObject * newObjectCopy);
	//Tells you the number of gameobjects, including all tiles and enemies on the field.
	int getNumberOfObjects();

private:
	//Iterates thru and destroys all objects marked for deletion.
	void deallocateMarkedGameObjects();
	//Transfers new game objects from queue to master list.
	void addQueuedGameObjects();
};