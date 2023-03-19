#include <coordinates.h>
#include <cell.h>
#include "minunit.h"

MU_TEST(test_Cell_is_created_at_specified_location)
{
	Cell cell = Cell_New(5, 4);

	Coordinates coordinates = Cell_Coordinates(cell);
	mu_assert_int_eq(5, coordinates.x);
	mu_assert_int_eq(4, coordinates.y);
}

MU_TEST(test_Cell_is_created_from_coordinates)
{
	Cell cell = Cell_New_From_Coordinates(Coordinates_New(5, 4));

	Coordinates coordinates = Cell_Coordinates(cell);
	mu_assert_int_eq(5, coordinates.x);
	mu_assert_int_eq(4, coordinates.y);
}

MU_TEST(test_Cell_is_at_first_generation_upon_creation)
{
	Cell cell1 = Cell_New(0, 0);
	mu_assert_int_eq(1, cell1.generation);

	Cell cell2 = Cell_New_From_Coordinates(Coordinates_New(0, 0));
	mu_assert_int_eq(1, cell2.generation);
}

MU_TEST(test_Cell_generation_can_be_incremented_when_created)
{
	Cell cell = Cell_New_From_Coordinates_With_Incremented_Generation(Coordinates_New(5, 4), 5);

	Coordinates coordinates = Cell_Coordinates(cell);
	mu_assert_int_eq(5, coordinates.x);
	mu_assert_int_eq(4, coordinates.y);
	mu_assert_int_eq(6, cell.generation);
}

MU_TEST(test_Cell_is_at_location_when_its_coordinates_match)
{
	Cell cell = Cell_New(3, 4);

	mu_assert(Cell_Is_At(cell, Coordinates_New(3, 4)), "Expected cell to be present when ordinate and abscissa match, but wasn't");
}

MU_TEST(test_Cell_is_not_at_location_when_its_x_coordinates_do_not_match)
{
	Cell cell = Cell_New(3, 4);

	mu_assert(!Cell_Is_At(cell, Coordinates_New(2, 4)), "Expected cell to be not present when ordinate doesn't match, but was");
}

MU_TEST(test_Cell_is_not_at_location_when_its_y_coordinates_do_not_match)
{
	Cell cell = Cell_New(3, 4);

	mu_assert(!Cell_Is_At(cell, Coordinates_New(3, -4)), "Expected cell to be not present when abscissa doesn't match, but was");
}
