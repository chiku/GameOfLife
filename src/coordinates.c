#include <stdio.h>

#include "coordinates.h"

Coordinates Coordinates_New(long int x, long int y)
{
	Coordinates coordinates = {x, y};
	return coordinates;
}

int Coordinates_Match(Coordinates c1, Coordinates c2)
{
	return c1.x == c2.x && c1.y == c2.y;
}

long int Coordinates_X(Coordinates self)
{
	return self.x;
}

long int Coordinates_Y(Coordinates self)
{
	return self.y;
}

Coordinates Coordinates_Shifted_By(Coordinates self, Coordinates displacement)
{
	return Coordinates_New(self.x + displacement.x, self.y + displacement.y);
}

void Coordinates_Dump(Coordinates self)
{
	printf("(x=%ld, y=%ld)\n", self.x, self.y);
}
