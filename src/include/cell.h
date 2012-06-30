#ifndef GOL_CELL_H
#define GOL_CELL_H

#include "coordinates.h"

typedef struct Cell Cell;

struct Cell
{
	Coordinates coordinates;
};

/* Cell Methods */
Cell Cell_New(long int x, long int y);
Cell Cell_New_From_Coordinates(Coordinates coordinates);

struct Coordinates Cell_Coordinates(Cell self);

int Cell_Is_At(Cell self, Coordinates coordinates);

void Cell_Dump(Cell self);
/* Cell Methods */

#endif
