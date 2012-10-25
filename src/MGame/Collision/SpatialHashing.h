#pragma once 

#include <vector>
#include "../GameObjects/GameObject.h"

using namespace std;

class SpatialHashing
{
public:
	//Constructor for spatial hashing.
	SpatialHashing(int mapWidth, int mapHeight, int squareCellSize);
	//Detects collision then sends the pointer to the collision manager.
	void update(vector<GameObject*> masterList);
	//takes all the active gameobjects and then hashes them for detection management.
	void hashToBuckets(vector<GameObject*> masterList);
	//clears the buckets so they can used again for the new state.
	void clearAllBuckets();
	//Checks the buckets for the collisions and sends the pointer to the collision manager if it is detected.
	void checkAllBuckets();
private:
	//States the number of buckets
	int numBuckets;
	//Stores the number of cells within the entire map.
	int xNumOfCells; int yNumOfCells;
	//stores the cell size
	int squareCellSize;
	//contains all the buckets to check the collisions within each individual bucket.
	vector<vector<GameObject*>*> buckets;
	
};