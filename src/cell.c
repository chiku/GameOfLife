#include <stdlib.h>

#include <game_of_life.h>

Cell* Cell_Initialize(World *world)
{
	Cell *self = (Cell*) (malloc( sizeof(Cell) ));
	self->x = 0;
	self->y = 0;
	self->world = world;
	World_Add_Cell(world, self);
	return self;
}

void Cell_Destroy(Cell *self)
{
	// LEAK
}

long int Cell_X(Cell *self)
{
	return self->x;
}

long int Cell_Y(Cell *self)
{
	return self->y;
}

World* Cell_World(Cell *self)
{
	return self->world;
}

Cell* Cell_Spawn_At(Cell *self, long int x, long int y)
{
	Cell *new_cell = Cell_Initialize(self->world);
	new_cell->x = x;
	new_cell->y = y;
	return new_cell;
}

long int Cell_Total_Neighbours(Cell *self)
{
	long int count = 0, i;
	Cell *other_cell;
	Cell **all_cells = World_Cells(self->world);
	long int all_cells_count = World_Cell_Count(self->world);

	for (i = 0; i < all_cells_count; i++) {
		other_cell = all_cells[i];
		if (self->x     == other_cell->x && self->y + 1 == other_cell->y) count += 1;
		if (self->x + 1 == other_cell->x && self->y + 1 == other_cell->y) count += 1;
		if (self->x + 1 == other_cell->x && self->y     == other_cell->y) count += 1;
		if (self->x + 1 == other_cell->x && self->y - 1 == other_cell->y) count += 1;
		if (self->x     == other_cell->x && self->y - 1 == other_cell->y) count += 1;
		if (self->x - 1 == other_cell->x && self->y - 1 == other_cell->y) count += 1;
		if (self->x - 1 == other_cell->x && self->y     == other_cell->y) count += 1;
		if (self->x - 1 == other_cell->x && self->y + 1 == other_cell->y) count += 1;
	}

	return count;
}

