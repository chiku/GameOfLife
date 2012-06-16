#include <stdio.h>
#include <stdlib.h>

#include "game_of_life.h"

Cell* Cell_Allocate()
{
	Cell *cell = (Cell*) (malloc( sizeof(Cell) ));
	cell->coordinates = (Coordinates*) (malloc( sizeof(Coordinates) ));
	return cell;
}

Cell* Cell_Initialize(Cell* allocated_cell, long int x, long int y)
{
	allocated_cell->coordinates = Coordinates_New(x, y);
	return allocated_cell;
}

Cell* Cell_New(long int x, long int y)
{
	return Cell_Initialize( Cell_Allocate(), x, y );
}

void Cell_Destroy(Cell *self)
{
	Coordinates_Destroy(self->coordinates);
	free(self);
}

Coordinates Cell_Coordinates(const Cell *self)
{
	return Coordinates_Get(self->coordinates);
}

int Cell_Is_At(const Cell *self, Coordinates coordinates)
{
	return Coordinates_Match(self->coordinates, &coordinates);
}

void Cell_Dump(const Cell* self)
{
	Coordinates_Dump(self->coordinates);
}
