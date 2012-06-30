#ifndef GOL_WORLD_H
#define GOL_WORLD_H

#include "coordinates.h"
#include "cell.h"

typedef struct World World;

struct World
{
	long int cell_count;
	Cell *cells;
};

/* World Methods */
World* World_Allocate();
World* World_Initialize(World *allocated_world);

World* World_New();
void World_Destroy(World *self);

long int World_Cell_Count(const World *self);

void World_Add_Cell(World *self, Cell cell);
int World_Has_Cell_At(const World *self, Coordinates coordinates);
int World_Cell_Count_Around(const World *self, Coordinates coordinates, Coordinates *neighbour_locations, int location_size);
World* World_All_Neighbours_For_Set(const World *self, Coordinates *neighbour_locations, int location_size);

void World_At_Each_Cell(const World *self, void (*visitor)(Coordinates coordinates, void *), void *data);

void World_Dump(const World *self);
/* World Methods */

#endif
