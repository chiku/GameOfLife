START_TEST (test_CellCollection_adds_cell)
{
	CellCollection *cell_collection = CellCollection_New();
	Cell cell = Cell_New(0, 0);
	CellCollection_Add_Cell(cell_collection, cell);

	fail_unless(CellCollection_Has_Cell_At(cell_collection, Coordinates_New(0, 0)), "Expected cell (address=%p) to be present, but wasn't", cell);
	CellCollection_Destroy(cell_collection);
}
END_TEST

START_TEST (test_CellCollection_does_not_add_cell_if_cell_already_exists_in_the_cell_collection)
{
	CellCollection *cell_collection = CellCollection_New();
	CellCollection_Add_Cell(cell_collection, Cell_New(5, 4));
	CellCollection_Add_Cell(cell_collection, Cell_New(5, 4));

	long cell_count = CellCollection_Cell_Count(cell_collection);
	fail_unless(CellCollection_Cell_Count(cell_collection) == 1, "Expected cell_collection to contain %ld cell, but contained %ld", 1, cell_count);
	CellCollection_Destroy(cell_collection);
}
END_TEST

START_TEST (test_CellCollection_creation_is_allocation_followed_by_initialization)
{
	CellCollection *allocated_cell_collection = CellCollection_Allocate();
	CellCollection *initialized_cell_collection = CellCollection_Initialize(allocated_cell_collection);

	fail_unless(initialized_cell_collection == allocated_cell_collection, "Expected initialized cell_collection to have same memory location as allocated cell_collection, but didn't");
}
END_TEST

START_TEST (test_CellCollection_knows_its_cell_count)
{
	CellCollection *cell_collection = CellCollection_New();
	CellCollection_Add_Cell(cell_collection, Cell_New(0, 0));
	CellCollection_Add_Cell(cell_collection, Cell_New(1, 4));
	CellCollection_Add_Cell(cell_collection, Cell_New(2, 4));

	long int cell_count = CellCollection_Cell_Count(cell_collection);
	fail_unless(cell_count == 3, "Expected cell count to be %ld, but was %ld", 3, cell_count);
	CellCollection_Destroy(cell_collection);
}
END_TEST

START_TEST (test_CellCollection_if_it_has_a_cell_at_specified_location)
{
	CellCollection *cell_collection = CellCollection_New();
	CellCollection_Add_Cell(cell_collection, Cell_New(0, 0));

	fail_unless(CellCollection_Has_Cell_At(cell_collection, Coordinates_New(0, 0)), "Excepted cell (x=%d, y=%d) to be present in the cell_collection, but wasn't", 0, 0);
	fail_if(CellCollection_Has_Cell_At(cell_collection, Coordinates_New(1, 0)), "Excepted cell (x=%d, y=%d) to be not present in the cell_collection, but was", 1, 0);
	CellCollection_Destroy(cell_collection);
}
END_TEST

START_TEST (test_CellCollection_does_not_have_a_cell_at_specified_location_when_cell_is_in_different_cell_collection)
{
	CellCollection *cell_collection = CellCollection_New();
	CellCollection_Add_Cell(CellCollection_New(), Cell_New(0, 0)); /* cell in another cell_collection */

	fail_if(CellCollection_Has_Cell_At(cell_collection, Coordinates_New(0, 0)), "Excepted cell (x=%d, y=%d) to be not present in the cell_collection, but was", 0, 0);
	CellCollection_Destroy(cell_collection);
}
END_TEST

START_TEST (test_CellCollection_knows_count_of_neighbours_around_locations)
{
	CellCollection *cell_collection = CellCollection_New();
	Cell cell = Cell_New(0, 0);
	CellCollection_Add_Cell(cell_collection, cell);
	Coordinates locations[2];
	locations[0] = Coordinates_New(0, 1);
	locations[1] = Coordinates_New(3, 0);

	CellCollection_Add_Cell(cell_collection, Cell_New(0, 1)); /* neighbour */
	CellCollection_Add_Cell(cell_collection, Cell_New(3, 0)); /* neighbour */

	long int count = CellCollection_Cell_Count_Around(cell_collection, Coordinates_New(0, 0), locations, 2);
	fail_unless(count == 2, "Expected neighbour count to be %ld, but was %ld", 1, count);
	CellCollection_Destroy(cell_collection);
}
END_TEST

