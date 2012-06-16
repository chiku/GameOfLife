START_TEST (test_Cell_is_created_at_specified_location)
{
	World *world = World_New();
	Cell *cell = Cell_New2(5, 4);
	World_Add_Cell2(world, cell);

	long int x_coordinate = Cell_X(cell);
	fail_unless(x_coordinate == 5, "Expected x-coordinate of cell to be %ld, but was %ld", 5, x_coordinate);

	long int y_coordinate = Cell_Y(cell);
	fail_unless(y_coordinate == 4, "Expected y-coordinate of cell to be %ld, but was %ld", 4, y_coordinate);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_creation_is_allocation_followed_by_initialization)
{
	World *world = World_New();
	Cell *allocated_cell = Cell_Allocate();
	Cell *initialized_cell = Cell_Initialize(allocated_cell, world, 10, 5);
	long int x_coordinate, y_coordinate;

	fail_unless(allocated_cell == initialized_cell, "Expected initialized cell to have same memory location as allocated cell, but didn't");

	fail_unless(Cell_World(initialized_cell) == world, "Expected cell to be in same world, but didn't");

	x_coordinate = Cell_X(initialized_cell);
	fail_unless(x_coordinate == 10, "Expected x-coordinate of cell to be %ld, but was %ld", 10, x_coordinate);

	y_coordinate = Cell_Y(initialized_cell);
	fail_unless(y_coordinate == 5, "Expected y-coordinate of cell to be %ld, but was %ld", 5, y_coordinate);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_knows_its_neighbour_to_north)
{
	World *world = World_New();
	Cell *cell = Cell_New(world, 0, 0);

	Cell_New(world, 0, 1); /* another cell */

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_knows_its_neighbour_to_north_east)
{
	World *world = World_New();
	Cell *cell = Cell_New(world, 0, 0);

	Cell_New(world, 1, 1); /* another cell */

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_knows_its_neighbour_to_east)
{
	World *world = World_New();
	Cell *cell = Cell_New(world, 0, 0);

	Cell_New(world, 1, 0); /* another cell */

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_knows_its_neighbour_to_south_east)
{
	World *world = World_New();
	Cell *cell = Cell_New(world, 0, 0);

	Cell_New(world, 1, -1); /* another cell */

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_knows_its_neighbour_to_south)
{
	World *world = World_New();
	Cell *cell = Cell_New(world, 0, 0);

	Cell_New(world, 0, -1); /* another cell */

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_knows_its_neighbour_to_south_west)
{
	World *world = World_New();
	Cell *cell = Cell_New(world, 0, 0);

	Cell_New(world, -1, -1); /* another cell */

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_knows_its_neighbour_to_west)
{
	World *world = World_New();
	Cell *cell = Cell_New(world, 0, 0);

	Cell_New(world, -1, 0); /* another cell */

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_knows_its_neighbour_to_north_west)
{
	World *world = World_New();
	Cell *cell = Cell_New(world, 0, 0);

	Cell_New(world, -1, 1); /* another cell */

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_knows_does_not_consider_far_away_cell_as_neighbours)
{
	World *world = World_New();
	Cell *cell = Cell_New(world, 0, 0);

	Cell_New(world,  0,  2);	Cell_New(world,  2,  2);
	Cell_New(world,  2,  0);	Cell_New(world,  2, -2);
	Cell_New(world,  0, -2);	Cell_New(world, -2, -2);
	Cell_New(world, -2,  0);	Cell_New(world, -2,  2);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 0, "Expected neighbour count to be %ld, but was %ld", 0, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_is_at_location_when_its_coordinates_match)
{
	World *world = World_New();
	Cell *cell = Cell_New2(3, 4);
	World_Add_Cell2(world, cell);

	fail_unless(Cell_Is_At2(cell, 3, 4), "Expected cell to be present at location (3, 4), but wasn't");
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_is_not_at_location_when_its_x_coordinates_do_not_match)
{
	World *world = World_New();
	Cell *cell = Cell_New2(3, 4);
	World_Add_Cell2(world, cell);

	fail_if(Cell_Is_At2(cell, 2, 4), "Expected cell to be not present at location (2, 4), but was");
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_is_not_at_location_when_its_y_coordinates_do_not_match)
{
	World *world = World_New();
	Cell *cell = Cell_New2(3, 4);
	World_Add_Cell2(world, cell);

	fail_if(Cell_Is_At2(cell, 3, -4), "Expected cell to be not present at location (3, -4), but was");
	World_Destroy(world);
}
END_TEST
