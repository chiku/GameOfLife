#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

typedef struct Cell Cell;
typedef struct World World;

struct Cell
{
	long int x;
	long int y;
};

struct World
{
	int **neighbour_locations;
	long int cell_count;
	Cell **cells;
};

/* Cell Methods */
Cell* Cell_Allocate();
Cell* Cell_Initialize(Cell *allocated_cell, long int x, long int y);

Cell* Cell_New(long int x, long int y);
void Cell_Destroy(Cell *self);

long int Cell_X(const Cell *self);
long int Cell_Y(const Cell *self);

int Cell_Is_At(const Cell *self, long int x, long int y);

void Cell_Dump(const Cell *self);
/* Cell Methods */

/* World Methods */
World* World_Allocate();
World* World_Initialize(World *allocated_world);

World* World_New();
void World_Destroy(World *self);

World* World_Create_From_File(const char file_name[]);

long int World_Cell_Count(const World *self);

void World_Add_Cell(World *self, Cell *cell);
int World_Has_Cell_At(const World *self, long int x, long int y);
int World_Cell_Count_Around(const World *self, long int x, long int y);
World* World_Active_Zone(const World *self);

World* World_Tick(World *self);
void World_At_Each_Cell(const World *world, void (*visitor)(long int, long int, void*), void *data);

void World_Dump(const World *self);
/* World Methods */

/* Utility Functions */
char *handle_command_line_arguments(int argc, char *argv[]);
World* create_world_with_file(char *file_name);
/* Utility Functions */

#endif /* GAME_OF_LIFE_H */
