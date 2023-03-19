#include <stdio.h>

#include <world.h>
#include <game.h>
#include "minunit.h"

MU_TEST(test_Game_adds_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);

	mu_assert(World_Has_Cell_At(game->world, Coordinates_New(0, 0)), "Expected cell (0, 0) to be present, but wasn't");
	Game_Destroy(game);
}

MU_TEST(test_Game_creation_from_file_is_proper)
{
	FILE *fp;
	const char* file_name = "test.lif";

	fp = fopen(file_name, "w");
	fprintf(fp, "0 0\n0 1\n0 2");
	fclose(fp);

	Game* game = Game_Create_From_File(file_name);
	World* world = game->world;

	long int cell_count = World_Cell_Count(world);
	mu_assert_int_eq(3, cell_count);
	mu_assert(World_Has_Cell_At(world, Coordinates_New(0, 0)), "Expected world to contain cell (0, 0) but didn't'");
	mu_assert(World_Has_Cell_At(world, Coordinates_New(0, 1)), "Expected world to contain cell (0, 0) but didn't'");
	mu_assert(World_Has_Cell_At(world, Coordinates_New(0, 2)), "Expected world to contain cell (0, 0) but didn't'");
	Game_Destroy(game);
	remove(file_name);
}

MU_TEST(test_Game_neglects_lines_that_begin_with_hash_when_reading_file)
{
	FILE *fp;
	const char* file_name = "test.lif";

	fp = fopen(file_name, "w");
	fprintf(fp, "#Comment 0 0\n0 0\n0 1\n0 2\n#Some Comment");
	fclose(fp);

	Game* game = Game_Create_From_File(file_name);
	World* world = game->world;

	long int cell_count = World_Cell_Count(world);
	mu_assert_int_eq(3, cell_count);
	mu_assert(World_Has_Cell_At(world, Coordinates_New(0, 0)), "Expected world to contain cell (0, 0) but didn't");
	mu_assert(World_Has_Cell_At(world, Coordinates_New(0, 1)), "Expected world to contain cell (0, 1) but didn't");
	mu_assert(World_Has_Cell_At(world, Coordinates_New(0, 2)), "Expected world to contain cell (0, 2) but didn't");
	Game_Destroy(game);
	remove(file_name);
}

MU_TEST(test_Game_creation_is_allocation_followed_by_initialization)
{
	Game *allocated_game = Game_Allocate();
	Game *initialized_game = Game_Initialize(allocated_game);

	mu_assert(initialized_game == allocated_game, "Expected initialized game to have same memory location as allocated game, but didn't");
}

MU_TEST(test_Game_knows_neighbour_to_north_of_a_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 0, 1); /* neighbour */

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	mu_assert_int_eq(1, count);
	Game_Destroy(game);
}

MU_TEST(test_Game_knows_neighbour_to_north_east_of_a_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 1, 1); /* neighbour */

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	mu_assert_int_eq(1, count);
	Game_Destroy(game);
}

MU_TEST(test_Game_knows_neighbour_to_east_of_a_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 1, 0); /* neighbour */

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	mu_assert_int_eq(1, count);
	Game_Destroy(game);
}

MU_TEST(test_Game_knows_neighbour_to_south_east_of_a_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 1, -1); /* neighbour */

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	mu_assert_int_eq(1, count);
	Game_Destroy(game);
}

MU_TEST(test_Game_knows_neighbour_to_south_of_a_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 0, -1); /* neighbour */

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	mu_assert_int_eq(1, count);
	Game_Destroy(game);
}

MU_TEST(test_Game_knows_neighbour_to_south_west_of_a_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, -1, -1); /* neighbour */

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	mu_assert_int_eq(1, count);
	Game_Destroy(game);
}

MU_TEST(test_Game_knows_neighbour_to_west_of_a_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, -1, 0); /* neighbour */

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	mu_assert_int_eq(1, count);
	Game_Destroy(game);
}

MU_TEST(test_Game_knows_neighbour_to_north_west_of_a_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, -1, 1); /* neighbour */

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	mu_assert_int_eq(1, count);
	Game_Destroy(game);
}

