#include <stdio.h>
#include <stdlib.h>

#include "game_of_life.h"

const long int MAX_CELL_COLLECTION_SIZE = 10000;
const int MAX_NEIGHBOURS_FOR_CELL = 8;

CellCollection* CellCollection_Allocate()
{
	CellCollection *self = (CellCollection*) (malloc( sizeof(CellCollection) ));
	self->cells = (Cell*) (malloc( sizeof(Cell) * MAX_CELL_COLLECTION_SIZE ));
	self->neighbour_locations = (Coordinates*) (malloc ( sizeof(Coordinates) * MAX_NEIGHBOURS_FOR_CELL ));
	return self;
}

CellCollection* CellCollection_Initialize(CellCollection *cell_collection)
{
	cell_collection->cell_count = 0;
	cell_collection->neighbour_locations[0] = Coordinates_New(-1, -1);
	cell_collection->neighbour_locations[1] = Coordinates_New(-1,  0);
	cell_collection->neighbour_locations[2] = Coordinates_New(-1, +1);
	cell_collection->neighbour_locations[3] = Coordinates_New( 0, -1);
	cell_collection->neighbour_locations[4] = Coordinates_New( 0, +1);
	cell_collection->neighbour_locations[5] = Coordinates_New(+1, -1);
	cell_collection->neighbour_locations[6] = Coordinates_New(+1,  0);
	cell_collection->neighbour_locations[7] = Coordinates_New(+1, +1);

	return cell_collection;
}

CellCollection *CellCollection_New()
{
	return CellCollection_Initialize(CellCollection_Allocate());
}

void CellCollection_Destroy(CellCollection *self)
{
	free(self->neighbour_locations);
	free(self->cells);
	free(self);
}

long int CellCollection_Cell_Count(const CellCollection *self){
	return self->cell_count;
}

void CellCollection_Add_Cell(CellCollection *self, Cell cell)
{
	if (CellCollection_Has_Cell_At(self, Cell_Coordinates(cell)))
		return ;

	self->cells[self->cell_count] = cell;
	self->cell_count++;
}

int CellCollection_Has_Cell_At(const CellCollection *self, Coordinates coordinates)
{
	long int i;
	for (i = 0; i < self->cell_count; i++)
		if (Cell_Is_At(self->cells[i], coordinates))
			return 1;
	return 0;
}

int CellCollection_Cell_Count_Around(const CellCollection *self, Coordinates coordinates)
{
	long int count = 0, i, corner;
	Cell cell;

	for (i = 0; i < self->cell_count; i++) {
		cell = self->cells[i];
		for (corner = 0; corner < MAX_NEIGHBOURS_FOR_CELL; corner++) {
			if (Cell_Is_At(cell, Coordinates_Shifted_By(coordinates, self->neighbour_locations[corner])))
				count += 1;
			}
	}

	return count;
}
