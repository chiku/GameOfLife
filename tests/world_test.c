#include <stdio.h>
START_TEST (test_World_knows_its_first_cell)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	Cell *retrived_cell = World_Cells(world)[0];
	fail_unless(retrived_cell == cell, "Expected retrived cell (address=%p) to be same as the actual cell (addess=%p), but wasn't", retrived_cell, cell);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_its_second_cell)
{
	World *world = World_Initialize();
	Cell *first_cell = Cell_Initialize(world);
	Cell *second_cell = Cell_Spawn_At(first_cell, 3, 4);

	Cell *retrived_cell = World_Cells(world)[1];
	fail_unless(retrived_cell == second_cell, "Expected retrived cell (address=%p) to be same as the actual cell (addess=%p), but wasn't", retrived_cell, second_cell);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_knows_its_cell_count)
{
	World *world = World_Initialize();
	Cell *first_cell = Cell_Initialize(world);
	Cell_Spawn_At(first_cell, 1, 4);
	Cell_Spawn_At(first_cell, 2, 4);

	long int cell_count = World_Cell_Count(world);
	fail_unless(cell_count == 3, "Expected cell count to be %ld, but was %ld", 3, cell_count);
	World_Destroy(world);
}
END_TEST

START_TEST (test_World_if_it_has_a_cell)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	World *another_world = World_Initialize();
	Cell *another_cell = Cell_Initialize(another_world);

	fail_unless(World_Has_Cell(world, cell), "Excepted cell (address=%p) to be present in the world, but wasn't", cell);
	fail_if(World_Has_Cell(world, another_cell), "Excepted another cell (address=%p) to be not present in the world, but was", another_cell);
}
END_TEST

START_TEST (test_World_if_it_has_a_cell_at_specified_location)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	fail_unless(World_Has_Cell_At(world, 0, 0), "Excepted cell (x=%d, y=%d) to be present in the world, but wasn't", 0, 0);
	fail_if(World_Has_Cell_At(world, 1, 0), "Excepted cell (x=%d, y=%d) to be not present in the world, but was", 1, 0);
}
END_TEST


START_TEST (test_World_has_the_neighbours_for_a_cell)
{
	World *world = World_Initialize();
	Cell *cell = Cell_Initialize(world);

	fail("unimplmemented");
}
END_TEST

