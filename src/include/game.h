#ifndef GOL_GAME_H
#define GOL_GAME_H

#include "coordinates.h"
#include "cell.h"
#include "world.h"
#include "rules.h"


typedef struct Game Game;


struct Game
{
	struct Coordinates *neighbour_locations;
	World *world;
};

static const int MAX_NEIGHBOURS = 8;


/* Game Methods */
Game* Game_Allocate();
Game* Game_Initialize(Game *allocated_game);

Game* Game_New();
void Game_Destroy(Game *self);

Game* Game_Create_From_File(const char file_name[]);

void Game_Add_Cell(Game *self, Cell cell);
int Game_Cell_Count_Around(const Game *self, struct Coordinates coordinates);
World* Game_Active_Zone(const Game *self);

Game* Game_Tick(Game *self);
void Game_At_Each_Cell(const Game *self, void (*visitor)(struct Coordinates coordinates, void*), void *data);

void Game_Dump(const Game *self);
/* Game Methods */


#endif
