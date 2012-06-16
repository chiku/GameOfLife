#include <stdio.h>
#include <stdlib.h>

#include "game_of_life.h"

Cell* Cell_Allocate()
{
	return (Cell*) (malloc( sizeof(Cell) ));
}

Cell* Cell_Initialize(Cell* allocated_cell, long int x, long int y)
{
	allocated_cell->x = x;
	allocated_cell->y = y;
	return allocated_cell;
}

Cell* Cell_New(long int x, long int y)
{
	return Cell_Initialize( Cell_Allocate(), x, y );
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

int Cell_Is_At(const Cell *self, long int x, long int y)
{
	return (self->x == x && self->y ==y) ? 1 : 0;
}

void Cell_Dump(const Cell* self)
{
	printf("(x=%ld, y=%ld)\n", self->x, self->y);
}
