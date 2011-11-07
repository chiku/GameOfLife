#include <stdio.h>
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
	tcase_add_test(tc_cell, test_Cell_Is_created_at_specified_world);
	tcase_add_test(tc_cell, test_Cell_Is_created_at_specified_location);
	tcase_add_test(tc_cell, test_Cell_Is_not_created_if_it_already_exists_in_the_world);
	tcase_add_test(tc_cell, test_Cell_Knows_its_neighbour_to_north);
	tcase_add_test(tc_cell, test_Cell_Knows_its_neighbour_to_north_east);
	tcase_add_test(tc_cell, test_Cell_Knows_its_neighbour_to_east);
	tcase_add_test(tc_cell, test_Cell_Knows_its_neighbour_to_south_east);
	tcase_add_test(tc_cell, test_Cell_Knows_its_neighbour_to_south);
	tcase_add_test(tc_cell, test_Cell_Knows_its_neighbour_to_south_west);
	tcase_add_test(tc_cell, test_Cell_Knows_its_neighbour_to_west);
	tcase_add_test(tc_cell, test_Cell_Knows_its_neighbour_to_north_west);
	tcase_add_test(tc_cell, test_Cell_Knows_does_not_consider_far_away_cell_as_neighbours);
	tcase_add_test(tc_cell, test_Cell_Is_at_location_when_its_coordinates_and_world_match);
	tcase_add_test(tc_cell, test_Cell_Is_not_at_location_when_its_coordinates_do_not_match);
	tcase_add_test(tc_cell, test_Cell_Is_not_at_location_when_its_world_does_not_match);
	suite_add_tcase(s, tc_cell);

	TCase *tc_world = tcase_create("World");
	tcase_add_test(tc_world, test_World_knows_its_cell_count);
	tcase_add_test(tc_world, test_World_knows_its_cell_by_position);
	tcase_add_test(tc_world, test_World_if_it_has_a_cell);
	tcase_add_test(tc_world, test_World_if_it_has_a_cell_at_specified_location);
	tcase_add_test(tc_world, test_World_does_not_have_a_cell_at_specified_location_when_cell_is_in_different_world);
	tcase_add_test(tc_world, test_World_knows_living_cell_count_around_an_occupied_location);
	tcase_add_test(tc_world, test_World_knows_living_cell_count_around_an_unoccupied_location);
	tcase_add_test(tc_world, test_World_knows_all_cell_locations_near_all_living_cells);
	suite_add_tcase(s, tc_world);

	TCase *tc_rules = tcase_create("Rules");
	tcase_add_test(tc_rules, test_Rule_1_Any_live_cell_with_zero_live_neighbours_dies_As_if_caused_by_under_population);
	tcase_add_test(tc_rules, test_Rule_1_Any_live_cell_with_one_live_neighbour_dies_As_if_caused_by_under_population);
	tcase_add_test(tc_rules, test_Rule_2_Any_live_cell_with_two_live_neighbours_lives_on_to_the_next_generation);
	tcase_add_test(tc_rules, test_Rule_2_Any_live_cell_with_three_live_neighbours_lives_on_to_the_next_generation);
	tcase_add_test(tc_rules, test_Rule_3_Any_live_cell_with_more_than_three_live_neighbours_dies_As_if_by_overcrowding);
	tcase_add_test(tc_rules, test_Rule_4_Any_dead_cell_with_exactly_three_live_neighbours_becomes_a_live_cell_As_if_by_reproduction);
	tcase_add_test(tc_rules, test_Rule_4_Any_dead_cell_with_two_live_neighbours_does_not_become_a_live_cell);
	tcase_add_test(tc_rules, test_Rule_4_Any_dead_cell_with_four_live_neighbours_does_not_become_a_live_cell);

	suite_add_tcase(s, tc_rules);

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

