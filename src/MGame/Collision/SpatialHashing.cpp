#pragma once
#include "SpatialHashing.h"
#include "CollisionDetection.h"
#include "../GameObjects/GameObject.h"

using namespace std; //I do this out of habit.

SpatialHashing::SpatialHashing(int mapWidth, int mapHeight, int squareCellSize)
{
	//Determine how many buckets are required.
	xNumOfCells = mapWidth / squareCellSize;
	yNumOfCells = mapHeight / squareCellSize;

	if(mapWidth%squareCellSize > 0)
		xNumOfCells += 1;
	if(mapHeight%squareCellSize > 0)
		yNumOfCells += 1;

	//Stores the square cell size.
	this->squareCellSize = squareCellSize; 

	//Allocates space?
	numBuckets = xNumOfCells * yNumOfCells;
	buckets.reserve(numBuckets);
	for(int i = 0; i < numBuckets; i++)
		buckets.push_back(new vector<GameObject*>());
}

void SpatialHashing::update(vector<GameObject*> masterList)
{
	clearAllBuckets(); //Clears buckets
	hashToBuckets(masterList);//Hashes to buckets
	checkAllBuckets();	//Checks all buckets for collisions
}

void SpatialHashing::checkAllBuckets()
{
	for(int bucketIndex = 0; bucketIndex < numBuckets; bucketIndex++)
	{
		int sizeOfBucket = buckets[bucketIndex]->size();
		for(int objIndex1 = 0; objIndex1 < sizeOfBucket; objIndex1++) //O(n^2). This could be optimized...
			for(int objIndex2 = 0; objIndex2 < sizeOfBucket; objIndex2++)
			{
				if(objIndex1 == objIndex2) continue; //no need to check self.
				else
				{
					if(CollisionDetection::rectangleIntersecting(
						(*buckets[bucketIndex])[objIndex1],
						(*buckets[bucketIndex])[objIndex2]))
					{
						//Run collision handling
						(*buckets[bucketIndex])[objIndex1]->checkCollisionWith(
							(*buckets[bucketIndex])[objIndex2]);
					}
				}
			}
	}
}

void SpatialHashing::hashToBuckets(vector<GameObject*> masterList)
{
	int listSize = masterList.size(); //Size returns the number of elements in the vector container
	const int NUM_OF_CORNERS = 4;
	for(int i = 0; i < listSize; i++) //Iterates thru gameobjects
	{
		//Get the two corners:
		int xCellTopLeft = masterList[i]->collisionBox.x / squareCellSize;
		int yCellTopLeft = masterList[i]->collisionBox.y / squareCellSize;
		int xCellBotRight = (masterList[i]->collisionBox.x + masterList[i]->collisionBox.w)  / squareCellSize;
		int yCellBotRight = (masterList[i]->collisionBox.y + masterList[i]->collisionBox.h) / squareCellSize;

		//Error bound checking. If it's out of bounds, it will assign the object to the closest cell in the border.
		if(xCellTopLeft < 0) xCellTopLeft = 0;
		if(xCellBotRight >= this->xNumOfCells) xCellBotRight = this->xNumOfCells - 1;
		if(yCellTopLeft < 0) yCellTopLeft = 0;
		if(yCellBotRight >= this->yNumOfCells) yCellBotRight = this->yNumOfCells - 1;

		//Determine how big the object is and what buckets it lies in
		for(int yRow = yCellTopLeft; yRow <= yCellBotRight; yRow++)
			for(int xCol = xCellTopLeft; xCol <= xCellBotRight; xCol++)
				buckets[yRow * xNumOfCells + xCol]->push_back(masterList[i]);

	}
}//end SpatialHashing()

void SpatialHashing::clearAllBuckets()
{
	for(int i = 0; i < numBuckets; i++)
		buckets[i]->clear();
}