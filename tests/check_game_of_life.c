#include <stdlib.h>
#include <check.h>

#include <game_of_life.h>


START_TEST (test_Rule_1_Any_live_cell_with_fewer_than_two_live_neighbours_dies_As_if_caused_by_under_population)
{
	fail_unless(0 == 0, "Unexpected");
}
END_TEST

Suite *create_game_of_life_suite(void)
{
	Suite *s = suite_create("Game of Life");

	/* Core test case */
	TCase *tc_core = tcase_create("Rules");
	tcase_add_test(tc_core, test_Rule_1_Any_live_cell_with_fewer_than_two_live_neighbours_dies_As_if_caused_by_under_population);
	suite_add_tcase(s, tc_core);

	return s;
}

int main(void)
{
	int number_failed;
	Suite *game_of_life_suite = create_game_of_life_suite();
	SRunner *game_of_life_suite_runner = srunner_create(game_of_life_suite);

	srunner_run_all(game_of_life_suite_runner, CK_NORMAL);

	number_failed = srunner_ntests_failed(game_of_life_suite_runner);
	srunner_free(game_of_life_suite_runner);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

