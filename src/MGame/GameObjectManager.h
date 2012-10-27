#pragma once
#include "GameObjects\GameObject.h"
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

//Manages allocation, deallocation, updates and draws of all game objects in the world.
//This object should be a static object; it's public functions accessible everywhere. -JVL
class GameObjectManager
{
public:
	//Contains the addresses of newly created objects to be added to the world
	static vector<GameObject*> queuedNewGameObjects;
	//Contains gameobjects (Floor)
	vector<GameObject*> activeGameObjectsLayer1; 
	//Contains gameobjects (Player, Player melee attacks)
	vector<GameObject*> activeGameObjectsLayer2; 
	//Contains gameobjects (Enemies)
	vector<GameObject*> activeGameObjectsLayer3;
	//Contains gameobjects (Tall Environments)
	vector<GameObject*> activeGameObjectsLayer4;

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
	//Returns a master list of all objects
	vector<GameObject*> getAllObjectsList();
private:
	//Iterates thru and destroys all objects marked for deletion.
	void deallocateMarkedGameObjects();
	//Transfers new game objects from queue to master list.
	void addQueuedGameObjects();
};