MU_TEST(test_Game_does_not_consider_far_away_cell_as_neighbours)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game,  0,  0);
	Game_Add_Cell_At(game,  0,  2); Game_Add_Cell_At(game,  2,  2);
	Game_Add_Cell_At(game,  2,  0); Game_Add_Cell_At(game,  2, -2);
	Game_Add_Cell_At(game,  0, -2); Game_Add_Cell_At(game, -2, -2);
	Game_Add_Cell_At(game, -2,  0); Game_Add_Cell_At(game, -2,  2);

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	mu_assert_int_eq(0, count);
	Game_Destroy(game);
}

MU_TEST(test_Game_knows_living_cell_count_around_an_occupied_location)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game,  0, 0);
	Game_Add_Cell_At(game,  1, 1);
	Game_Add_Cell_At(game, -1, 0);

	long int cell_count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	mu_assert_int_eq(2, cell_count);
	Game_Destroy(game);
}

MU_TEST(test_Game_knows_living_cell_count_around_an_unoccupied_location)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game,  0, 0);
	Game_Add_Cell_At(game,  1, 1);
	Game_Add_Cell_At(game, -1, 0);

	long int cell_count = Game_Cell_Count_Around(game, Coordinates_New(-2, -1));
	mu_assert_int_eq(1, cell_count);
	Game_Destroy(game);
}

MU_TEST(test_Game_knows_all_cell_locations_near_all_living_cells)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 1, 1);

	World *active_zone = Game_Active_Zone(game);
	long int cell_count = World_Cell_Count(active_zone);
	mu_assert_int_eq(14, cell_count);

	mu_assert(World_Has_Cell_At(active_zone, Coordinates_New( 0,  2)), "Expected cell (0, 2) count to be present, but wasn't");
	mu_assert(World_Has_Cell_At(active_zone, Coordinates_New( 1,  2)), "Expected cell (1, 2) count to be present, but wasn't");
	mu_assert(World_Has_Cell_At(active_zone, Coordinates_New( 2,  2)), "Expected cell (2, 2) count to be present, but wasn't");
	mu_assert(World_Has_Cell_At(active_zone, Coordinates_New(-1,  1)), "Expected cell (-1, 1) count to be present, but wasn't");
	mu_assert(World_Has_Cell_At(active_zone, Coordinates_New( 1,  1)), "Expected cell (1, 1) count to be present, but wasn't");
	mu_assert(World_Has_Cell_At(active_zone, Coordinates_New( 0,  1)), "Expected cell (0, 1) count to be present, but wasn't");
	mu_assert(World_Has_Cell_At(active_zone, Coordinates_New( 2,  1)), "Expected cell (2, 1) count to be present, but wasn't");
	mu_assert(World_Has_Cell_At(active_zone, Coordinates_New(-1,  0)), "Expected cell (-1, 0) count to be present, but wasn't");
	mu_assert(World_Has_Cell_At(active_zone, Coordinates_New( 0,  0)), "Expected cell (0, 0) count to be present, but wasn't");
	mu_assert(World_Has_Cell_At(active_zone, Coordinates_New( 1,  0)), "Expected cell (1, 0) count to be present, but wasn't");
	mu_assert(World_Has_Cell_At(active_zone, Coordinates_New( 2,  0)), "Expected cell (2, 0) count to be present, but wasn't");
	mu_assert(World_Has_Cell_At(active_zone, Coordinates_New(-1, -1)), "Expected cell (-1, -1) count to be present, but wasn't");
	mu_assert(World_Has_Cell_At(active_zone, Coordinates_New( 0, -1)), "Expected cell (0, -1) count to be present, but wasn't");
	mu_assert(World_Has_Cell_At(active_zone, Coordinates_New( 1, -1)), "Expected cell (1, -1) count to be present, but wasn't");
	Game_Destroy(game);
}

static long int g_sum_x, g_sum_y, g_sum_gen, g_trace;
static void add_up_cell_values(Cell cell, void *data)
{
	g_sum_x += cell.coordinates.x;
	g_sum_y += cell.coordinates.y;
	g_sum_gen += cell.generation;
	g_trace = data ? *((long int*)data) : 0;
}
static void reset_add_up_cell_values()
{
	g_sum_x = 0;
	g_sum_y = 0;
	g_sum_gen = 0;
	g_trace = 0;
}

