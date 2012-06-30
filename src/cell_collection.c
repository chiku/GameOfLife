#include <stdio.h>
#include <stdlib.h>

#include "game_of_life.h"

const long int MAX_CELL_COLLECTION_SIZE = 10000;

CellCollection* CellCollection_Allocate()
{
	CellCollection *self = (CellCollection*) (malloc( sizeof(CellCollection) ));
	self->cells = (Cell*) (malloc( sizeof(Cell) * MAX_CELL_COLLECTION_SIZE ));
	return self;
}

CellCollection* CellCollection_Initialize(CellCollection *cell_collection)
{
	cell_collection->cell_count = 0;
	return cell_collection;
}

CellCollection *CellCollection_New()
{
	return CellCollection_Initialize(CellCollection_Allocate());
}

void CellCollection_Destroy(CellCollection *self)
{
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

int CellCollection_Cell_Count_Around(const CellCollection *self, Coordinates coordinates, Coordinates *locations, int location_size)
{
	long int count = 0, i, corner;
	Cell cell;

	for (i = 0; i < self->cell_count; i++) {
		cell = self->cells[i];
		for (corner = 0; corner < location_size; corner++) {
			if (Cell_Is_At(cell, Coordinates_Shifted_By(coordinates, locations[corner])))
				count += 1;
			}
	}

	return count;
}

CellCollection* CellCollection_All_Neighbours_For_Set(const CellCollection *self, Coordinates *locations, int location_size)
{
	long int i, corner;
	Cell cell;
	CellCollection *neighbours = CellCollection_New();
	Coordinates coordinates;

	for (i = 0; i < self->cell_count; i++) {
		cell = self->cells[i];
		for (corner = 0; corner < location_size; corner++) {
			coordinates = Coordinates_Shifted_By(Cell_Coordinates(cell), locations[corner]);
			CellCollection_Add_Cell(neighbours, Cell_New_From_Coordinates(coordinates));
		}
	}

	return neighbours;
}

void CellCollection_At_Each_Cell(const CellCollection *self, void (*visitor)(Coordinates coordinates, void *), void *data)
{
	Cell cell;
	long int i;
	for (i = 0; i < self->cell_count; i++) {
		cell = self->cells[i];
		visitor(Cell_Coordinates(cell), data);
	}
}

void CellCollection_Dump(const CellCollection *self)
{
	int i;

	printf("Total cells = %ld\n", self->cell_count);
	for (i = 0; i < self->cell_count; i++)
		Cell_Dump(self->cells[i]);
	printf("\n");
}