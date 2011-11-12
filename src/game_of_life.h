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
Cell* Cell_Initialize(World *world, long int x, long int y);
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

void World_Add_Cell(World *self, Cell *cell);
Cell* World_Cell_At(World *self, long int x, long int y);
int World_Has_Cell(World *self, Cell* cell);
int World_Has_Cell_At(World *self, long int x, long int y);
int World_Cell_Count_Around(World *self, long int x, long int y);
World* World_Active_Zone(World *self);

World* World_Tick(World *self);
void World_At_Each_Cell(World *world, void (*visitor)(long int, long int));

void World_Dump(World *self);
/* World Methods */

/* Utility Functions */
char *handle_command_line_arguments(int argc, char *argv[]);
World* create_world_with_file(char *file_name);
/* Utility Functions */
#endif /* GAME_OF_LIFE_H */

