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

START_TEST (test_Cell_Is_spawned_relative_to_an_existing_cell)
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


START_TEST (test_Cell_Is_spawned_in_the_same_world)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Spawn_At(cell, 5, 8);

	World *other_world = Cell_World(another_cell);
	fail_unless(other_world == world, "Expected world of spawned cell to be in the same world");
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_its_neighbour_to_north)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Spawn_At(cell, 0, 1);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_its_neighbour_to_north_east)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Spawn_At(cell, 1, 1);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_its_neighbour_to_east)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Spawn_At(cell, 1, 0);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_its_neighbour_to_south_east)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Spawn_At(cell, 1, -1);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_its_neighbour_to_south)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Spawn_At(cell, 0, -1);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_its_neighbour_to_south_west)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Spawn_At(cell, -1, -1);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_its_neighbour_to_west)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Spawn_At(cell, -1, 0);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_its_neighbour_to_north_west)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *another_cell = Cell_Spawn_At(cell, -1, 1);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 1, "Expected neighbour count to be %ld, but was %ld", 1, count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_Cell_Knows_does_not_consider_far_away_cell_as_neighbours)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell_Spawn_At(cell,  0,  2);	Cell_Spawn_At(cell,  2,  2);
	Cell_Spawn_At(cell,  2,  0);	Cell_Spawn_At(cell,  2, -2);
	Cell_Spawn_At(cell,  0, -2);	Cell_Spawn_At(cell, -2, -2);
	Cell_Spawn_At(cell, -2,  0);	Cell_Spawn_At(cell, -2,  2);

	long int count = Cell_Total_Neighbours(cell);
	fail_unless(count == 0, "Expected neighbour count to be %ld, but was %ld", 0, count);
	World_Destroy(world);
}
END_TEST

