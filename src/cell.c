#include <stdio.h>
#include <stdlib.h>

#include "game_of_life.h"

Cell* Cell_Allocate()
{
	return (Cell*) (malloc( sizeof(Cell) ));
}

Cell* Cell_Initialize(Cell* allocated_cell, World* world, long int x, long int y)
{
	Cell *already_present;

	already_present = World_Cell_At(world, x, y);
	if (already_present != '\0')
		return already_present;

	allocated_cell->x = x;
	allocated_cell->y = y;
	allocated_cell->world = world;

	World_Add_Cell(world, allocated_cell);
	return allocated_cell;
}

Cell* Cell_Initialize2(Cell* allocated_cell, long int x, long int y)
{
	allocated_cell->x = x;
	allocated_cell->y = y;
	return allocated_cell;
}

Cell* Cell_New(World *world, long int x, long int y)
{
	return Cell_Initialize( Cell_Allocate(), world, x, y );
}

Cell* Cell_New2(long int x, long int y)
{
	return Cell_Initialize2( Cell_Allocate(), x, y );
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
	return (self->x == x && self->y ==y) ? 1 : 0;
}

int Cell_Is_At2(const Cell *self, long int x, long int y)
{
	return (self->x == x && self->y ==y) ? 1 : 0;
}

void Cell_Dump(const Cell* self)
{
	printf("world <%p> : (x=%ld, y=%ld)\n", self->world, self->x, self->y);
}
