#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <string>

#include "SDLBase.h"
#include <iostream>
//#include <unistd.h>
//#include <sys/param.h>

SDL_Surface* SDLBase::load_image(std::string filename){
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	loadedImage = IMG_Load(filename.c_str());
	if(loadedImage != NULL){
		optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	return optimizedImage;
}

void SDLBase::apply_surface(int x, int y, SDL_Surface* source, SDL_Surface *destination){
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(source, NULL, destination, &offset);
}

/*
std::string SDLBase::convert_path(std::string filename){
	char path[MAXPATHLEN];
	getcwd(path, MAXPATHLEN);
	strcat(path, ('/'+filename).c_str() );
	return (std::string)path;
}*/

SDL_Color SDLBase::setColor(Uint8 r, Uint8 g, Uint8 b){
	SDL_Color temp = {r,g,b};
	return temp;
}