MU_TEST(test_Game_is_visitable_for_each_cell_of_current_generation)
{
	reset_add_up_cell_values();
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, -1);
	Game_Add_Cell_At(game, 1,  5);

	Game_At_Each_Cell(game, add_up_cell_values, NULL);

	mu_assert_int_eq(1, g_sum_x);
	mu_assert_int_eq(4, g_sum_y);
	mu_assert_int_eq(2, g_sum_gen);
	Game_Destroy(game);
}

MU_TEST(test_Game_visits_accept_custom_data)
{
	reset_add_up_cell_values();
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, -1);

	long int *expected_trace = (long int*)(malloc( sizeof(long int) ));
	*expected_trace = 100;

	Game_At_Each_Cell(game, add_up_cell_values, expected_trace);

	mu_assert_int_eq(100, g_trace);
	free(expected_trace);
	Game_Destroy(game);
}

MU_TEST(test_Game_is_visitable_for_each_cell_of_previous_generation)
{
	reset_add_up_cell_values();
	Game *game = Game_New();
	Game_Add_Cell_At(game, 1, 0);
	Game_Add_Cell_At(game, 0, 5);
	Game_Add_Cell_At(game, 1, 1);
	Game_Tick(game);

	Game_At_Each_Old_Cell(game, add_up_cell_values, NULL);

	mu_assert_int_eq(2, g_sum_x);
	mu_assert_int_eq(6, g_sum_y);
	Game_Destroy(game);
}

MU_TEST(test_Game_tick_preserves_previous_generation)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 1, 0);
	Game_Add_Cell_At(game, 0, 5);
	Game_Add_Cell_At(game, 1, 1);
	Game_Tick(game);

	long int count = World_Cell_Count(game->old_world);
	mu_assert_int_eq(3, count);
	mu_assert(World_Has_Cell_At(game->old_world, Coordinates_New(1, 0)), "Expected cell (1, 0) count to be present, but wasn't");
	mu_assert(World_Has_Cell_At(game->old_world, Coordinates_New(0, 5)), "Expected cell (0, 5) count to be present, but wasn't");
	mu_assert(World_Has_Cell_At(game->old_world, Coordinates_New(1, 1)), "Expected cell (1, 1) count to be present, but wasn't");
	Game_Destroy(game);
}

MU_TEST(test_Game_increases_the_number_of_generations_its_cells_have_been_alive_for_on_survival)
{
	long int gen;
	Game *game = Game_New();
	Game_Add_Cell_At(game, -1, 0);
	Game_Add_Cell_At(game,  0, 0);
	Game_Add_Cell_At(game,  1, 0);

	gen = World_Generation_For(game->world, Coordinates_New(0, 0));
	mu_assert_int_eq(1, gen);

	Game_Tick(game);

	gen = World_Generation_For(game->world, Coordinates_New(0, 0));
	mu_assert_int_eq(2, gen);

	Game_Tick(game);

	gen = World_Generation_For(game->world, Coordinates_New(0, 0));
	mu_assert_int_eq(3, gen);

	Game_Tick(game);

	gen = World_Generation_For(game->world, Coordinates_New(0, 0));
	mu_assert_int_eq(4, gen);

	Game_Destroy(game);
}

MU_TEST(test_Game_sets_number_of_generations_for_a_cell_to_zero_on_death)
{
	long int gen;
	Game *game = Game_New();
	Game_Add_Cell_At(game, -1, 0);
	Game_Add_Cell_At(game,  0, 0);
	Game_Add_Cell_At(game,  1, 0);

	gen = World_Generation_For(game->world, Coordinates_New(-1, 0));
	mu_assert_int_eq(1, gen);

	Game_Tick(game);

	gen = World_Generation_For(game->world, Coordinates_New(-1, 0));
	mu_assert_int_eq(0, gen);

	Game_Tick(game);

	gen = World_Generation_For(game->world, Coordinates_New(-1, 0));
	mu_assert_int_eq(1, gen);

	Game_Tick(game);

	gen = World_Generation_For(game->world, Coordinates_New(-1, 0));
	mu_assert_int_eq(0, gen);

	Game_Destroy(game);
}
