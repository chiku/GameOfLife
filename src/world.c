#include <stdlib.h>

#include <game_of_life.h>

const long int MAX_WORLD_SIZE = 10000;

World *World_Initialize()
{
	World *self = (World*) (malloc( sizeof(World) ));
	self->cell_count = 0;
	self->cells = (Cell**) (malloc( sizeof(Cell*) * MAX_WORLD_SIZE ));
	return self;
}

void World_Destroy(World *self)
{
	// LEAK
	free(self->cells);
}

Cell** World_Cells(World *self)
{
	return self->cells;
}


long int World_Cell_Count(World *self)
{
	return self->cell_count;
}

void World_Add_Cell(World *self, Cell *cell)
{
	self->cells[self->cell_count] = cell;
	self->cell_count ++;
}

int World_Has_Cell(World *self, Cell *cell)
{
	long int i;
	for (i = 0; i < self->cell_count; i++)
		if (self->cells[i] == cell)
			return 1;
	return 0;
}

int World_Has_Cell_At(World *self, int x, int y)
{
	long int i;
	for (i = 0; i < self->cell_count; i++)
		if (Cell_Is_At(self->cells[i], self, x, y))
			return 1;
	return 0;
}

int World_Cell_Count_Around(World *self, int x, int y)
{
	long int count = 0, i, j, k;
	Cell *cell;

	for (i = 0; i < self->cell_count; i++) {
		cell = self->cells[i];
		if (Cell_Is_At(cell, self, x - 1, y - 1) ||
		    Cell_Is_At(cell, self, x - 1, y    ) ||
		    Cell_Is_At(cell, self, x - 1, y + 1) ||
		    Cell_Is_At(cell, self, x    , y - 1) ||
		    Cell_Is_At(cell, self, x    , y + 1) ||
		    Cell_Is_At(cell, self, x + 1, y - 1) ||
		    Cell_Is_At(cell, self, x + 1, y    ) ||
		    Cell_Is_At(cell, self, x + 1, y + 1)) {
				count += 1;
			}
	}

	return count;
}

void World_Tick(World *self)
{
	World *new_world = World_Initialize();
	int count, i;

	for (i = 0; i < self->cell_count; i++) {
		count = Cell_Total_Neighbours(self->cells[i]);
		if (count == 2 || count == 3)
			World_Add_Cell(new_world, self->cells[i]);
	}
	*self = *new_world;
}

