#include "Game.h"
#include "Constants.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void PlayGame(SDL_Surface *screen,SDL_Rect playerPos,SDL_Rect *staticObjects,int staticObjectsCount){

      int levelEnded = 0;
      int asMoved = 0;
      SDL_Surface *playerSurface;
      SDL_Surface *BlockingLayer;
      SDL_Event event;

      //LOAD IMAGES
      playerSurface = IMG_Load("wizard.png");
      BlockingLayer = IMG_Load("BlockingLayer.png");

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
                asMoved = PlayerAttemptMove(screen,BlockingLayer,UP,playerSurface,&playerPos,staticObjects,staticObjectsCount);
                break;
              case SDLK_DOWN:
                asMoved = PlayerAttemptMove(screen,BlockingLayer,DOWN,playerSurface,&playerPos,staticObjects,staticObjectsCount);
                break;
              case SDLK_LEFT:
                  asMoved = PlayerAttemptMove(screen,BlockingLayer,LEFT,playerSurface,&playerPos,staticObjects,staticObjectsCount);
                break;
              case SDLK_RIGHT:
                  asMoved = PlayerAttemptMove(screen,BlockingLayer,RIGHT,playerSurface,&playerPos,staticObjects,staticObjectsCount);
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

int PlayerAttemptMove(SDL_Surface *screen,SDL_Surface *BlockingLayer, int direction,SDL_Surface *player,SDL_Rect *playerPos,SDL_Rect *staticObjects, int staticObjectsCount){

  SDL_Rect playerNextPos = *playerPos;
  int canMove = 1;  //0 : CAN'T MOVE ; 1 : NOTHING IN FRONT ; 2 : MOVABLE OBJECT IN FRONT

  //CONVERT DIRECTION
  if(direction == UP){
    playerNextPos.y -= BLOCK_SIZE;
  }
  if(direction == DOWN){
    playerNextPos.y += BLOCK_SIZE;
  }
  if(direction == RIGHT){
    playerNextPos.x += BLOCK_SIZE;
  }
  if(direction == LEFT){
    playerNextPos.x -= BLOCK_SIZE;
  }

  //CHECK FOR WALLS
  for(int i = 0;i<staticObjectsCount-1;i++){
      if(staticObjects[i].x == playerNextPos.x && staticObjects[i].y == playerNextPos.y){
        playerNextPos = *playerPos;
        canMove = 0;
      }
  }

  //CHECK WHAT TO DO
  if(canMove == 1){
    MoveObject(screen,BlockingLayer,player,playerPos,playerNextPos);
  }
  return canMove;
}

void MoveObject(SDL_Surface *screen,SDL_Surface *BlockingLayer,SDL_Surface *objectToMove, SDL_Rect *objectToMovePos,SDL_Rect objectNextPos){

  SDL_BlitSurface(objectToMove,NULL,screen,&objectNextPos);
  SDL_BlitSurface(BlockingLayer,NULL,screen,objectToMovePos);

  *objectToMovePos = objectNextPos;
}
