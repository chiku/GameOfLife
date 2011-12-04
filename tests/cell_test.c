START_TEST (test_Cell_is_created_at_specified_world)
{
	World *world = World_New();
	Cell *cell = Cell_New(world, 0, 0);

	fail_unless(Cell_World(cell) == world, "Expected cell to be be in the same world but wasn't");
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_is_created_at_specified_location)
{
	World *world = World_New();
	Cell *cell = Cell_New(world, 5, 4);

	long int x_coordinate = Cell_X(cell);
	fail_unless(x_coordinate == 5, "Expected x-coordinate of cell to be %ld, but was %ld", 5, x_coordinate);

	long int y_coordinate = Cell_Y(cell);
	fail_unless(y_coordinate == 4, "Expected y-coordinate of cell to be %ld, but was %ld", 4, y_coordinate);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_is_not_created_if_it_already_exists_in_the_world)
{
	World *world = World_New();
	Cell *original = Cell_New(world, 5, 4);
	Cell *duplicate = Cell_New(world, 5, 4);

	fail_unless(duplicate == original, "Expected duplicate cell (address=%p) to be same as original cell (address=%p), but wasn't", duplicate, original);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_creation_is_allocation_followed_by_initialization)
{
	World *world = World_New();
	Cell *allocatedCell = Cell_Allocate();
	Cell *initializedCell = Cell_Initialize(allocatedCell, world, 10, 5);
	long int x_coordinate, y_coordinate;

	fail_unless(allocatedCell == initializedCell, "Expected allocated cell to share after initiazation, but didn't");

	fail_unless(Cell_World(initializedCell) == world, "Expected cell to be in same world, but didn't");

	x_coordinate = Cell_X(initializedCell);
	fail_unless(x_coordinate == 10, "Expected x-coordinate of cell to be %ld, but was %ld", 10, x_coordinate);

	y_coordinate = Cell_Y(initializedCell);
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

START_TEST (test_Cell_is_at_location_when_its_coordinates_and_world_match)
{
	World *world = World_New();
	Cell *cell = Cell_New(world, 3, 4);

	fail_unless(Cell_Is_At(cell, world, 3, 4), "Expected cell to be present at location (3, 4), but wasn't");
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_is_not_at_location_when_its_coordinates_do_not_match)
{
	World *world = World_New();
	Cell *cell = Cell_New(world, 3, 4);

	fail_if(Cell_Is_At(cell, world, 2, 4), "Expected cell to be not present at location (2, 4), but was");
	fail_if(Cell_Is_At(cell, world, 3, -4), "Expected cell to be not present at location (3, -4), but was");
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_is_not_at_location_when_its_world_does_not_match)
{
	World *world = World_New();
	Cell *cell = Cell_New(world, 3, 4);

	fail_if(Cell_Is_At(cell, World_New(), 3, 4), "Expected cell to be present in different world, but wasn't");
	World_Destroy(world);
}
END_TEST

