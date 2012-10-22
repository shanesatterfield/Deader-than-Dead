#include "GameObjectManager.h"

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
			tempObject->cleanUp();
			delete tempObject; //Gone from memory! Do not try to access this again!
		}
}

void GameObjectManager::addQueuedGameObjects()
{
	int numberObjects = queuedNewGameObjects.size();
	for(int i = 0; i < numberObjects; i++) //Transfers
		activeGameObjects.push_back(queuedNewGameObjects[i]);
	queuedNewGameObjects.clear(); //resets list for future transfers.
}

void GameObjectManager::addGameObject(GameObject * newObjectCopy)
{
	queuedNewGameObjects.push_back(newObjectCopy);
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

