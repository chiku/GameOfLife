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

/* Cell Methods */
Cell* Cell_Initialize(World *world);
Cell* Cell_Initialize_At(World *world, long int x, long int y);
void Cell_Destroy(Cell *self);

long int Cell_X(Cell *self);
long int Cell_Y(Cell *self);
World* Cell_World(Cell *self);

long int Cell_Total_Neighbours(Cell *self);
int Cell_Is_At(Cell *self, World *world, long int x, long int y);

void Cell_Dump(Cell *self);
/* Cell Methods */

/* World Methods */
World* World_Initialize();
void World_Destroy(World *self);

Cell** World_Cells(World *self);
long int World_Cell_Count(World *self);

int World_Has_Cell(World *self, Cell* cell);
int World_Has_Cell_At(World *self, long int x, long int y);
int World_Cell_Count_Around(World *self, long int x, long int y);
void World_Tick(World *self);
World* World_All_Potential_Births(World *self);

void World_Dump(World *self);
/* World Methods */

#endif /* GAME_OF_LIFE_H */

