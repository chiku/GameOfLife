#include <stdio.h>
#include <stdlib.h>

#include "game_of_life.h"

Coordinates Coordinates_New(long int x, long int y)
{
	Coordinates coordinates = {x, y};
	return coordinates;
}

int Coordinates_Match(Coordinates c1, Coordinates c2)
{
	return c1.x == c2.x && c1.y == c2.y;
}

Coordinates Coordinates_Get(Coordinates self)
{
	Coordinates c = {self.x, self.y};
	return c;
}

Coordinates Coordinates_Shifted_By(Coordinates self, Coordinates displacement)
{
	return Coordinates_New(self.x + displacement.x, self.y + displacement.y);
}

void Coordinates_Dump(Coordinates self)
{
	printf("(x=%ld, y=%ld)\n", self.x, self.y);
}
