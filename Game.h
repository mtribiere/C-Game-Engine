#ifndef DEF_GAME
#define DEF_GAME
#include <SDL/SDL.h>

  void PlayGame(SDL_Surface  *screen,SDL_Rect playerPos,SDL_Rect *staticObjects,int staticObjectsCount);
  int PlayerAttemptMove(SDL_Surface *screen,SDL_Surface *BlockingLayer,int direction,SDL_Surface *player,SDL_Rect *playerPos,SDL_Rect *staticObjects, int staticObjectsCount);
  void MoveObject(SDL_Surface *screen,SDL_Surface *BlockingLayer,SDL_Surface *objectToMove, SDL_Rect *objectToMovePos,SDL_Rect objectNextPos);

#endif
