#include "GameObjectManager.h"

using namespace std;

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
	int size = activeGameObjectsLayer1.size();
	for(int i = 0; i < size; i++)
		if(activeGameObjectsLayer1[i]->deallocate)
		{
			GameObject * tempObject = activeGameObjectsLayer1[i];
			activeGameObjectsLayer1.erase(activeGameObjectsLayer1.begin() + i);
			delete tempObject; //Gone from memory! Do not try to access this again!
			size--; i--; //moves the for loop pointer back one notch compensating for the erasure so that it does not go out of bounds
		}

	size = activeGameObjectsLayer2.size();
	for(int i = 0; i < size; i++)
		if(activeGameObjectsLayer2[i]->deallocate)
		{
			GameObject * tempObject = activeGameObjectsLayer2[i];
			activeGameObjectsLayer2.erase(activeGameObjectsLayer2.begin() + i);
			delete tempObject; //Gone from memory! Do not try to access this again!
			size--; i--; //moves the for loop pointer back one notch compensating for the erasure so that it does not go out of bounds
		}

	size = activeGameObjectsLayer3.size();
	for(int i = 0; i < size; i++)
		if(activeGameObjectsLayer3[i]->deallocate)
		{
			GameObject * tempObject = activeGameObjectsLayer3[i];
			activeGameObjectsLayer3.erase(activeGameObjectsLayer3.begin() + i);
			delete tempObject; //Gone from memory! Do not try to access this again!
			size--; i--; //moves the for loop pointer back one notch compensating for the erasure so that it does not go out of bounds
		}

	size = activeGameObjectsLayer4.size();
	for(int i = 0; i < size; i++)
		if(activeGameObjectsLayer4[i]->deallocate)
		{
			GameObject * tempObject = activeGameObjectsLayer4[i];
			activeGameObjectsLayer4.erase(activeGameObjectsLayer4.begin() + i);
			delete tempObject; //Gone from memory! Do not try to access this again!
			size--; i--; //moves the for loop pointer back one notch compensating for the erasure so that it does not go out of bounds
		}
}

void GameObjectManager::addQueuedGameObjects()
{
	int numberObjects = GameObjectManager::queuedNewGameObjects.size();
	for(int i = 0; i < numberObjects; i++) //Transfers
	{
		int thisObjectType = GameObjectManager::queuedNewGameObjects[i]->type;

		if(thisObjectType >= 1 && thisObjectType <= 99)//Monsters, Power ups
			activeGameObjectsLayer3.push_back(GameObjectManager::queuedNewGameObjects[i]);
		else if(thisObjectType >= 300) //Attacks
			activeGameObjectsLayer2.push_back(GameObjectManager::queuedNewGameObjects[i]);
		else if(thisObjectType >= 100 && thisObjectType <= 199) //UpperLayerFloor
			activeGameObjectsLayer4.push_back(GameObjectManager::queuedNewGameObjects[i]);
		else if(thisObjectType == 0) //Death
			activeGameObjectsLayer2.push_back(GameObjectManager::queuedNewGameObjects[i]);
		else //Lower layer floors and miscellaneous
			activeGameObjectsLayer1.push_back(GameObjectManager::queuedNewGameObjects[i]);

	}
	GameObjectManager::queuedNewGameObjects.clear(); //resets list for future transfers.
}

void GameObjectManager::addGameObject(GameObject * newObjectCopy)
{
	GameObjectManager::queuedNewGameObjects.push_back(newObjectCopy);
}

void GameObjectManager::draw(SDL_Surface *destination, int xOffset, int yOffset)
{
	int size = activeGameObjectsLayer1.size();
	for(int i = 0; i < size; i++)
		activeGameObjectsLayer1[i]->draw(destination, xOffset, yOffset);
	size = activeGameObjectsLayer2.size();
	for(int i = 0; i < size; i++)
		activeGameObjectsLayer2[i]->draw(destination, xOffset, yOffset);
	size = activeGameObjectsLayer3.size();
	for(int i = 0; i < size; i++)
		activeGameObjectsLayer3[i]->draw(destination, xOffset, yOffset);
	size = activeGameObjectsLayer4.size();
	for(int i = 0; i < size; i++)
		activeGameObjectsLayer4[i]->draw(destination, xOffset, yOffset);
}

void GameObjectManager::updateAllGameObjects(Uint32 timeElapsedMs)
{
	int size = activeGameObjectsLayer1.size();
	for(int i = 0; i < size; i++)
		activeGameObjectsLayer1[i]->update(timeElapsedMs);
	size = activeGameObjectsLayer2.size();
	for(int i = 0; i < size; i++)
		activeGameObjectsLayer2[i]->update(timeElapsedMs);
	size = activeGameObjectsLayer3.size();
	for(int i = 0; i < size; i++)
		activeGameObjectsLayer3[i]->update(timeElapsedMs);
	size = activeGameObjectsLayer4.size();
	for(int i = 0; i < size; i++)
		activeGameObjectsLayer4[i]->update(timeElapsedMs);
}


vector<GameObject*> GameObjectManager::getAllObjectsList()
{
	//Declare the list and allocate the appropriate space
	vector<GameObject*> masterList;
	
	masterList.reserve(activeGameObjectsLayer1.size() +
		activeGameObjectsLayer2.size() + 
		activeGameObjectsLayer3.size() + 
		activeGameObjectsLayer4.size());


	//merge 1-2 as list, then list-3, then list-4.
	std::merge(activeGameObjectsLayer1.begin(),
		activeGameObjectsLayer1.end(),
		activeGameObjectsLayer2.begin(),
		activeGameObjectsLayer2.end(),
		std::back_inserter(masterList));
	std::merge(activeGameObjectsLayer4.begin(),
		activeGameObjectsLayer4.end(),
		activeGameObjectsLayer3.begin(),
		activeGameObjectsLayer3.end(),
		std::back_inserter(masterList));
	return masterList;
}


