#ifndef DEF_LEVEL_LOADER
#define DEF_LEVEL_LOADER
#include <SDL/SDL.h>
#include "Constants.h"

  void LoadLevel(int id,SDL_Surface *screen,SDL_Rect *playerPos,SDL_Rect *staticObjects,int *staticObjectsCount);

#endif
