#include <stdio.h>
#include <stdlib.h>

#include <game_of_life.h>

Cell* Cell_Initialize(World *world)
{
	return Cell_Initialize_At(world, 0, 0);
}

Cell* Cell_Initialize_At(World *world, long int x, long int y)
{
	Cell *self = (Cell*) (malloc( sizeof(Cell) ));
	self->x = x;
	self->y = y;
	self->world = world;
	World_Add_Cell(world, self);
	return self;
}

void Cell_Destroy(Cell *self)
{
	free(self);
}

long int Cell_X(Cell *self)
{
	return self->x;
}

long int Cell_Y(Cell *self)
{
	return self->y;
}

World* Cell_World(Cell *self)
{
	return self->world;
}

long int Cell_Total_Neighbours(Cell *self)
{
	return World_Cell_Count_Around(self->world, self->x, self->y);
}

int Cell_Is_At(Cell *self, World *world, long int x, long int y)
{
	return (self->world == world && self->x == x && self->y ==y) ? 1 : 0;
}

void Cell_Dump(Cell* self)
{
	printf("world <%p> : (x=%d, y=%d)\n", self->world, self->x, self->y);
}

