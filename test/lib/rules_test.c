#include <game.h>
#include <cell.h>
#include "minunit.h"

MU_TEST(test_Rule_1_Any_live_cell_with_zero_live_neighbours_dies_As_if_caused_by_under_population)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);

	game = Game_Tick(game);

	int cell_present = World_Has_Cell_At(game->world, Coordinates_New(0, 0));
	mu_assert(!cell_present, "Cell (0, 0) was present, when it should have died");

	Game_Destroy(game);
}

MU_TEST(test_Rule_1_Any_live_cell_with_one_live_neighbour_dies_As_if_caused_by_under_population)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 0, 1);

	game = Game_Tick(game);

	int cell_present = World_Has_Cell_At(game->world, Coordinates_New(0, 0));
	mu_assert(!cell_present, "Cell (0, 0) was present, when it should have died");

	Game_Destroy(game);
}

MU_TEST(test_Rule_2_Any_live_cell_with_two_live_neighbours_lives_on_to_the_next_generation)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 0, 1);
	Game_Add_Cell_At(game, 1, 1);

	game = Game_Tick(game);

	int cell_present = World_Has_Cell_At(game->world, Coordinates_New(0, 0));
	mu_assert(cell_present, "Cell (0, 0) was not present, when it should have lived");

	Game_Destroy(game);
}

MU_TEST(test_Rule_2_Any_live_cell_with_three_live_neighbours_lives_on_to_the_next_generation)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 0, 1);
	Game_Add_Cell_At(game, 1, 0);
	Game_Add_Cell_At(game, 1, 1);

	game = Game_Tick(game);

	int cell_present = World_Has_Cell_At(game->world, Coordinates_New(0, 0));
	mu_assert(cell_present, "Cell (0, 0) was not present, when it should have lived");

	Game_Destroy(game);
}

MU_TEST(test_Rule_3_Any_live_cell_with_more_than_three_live_neighbours_dies_As_if_by_overcrowding)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 0, 1);
	Game_Add_Cell_At(game, 1, 0);
	Game_Add_Cell_At(game, 1, 1);
	Game_Add_Cell_At(game, -1, 1);

	game = Game_Tick(game);

	int cell_present = World_Has_Cell_At(game->world, Coordinates_New(0, 0));
	mu_assert(!cell_present, "Cell (0, 0) was present, when it should have died");

	Game_Destroy(game);
}

MU_TEST(test_Rule_4_Any_dead_cell_with_exactly_three_live_neighbours_becomes_a_live_cell_As_if_by_reproduction)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 0, 1);
	Game_Add_Cell_At(game, 1, 1);

	game = Game_Tick(game);

	int cell_present = World_Has_Cell_At(game->world, Coordinates_New(1, 0));
	mu_assert(cell_present, "Cell (1, 0) was not present, when it should have come alive");

	Game_Destroy(game);
}


MU_TEST(test_Rule_4_Any_dead_cell_with_two_live_neighbours_does_not_become_a_live_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 0, 1);

	game = Game_Tick(game);

	int cell_present = World_Has_Cell_At(game->world, Coordinates_New(1, 0));
	mu_assert(!cell_present, "Cell (1, 0) was present, when it shouldn't have come alive");

	Game_Destroy(game);
}


MU_TEST(test_Rule_4_Any_dead_cell_with_four_live_neighbours_does_not_become_a_live_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 0, 1);
	Game_Add_Cell_At(game, 1, 1);
	Game_Add_Cell_At(game, 0, -1);

	game = Game_Tick(game);

	int cell_present = World_Has_Cell_At(game->world, Coordinates_New(1, 0));
	mu_assert(!cell_present, "Cell (1, 0) was present, when it shouldn't have come alive");

	Game_Destroy(game);
}
