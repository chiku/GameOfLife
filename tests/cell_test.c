START_TEST (test_Cell_Is_created_at_origin)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	long int x_coordinate = Cell_X(cell);
	fail_unless(x_coordinate == 0, "Expected x-coordinate of cell to be 0, but was %ld", x_coordinate);

	long int y_coordinate = Cell_Y(cell);
	fail_unless(y_coordinate == 0, "Expected y-coordinate of cell to be 0, but was %ld", y_coordinate);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Is_created_at_specified_world)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	fail_unless(Cell_World(cell) == world, "Expected cell to be be in the same world but wasn't");
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Is_created_at_specified_location)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize_At(world, 5, 4);

	long int x_coordinate = Cell_X(cell);
	fail_unless(x_coordinate == 5, "Expected x-coordinate of cell to be %ld, but was %ld", 5, x_coordinate);

	long int y_coordinate = Cell_Y(cell);
	fail_unless(y_coordinate == 4, "Expected y-coordinate of cell to be %ld, but was %ld", 4, y_coordinate);

	fail_unless(Cell_World(cell) == world, "Expected cell to be be in the same world but wasn't");
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_its_neighbour_to_north)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Initialize_At(world, 0, 1);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_its_neighbour_to_north_east)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Initialize_At(world, 1, 1);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_its_neighbour_to_east)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Initialize_At(world, 1, 0);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_its_neighbour_to_south_east)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Initialize_At(world, 1, -1);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_its_neighbour_to_south)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Initialize_At(world, 0, -1);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_its_neighbour_to_south_west)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Initialize_At(world, -1, -1);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_its_neighbour_to_west)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Initialize_At(world, -1, 0);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_its_neighbour_to_north_west)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Initialize_At(world, -1, 1);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_does_not_consider_far_away_cell_as_neighbours)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell_Initialize_At(world,  0,  2);	Cell_Initialize_At(world,  2,  2);
	Cell_Initialize_At(world,  2,  0);	Cell_Initialize_At(world,  2, -2);
	Cell_Initialize_At(world,  0, -2);	Cell_Initialize_At(world, -2, -2);
	Cell_Initialize_At(world, -2,  0);	Cell_Initialize_At(world, -2,  2);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 0, "Expected neighbour count to be %ld, but was %ld", 0, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Is_at_location_when_its_coordinates_and_world_match)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize_At(world, 3, 4);

	fail_unless(Cell_Is_At(cell, world, 3, 4), "Expected cell to be present at location (3, 4), but wasn't");
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Is_not_at_location_when_its_coordinates_do_not_match)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize_At(world, 3, 4);

	fail_if(Cell_Is_At(cell, world, 2, 4), "Expected cell to be not present at location (2, 4), but was");
	fail_if(Cell_Is_At(cell, world, 3, -4), "Expected cell to be not present at location (3, -4), but was");
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Is_not_at_location_when_its_world_does_not_match)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize_At(world, 3, 4);

	fail_if(Cell_Is_At(cell, World_Initialize(), 3, 4), "Expected cell to be present in different world, but wasn't");
	World_Destroy(world);
}
END_TEST

