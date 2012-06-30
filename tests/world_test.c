START_TEST (test_World_adds_cell)
{
	World *world = World_New();
	Cell cell = Cell_New(0, 0);
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

START_TEST (test_World_knows_count_of_neighbours_around_locations)
{
	World *world = World_New();
	Cell cell = Cell_New(0, 0);
	World_Add_Cell(world, cell);
	Coordinates locations[2];
	locations[0] = Coordinates_New(0, 1);
	locations[1] = Coordinates_New(3, 0);

	World_Add_Cell(world, Cell_New(0, 1)); /* neighbour */
	World_Add_Cell(world, Cell_New(3, 0)); /* neighbour */

	long int count = World_Cell_Count_Around(world, Coordinates_New(0, 0), locations, 2);
	fail_unless(count == 2, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_knows_does_not_count_cell_not_present_in_pool)
{
	World *world = World_New();
	Cell cell = Cell_New(0, 0);
	World_Add_Cell(world, cell);
	Coordinates locations[2];
	locations[0] = Coordinates_New(0, 1);
	locations[1] = Coordinates_New(3, 0);

	World_Add_Cell(world, Cell_New( 0,  2)); World_Add_Cell(world, Cell_New( 2,  2));
	World_Add_Cell(world, Cell_New( 2,  0)); World_Add_Cell(world, Cell_New( 2, -2));
	World_Add_Cell(world, Cell_New( 0, -2)); World_Add_Cell(world, Cell_New(-2, -2));
	World_Add_Cell(world, Cell_New(-2,  0)); World_Add_Cell(world, Cell_New(-2,  2));

	long int count = World_Cell_Count_Around(world, Coordinates_New(0, 0), locations, 2);
	fail_unless(count == 0, "Expected neighbour count to be %ld, but was %ld", 0, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_all_cell_locations_near_a_set)
{
	World *world = World_New();
	World_Add_Cell(world, Cell_New(0, 0));
	World_Add_Cell(world, Cell_New(1, 1));
	Coordinates locations[4];
	locations[0] = Coordinates_New(0, 1);
	locations[1] = Coordinates_New(1, 1);

	World *zone = World_All_Neighbours_For_Set(world, locations, 2);
	long int cell_count = World_Cell_Count(zone);
	fail_unless(cell_count == 4, "Expected cell count to be %ld, but was %ld", 4, cell_count);

	fail_unless(World_Has_Cell_At(zone, Coordinates_New( 1,  2)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  1,  2);
	fail_unless(World_Has_Cell_At(zone, Coordinates_New( 2,  2)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  2,  2);
	fail_unless(World_Has_Cell_At(zone, Coordinates_New( 1,  1)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  1,  1);
	fail_unless(World_Has_Cell_At(zone, Coordinates_New( 0,  1)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  0,  1);
	World_Destroy(world);
}
END_TEST

static long int sum_x, sum_y, trace;
static void cc_add_up_cell_values(Coordinates coordinates, void *data)
{
	sum_x += coordinates.x;
	sum_y += coordinates.y;
	trace = data ? *((long int*)data) : 0;
}

START_TEST (test_World_at_cells_is_visitable)
{
	World *world = World_New();
	World_Add_Cell(world, Cell_New(0, -1));
	World_Add_Cell(world, Cell_New(1, 5));

	World_At_Each_Cell(world, cc_add_up_cell_values, NULL);

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

	World_At_Each_Cell(world, cc_add_up_cell_values, expected_trace);

	fail_unless(trace == 100, "Expected trace %ld, but was %ld", *expected_trace, trace);
	free(expected_trace);
	World_Destroy(world);
}
END_TEST
