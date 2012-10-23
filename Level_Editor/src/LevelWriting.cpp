#include "LevelWriting.h"
#include <fstream>
#include <string>
#include <vector>

LevelWriting::LevelWriting(){
	currFile = "";
	currType = "";
	currBackground = "";
}

void LevelWriting::update(std::string type, std::string fromFile){
	if(type == "Background"){
		currBackground = fromFile;
	}
	else{
		currType = type;
		currFile = fromFile;
	}
}

bool LevelWriting::fileLoaded(){
	return currFile != "";
}

std::string LevelWriting::getFile(){
	return currFile;
}

std::string LevelWriting::getType(){
	return currType;
}

bool LevelWriting::writeToFile(std::string filename, std::vector<Sprites> spriteVec, int yMenuOffset){
	bool bl = false;
	std::string finalName = "levels/";
	finalName += filename;
	std::ofstream file;
	file.open(finalName.c_str());
	if(file.is_open()){
		bl = true;

		if(currBackground != ""){
			file << currBackground << '\n';
		}
		for(int i = 0; i < spriteVec.size(); i++){
			file << spriteVec[i].box.x << " ";
			file << (spriteVec[i].box.y - yMenuOffset) << " ";
			file << spriteVec[i].box.w << " ";
			file << spriteVec[i].box.h << " ";
			file << spriteVec[i].type << " ";
			file << spriteVec[i].fromFile << '\n';
		}

		file.close();
	}
	return bl;
}