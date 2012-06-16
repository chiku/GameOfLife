START_TEST (test_Cell_is_created_at_specified_location)
{
	Cell *cell = Cell_New(5, 4);

	long int x_coordinate = Cell_X(cell);
	fail_unless(x_coordinate == 5, "Expected x-coordinate of cell to be %ld, but was %ld", 5, x_coordinate);

	long int y_coordinate = Cell_Y(cell);
	fail_unless(y_coordinate == 4, "Expected y-coordinate of cell to be %ld, but was %ld", 4, y_coordinate);
	Cell_Destroy(cell);
}
END_TEST

START_TEST (test_Cell_creation_is_allocation_followed_by_initialization)
{
	Cell *allocated_cell = Cell_Allocate();
	Cell *initialized_cell = Cell_Initialize(allocated_cell, 10, 5);
	long int x_coordinate, y_coordinate;

	fail_unless(allocated_cell == initialized_cell, "Expected initialized cell to have same memory location as allocated cell, but didn't");

	x_coordinate = Cell_X(initialized_cell);
	fail_unless(x_coordinate == 10, "Expected x-coordinate of cell to be %ld, but was %ld", 10, x_coordinate);

	y_coordinate = Cell_Y(initialized_cell);
	fail_unless(y_coordinate == 5, "Expected y-coordinate of cell to be %ld, but was %ld", 5, y_coordinate);
	Cell_Destroy(allocated_cell);
}
END_TEST

START_TEST (test_Cell_is_at_location_when_its_coordinates_match)
{
	World *world = World_New();
	Cell *cell = Cell_New(3, 4);
	World_Add_Cell(world, cell);

	fail_unless(Cell_Is_At(cell, 3, 4), "Expected cell to be present at location (3, 4), but wasn't");
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_is_not_at_location_when_its_x_coordinates_do_not_match)
{
	World *world = World_New();
	Cell *cell = Cell_New(3, 4);
	World_Add_Cell(world, cell);

	fail_if(Cell_Is_At(cell, 2, 4), "Expected cell to be not present at location (2, 4), but was");
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_is_not_at_location_when_its_y_coordinates_do_not_match)
{
	World *world = World_New();
	Cell *cell = Cell_New(3, 4);
	World_Add_Cell(world, cell);

	fail_if(Cell_Is_At(cell, 3, -4), "Expected cell to be not present at location (3, -4), but was");
	World_Destroy(world);
}
END_TEST
