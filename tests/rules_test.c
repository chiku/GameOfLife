START_TEST (test_Rule_1_Any_live_cell_with_zero_live_neighbours_dies_As_if_caused_by_under_population)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	World_Tick(world);

	int cell_present = World_Has_Cell(world, cell);
	fail_if(cell_present, "Cell (address=%p) was present, when it should have died", cell);

	World_Destroy(world);
}
END_TEST

START_TEST (test_Rule_1_Any_live_cell_with_one_live_neighbour_dies_As_if_caused_by_under_population)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);
	Cell_Initialize_At(world, 0, 1);

	World_Tick(world);

	int cell_present = World_Has_Cell(world, cell);
	fail_if(cell_present, "Cell (address=%p) was present, when it should have died", cell);

	World_Destroy(world);
}
END_TEST

START_TEST (test_Rule_2_Any_live_cell_with_two_live_neighbours_lives_on_to_the_next_generation)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);
	Cell_Initialize_At(world, 0, 1);
	Cell_Initialize_At(world, 1, 1);

	World_Tick(world);

	int cell_present = World_Has_Cell(world, cell);
	fail_unless(cell_present, "Cell (address=%p) was not present, when it should have lived", cell);

	World_Destroy(world);
}
END_TEST

START_TEST (test_Rule_2_Any_live_cell_with_three_live_neighbours_lives_on_to_the_next_generation)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);
	Cell_Initialize_At(world, 0, 1);
	Cell_Initialize_At(world, 1, 0);
	Cell_Initialize_At(world, 1, 1);

	World_Tick(world);

	int cell_present = World_Has_Cell(world, cell);
	fail_unless(cell_present, "Cell (address=%p) was not present, when it should have lived", cell);

	World_Destroy(world);
}
END_TEST

START_TEST (test_Rule_3_Any_live_cell_with_more_than_three_live_neighbours_dies_As_if_by_overcrowding)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);
	Cell_Initialize_At(world, 0, 1);
	Cell_Initialize_At(world, 1, 0);
	Cell_Initialize_At(world, 1, 1);
	Cell_Initialize_At(world, -1, 1);

	World_Tick(world);

	int cell_present = World_Has_Cell(world, cell);
	fail_if(cell_present, "Cell (address=%p) was present, when it should have died", cell);

	World_Destroy(world);
}
END_TEST

START_TEST (test_Rule_4_Any_dead_cell_with_exactly_three_live_neighbours_becomes_a_live_cell_As_if_by_reproduction)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);
	Cell_Initialize_At(world, 0, 1);
	Cell_Initialize_At(world, 1, 1);

	World_Tick(world);

	int cell_present = World_Has_Cell_At(world, 1, 0);
	fail_unless(cell_present, "Cell (x=%d, y=%d) was not present, when it should have come alive", 1, 0);

	World_Destroy(world);
}
END_TEST


START_TEST (test_Rule_4_Any_dead_cell_with_two_live_neighbours_does_not_become_a_live_cell)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);
	Cell_Initialize_At(world, 0, 1);

	World_Tick(world);

	int cell_present = World_Has_Cell_At(world, 1, 0);
	fail_if(cell_present, "Cell (x=%d, y=%d) was present, when it shouldn't have come alive", 1, 0);

	World_Destroy(world);
}
END_TEST


START_TEST (test_Rule_4_Any_dead_cell_with_four_live_neighbours_does_not_become_a_live_cell)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);
	Cell_Initialize_At(world, 0, 1);
	Cell_Initialize_At(world, 1, 1);
	Cell_Initialize_At(world, 0, -1);

	World_Tick(world);

	int cell_present = World_Has_Cell_At(world, 1, 0);
	fail_if(cell_present, "Cell (x=%d, y=%d) was present, when it shouldn't have come alive", 1, 0);

	World_Destroy(world);
}
END_TEST

