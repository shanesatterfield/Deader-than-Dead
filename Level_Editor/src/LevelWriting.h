#ifndef LEVELWRITING_H
#define LEVELWRITING_H

#include <fstream>
#include <string>
#include <vector>
#include "Sprites.h"

class LevelWriting{
private:
	std::string currFile;
	std::string currType;
	std::string currBackground;
public:
	LevelWriting();
	bool writeToFile(std::string filename, std::vector<Sprites> vec, int yMenuOffset);
	void update(std::string type, std::string fromFile);
	bool fileLoaded();
	std::string getFile();
	std::string getType();
};

#endif
