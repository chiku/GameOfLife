#ifndef GOL_COORDINATES_H
#define GOL_COORDINATES_H

typedef struct Coordinates Coordinates;

struct Coordinates
{
	long int x;
	long int y;
};

/* Coordinates Methods */
Coordinates Coordinates_New(long int x, long int y);

Coordinates Coordinates_Get(Coordinates coordinates);
int Coordinates_Match(Coordinates c1, Coordinates c2);
Coordinates Coordinates_Shifted_By(Coordinates self, Coordinates displacement);

void Coordinates_Dump(Coordinates self);
/* Coordinates Methods */

#endif
