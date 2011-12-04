#include <stdio.h>
#include <stdlib.h>

#include "game_of_life.h"

Cell* Cell_Allocate()
{
	return (Cell*) (malloc( sizeof(Cell) ));
}

Cell* Cell_Initialize(Cell* allocatedCell, World* world, long int x, long int y)
{
	Cell *alreadyPresent;

	alreadyPresent = World_Cell_At(world, x, y);
	if (alreadyPresent != '\0')
		return alreadyPresent;

	allocatedCell->x = x;
	allocatedCell->y = y;
	allocatedCell->world = world;

	World_Add_Cell(world, allocatedCell);
	return allocatedCell;
}

Cell* Cell_New(World *world, long int x, long int y)
{
	return Cell_Initialize( Cell_Allocate(), world, x, y );
}

void Cell_Destroy(Cell *self)
{
	free(self);
}

long int Cell_X(const Cell *self)
{
	return self->x;
}

long int Cell_Y(const Cell *self)
{
	return self->y;
}

World* Cell_World(const Cell *self)
{
	return self->world;
}

long int Cell_Total_Neighbours(const Cell *self)
{
	return World_Cell_Count_Around(self->world, self->x, self->y);
}

int Cell_Is_At(const Cell *self, const World *world, long int x, long int y)
{
	return (self->world == world && self->x == x && self->y ==y) ? 1 : 0;
}

void Cell_Dump(const Cell* self)
{
	printf("world <%p> : (x=%ld, y=%ld)\n", self->world, self->x, self->y);
}

