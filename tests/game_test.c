START_TEST (test_Game_adds_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);

	fail_unless(World_Has_Cell_At(game->world, Coordinates_New(0, 0)), "Expected cell (%ld, %ld) to be present, but wasn't", 0, 0);
	Game_Destroy(game);
}
END_TEST

START_TEST (test_Game_creation_from_file_is_proper)
{
	const char file_name[] = "data/oscillator.lif";
	Game* game = Game_Create_From_File(file_name);
	World* world = game->world;

	long int cell_count = World_Cell_Count(world);
	fail_unless(cell_count == 3, "Expected cell count to be %ld, but was %ld", 3, cell_count);
	fail_unless(World_Has_Cell_At(world, Coordinates_New(0, 0)), "Expected world to contain cell (%d, %d) but didn't'", 0, 0);
	fail_unless(World_Has_Cell_At(world, Coordinates_New(0, 1)), "Expected world to contain cell (%d, %d) but didn't'", 0, 0);
	fail_unless(World_Has_Cell_At(world, Coordinates_New(0, 2)), "Expected world to contain cell (%d, %d) but didn't'", 0, 0);
	Game_Destroy(game);
}
END_TEST

START_TEST (test_Game_creation_is_allocation_followed_by_initialization)
{
	Game *allocated_game = Game_Allocate();
	Game *initialized_game = Game_Initialize(allocated_game);

	fail_unless(initialized_game == allocated_game, "Expected initialized game to have same memory location as allocated game, but didn't");
}
END_TEST

START_TEST (test_Game_knows_neighbour_to_north_of_a_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 0, 1); /* neighbour */

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	Game_Destroy(game);
}
END_TEST

START_TEST (test_Game_knows_neighbour_to_north_east_of_a_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 1, 1); /* neighbour */

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	Game_Destroy(game);
}
END_TEST

START_TEST (test_Game_knows_neighbour_to_east_of_a_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 1, 0); /* neighbour */

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	Game_Destroy(game);
}
END_TEST

START_TEST (test_Game_knows_neighbour_to_south_east_of_a_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 1, -1); /* neighbour */

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	Game_Destroy(game);
}
END_TEST

START_TEST (test_Game_knows_neighbour_to_south_of_a_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 0, -1); /* neighbour */

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	Game_Destroy(game);
}
END_TEST

START_TEST (test_Game_knows_neighbour_to_south_west_of_a_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, -1, -1); /* neighbour */

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	Game_Destroy(game);
}
END_TEST

START_TEST (test_Game_knows_neighbour_to_west_of_a_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, -1, 0); /* neighbour */

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	Game_Destroy(game);
}
END_TEST

START_TEST (test_Game_knows_neighbour_to_north_west_of_a_cell)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, -1, 1); /* neighbour */

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	Game_Destroy(game);
}
END_TEST

START_TEST (test_Cell_knows_does_not_consider_far_away_cell_as_neighbours)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game,  0,  0);
	Game_Add_Cell_At(game,  0,  2); Game_Add_Cell_At(game,  2,  2);
	Game_Add_Cell_At(game,  2,  0); Game_Add_Cell_At(game,  2, -2);
	Game_Add_Cell_At(game,  0, -2); Game_Add_Cell_At(game, -2, -2);
	Game_Add_Cell_At(game, -2,  0); Game_Add_Cell_At(game, -2,  2);

	long int count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	fail_unless(count == 0, "Expected neighbour count to be %ld, but was %ld", 0, count);
	Game_Destroy(game);
}
END_TEST

START_TEST (test_Game_knows_living_cell_count_around_an_occupied_location)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game,  0, 0);
	Game_Add_Cell_At(game,  1, 1);
	Game_Add_Cell_At(game, -1, 0);

	long int cell_count = Game_Cell_Count_Around(game, Coordinates_New(0, 0));
	fail_unless(cell_count == 2, "Expected cell count to be %ld, but was %ld", 2, cell_count);
	Game_Destroy(game);
}
END_TEST

