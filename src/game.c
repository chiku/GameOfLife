#include <stdio.h>
#include <stdlib.h>

#include "coordinates.h"
#include "cell.h"
#include "world.h"
#include "rules.h"
#include "game.h"

/* Private */
static void Game_Create_Cell_In_Next_World(Game *self, Cell cell)
{
	Coordinates coordinates = Cell_Coordinates(cell);
	int neighbours = Game_Cell_Count_Around(self, coordinates);
	int cell_alive = World_Has_Cell_At(self->world, coordinates);
	long int generation = World_Generation_For(self->world, coordinates);
	Cell new_cell;

	if (Rule_Carry_Forward_Cell(cell_alive, neighbours)) {
		if (cell_alive) {
			new_cell = Cell_New_From_Coordinates_With_Incremented_Generation(coordinates, generation);
		} else {
			new_cell = Cell_New_From_Coordinates(coordinates);
		}
		World_Add_Cell(self->next_world, new_cell);
	}
}

static void Game_Initialize_Neighbours(Coordinates *neighbour_locations)
{
	neighbour_locations[0] = Coordinates_New(-1, -1);
	neighbour_locations[1] = Coordinates_New(-1,  0);
	neighbour_locations[2] = Coordinates_New(-1, +1);
	neighbour_locations[3] = Coordinates_New( 0, -1);
	neighbour_locations[4] = Coordinates_New( 0, +1);
	neighbour_locations[5] = Coordinates_New(+1, -1);
	neighbour_locations[6] = Coordinates_New(+1,  0);
	neighbour_locations[7] = Coordinates_New(+1, +1);
}
/* Private */

Game* Game_Allocate()
{
	Game *self = (Game*) (malloc( sizeof(Game) ));

	self->neighbour_locations = (Coordinates*) (malloc ( sizeof(Coordinates) * MAX_NEIGHBOURS ));
	self->world = World_Allocate();
	self->next_world = World_Allocate();
	self->old_world = World_Allocate();
	return self;
}

Game* Game_Initialize(Game *game)
{
	Game_Initialize_Neighbours(game->neighbour_locations);
	World_Initialize(game->world);
	World_Initialize(game->next_world);
	World_Initialize(game->old_world);
	return game;
}

Game *Game_New()
{
	return Game_Initialize(Game_Allocate());
}

void Game_Destroy(Game *self)
{
	free(self->neighbour_locations);
	World_Destroy(self->world);
	World_Destroy(self->next_world);
	World_Destroy(self->old_world);
	free(self);
}

Game* Game_Create_From_File(const char file_name[])
{
	FILE *fp = fopen(file_name, "r");
	Game *game = Game_New();
	long int x, y;
	const int MAX_SIZE = 256;
	char input[MAX_SIZE];

	while (fgets(input, MAX_SIZE, fp) != NULL) {
		input[MAX_SIZE - 1] = '\0';
		if (input[0] != '#') {
			sscanf(input, "%ld %ld", &x, &y);
			Game_Add_Cell_At(game, x, y);
		}
	}
	fclose(fp);

	return game;
}

long int Game_Cell_Count(const Game *self)
{
	return World_Cell_Count(self->world);
}

int Game_Has_Cell_At(const Game *self, long int x, long int y)
{
	return World_Has_Cell_At(self->world, Coordinates_New(x, y));
}

void Game_Add_Cell_At(Game *self, long int x, long int y)
{
	World_Add_Cell(self->world, Cell_New(x, y));
}

int Game_Cell_Count_Around(const const Game *self, Coordinates coordinates)
{
	return World_Cell_Count_Around(self->world, coordinates, self->neighbour_locations, MAX_NEIGHBOURS);
}

World* Game_Active_Zone(const Game *self)
{
	return World_All_Neighbours_For_Set(self->world, self->neighbour_locations, MAX_NEIGHBOURS);
}

Game* Game_Tick(Game *self)
{
	long int i;

	World *active_zone = Game_Active_Zone(self);
	for (i = 0; i < active_zone->cell_count; i++)
		Game_Create_Cell_In_Next_World(self, active_zone->cells[i]);

	World_Destroy(active_zone);
	World_Destroy(self->old_world);

	self->old_world = self->world;
	self->world = self->next_world;
	self->next_world = World_New();

	return self;
}

void Game_At_Each_Cell(const Game *self, void (*visitor)(Coordinates coordinates, void *), void *data)
{
	World_At_Each_Cell(self->world, visitor, data);
}

void Game_At_Each_Old_Cell(const Game *self, void (*visitor)(Coordinates coordinates, void *), void *data)
{
	World_At_Each_Cell(self->old_world, visitor, data);
}

void Game_Dump(const Game *self)
{
	World_Dump(self->world);
}
