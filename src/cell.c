#include <stdio.h>

#include "coordinates.h"
#include "cell.h"

Cell Cell_New(long int x, long int y)
{
	Cell cell = {Coordinates_New(x, y)};
	cell.generation = 1;
	return cell;
}

Cell Cell_New_From_Coordinates(Coordinates coordinates)
{
	Cell cell = {coordinates};
	cell.generation = 1;
	return cell;
}

Cell Cell_New_From_Coordinates_With_Incremented_Generation(Coordinates coordinates, long int old_generation)
{
	Cell cell = {coordinates, old_generation + 1};
	return cell;
}

Coordinates Cell_Coordinates(Cell self)
{
	return self.coordinates;
}

int Cell_Is_At(Cell self, Coordinates coordinates)
{
	return Coordinates_Match(self.coordinates, coordinates);
}

void Cell_Dump(Cell self)
{
	Coordinates coordinates = self.coordinates;
	printf("(x=%ld, y=%ld) <%ld>\n", coordinates.x, coordinates.y, self.generation);
}
