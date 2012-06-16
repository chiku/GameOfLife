#include <stdio.h>
#include <stdlib.h>

#include "game_of_life.h"

const long int MAX_WORLD_SIZE = 10000;

/* Private */
static void World_Create_Cell_In_New_World(World *self, Cell *cell, World *new_world)
{
	long int x = Cell_X(cell);
	long int y = Cell_Y(cell);
	int count = World_Cell_Count_Around(self, x, y);
	int cell_alive = World_Has_Cell_At(self, x, y);

	int live_cell_remains = cell_alive && (count == 2 || count == 3);
	int dead_cell_comes_alive = !cell_alive && count == 3;
	if (live_cell_remains || dead_cell_comes_alive)
		World_Add_Cell(new_world, Cell_New(x, y));
}
/* Private */

World* World_Allocate()
{
	World *self = (World*) (malloc( sizeof(World) ));
	self->cells = (Cell**) (malloc( sizeof(Cell*) * MAX_WORLD_SIZE ));
	return self;
}

World* World_Initialize(World *allocatedWorld)
{
	allocatedWorld->cell_count = 0;
	return allocatedWorld;
}

World *World_New()
{
	return World_Initialize(World_Allocate());
}

void World_Destroy(World *self)
{
	int i;
	for (i = 0; i < self->cell_count; i++)
		free(self->cells[i]);
	free(self->cells);
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
	return self->cell_count;
}

void World_Add_Cell(World *self, Cell *cell)
{
	if (World_Has_Cell_At(self, Cell_X(cell), Cell_Y(cell)))
		return ;

	self->cells[self->cell_count] = cell;
	self->cell_count ++;
}

int World_Has_Cell_At(const World *self, long int x, long int y)
{
	long int i;
	for (i = 0; i < self->cell_count; i++)
		if (Cell_Is_At(self->cells[i], x, y))
			return 1;
	return 0;
}

int World_Cell_Count_Around(const World *self, long int x, long int y)
{
	long int count = 0, i;
	Cell *cell;

	for (i = 0; i < self->cell_count; i++) {
		cell = self->cells[i];
		if (Cell_Is_At(cell, x - 1, y - 1) ||
		    Cell_Is_At(cell, x - 1, y    ) ||
		    Cell_Is_At(cell, x - 1, y + 1) ||
		    Cell_Is_At(cell, x    , y - 1) ||
		    Cell_Is_At(cell, x    , y + 1) ||
		    Cell_Is_At(cell, x + 1, y - 1) ||
		    Cell_Is_At(cell, x + 1, y    ) ||
		    Cell_Is_At(cell, x + 1, y + 1)) {
				count += 1;
			}
	}

	return count;
}

World* World_Active_Zone(const World *self)
{
	long int i, x, y;
	Cell *cell;
	World *potential_births = World_New();

	for (i = 0; i < self->cell_count; i++) {
		cell = self->cells[i];
		x = Cell_X(cell);
		y = Cell_Y(cell);
		World_Add_Cell(potential_births, Cell_New(x - 1, y - 1));
		World_Add_Cell(potential_births, Cell_New(x - 1, y    ));
		World_Add_Cell(potential_births, Cell_New(x - 1, y + 1));
		World_Add_Cell(potential_births, Cell_New(x    , y - 1));
		World_Add_Cell(potential_births, Cell_New(x    , y + 1));
		World_Add_Cell(potential_births, Cell_New(x + 1, y - 1));
		World_Add_Cell(potential_births, Cell_New(x + 1, y    ));
		World_Add_Cell(potential_births, Cell_New(x + 1, y + 1));
	}

	return potential_births;
}

World* World_Tick(World *self)
{
	World *new_world = World_New();
	long int i;

	World *active_zone = World_Active_Zone(self);
	for (i = 0; i < active_zone->cell_count; i++)
		World_Create_Cell_In_New_World(self, active_zone->cells[i], new_world);

	World_Destroy(self);
	World_Destroy(active_zone);

	return new_world;
}

void World_At_Each_Cell(const World *world, void (*visitor)(long int, long int, void *), void *data)
{
	Cell *cell;
	long int i;
	for (i = 0; i < world->cell_count; i++) {
		cell = world->cells[i];
		visitor(Cell_X(cell), Cell_Y(cell), data);
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
