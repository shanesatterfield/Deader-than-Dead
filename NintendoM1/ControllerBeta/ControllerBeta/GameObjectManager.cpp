#include "GameObjectManager.h"

vector<GameObject*> GameObjectManager::queuedNewGameObjects;

void GameObjectManager::update(Uint32 timeElapsedMs)
{
	//deallocates objects that should be gone.
	deallocateMarkedGameObjects();

	//Allocates new objects.
	addQueuedGameObjects();

	//Updates all objects on field.
	updateAllGameObjects(timeElapsedMs);
}

void GameObjectManager::deallocateMarkedGameObjects()
{
	//Iterate through all the objects
	int size = activeGameObjects.size();
	for(int i = 0; i < size; i++)
		if(activeGameObjects[i]->deallocate)
		{
			GameObject * tempObject = activeGameObjects[i];
			activeGameObjects.erase(activeGameObjects.begin() + i);
			delete tempObject; //Gone from memory! Do not try to access this again!
			size--; i--; //moves the for loop pointer back one notch compensating for the erasure so that it does not go out of bounds
		}
}

void GameObjectManager::addQueuedGameObjects()
{
	int numberObjects = GameObjectManager::queuedNewGameObjects.size();
	for(int i = 0; i < numberObjects; i++) //Transfers
		activeGameObjects.push_back(GameObjectManager::queuedNewGameObjects[i]);
	GameObjectManager::queuedNewGameObjects.clear(); //resets list for future transfers.
}

void GameObjectManager::addGameObject(GameObject * newObjectCopy)
{
	GameObjectManager::queuedNewGameObjects.push_back(newObjectCopy);
}

void GameObjectManager::draw(SDL_Surface *destination)
{
	int size = activeGameObjects.size();
	for(int i = 0; i < size; i++)
		activeGameObjects[i]->draw(destination);
}

void GameObjectManager::updateAllGameObjects(Uint32 timeElapsedMs)
{
	int size = activeGameObjects.size();
	for(int i = 0; i < size; i++)
		activeGameObjects[i]->update(timeElapsedMs);
}

