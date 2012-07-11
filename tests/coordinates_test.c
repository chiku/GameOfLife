START_TEST (test_Coordinates_have_an_abscissa)
{
	Coordinates c = Coordinates_New(10, -20);
	long int x = Coordinates_X(c);
	fail_unless(x == 10, "Expected y-coordinate of cell to be %ld, but was %ld", 10, x);
}
END_TEST

START_TEST (test_Coordinates_have_an_ordinate)
{
	Coordinates c = Coordinates_New(10, -20);
	long int y = Coordinates_Y(c);
	fail_unless(y == -20, "Expected y-coordinate of cell to be %ld, but was %ld", 20, y);
}
END_TEST

START_TEST (test_Coordinates_match_when_absicca_and_ordinate_are_equal)
{
	Coordinates c1 = Coordinates_New(10, -20);
	Coordinates c2 = Coordinates_New(10, -20);
	fail_unless(Coordinates_Match(c1, c2), "Expected coordinates (%ld, %ld) to equal (%ld, %ld), but didn't", 10, -20, 10, -20);
}
END_TEST

START_TEST (test_Coordinates_do_not_match_when_absicca_are_not_equal)
{
	Coordinates c1 = Coordinates_New(10, -20);
	Coordinates c2 = Coordinates_New(-10, -20);
	fail_unless(!Coordinates_Match(c1, c2), "Expected coordinates (%ld, %ld) to not equal (%ld, %ld), but did", 10, -20, -10, -20);
}
END_TEST

START_TEST (test_Coordinates_do_not_match_when_ordinate_are_not_equal)
{
	Coordinates c1 = Coordinates_New(10, -20);
	Coordinates c2 = Coordinates_New(10, 20);
	fail_unless(!Coordinates_Match(c1, c2), "Expected coordinates (%ld, %ld) to not equal (%ld, %ld), but did", 10, -20, 10, 20);
}
END_TEST

START_TEST (test_Coordinates_is_created_at_location_shifted_from_an_existing_coordinate)
{
	Coordinates c = Coordinates_Shifted_By(Coordinates_New(10, -20), Coordinates_New(-2, 10));
	long int x = Coordinates_X(c);
	long int y = Coordinates_Y(c);
	fail_unless(Coordinates_X(c), "Expected x-coordinate to be %ld, but was", 8, x);
	fail_unless(Coordinates_Y(c), "Expected y-coordinate to be %ld, but was", -10, y);
}
END_TEST