START_TEST (test_Cell_knows_does_not_count_cell_not_present_in_pool)
{
	CellCollection *cell_collection = CellCollection_New();
	Cell cell = Cell_New(0, 0);
	CellCollection_Add_Cell(cell_collection, cell);
	Coordinates locations[2];
	locations[0] = Coordinates_New(0, 1);
	locations[1] = Coordinates_New(3, 0);

	CellCollection_Add_Cell(cell_collection, Cell_New( 0,  2)); CellCollection_Add_Cell(cell_collection, Cell_New( 2,  2));
	CellCollection_Add_Cell(cell_collection, Cell_New( 2,  0)); CellCollection_Add_Cell(cell_collection, Cell_New( 2, -2));
	CellCollection_Add_Cell(cell_collection, Cell_New( 0, -2)); CellCollection_Add_Cell(cell_collection, Cell_New(-2, -2));
	CellCollection_Add_Cell(cell_collection, Cell_New(-2,  0)); CellCollection_Add_Cell(cell_collection, Cell_New(-2,  2));

	long int count = CellCollection_Cell_Count_Around(cell_collection, Coordinates_New(0, 0), locations, 2);
	fail_unless(count == 0, "Expected neighbour count to be %ld, but was %ld", 0, count);
	CellCollection_Destroy(cell_collection);
}
END_TEST

START_TEST (test_CellCollection_knows_all_cell_locations_near_a_set)
{
	CellCollection *cell_collection = CellCollection_New();
	CellCollection_Add_Cell(cell_collection, Cell_New(0, 0));
	CellCollection_Add_Cell(cell_collection, Cell_New(1, 1));
	Coordinates locations[4];
	locations[0] = Coordinates_New(0, 1);
	locations[1] = Coordinates_New(1, 1);

	CellCollection *zone = CellCollection_All_Neighbours_For_Set(cell_collection, locations, 2);
	long int cell_count = CellCollection_Cell_Count(zone);
	fail_unless(cell_count == 4, "Expected cell count to be %ld, but was %ld", 4, cell_count);

	fail_unless(CellCollection_Has_Cell_At(zone, Coordinates_New( 1,  2)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  1,  2);
	fail_unless(CellCollection_Has_Cell_At(zone, Coordinates_New( 2,  2)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  2,  2);
	fail_unless(CellCollection_Has_Cell_At(zone, Coordinates_New( 1,  1)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  1,  1);
	fail_unless(CellCollection_Has_Cell_At(zone, Coordinates_New( 0,  1)), "Expected cell (x=%d,y=%d) count to be present, but wasn't",  0,  1);
	CellCollection_Destroy(cell_collection);
}
END_TEST

static long int sum_x, sum_y, trace;
static void cc_add_up_cell_values(Coordinates coordinates, void *data)
{
	sum_x += coordinates.x;
	sum_y += coordinates.y;
	trace = data ? *((long int*)data) : 0;
}

START_TEST (test_CellCollection_at_cells_is_visitable)
{
	CellCollection *cell_collection = CellCollection_New();
	CellCollection_Add_Cell(cell_collection, Cell_New(0, -1));
	CellCollection_Add_Cell(cell_collection, Cell_New(1, 5));

	CellCollection_At_Each_Cell(cell_collection, cc_add_up_cell_values, NULL);

	fail_unless(sum_x == 1, "Expected sum of x's to be %ld, but was %ld", 1, sum_x);
	fail_unless(sum_y == 4, "Expected sum of x's to be %ld, but was %ld", 4, sum_y);
	CellCollection_Destroy(cell_collection);
}
END_TEST

START_TEST (test_CellCollection_visits_accept_custom_data)
{
	CellCollection *cell_collection = CellCollection_New();
	CellCollection_Add_Cell(cell_collection, Cell_New(0, -1));

	long int *expected_trace = (long int*)(malloc( sizeof(long int) ));
	*expected_trace = 100;

	CellCollection_At_Each_Cell(cell_collection, cc_add_up_cell_values, expected_trace);

	fail_unless(trace == 100, "Expected trace %ld, but was %ld", *expected_trace, trace);
	free(expected_trace);
	CellCollection_Destroy(cell_collection);
}
END_TEST
