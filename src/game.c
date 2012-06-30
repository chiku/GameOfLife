#include <stdio.h>
#include <stdlib.h>

#include "game_of_life.h"

const long int MAX_WORLD_SIZE = 10000;

/* Private */
static void Game_Create_Cell_In_New_Game(Game *self, Cell cell, Game *new_game)
{
	Coordinates coordinates = Cell_Coordinates(cell);
	int neighbours = Game_Cell_Count_Around(self, coordinates);
	int cell_alive = CellCollection_Has_Cell_At(self->cell_collection, coordinates);

	if (Rule_Carry_Forward_Cell(cell_alive, neighbours))
		Game_Add_Cell(new_game, Cell_New_From_Coordinates(coordinates));
}
/* Private */

Game* Game_Allocate()
{
	Game *self = (Game*) (malloc( sizeof(Game) ));
	self->neighbour_locations = (Coordinates*) (malloc ( sizeof(Coordinates) * MAX_NEIGHBOURS ));
	self->cell_collection = CellCollection_Allocate();
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
	CellCollection_Initialize(game->cell_collection);
	return game;
}

Game *Game_New()
{
	return Game_Initialize(Game_Allocate());
}

void Game_Destroy(Game *self)
{
	free(self->neighbour_locations);
	CellCollection_Destroy(self->cell_collection);
	free(self);
}

Game* Game_Create_From_File(const char file_name[])
{
	FILE *fp = fopen(file_name, "r");
	Game *game = Game_New();
	long int x, y;

	while (fscanf(fp, "%ld %ld", &x, &y) != EOF)
		Game_Add_Cell(game, Cell_New(x, y));

	fclose(fp);

	return game;
}

void Game_Add_Cell(Game *self, Cell cell)
{
	CellCollection_Add_Cell(self->cell_collection, cell);
}

int Game_Cell_Count_Around(const Game *self, Coordinates coordinates)
{
	return CellCollection_Cell_Count_Around(self->cell_collection, coordinates, self->neighbour_locations, MAX_NEIGHBOURS);
}

CellCollection* Game_Active_Zone(const Game *self)
{
	return CellCollection_All_Neighbours_For_Set(self->cell_collection, self->neighbour_locations, MAX_NEIGHBOURS);
}

Game* Game_Tick(Game *self)
{
	Game *new_game = Game_New();
	long int i;

	CellCollection *active_zone = Game_Active_Zone(self);
	for (i = 0; i < active_zone->cell_count; i++)
		Game_Create_Cell_In_New_Game(self, active_zone->cells[i], new_game);

	Game_Destroy(self);
	CellCollection_Destroy(active_zone);

	return new_game;
}

void Game_At_Each_Cell(const Game *self, void (*visitor)(Coordinates coordinates, void *), void *data)
{
	CellCollection_At_Each_Cell(self->cell_collection, visitor, data);
}

void Game_Dump(const Game *self)
{
	CellCollection_Dump(self->cell_collection);
}
