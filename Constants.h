#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS

  #define BLOCK_SIZE          64
  #define MAP_SIZE            12
  #define WINDOW_WIDTH        BLOCK_SIZE * MAP_SIZE
  #define WINDOW_HEIGHT       BLOCK_SIZE * MAP_SIZE

  #define WINDOW_TITLE        "Sokoban"

  #define STATIC_MAX_NUMBER     100
  #define DYNAMIC_MAX_NUMBER    100

  enum directions { UP,DOWN,LEFT,RIGHT };
  enum block_type { WALL,BOX,GOAL,PLAYER,EMPTY };

#endif
