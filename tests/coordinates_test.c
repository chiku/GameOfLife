START_TEST (test_Coordinates_have_an_abscissa)
{
	Coordinates *c = Coordinates_New(10, -20);
	long int x = Coordinates_Get(c).x;
	fail_unless(x == 10, "Expected y-coordinate of cell to be %ld, but was %ld", 10, x);
	Coordinates_Destroy(c);
}
END_TEST

START_TEST (test_Coordinates_have_an_ordinate)
{
	Coordinates *c = Coordinates_New(10, -20);
	long int y = Coordinates_Get(c).y;
	fail_unless(y == -20, "Expected y-coordinate of cell to be %ld, but was %ld", 20, y);
	Coordinates_Destroy(c);
}
END_TEST

START_TEST (test_Coordinates_match_when_absicca_and_ordinate_are_equal)
{
	Coordinates *c1 = Coordinates_New(10, -20);
	Coordinates *c2 = Coordinates_New(10, -20);
	fail_unless(Coordinates_Match(c1, c2), "Expected coordinates (%ld, %ld) to equal (%ld, %ld) to be equal, but didn't", 10, -20, 10, -20);
	Coordinates_Destroy(c1);
	Coordinates_Destroy(c2);
}
END_TEST

START_TEST (test_Coordinates_do_not_match_when_absicca_are_not_equal)
{
	Coordinates *c1 = Coordinates_New(10, -20);
	Coordinates *c2 = Coordinates_New(-10, -20);
	fail_unless(!Coordinates_Match(c1, c2), "Expected coordinates (%ld, %ld) to not equal (%ld, %ld) to be equal, but did", 10, -20, -10, -20);
	Coordinates_Destroy(c1);
	Coordinates_Destroy(c2);
}
END_TEST

START_TEST (test_Coordinates_do_not_match_when_ordinate_are_not_equal)
{
	Coordinates *c1 = Coordinates_New(10, -20);
	Coordinates *c2 = Coordinates_New(10, 20);
	fail_unless(!Coordinates_Match(c1, c2), "Expected coordinates (%ld, %ld) to not equal (%ld, %ld) to be equal, but did", 10, -20, 10, 20);
	Coordinates_Destroy(c1);
	Coordinates_Destroy(c2);
}
END_TEST
