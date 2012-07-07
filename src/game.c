#include <stdio.h>
#include <stdlib.h>

#include "coordinates.h"
#include "cell.h"
#include "world.h"
#include "rules.h"
#include "game.h"

const long int MAX_WORLD_SIZE = 10000;

/* Private */
static void Game_Create_Cell_In_Next_World(Game *self, Cell cell)
{
	Coordinates coordinates = Cell_Coordinates(cell);
	int neighbours = Game_Cell_Count_Around(self, coordinates);
	int cell_alive = World_Has_Cell_At(self->world, coordinates);

	if (Rule_Carry_Forward_Cell(cell_alive, neighbours))
		World_Add_Cell(self->next_world, Cell_New_From_Coordinates(coordinates));
}
/* Private */

Game* Game_Allocate()
{
	Game *self = (Game*) (malloc( sizeof(Game) ));
	self->neighbour_locations = (Coordinates*) (malloc ( sizeof(Coordinates) * MAX_NEIGHBOURS ));
	self->world = World_Allocate();
	self->next_world = World_Allocate();
	return self;
}

Game* Game_Initialize(Game *game)
{
	game->neighbour_locations[0] = Coordinates_New(-1, -1);
	game->neighbour_locations[1] = Coordinates_New(-1,  0);
	game->neighbour_locations[2] = Coordinates_New(-1, +1);
	game->neighbour_locations[3] = Coordinates_New( 0, -1);
	game->neighbour_locations[4] = Coordinates_New( 0, +1);
	game->neighbour_locations[5] = Coordinates_New(+1, -1);
	game->neighbour_locations[6] = Coordinates_New(+1,  0);
	game->neighbour_locations[7] = Coordinates_New(+1, +1);
	World_Initialize(game->world);
	World_Initialize(game->next_world);
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
	free(self);
}

Game* Game_Create_From_File(const char file_name[])
{
	FILE *fp = fopen(file_name, "r");
	Game *game = Game_New();
	long int x, y;

	while (fscanf(fp, "%ld %ld", &x, &y) != EOF)
		Game_Add_Cell_At(game, x, y);

	fclose(fp);

	return game;
}

long int Game_Cell_Count(Game *self)
{
	return World_Cell_Count(self->world);
}

int Game_Has_Cell_At(Game *self, long int x, long int y)
{
	return World_Has_Cell_At(self->world, Coordinates_New(x, y));
}

void Game_Add_Cell(Game *self, Cell cell)
{
	World_Add_Cell(self->world, cell);
}

void Game_Add_Cell_At(Game *self, long int x, long int y)
{
	World_Add_Cell(self->world, Cell_New(x, y));
}

int Game_Cell_Count_Around(const Game *self, Coordinates coordinates)
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
	World_Destroy(self->world);

	self->world = self->next_world;
	self->next_world = World_New();

	return self;
}

void Game_At_Each_Cell(const Game *self, void (*visitor)(Coordinates coordinates, void *), void *data)
{
	World_At_Each_Cell(self->world, visitor, data);
}

void Game_Dump(const Game *self)
{
	World_Dump(self->world);
}
