#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "Constants.h"
#include "LevelLoader.h"
#include "Game.h"

int main(int argc, char *argv[])
{

	SDL_Surface *screen = NULL;
	SDL_Rect playerPos;
	SDL_Rect *staticObjects;
	int staticObjectsCount = 0;
	SDL_Rect *dynamicObjects;
	int dynamicObjectsCount = 0;

	//INIT SDL
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(WINDOW_WIDTH,WINDOW_HEIGHT,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption(WINDOW_TITLE,NULL);

	//INIT STATIC OBJECTS
	staticObjects = malloc(sizeof(SDL_Rect)*STATIC_MAX_NUMBER);

	//INIT DYNAMIC OBJECTS
	dynamicObjects = malloc(sizeof(SDL_Rect)*DYNAMIC_MAX_NUMBER);

	//LOAD THE LEVEL
	LoadLevel(0,screen,&playerPos,staticObjects,&staticObjectsCount,dynamicObjects,&dynamicObjectsCount);

	//RUN THE GAME
	PlayGame(screen,playerPos,staticObjects,staticObjectsCount,dynamicObjects,dynamicObjectsCount);

	//QUIT
	free(staticObjects);
	free(dynamicObjects);
	SDL_Quit();

	return EXIT_SUCCESS;

}
