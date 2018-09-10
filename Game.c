#include "Game.h"
#include "Constants.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void PlayGame(SDL_Surface *screen,SDL_Rect playerPos,SDL_Rect *staticObjects,int staticObjectsCount,SDL_Rect *dynamicObjects,int dynamicObjectsCount){

      int levelEnded = 0;
      int asMoved = 0;
      SDL_Surface *playerSurface = NULL;
      SDL_Surface *BlockingLayer = NULL;
      SDL_Surface *boxSurface = NULL;
      SDL_Event event;

      //LOAD IMAGES
      playerSurface = IMG_Load("wizard.png");
      BlockingLayer = IMG_Load("BlockingLayer.png");
      boxSurface = IMG_Load("box_movable.png");

      while (!levelEnded) {

        //WAIT EVENT
        SDL_WaitEvent(&event);

        switch (event.type) {

          //IF QUIT EVENT
          case SDL_QUIT:
            levelEnded = 1;
            break;

          case SDL_KEYDOWN:
            //IF KEY PRESSED
            switch(event.key.keysym.sym)
            {
              case SDLK_UP:
                asMoved = PlayerAttemptMove(screen,BlockingLayer,boxSurface,UP,playerSurface,&playerPos,staticObjects,staticObjectsCount,dynamicObjects,dynamicObjectsCount);
                break;
              case SDLK_DOWN:
                asMoved = PlayerAttemptMove(screen,BlockingLayer,boxSurface,DOWN,playerSurface,&playerPos,staticObjects,staticObjectsCount,dynamicObjects,dynamicObjectsCount);
                break;
              case SDLK_LEFT:
                  asMoved = PlayerAttemptMove(screen,BlockingLayer,boxSurface,LEFT,playerSurface,&playerPos,staticObjects,staticObjectsCount,dynamicObjects,dynamicObjectsCount);
                break;
              case SDLK_RIGHT:
                  asMoved = PlayerAttemptMove(screen,BlockingLayer,boxSurface,RIGHT,playerSurface,&playerPos,staticObjects,staticObjectsCount,dynamicObjects,dynamicObjectsCount);
                break;
            }
            break;
        }
        //UPDATE SCREEN IF NEEDED
        if(asMoved){
          SDL_Flip(screen);
          asMoved = 0;
        }
      }

      //FREE POINTERS
      free(playerSurface);
      free(BlockingLayer);
}

int PlayerAttemptMove(SDL_Surface *screen,SDL_Surface *BlockingLayer, SDL_Surface *boxSurface,int direction,SDL_Surface *player,SDL_Rect *playerPos,SDL_Rect *staticObjects, int staticObjectsCount,SDL_Rect *dynamicObjects,int dynamicObjectsCount){

  SDL_Rect playerNextPos = *playerPos;
  SDL_Rect foundDynamicPos;
  int canMove = 1;  //0 : CAN'T MOVE ; 1 : NOTHING IN FRONT ; 2 : MOVABLE OBJECT IN FRONT
  int foundDynamicIndex;

  //CONVERT DIRECTION
  playerNextPos = convertDirectionToRect(direction,*playerPos);

  //CHECK FOR COLLISION
  canMove = checkForCollision(playerNextPos,staticObjects,staticObjectsCount,dynamicObjects,dynamicObjectsCount,&foundDynamicIndex);

  //CHECK WHAT TO DO
  if(canMove == 1){
    MoveObject(screen,BlockingLayer,player,playerPos,playerNextPos);
  }

  if(canMove == 2){
    SDL_Rect dynamicInFrontPos = convertDirectionToRect(direction,dynamicObjects[foundDynamicIndex]);
    if(checkForCollision(dynamicInFrontPos,staticObjects,staticObjectsCount,dynamicObjects,dynamicObjectsCount,&foundDynamicIndex) == 1){
      MoveObject(screen,BlockingLayer,boxSurface,&dynamicObjects[foundDynamicIndex],dynamicInFrontPos);
      MoveObject(screen,BlockingLayer,player,playerPos,playerNextPos);
    }
  }

  return canMove;
}

SDL_Rect convertDirectionToRect(int direction,SDL_Rect startingPosition){
  SDL_Rect converted = startingPosition;

  if(direction == UP){
    converted.y -= BLOCK_SIZE;
  }
  if(direction == DOWN){
    converted.y += BLOCK_SIZE;
  }
  if(direction == RIGHT){
    converted.x += BLOCK_SIZE;
  }
  if(direction == LEFT){
    converted.x -= BLOCK_SIZE;
  }
  return converted;
}

int checkForCollision(SDL_Rect checkPosition,SDL_Rect *staticObjects,int staticObjectsCount,SDL_Rect *dynamicObjects,int dynamicObjectsCount,int *foundDynamicIndex){
  int found = 1;
  for(int i = 0;i<staticObjectsCount;i++){
      if(staticObjects[i].x == checkPosition.x && staticObjects[i].y == checkPosition.y){
        found = 0;
      }
      if(dynamicObjects[i].x == checkPosition.x && dynamicObjects[i].y == checkPosition.y){
        found = 2;
        *foundDynamicIndex = i;
      }
  }
  return found;
}

void MoveObject(SDL_Surface *screen,SDL_Surface *BlockingLayer,SDL_Surface *objectToMove, SDL_Rect *objectToMovePos,SDL_Rect objectNextPos){

  SDL_BlitSurface(objectToMove,NULL,screen,&objectNextPos);
  SDL_BlitSurface(BlockingLayer,NULL,screen,objectToMovePos);

  *objectToMovePos = objectNextPos;
}
