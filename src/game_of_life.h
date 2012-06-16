#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

typedef struct Coordinates Coordinates;
typedef struct Cell Cell;
typedef struct World World;


struct Coordinates
{
	long int x;
	long int y;
};

struct Cell
{
	Coordinates coordinates;
};

struct World
{
	Coordinates *neighbour_locations;
	long int cell_count;
	Cell *cells;
};


/* Coordinates Methods */
Coordinates Coordinates_New(long int x, long int y);

Coordinates Coordinates_Get(Coordinates coordinates);
int Coordinates_Match(Coordinates c1, Coordinates c2);
Coordinates Coordinates_Shifted_By(Coordinates self, Coordinates displacement);

void Coordinates_Dump(Coordinates self);
/* Coordinates Methods */


/* Cell Methods */
Cell Cell_New(long int x, long int y);
Cell Cell_New_From_Coordinates(Coordinates coordinates);

Coordinates Cell_Coordinates(Cell self);

int Cell_Is_At(Cell self, Coordinates coordinates);

void Cell_Dump(Cell self);
/* Cell Methods */


/* Rules Methods */
int Rule_Carry_Forward_Cell(int cell_alive, int neighbours);
/* Rules Methods */


/* World Methods */
World* World_Allocate();
World* World_Initialize(World *allocated_world);

World* World_New();
void World_Destroy(World *self);

World* World_Create_From_File(const char file_name[]);

long int World_Cell_Count(const World *self);

void World_Add_Cell(World *self, Cell cell);
int World_Has_Cell_At(const World *self, Coordinates coordinates);
int World_Cell_Count_Around(const World *self, Coordinates coordinates);
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
