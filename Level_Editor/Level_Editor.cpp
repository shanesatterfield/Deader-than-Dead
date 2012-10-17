#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "src/Button.h"
#include "src/StringInput.h"
#include "src/Sprites.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

SDL_Surface* screen = NULL;
SDL_Surface* background = NULL;
SDL_Event event;

TTF_Font* font = NULL;
SDL_Color textColor = {0,0,0};

const int BUTTONSIZE = 4;
Button buttonArray[BUTTONSIZE];

const int yMenuOffset = 18;
std::vector<Sprites> spriteVec;

SDL_Surface* load_image(std::string filename){
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	loadedImage = IMG_Load(filename.c_str());
	if(loadedImage != NULL){
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	return optimizedImage;
}

bool init(){
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
		return false;
	
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	
	if(screen == NULL)
		return false;

	if(TTF_Init() == -1)
		return false;

	SDL_WM_SetCaption("Deader-than-Dead Level Editor Test", NULL);

	return true;
}

bool load_files(){
	font = TTF_OpenFont("res/arial.ttf", 18);
	if(font == NULL)
		return false;
	return true;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface *destination){
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, NULL, destination, &offset);
}

void cleanup(){
	for(int i = 0; i < spriteVec.size(); i++){
		SDL_FreeSurface(spriteVec[i].spriteSurface);
	}
	SDL_FreeSurface(background);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

bool initButtons(){
	buttonArray[0].message = TTF_RenderText_Solid(font, "Save", textColor);
	buttonArray[0].box.x = 25;
	buttonArray[0].box.y = 0;
	buttonArray[0].box.w = buttonArray[0].message->w;
	buttonArray[0].box.h = buttonArray[0].message->h;

	buttonArray[1].message = TTF_RenderText_Solid(font, "Load Level", textColor);
	buttonArray[1].box.x = 100 + buttonArray[0].box.x + buttonArray[0].box.w;
	buttonArray[1].box.y = 0;
	buttonArray[1].box.w = buttonArray[1].message->w;
	buttonArray[1].box.h = buttonArray[1].message->h;

	buttonArray[2].message = TTF_RenderText_Solid(font, "Objects", textColor);
	buttonArray[2].box.x = 100 + buttonArray[1].box.x + buttonArray[1].box.w;
	buttonArray[2].box.y = 0;
	buttonArray[2].box.w = buttonArray[2].message->w;
	buttonArray[2].box.h = buttonArray[2].message->h;

	buttonArray[3].message = TTF_RenderText_Solid(font, "Enemies", textColor);
	buttonArray[3].box.x = 100 + buttonArray[2].box.x + buttonArray[2].box.w;
	buttonArray[3].box.y = 0;
	buttonArray[3].box.w = buttonArray[3].message->w;
	buttonArray[3].box.h = buttonArray[3].message->h;

	for(int i = 0; i < BUTTONSIZE; i++){
		if(buttonArray[i].message == NULL){
			return false;
		}
	}

	return true;
}
/*
bool writeToFile(std::string filename, std::vector<Sprites> vec){
	bool bl = false;
	ofstream file(filename.c_str());
	if(file.is_open()){
		bl = true;
		file.close();
	}
	return bl;
}
*/

void loadBackground(bool &quit){
	StringInput strIn;
	bool end = false;

	while(!end && !quit){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				quit = true;
			}
			if(event.type == SDL_KEYDOWN){
				int temp = strIn.get_input(event);
				if(temp == 1){
					SDL_FreeSurface(strIn.textInput);
					strIn.textInput = TTF_RenderText_Solid(font, strIn.getStr().c_str(), textColor);
					std::cout << "Hey" << std::endl;
				}
				if(temp == 2){
					background = load_image(strIn.getStr());
					end = true;
				}
			}
		}

		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

		strIn.display(SCREEN_WIDTH, SCREEN_HEIGHT, yMenuOffset, screen);
		std::cout << strIn.getStr() << std::endl;

		if(SDL_Flip(screen) == -1){
			std::cout << "hey there" << std::endl;
		}
	}
}

int main(int argc, char* argv[]){
	bool quit = false;

	if(init() == false)
		return 1;
	if(load_files() == false)
		return 1;
	if(initButtons() == false)
		return 1;
	
	while(!quit){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				quit = true;
			}
			if(event.type == SDL_MOUSEBUTTONUP){
				if(event.button.button == SDL_BUTTON_LEFT){
					int x = event.button.x;
					int y = event.button.y;
					bool bl = false;
					/*
					if(buttonArray[0].check_click(x, y)){
						writeToFile(filename, spriteVec);
					}
					*/
					if(buttonArray[1].check_click(x, y)){
						loadBackground(quit);
						bl = true;
					}
					if(!bl){
						Sprites temp;
						temp.spriteSurface = load_image("res/pumpkin.png");
						temp.box.w = temp.spriteSurface->w;
						temp.box.h = temp.spriteSurface->h;
						temp.box.x = x - temp.box.w/2;
						temp.box.y = y - temp.box.h/2;
						temp.type = "player";
						temp.fromFile = "res/pumpkin.png";
						
						spriteVec.push_back(temp);
					}
				}
			}
		}

		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

		for(int i = 0; i < BUTTONSIZE; i++){
			apply_surface(buttonArray[i].box.x, buttonArray[i].box.y, buttonArray[i].message, screen);
		}

		if(background != NULL){
			apply_surface(0,yMenuOffset, background, screen);
		}

		for(int i = 0; i < spriteVec.size(); i++){
			apply_surface(spriteVec[i].box.x, spriteVec[i].box.y, spriteVec[i].spriteSurface, screen);
		}

		if(SDL_Flip(screen) == -1)
			return 1;
	}

	cleanup();
	
	return 0;
}