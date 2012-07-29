#ifndef GOL_GAME_OF_LIFE_H
#define GOL_GAME_OF_LIFE_H

typedef struct Coordinates Coordinates;
typedef struct Cell Cell;
typedef struct Game Game;

struct Coordinates
{
	long int x;
	long int y;
};

struct Cell
{
	Coordinates coordinates;
	long int generation;
};

extern Game* Game_New();
extern void Game_Destroy(Game *self);

extern Game* Game_Create_From_File(const char file_name[]);

extern long int Game_Cell_Count(const Game *self);
extern int Game_Has_Cell_At(const Game *self, long int x, long int y);
extern void Game_Add_Cell_At(Game *self, long int x, long int y);

extern void Game_At_Each_Cell(const Game *self, void (*visitor)(Cell cell, void*), void *data);
extern void Game_At_Each_Old_Cell(const Game *self, void (*visitor)(Cell cell, void*), void *data);

extern Game* Game_Tick(Game *self);
extern Game* Game_Dump(Game *self);

#endif
