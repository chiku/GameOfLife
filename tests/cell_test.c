START_TEST (test_Cell_is_created_at_specified_location)
{
	Cell cell = Cell_New(5, 4);

	Coordinates coordinates = Cell_Coordinates(cell);
	fail_unless(coordinates.x == 5, "Expected x-coordinate of cell to be %ld, but was %ld", 5, coordinates.x);
	fail_unless(coordinates.y == 4, "Expected y-coordinate of cell to be %ld, but was %ld", 4, coordinates.y);
}
END_TEST

START_TEST (test_Cell_is_created_from_coordinates)
{
	Cell cell = Cell_New_From_Coordinates(Coordinates_New(5, 4));

	Coordinates coordinates = Cell_Coordinates(cell);
	fail_unless(coordinates.x == 5, "Expected x-coordinate of cell to be %ld, but was %ld", 5, coordinates.x);
	fail_unless(coordinates.y == 4, "Expected y-coordinate of cell to be %ld, but was %ld", 4, coordinates.y);
}
END_TEST

START_TEST (test_Cell_is_at_first_generation_upon_creation)
{
	Cell cell1 = Cell_New(0, 0);
	fail_unless(cell1.generation == 1, "Expected cell generation to be %ld, but was %ld", 1, cell1.generation);

	Cell cell2 = Cell_New_From_Coordinates(Coordinates_New(0, 0));
	fail_unless(cell2.generation == 1, "Expected cell generation to be %ld, but was %ld", 1, cell2.generation);
}
END_TEST

START_TEST (test_Cell_generation_can_be_incremented_when_created)
{
	Cell cell = Cell_New_From_Coordinates_With_Incremented_Generation(Coordinates_New(5, 4), 5);

	Coordinates coordinates = Cell_Coordinates(cell);
	fail_unless(coordinates.x == 5, "Expected x-coordinate of cell to be %ld, but was %ld", 5, coordinates.x);
	fail_unless(coordinates.y == 4, "Expected y-coordinate of cell to be %ld, but was %ld", 4, coordinates.y);
	fail_unless(cell.generation == 6, "Expected generation of cell to be %ld, but was %ld", 6, cell.generation);
}
END_TEST

START_TEST (test_Cell_is_at_location_when_its_coordinates_match)
{
	Cell cell = Cell_New(3, 4);

	fail_unless(Cell_Is_At(cell, Coordinates_New(3, 4)), "Expected cell to be present at location (%ld, %ld), but wasn't", 3, 4);
}
END_TEST

START_TEST (test_Cell_is_not_at_location_when_its_x_coordinates_do_not_match)
{
	Cell cell = Cell_New(3, 4);

	fail_if(Cell_Is_At(cell, Coordinates_New(2, 4)), "Expected cell to be not present at location (%ld, %ld), but was", 2, 4);
}
END_TEST

START_TEST (test_Cell_is_not_at_location_when_its_y_coordinates_do_not_match)
{
	Cell cell = Cell_New(3, 4);

	fail_if(Cell_Is_At(cell, Coordinates_New(3, -4)), "Expected cell to be not present at location (%ld, %ld), but was", 3, -4);
}
END_TEST
