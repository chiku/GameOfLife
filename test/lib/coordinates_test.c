#include <coordinates.h>
#include "minunit.h"

MU_TEST(test_Coordinates_have_an_abscissa)
{
	Coordinates c = Coordinates_New(10, -20);
	long int x = Coordinates_X(c);
	mu_assert_int_eq(10, x);
}

MU_TEST(test_Coordinates_have_an_ordinate)
{
	Coordinates c = Coordinates_New(10, -20);
	long int y = Coordinates_Y(c);
	mu_assert_int_eq(-20, y);
}

MU_TEST(test_Coordinates_match_when_absicca_and_ordinate_are_equal)
{
	Coordinates c1 = Coordinates_New(10, -20);
	Coordinates c2 = Coordinates_New(10, -20);
	mu_assert(Coordinates_Match(c1, c2), "Expected coordinates with equal abscissa & ordinate to be equal, but wasn't");
}

MU_TEST(test_Coordinates_do_not_match_when_absicca_are_not_equal)
{
	Coordinates c1 = Coordinates_New(10, -20);
	Coordinates c2 = Coordinates_New(-10, -20);
	mu_assert(!Coordinates_Match(c1, c2), "Expected coordinates with different ordinate to be unequal, but wasn't");
}

MU_TEST(test_Coordinates_do_not_match_when_ordinate_are_not_equal)
{
	Coordinates c1 = Coordinates_New(10, -20);
	Coordinates c2 = Coordinates_New(10, 20);
	mu_assert(!Coordinates_Match(c1, c2), "Expected coordinates with different abscissa to be unequal, but wasn't");
}

MU_TEST(test_Coordinates_is_created_at_location_shifted_from_an_existing_coordinate)
{
	Coordinates c = Coordinates_Shifted_By(Coordinates_New(10, -20), Coordinates_New(-2, 10));
	long int x = Coordinates_X(c);
	long int y = Coordinates_Y(c);
	mu_assert_int_eq(8, x);
	mu_assert_int_eq(-10, y);
}
