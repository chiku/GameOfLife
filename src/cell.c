#include <stdio.h>
#include <stdlib.h>

#include <game_of_life.h>

/* Private */
Cell* Cell_Create()
{
	return (Cell*) (malloc( sizeof(Cell) ));
}
/* Private */

Cell* Cell_Initialize(World *world, long int x, long int y)
{
	Cell *self;

	self = World_Cell_At(world, x, y);
	if (self != '\0')
		return self;

	self = Cell_Create();
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
	printf("world <%p> : (x=%ld, y=%ld)\n", self->world, self->x, self->y);
}

