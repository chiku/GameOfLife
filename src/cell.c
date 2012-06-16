#include <stdio.h>
#include <stdlib.h>

#include "game_of_life.h"

Cell Cell_New(long int x, long int y)
{
	Cell cell = {Coordinates_New(x, y)};
	return cell;
}

Cell Cell_New_From_Coordinates(Coordinates coordinates)
{
	Cell cell = {coordinates};
	return cell;
}

Coordinates Cell_Coordinates(Cell self)
{
	return Coordinates_Get(self.coordinates);
}

int Cell_Is_At(Cell self, Coordinates coordinates)
{
	return Coordinates_Match(self.coordinates, coordinates);
}

void Cell_Dump(Cell self)
{
	Coordinates_Dump(self.coordinates);
}
