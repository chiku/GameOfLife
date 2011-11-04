#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

typedef struct Cell Cell;
typedef struct World World;

struct Cell
{
	long int x;
	long int y;
	World *world;
};

struct World
{
	long int cell_count;
	Cell **cells;
};

Cell* Cell_Initialize(World *world);
void Cell_Destroy(Cell *self);

long int Cell_X(Cell *self);
long int Cell_Y(Cell *self);
World* Cell_World(Cell *self);

Cell* Cell_Spawn_At(Cell *self, long int x, long int y);
long int Cell_Total_Neighbours(Cell *self);


World World_Initialize();
void World_Destroy(World *self);
Cell** World_Cells(World *self);
long int World_Cell_Count(World *self);
int World_Has_Cell(World *self, Cell* cell);
void World_Tick(World *self);

#endif /* GAME_OF_LIFE_H */

