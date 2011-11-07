#include <stdio.h>
#include <stdlib.h>

#include <game_of_life.h>

const long int MAX_WORLD_SIZE = 10000;

/* Private */
World* World_Create()
{
	World *self = (World*) (malloc( sizeof(World) ));
	self->cells = (Cell**) (malloc( sizeof(Cell*) * MAX_WORLD_SIZE ));
	return self;
}
/* Private */

World *World_Initialize()
{
	World *self = World_Create();
	self->cell_count = 0;
	return self;
}

void World_Destroy(World *self)
{
	int i;
	for (i = 0; i < self->cell_count; i++)
		free(self->cells[i]);
	free(self->cells);
	free(self);
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

Cell* World_Cell_At(World *self, long int x, long int y)
{
	long int i;
	for (i = 0; i < self->cell_count; i++)
		if (Cell_Is_At(self->cells[i], self, x, y))
			return self->cells[i];
	return '\0';
}

int World_Has_Cell_At(World *self, long int x, long int y)
{
	return World_Cell_At(self, x, y) == '\0' ? 0 : 1;
}

int World_Cell_Count_Around(World *self, long int x, long int y)
{
	long int count = 0, i;
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

World* World_Active_Zone(World *self)
{
	long int i, x, y;
	Cell *cell;
	World *potential_births = World_Initialize();

	for (i = 0; i < self->cell_count; i++) {
		cell = self->cells[i];
		x = Cell_X(cell);
		y = Cell_Y(cell);
		Cell_Initialize(potential_births, x - 1, y - 1);
		Cell_Initialize(potential_births, x - 1, y    );
		Cell_Initialize(potential_births, x - 1, y + 1);
		Cell_Initialize(potential_births, x    , y - 1);
		Cell_Initialize(potential_births, x    , y + 1);
		Cell_Initialize(potential_births, x + 1, y - 1);
		Cell_Initialize(potential_births, x + 1, y    );
		Cell_Initialize(potential_births, x + 1, y + 1);
	}

	return potential_births;
}

World* World_Tick(World *self)
{
	World *new_world = World_Initialize();
	Cell *cell;
	int count, i;

	World *active_zone = World_Active_Zone(self);
	for (i = 0; i < active_zone->cell_count; i++) {
		cell = active_zone->cells[i];
		count = World_Cell_Count_Around(self, Cell_X(cell), Cell_Y(cell));
		if (World_Has_Cell_At(self, cell->x, cell->y)) {
			if (count == 2 || count == 3)
				Cell_Initialize(new_world, Cell_X(cell), Cell_Y(cell));
		} else {
			if (count == 3)
				Cell_Initialize(new_world, Cell_X(cell), Cell_Y(cell));
		}
	}

	World_Destroy(self);
	World_Destroy(active_zone);

	return new_world;
}

void World_Dump(World *self)
{
	int i;

	printf("Pointer to world = %p\n", self);
	printf("Total cells = %ld\n", self->cell_count);
	for (i = 0; i < self->cell_count; i++)
		Cell_Dump(self->cells[i]);
	printf("\n");
}

