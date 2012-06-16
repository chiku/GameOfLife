START_TEST (test_Cell_is_created_at_specified_location)
{
	Cell cell = Cell_New(5, 4);

	long int x_coordinate = Cell_Coordinates(cell).x;
	fail_unless(x_coordinate == 5, "Expected x-coordinate of cell to be %ld, but was %ld", 5, x_coordinate);

	long int y_coordinate = Cell_Coordinates(cell).y;
	fail_unless(y_coordinate == 4, "Expected y-coordinate of cell to be %ld, but was %ld", 4, y_coordinate);
}
END_TEST

START_TEST (test_Cell_is_at_location_when_its_coordinates_match)
{
	World *world = World_New();
	Cell cell = Cell_New(3, 4);
	World_Add_Cell(world, cell);

	fail_unless(Cell_Is_At(cell, Coordinates_New(3, 4)), "Expected cell to be present at location (%ld, %ld), but wasn't", 3, 4);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_is_not_at_location_when_its_x_coordinates_do_not_match)
{
	World *world = World_New();
	Cell cell = Cell_New(3, 4);
	World_Add_Cell(world, cell);

	fail_if(Cell_Is_At(cell, Coordinates_New(2, 4)), "Expected cell to be not present at location (%ld, %ld), but was", 2, 4);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_is_not_at_location_when_its_y_coordinates_do_not_match)
{
	World *world = World_New();
	Cell cell = Cell_New(3, 4);
	World_Add_Cell(world, cell);

	fail_if(Cell_Is_At(cell, Coordinates_New(3, -4)), "Expected cell to be not present at location (%ld, %ld), but was", 3, -4);
	World_Destroy(world);
}
END_TEST
