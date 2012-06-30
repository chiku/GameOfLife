#include <stdio.h>
#include <stdlib.h>

#include "coordinates.h"
#include "cell.h"
#include "world.h"

const long int MAX_CELL_COLLECTION_SIZE = 10000;

World* World_Allocate()
{
	World *self = (World*) (malloc( sizeof(World) ));
	self->cells = (Cell*) (malloc( sizeof(Cell) * MAX_CELL_COLLECTION_SIZE ));
	return self;
}

World* World_Initialize(World *world)
{
	world->cell_count = 0;
	return world;
}

World *World_New()
{
	return World_Initialize(World_Allocate());
}

void World_Destroy(World *self)
{
	free(self->cells);
	free(self);
}

long int World_Cell_Count(const World *self){
	return self->cell_count;
}

void World_Add_Cell(World *self, Cell cell)
{
	if (World_Has_Cell_At(self, Cell_Coordinates(cell)))
		return ;

	self->cells[self->cell_count] = cell;
	self->cell_count++;
}

int World_Has_Cell_At(const World *self, Coordinates coordinates)
{
	long int i;
	for (i = 0; i < self->cell_count; i++)
		if (Cell_Is_At(self->cells[i], coordinates))
			return 1;
	return 0;
}

int World_Cell_Count_Around(const World *self, Coordinates coordinates, Coordinates *locations, int location_size)
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

World* World_All_Neighbours_For_Set(const World *self, Coordinates *locations, int location_size)
{
	long int i, corner;
	Cell cell;
	World *neighbours = World_New();
	Coordinates coordinates;

	for (i = 0; i < self->cell_count; i++) {
		cell = self->cells[i];
		for (corner = 0; corner < location_size; corner++) {
			coordinates = Coordinates_Shifted_By(Cell_Coordinates(cell), locations[corner]);
			World_Add_Cell(neighbours, Cell_New_From_Coordinates(coordinates));
		}
	}

	return neighbours;
}

void World_At_Each_Cell(const World *self, void (*visitor)(Coordinates coordinates, void *), void *data)
{
	Cell cell;
	long int i;
	for (i = 0; i < self->cell_count; i++) {
		cell = self->cells[i];
		visitor(Cell_Coordinates(cell), data);
	}
}

void World_Dump(const World *self)
{
	int i;

	printf("Total cells = %ld\n", self->cell_count);
	for (i = 0; i < self->cell_count; i++)
		Cell_Dump(self->cells[i]);
	printf("\n");
}
