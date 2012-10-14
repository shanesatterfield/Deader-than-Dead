#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "src/Button.h"
#include <string>
#include <iostream>
#include <fstream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

SDL_Surface* screen = NULL;
SDL_Event event;

TTF_Font* font = NULL;
SDL_Color textColor = {0x44,0x44,0x44};

const int BUTTONSIZE = 3;
Button buttonArray[BUTTONSIZE];

SDL_Surface* load_image(std::string filename){
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	loadedImage = IMG_Load(filename.c_str());
	if(loadedImage == NULL){
		optimizedImage = SDL_DisplayFormat(loadedImage);
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
	font = TTF_OpenFont("res/arial.ttf", 28);
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
	for(int i = 0; i < BUTTONSIZE; i++){
		SDL_FreeSurface(buttonArray[i].message);
	}
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

bool initButtons(){
	buttonArray[0].message = TTF_RenderText_Solid(font, "Save", textColor);
	buttonArray[0].box.x = 0;
	buttonArray[0].box.y = 0;
	buttonArray[0].box.w = buttonArray[0].message->w;
	buttonArray[0].box.h = buttonArray[0].message->h;

	buttonArray[1].message = TTF_RenderText_Solid(font, "Load", textColor);
	buttonArray[1].box.x = 100 + buttonArray[0].box.x + buttonArray[0].box.w;
	buttonArray[1].box.y = 0;
	buttonArray[1].box.w = buttonArray[1].message->w;
	buttonArray[1].box.h = buttonArray[1].message->h;

	buttonArray[2].message = TTF_RenderText_Solid(font, "Close", textColor);
	buttonArray[2].box.x = 100 + buttonArray[1].box.x + buttonArray[1].box.w;
	buttonArray[2].box.y = 0;
	buttonArray[2].box.w = buttonArray[2].message->w;
	buttonArray[2].box.h = buttonArray[2].message->h;

	for(int i = 0; i < BUTTONSIZE; i++){
		if(buttonArray[i].message == NULL){
			return false;
		}
	}

	return true;
}

bool writeToFile(std::string filename, std::vector<Sprites> vec){
	bool bl = false;
	ofstream file(filename.c_str());
	if(file.is_open()){
		bl = true;
		file.close();
	}
	return bl;
}

int main(int argc, char* argv[]){
	bool quit = false;

	if(init() == false)
		return 1;
	if(load_files() == false)
		return 1;
	if(initButtons() == false)
		return 1;

	std::vector<Sprites> vec;

	while(!quit){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				quit = true;
			}
			if(event.type == SDL_MOUSEBUTTONUP){
				if(event.button.button == SDL_BUTTON_LEFT){
					for(int i = 0; i < BUTTONSIZE; i++){
						int x = event.button.x;
						int y = event.button.y;
						if(buttonArray[i].check_click(x, y)){
							std::cout << "Clicked" << std::endl;
						}
					}
				}
			}
		}

		SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

		for(int i = 0; i < BUTTONSIZE; i++){
			apply_surface(buttonArray[i].box.x, buttonArray[i].box.y, buttonArray[i].message, screen);
			//std::cout << "Hey" << std::endl;
		}

		if(SDL_Flip(screen) == -1)
			return 1;
	}

	cleanup();
	
	return 0;
}