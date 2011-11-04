#include <stdlib.h>
#include <check.h>

#include <game_of_life.h>

#include "cell_test.c"
#include "world_test.c"
#include "rules_test.c"

Suite *create_game_of_life_suite(void)
{
	Suite *s = suite_create("Game of Life");

	TCase *tc_cell = tcase_create("Cell");
	tcase_add_test(tc_cell, test_Cell_Is_created_at_origin);
	tcase_add_test(tc_cell, test_Cell_Is_spawned_relative_to_an_existing_cell);
	tcase_add_test(tc_cell, test_Cell_Is_spawned_in_the_same_world);
	tcase_add_test(tc_cell, test_Cell_Knows_its_neighbour_to_north);
	tcase_add_test(tc_cell, test_Cell_Knows_its_neighbour_to_north_east);
	tcase_add_test(tc_cell, test_Cell_Knows_its_neighbour_to_east);
	tcase_add_test(tc_cell, test_Cell_Knows_its_neighbour_to_south_east);
	tcase_add_test(tc_cell, test_Cell_Knows_its_neighbour_to_south);
	tcase_add_test(tc_cell, test_Cell_Knows_its_neighbour_to_south_west);
	tcase_add_test(tc_cell, test_Cell_Knows_its_neighbour_to_west);
	tcase_add_test(tc_cell, test_Cell_Knows_its_neighbour_to_north_west);
	tcase_add_test(tc_cell, test_Cell_Knows_does_not_consider_far_away_cell_as_neighbours);
	suite_add_tcase(s, tc_cell);

	TCase *tc_world = tcase_create("World");
	tcase_add_test(tc_world, test_World_knows_its_first_cell);
	tcase_add_test(tc_world, test_World_knows_its_second_cell);
	tcase_add_test(tc_world, test_World_knows_its_cell_count);
	tcase_add_test(tc_world, test_World_if_it_has_a_cell_present);
	suite_add_tcase(s, tc_world);

	TCase *tc_rules = tcase_create("Rules");
	tcase_add_test(tc_rules, test_Rule_1_Any_live_cell_with_zero_live_neighbours_dies_As_if_caused_by_under_population);
	tcase_add_test(tc_rules, test_Rule_1_Any_live_cell_with_one_live_neighbour_dies_As_if_caused_by_under_population);
	suite_add_tcase(s, tc_rules);

	return s;
}

int main(void)
{
	int number_failed;
	Suite *game_of_life_suite = create_game_of_life_suite();
	SRunner *game_of_life_suite_runner = srunner_create(game_of_life_suite);

	srunner_run_all(game_of_life_suite_runner, CK_VERBOSE);

	number_failed = srunner_ntests_failed(game_of_life_suite_runner);
	srunner_free(game_of_life_suite_runner);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

