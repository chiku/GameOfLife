START_TEST (test_World_adds_cell)
{
	World *world = World_New();
	Cell *cell = Cell_New(0, 0);
	World_Add_Cell(world, cell);

	fail_unless(World_Has_Cell_At(world, Coordinates_New(0, 0)), "Expected cell (address=%p) to be present, but wasn't", cell);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_does_not_add_cell_if_cell_already_exists_in_the_world)
{
	World *world = World_New();
	World_Add_Cell(world, Cell_New(5, 4));
	World_Add_Cell(world, Cell_New(5, 4));

	long cell_count = World_Cell_Count(world);
	fail_unless(World_Cell_Count(world) == 1, "Expected world to contain %ld cell, but contained %ld", 1, cell_count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_creation_from_file_is_proper)
{
	const char file_name[] = "data/oscillator.lif";
	World* world = World_Create_From_File(file_name);

	long int cell_count = World_Cell_Count(world);
	fail_unless(cell_count == 3, "Expected cell count to be %ld, but was %ld", 3, cell_count);
	fail_unless(World_Has_Cell_At(world, Coordinates_New(0, 0)), "Expected world to contain cell (%d, %d) but didn't'", 0, 0);
	fail_unless(World_Has_Cell_At(world, Coordinates_New(0, 1)), "Expected world to contain cell (%d, %d) but didn't'", 0, 0);
	fail_unless(World_Has_Cell_At(world, Coordinates_New(0, 2)), "Expected world to contain cell (%d, %d) but didn't'", 0, 0);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_creation_is_allocation_followed_by_initialization)
{
	World *allocated_world = World_Allocate();
	World *initialized_world = World_Initialize(allocated_world);

	fail_unless(initialized_world == allocated_world, "Expected initialized world to have same memory location as allocated world, but didn't");
}
END_TEST

START_TEST (test_World_knows_its_cell_count)
{
	World *world = World_New();
	World_Add_Cell(world, Cell_New(0, 0));
	World_Add_Cell(world, Cell_New(1, 4));
	World_Add_Cell(world, Cell_New(2, 4));

	long int cell_count = World_Cell_Count(world);
	fail_unless(cell_count == 3, "Expected cell count to be %ld, but was %ld", 3, cell_count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_if_it_has_a_cell_at_specified_location)
{
	World *world = World_New();
	World_Add_Cell(world, Cell_New(0, 0));

	fail_unless(World_Has_Cell_At(world, Coordinates_New(0, 0)), "Excepted cell (x=%d, y=%d) to be present in the world, but wasn't", 0, 0);
	fail_if(World_Has_Cell_At(world, Coordinates_New(1, 0)), "Excepted cell (x=%d, y=%d) to be not present in the world, but was", 1, 0);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_does_not_have_a_cell_at_specified_location_when_cell_is_in_different_world)
{
	World *world = World_New();
	World_Add_Cell(World_New(), Cell_New(0, 0)); /* cell in another world */

	fail_if(World_Has_Cell_At(world, Coordinates_New(0, 0)), "Excepted cell (x=%d, y=%d) to be not present in the world, but was", 0, 0);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_neighbour_to_north_of_a_cell)
{
	World *world = World_New();
	Cell *cell = Cell_New(0, 0);
	World_Add_Cell(world, cell);

	World_Add_Cell(world, Cell_New(0, 1)); /* neighbour */

	long int count = World_Cell_Count_Around(world, Coordinates_New(0, 0));
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_neighbour_to_north_east_of_a_cell)
{
	World *world = World_New();
	Cell *cell = Cell_New(0, 0);
	World_Add_Cell(world, cell);

	World_Add_Cell(world, Cell_New(1, 1)); /* neighbour */

	long int count = World_Cell_Count_Around(world, Coordinates_New(0, 0));
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_neighbour_to_east_of_a_cell)
{
	World *world = World_New();
	Cell *cell = Cell_New(0, 0);
	World_Add_Cell(world, cell);

	World_Add_Cell(world, Cell_New(1, 0)); /* neighbour */

	long int count = World_Cell_Count_Around(world, Coordinates_New(0, 0));
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_neighbour_to_south_east_of_a_cell)
{
	World *world = World_New();
	Cell *cell = Cell_New(0, 0);
	World_Add_Cell(world, cell);

	World_Add_Cell(world, Cell_New(1, -1)); /* neighbour */

	long int count = World_Cell_Count_Around(world, Coordinates_New(0, 0));
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_neighbour_to_south_of_a_cell)
{
	World *world = World_New();
	Cell *cell = Cell_New(0, 0);
	World_Add_Cell(world, cell);

	World_Add_Cell(world, Cell_New(0, -1)); /* neighbour */

	long int count = World_Cell_Count_Around(world, Coordinates_New(0, 0));
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_neighbour_to_south_west_of_a_cell)
{
	World *world = World_New();
	Cell *cell = Cell_New(0, 0);
	World_Add_Cell(world, cell);

	World_Add_Cell(world, Cell_New(-1, -1)); /* neighbour */

	long int count = World_Cell_Count_Around(world, Coordinates_New(0, 0));
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_neighbour_to_west_of_a_cell)
{
	World *world = World_New();
	Cell *cell = Cell_New(0, 0);
	World_Add_Cell(world, cell);

	World_Add_Cell(world, Cell_New(-1, 0)); /* neighbour */

	long int count = World_Cell_Count_Around(world, Coordinates_New(0, 0));
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_neighbour_to_north_west_of_a_cell)
{
	World *world = World_New();
	Cell *cell = Cell_New(0, 0);
	World_Add_Cell(world, cell);

	World_Add_Cell(world, Cell_New(-1, 1)); /* neighbour */

	long int count = World_Cell_Count_Around(world, Coordinates_New(0, 0));
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_knows_does_not_consider_far_away_cell_as_neighbours)
{
	World *world = World_New();
	Cell *cell = Cell_New(0, 0);
	World_Add_Cell(world, cell);

	World_Add_Cell(world, Cell_New( 0,  2)); World_Add_Cell(world, Cell_New( 2,  2));
	World_Add_Cell(world, Cell_New( 2,  0)); World_Add_Cell(world, Cell_New( 2, -2));
	World_Add_Cell(world, Cell_New( 0, -2)); World_Add_Cell(world, Cell_New(-2, -2));
	World_Add_Cell(world, Cell_New(-2,  0)); World_Add_Cell(world, Cell_New(-2,  2));

	long int count = World_Cell_Count_Around(world, Coordinates_New(0, 0));
	fail_unless(count == 0, "Expected neighbour count to be %ld, but was %ld", 0, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_living_cell_count_around_an_occupied_location)
{
	World *world = World_New();
	World_Add_Cell(world, Cell_New(0, 0));
	World_Add_Cell(world, Cell_New(1, 1));
	World_Add_Cell(world, Cell_New(-1, 0));

	long int cell_count = World_Cell_Count_Around(world, Coordinates_New(0, 0));
	fail_unless(cell_count == 2, "Expected cell count to be %ld, but was %ld", 2, cell_count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_living_cell_count_around_an_unoccupied_location)
{
	World *world = World_New();
	World_Add_Cell(world, Cell_New(0, 0));
	World_Add_Cell(world, Cell_New(1, 1));
	World_Add_Cell(world, Cell_New(-1, 0));

	long int cell_count = World_Cell_Count_Around(world, Coordinates_New(-2, -1));
	fail_unless(cell_count == 1, "Expected cell count to be %ld, but was %ld", 1, cell_count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_all_cell_locations_near_all_living_cells)
{
	World *world = World_New();
	World_Add_Cell(world, Cell_New(0, 0));
	World_Add_Cell(world, Cell_New(1, 1));

	World *active_zone = World_Active_Zone(world);
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
	World_Destroy(world);
}
END_TEST

static long int sum_x, sum_y, trace;
static void add_up_cell_values(long int x, long int y, void *data)
{
	sum_x += x;
	sum_y += y;
	trace = data ? *((long int*)data) : 0;
}

START_TEST (test_World_at_cells_is_visitable)
{
	World *world = World_New();
	World_Add_Cell(world, Cell_New(0, -1));
	World_Add_Cell(world, Cell_New(1, 5));

	World_At_Each_Cell(world, add_up_cell_values, NULL);

	fail_unless(sum_x == 1, "Expected sum of x's to be %ld, but was %ld", 1, sum_x);
	fail_unless(sum_y == 4, "Expected sum of x's to be %ld, but was %ld", 4, sum_y);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_visits_accept_custom_data)
{
	World *world = World_New();
	World_Add_Cell(world, Cell_New(0, -1));

	long int *expected_trace = (long int*)(malloc( sizeof(long int) ));
	*expected_trace = 100;

	World_At_Each_Cell(world, add_up_cell_values, expected_trace);

	fail_unless(trace == 100, "Expected trace %ld, but was %ld", *expected_trace, trace);
	free(expected_trace);
	World_Destroy(world);
}
END_TEST
