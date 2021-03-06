#include "LevelLoader.h"
#include "Constants.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


//Load a level by ID
void LoadLevel(int id,SDL_Surface *screen,SDL_Rect *playerPos,SDL_Rect *staticObjects,int *staticObjectsCount,SDL_Rect *dynamicObjects,int *dynamicObjectsCount){

  FILE* levelFile = NULL;
  int currentChar = 0;
  int currentWallId = 0;
  int currentBoxId = 0;
  SDL_Rect currentBlockPos;

  currentBlockPos.x = 0;
  currentBlockPos.y = 0;

  //OPEN LEVEL FILE
  levelFile = fopen("level0","r");

  //IF CORRECTLY OPENED
  if(levelFile != NULL){
    do{
      currentChar = fgetc(levelFile);

      //BOX
      if(currentChar == BOX+'0'){
        SDL_Surface *tempBox = IMG_Load("box_movable.png");
        SDL_BlitSurface(tempBox,NULL,screen,&currentBlockPos);

        dynamicObjects[currentBoxId] = currentBlockPos;
        currentBoxId++;

        free(tempBox);
      }

      //WALL
      if(currentChar == WALL+'0'){
        SDL_Surface *tempWall = IMG_Load("box.png");
        SDL_BlitSurface(tempWall,NULL,screen,&currentBlockPos);

        staticObjects[currentWallId] = currentBlockPos;
        currentWallId++;

        free(tempWall);
      }

      //PLAYER
      if(currentChar == PLAYER+'0'){
        playerPos->x = currentBlockPos.x;
        playerPos->y = currentBlockPos.y;
        SDL_Surface *playerSurface;
        playerSurface = IMG_Load("wizard.png");
        SDL_BlitSurface(playerSurface,NULL,screen,playerPos);
        free(playerSurface);
      }
      currentBlockPos.x += BLOCK_SIZE;

      //IF END LINE
      if(currentChar == '\n'){
        currentBlockPos.y += BLOCK_SIZE;
        currentBlockPos.x = 0;
      }
    }while(currentChar !=EOF);

  }else{
    //IF ERRORS
    printf("Error while loading the level\n");
    exit(1);
  }

  //SET RETURN VALUES
  *staticObjectsCount = currentWallId;
  *dynamicObjectsCount = currentBoxId;

  fclose(levelFile);
  SDL_Flip(screen);
}
