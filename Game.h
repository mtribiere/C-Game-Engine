#ifndef DEF_GAME
#define DEF_GAME
#include <SDL/SDL.h>

  void PlayGame(SDL_Surface  *screen,SDL_Rect playerPos,SDL_Rect *staticObjects,int staticObjectsCount,SDL_Rect *dynamicObjects,int dynamicObjectsCount);
  int PlayerAttemptMove(SDL_Surface *screen,SDL_Surface *BlockingLayer, SDL_Surface *boxSurface,int direction,SDL_Surface *player,SDL_Rect *playerPos,SDL_Rect *staticObjects, int staticObjectsCount,SDL_Rect *dynamicObjects,int dynamicObjectsCount);
  void MoveObject(SDL_Surface *screen,SDL_Surface *BlockingLayer,SDL_Surface *objectToMove, SDL_Rect *objectToMovePos,SDL_Rect objectNextPos);
  int checkForCollision(SDL_Rect checkPosition,SDL_Rect *staticObjects,int staticObjectsCount,SDL_Rect *dynamicObjects,int dynamicObjectsCount,int *foundDynamicIndex);
  SDL_Rect convertDirectionToRect(int direction,SDL_Rect startingPosition);

#endif