START_TEST (test_Game_knows_living_cell_count_around_an_unoccupied_location)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game,  0, 0);
	Game_Add_Cell_At(game,  1, 1);
	Game_Add_Cell_At(game, -1, 0);

	long int cell_count = Game_Cell_Count_Around(game, Coordinates_New(-2, -1));
	fail_unless(cell_count == 1, "Expected cell count to be %ld, but was %ld", 1, cell_count);
	Game_Destroy(game);
}
END_TEST

START_TEST (test_Game_knows_all_cell_locations_near_all_living_cells)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, 0);
	Game_Add_Cell_At(game, 1, 1);

	World *active_zone = Game_Active_Zone(game);
	long int cell_count = World_Cell_Count(active_zone);
	fail_unless(cell_count == 14, "Expected cell count to be %ld, but was %ld", 14, cell_count);

	fail_unless(World_Has_Cell_At(active_zone, Coordinates_New( 0,  2)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  0,  2);
	fail_unless(World_Has_Cell_At(active_zone, Coordinates_New( 1,  2)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  1,  2);
	fail_unless(World_Has_Cell_At(active_zone, Coordinates_New( 2,  2)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  2,  2);
	fail_unless(World_Has_Cell_At(active_zone, Coordinates_New(-1,  1)), "Expected cell (x=%d,y=%d) count to be present, but wasn't", -1,  1);
	fail_unless(World_Has_Cell_At(active_zone, Coordinates_New( 1,  1)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  1,  1);
	fail_unless(World_Has_Cell_At(active_zone, Coordinates_New( 0,  1)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  0,  1);
	fail_unless(World_Has_Cell_At(active_zone, Coordinates_New( 2,  1)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  2,  1);
	fail_unless(World_Has_Cell_At(active_zone, Coordinates_New(-1,  0)), "Expected cell (x=%d,y=%d) count to be present, but wasn't", -1,  0);
	fail_unless(World_Has_Cell_At(active_zone, Coordinates_New( 0,  0)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  0,  0);
	fail_unless(World_Has_Cell_At(active_zone, Coordinates_New( 1,  0)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  1,  0);
	fail_unless(World_Has_Cell_At(active_zone, Coordinates_New( 2,  0)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  2,  0);
	fail_unless(World_Has_Cell_At(active_zone, Coordinates_New(-1, -1)), "Expected cell (x=%d,y=%d) count to be present, but wasn't", -1, -1);
	fail_unless(World_Has_Cell_At(active_zone, Coordinates_New( 0, -1)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  0, -1);
	fail_unless(World_Has_Cell_At(active_zone, Coordinates_New( 1, -1)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  1, -1);
	Game_Destroy(game);
}
END_TEST

static long int g_sum_x, g_sum_y, g_trace;
static void add_up_cell_values(Coordinates coordinates, void *data)
{
	g_sum_x += coordinates.x;
	g_sum_y += coordinates.y;
	g_trace = data ? *((long int*)data) : 0;
}

START_TEST (test_Game_at_cells_is_visitable)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, -1);
	Game_Add_Cell_At(game, 1,  5);

	Game_At_Each_Cell(game, add_up_cell_values, NULL);

	fail_unless(g_sum_x == 1, "Expected sum of x's to be %ld, but was %ld", 1, g_sum_x);
	fail_unless(g_sum_y == 4, "Expected sum of x's to be %ld, but was %ld", 4, g_sum_y);
	Game_Destroy(game);
}
END_TEST

START_TEST (test_Game_visits_accept_custom_data)
{
	Game *game = Game_New();
	Game_Add_Cell_At(game, 0, -1);

	long int *expected_trace = (long int*)(malloc( sizeof(long int) ));
	*expected_trace = 100;

	Game_At_Each_Cell(game, add_up_cell_values, expected_trace);

	fail_unless(g_trace == 100, "Expected trace %ld, but was %ld", *expected_trace, g_trace);
	free(expected_trace);
	Game_Destroy(game);
}
END_TEST
