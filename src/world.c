#include <stdlib.h>

#include <game_of_life.h>

const long int MAX_WORLD_SIZE = 10000;

World World_Initialize()
{
	World self;
	self.cell_count = 0;
	self.cells = (Cell**) (malloc( sizeof(Cell*) * MAX_WORLD_SIZE ));
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
	int i;
	for (i = 0; i < self->cell_count; i++)
		if (self->cells[i] == cell)
			return 1;
	return 0;
}

void World_Tick(World *self)
{
	// LEAK
	*self = World_Initialize();
}

