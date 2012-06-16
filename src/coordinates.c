#include <stdio.h>
#include <stdlib.h>

#include "game_of_life.h"

Coordinates* Coordinates_Allocate()
{
	return (Coordinates*) (malloc( sizeof(Coordinates) ));
}

Coordinates* Coordinates_Initialize(Coordinates* coordinates, long int x, long int y)
{
	coordinates->x = x;
	coordinates->y = y;
	return coordinates;
}

Coordinates* Coordinates_New(long int x, long int y)
{
	return Coordinates_Initialize( Coordinates_Allocate(), x, y );
}

void Coordinates_Destroy(Coordinates *self)
{
	free(self);
}

int Coordinates_Match(Coordinates *c1, Coordinates *c2)
{
	return c1->x == c2->x && c1->y == c2->y;
}

Coordinates Coordinates_Get(Coordinates *self)
{
	Coordinates c = {self->x, self->y};
	return c;
}

void Coordinates_Dump(const Coordinates *self)
{
	printf("(x=%ld, y=%ld)\n", self->x, self->y);
}