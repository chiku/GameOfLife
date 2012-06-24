#include <stdio.h>
#include <stdlib.h>

#include "game_of_life.h"

const long int MAX_WORLD_SIZE = 10000;
const int MAX_NEIGHBOURS = 8;

/* Private */
static void World_Create_Cell_In_New_World(World *self, Cell cell, World *new_world)
{
	Coordinates coordinates = Cell_Coordinates(cell);
	int neighbours = World_Cell_Count_Around(self, coordinates);
	int cell_alive = World_Has_Cell_At(self, coordinates);

	if (Rule_Carry_Forward_Cell(cell_alive, neighbours))
		World_Add_Cell(new_world, Cell_New_From_Coordinates(coordinates));
}
/* Private */

World* World_Allocate()
{
	World *self = (World*) (malloc( sizeof(World) ));
	self->neighbour_locations = (Coordinates*) (malloc ( sizeof(Coordinates) * MAX_NEIGHBOURS ));
	self->cell_collection = CellCollection_Allocate();
	return self;
}

World* World_Initialize(World *world)
{
	world->neighbour_locations[0] = Coordinates_New(-1, -1);
	world->neighbour_locations[1] = Coordinates_New(-1,  0);
	world->neighbour_locations[2] = Coordinates_New(-1, +1);
	world->neighbour_locations[3] = Coordinates_New( 0, -1);
	world->neighbour_locations[4] = Coordinates_New( 0, +1);
	world->neighbour_locations[5] = Coordinates_New(+1, -1);
	world->neighbour_locations[6] = Coordinates_New(+1,  0);
	world->neighbour_locations[7] = Coordinates_New(+1, +1);
	CellCollection_Initialize(world->cell_collection);
	return world;
}

World *World_New()
{
	return World_Initialize(World_Allocate());
}

void World_Destroy(World *self)
{
	free(self->neighbour_locations);
	CellCollection_Destroy(self->cell_collection);
	free(self);
}

World* World_Create_From_File(const char file_name[])
{
	FILE *fp = fopen(file_name, "r");
	World *world = World_New();
	long int x, y;

	while (fscanf(fp, "%ld %ld", &x, &y) != EOF)
		World_Add_Cell(world, Cell_New(x, y));

	fclose(fp);

	return world;
}

long int World_Cell_Count(const World *self)
{
	return CellCollection_Cell_Count(self->cell_collection);
}

void World_Add_Cell(World *self, Cell cell)
{
	CellCollection_Add_Cell(self->cell_collection, cell);
}

int World_Has_Cell_At(const World *self, Coordinates coordinates)
{
	return CellCollection_Has_Cell_At(self->cell_collection, coordinates);
}

int World_Cell_Count_Around(const World *self, Coordinates coordinates)
{
	long int count = 0, i, corner;
	Cell cell;

	for (i = 0; i < World_Cell_Count(self); i++) {
		cell = self->cell_collection->cells[i];
		for (corner = 0; corner < MAX_NEIGHBOURS; corner++) {
			if (Cell_Is_At(cell, Coordinates_Shifted_By(coordinates, self->neighbour_locations[corner])))
				count += 1;
			}
	}

	return count;
}

CellCollection* World_Active_Zone(const World *self)
{
	long int i, corner;
	Cell cell;
	CellCollection *potential_births = CellCollection_New();
	Coordinates coordinates;

	for (i = 0; i < World_Cell_Count(self); i++) {
		cell = self->cell_collection->cells[i];
		for (corner = 0; corner < MAX_NEIGHBOURS; corner++) {
			coordinates = Coordinates_Shifted_By(Cell_Coordinates(cell), self->neighbour_locations[corner]);
			CellCollection_Add_Cell(potential_births, Cell_New_From_Coordinates(coordinates));
		}
	}

	return potential_births;
}

World* World_Tick(World *self)
{
	World *new_world = World_New();
	long int i;

	CellCollection *active_zone = World_Active_Zone(self);
	for (i = 0; i < active_zone->cell_count; i++)
		World_Create_Cell_In_New_World(self, active_zone->cells[i], new_world);

	World_Destroy(self);
	CellCollection_Destroy(active_zone);

	return new_world;
}

void World_At_Each_Cell(const World *self, void (*visitor)(Coordinates coordinates, void *), void *data)
{
	Cell cell;
	long int i;
	for (i = 0; i < World_Cell_Count(self); i++) {
		cell = self->cell_collection->cells[i];
		visitor(Cell_Coordinates(cell), data);
	}
}

void World_Dump(const World *self)
{
	CellCollection_Dump(self->cell_collection);
}
