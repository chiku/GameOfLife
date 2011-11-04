START_TEST (test_Rule_1_Any_live_cell_with_zero_live_neighbours_dies_As_if_caused_by_under_population)
{
	World world = World_Initialize();
	Cell *cell = Cell_Initialize(&world);

	World_Tick(&world);

	int cell_present = World_Has_Cell(&world, cell);
	fail_if(cell_present, "Cell (address=%p) was present, when it should have died", cell);

	World_Destroy(&world);
}
END_TEST

START_TEST (test_Rule_1_Any_live_cell_with_one_live_neighbour_dies_As_if_caused_by_under_population)
{
	World world = World_Initialize();
	Cell *cell = Cell_Initialize(&world);
	Cell_Spawn_At(cell, 0, 1);

	World_Tick(&world);

	int cell_present = World_Has_Cell(&world, cell);
	fail_if(cell_present, "Cell (address=%p) was present, when it should have died", cell);

	World_Destroy(&world);
}
END_TEST

