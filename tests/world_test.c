START_TEST (test_World_knows_its_cell_count)
{
	World *world = World_Initialize();
	Cell *first_cell = Cell_Initialize(world, 0, 0);
	Cell_Initialize(world, 1, 4);
	Cell_Initialize(world, 2, 4);

	long int cell_count = World_Cell_Count(world);
	fail_unless(cell_count == 3, "Expected cell count to be %ld, but was %ld", 3, cell_count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_its_cell_by_position)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world, 0, 0);

	fail_unless(World_Cell_At(world, 0, 0) == cell, "Excepted cell <address=%p> (0, 0) to be present in the world, but wasn't", cell);
	fail_unless(World_Cell_At(world, 0, 1) == '\0', "Excepted cell <address=%p> (0, 1) to be not present in the world, but was", cell);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_if_it_has_a_cell)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world, 0, 0);

	World *another_world = World_Initialize();
	Cell *another_cell = Cell_Initialize(another_world, 0, 0);

	fail_unless(World_Has_Cell(world, cell), "Excepted cell (address=%p) to be present in the world, but wasn't", cell);
	fail_if(World_Has_Cell(world, another_cell), "Excepted another cell (address=%p) to be not present in the world, but was", another_cell);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_if_it_has_a_cell_at_specified_location)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world, 0, 0);

	fail_unless(World_Has_Cell_At(world, 0, 0), "Excepted cell (x=%d, y=%d) to be present in the world, but wasn't", 0, 0);
	fail_if(World_Has_Cell_At(world, 1, 0), "Excepted cell (x=%d, y=%d) to be not present in the world, but was", 1, 0);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_does_not_have_a_cell_at_specified_location_when_cell_is_in_different_world)
{
	World *world = World_Initialize();
	Cell *cell_in_other_world = Cell_Initialize(World_Initialize(), 0, 0);

	fail_if(World_Has_Cell_At(world, 0, 0), "Excepted cell (x=%d, y=%d) to be not present in the world, but was", 0, 0);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_living_cell_count_around_an_occupied_location)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world, 0, 0);
	Cell_Initialize(world, 1, 1);
	Cell_Initialize(world, -1, 0);

	long int cell_count = World_Cell_Count_Around(world, 0, 0);
	fail_unless(cell_count == 2, "Expected cell count to be %ld, but was %ld", 2, cell_count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_living_cell_count_around_an_unoccupied_location)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world, 0, 0);
	Cell_Initialize(world, 1, 1);
	Cell_Initialize(world, -1, 0);

	long int cell_count = World_Cell_Count_Around(world, -2, -1);
	fail_unless(cell_count == 1, "Expected cell count to be %ld, but was %ld", 1, cell_count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_all_cell_locations_near_all_living_cells)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world, 0, 0);
	Cell_Initialize(world, 1, 1);

	World *active_zone = World_Active_Zone(world);
	long int cell_count = World_Cell_Count(active_zone);
	fail_unless(cell_count == 14, "Expected cell count to be %ld, but was %ld", 14, cell_count);

	fail_unless(World_Has_Cell_At(active_zone,  0,  2), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  0,  2);
	fail_unless(World_Has_Cell_At(active_zone,  1,  2), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  1,  2);
	fail_unless(World_Has_Cell_At(active_zone,  2,  2), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  2,  2);
	fail_unless(World_Has_Cell_At(active_zone, -1,  1), "Expected cell (x=%d,y=%d) count to be present, but wasn't", -1,  1);
	fail_unless(World_Has_Cell_At(active_zone,  1,  1), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  1,  1);
	fail_unless(World_Has_Cell_At(active_zone,  0,  1), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  0,  1);
	fail_unless(World_Has_Cell_At(active_zone,  2,  1), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  2,  1);
	fail_unless(World_Has_Cell_At(active_zone, -1,  0), "Expected cell (x=%d,y=%d) count to be present, but wasn't", -1,  0);
	fail_unless(World_Has_Cell_At(active_zone,  0,  0), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  0,  0);
	fail_unless(World_Has_Cell_At(active_zone,  1,  0), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  1,  0);
	fail_unless(World_Has_Cell_At(active_zone,  2,  0), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  2,  0);
	fail_unless(World_Has_Cell_At(active_zone, -1, -1), "Expected cell (x=%d,y=%d) count to be present, but wasn't", -1, -1);
	fail_unless(World_Has_Cell_At(active_zone,  0, -1), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  0, -1);
	fail_unless(World_Has_Cell_At(active_zone,  1, -1), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  1, -1);
	World_Destroy(world);
}
END_TEST

