#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include <coordinates.h>
#include <cell.h>
#include <world.h>
#include <rules.h>
#include <game.h>

#include "coordinates_test.c"
#include "cell_test.c"
#include "world_test.c"
#include "game_test.c"
#include "rules_test.c"

Suite *create_game_of_life_suite(void)
{
	Suite *s = suite_create("Game of Life");

	TCase *tc_coordinates = tcase_create("Coordinates");
	tcase_add_test(tc_coordinates, test_Coordinates_have_an_abscissa);
	tcase_add_test(tc_coordinates, test_Coordinates_have_an_ordinate);
	tcase_add_test(tc_coordinates, test_Coordinates_is_created_at_location_shifted_from_an_existing_coordinate);
	tcase_add_test(tc_coordinates, test_Coordinates_match_when_absicca_and_ordinate_are_equal);
	tcase_add_test(tc_coordinates, test_Coordinates_do_not_match_when_absicca_are_not_equal);
	tcase_add_test(tc_coordinates, test_Coordinates_do_not_match_when_ordinate_are_not_equal);
	suite_add_tcase(s, tc_coordinates);

	TCase *tc_cell = tcase_create("Cell");
	tcase_add_test(tc_cell, test_Cell_is_created_at_specified_location);
	tcase_add_test(tc_cell, test_Cell_is_created_from_coordinates);
	tcase_add_test(tc_cell, test_Cell_knows_does_not_consider_far_away_cell_as_neighbours);
	tcase_add_test(tc_cell, test_Cell_is_at_location_when_its_coordinates_match);
	tcase_add_test(tc_cell, test_Cell_is_not_at_location_when_its_x_coordinates_do_not_match);
	tcase_add_test(tc_cell, test_Cell_is_not_at_location_when_its_y_coordinates_do_not_match);
	suite_add_tcase(s, tc_cell);

	TCase *tc_world = tcase_create("World");
	tcase_add_test(tc_world, test_World_adds_cell);
	tcase_add_test(tc_world, test_World_does_not_add_cell_if_cell_already_exists_in_the_world);
	tcase_add_test(tc_world, test_World_creation_is_allocation_followed_by_initialization);
	tcase_add_test(tc_world, test_World_knows_its_cell_count);
	tcase_add_test(tc_world, test_World_if_it_has_a_cell_at_specified_location);
	tcase_add_test(tc_world, test_World_does_not_have_a_cell_at_specified_location_when_cell_is_in_different_world);
	tcase_add_test(tc_world, test_World_knows_count_of_neighbours_around_locations);
	tcase_add_test(tc_world, test_World_knows_does_not_count_cell_not_present_in_pool);
	tcase_add_test(tc_world, test_World_knows_all_cell_locations_near_a_set);
	tcase_add_test(tc_world, test_World_at_cells_is_visitable);
	tcase_add_test(tc_world, test_World_visits_accept_custom_data);
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

	TCase *tc_game = tcase_create("Game");
	tcase_add_test(tc_game, test_Game_adds_cell);
	tcase_add_test(tc_game, test_Game_creation_from_file_is_proper);
	tcase_add_test(tc_game, test_Game_neglects_lines_that_begin_with_hash_when_reading_file);
	tcase_add_test(tc_game, test_Game_creation_is_allocation_followed_by_initialization);
	tcase_add_test(tc_game, test_Game_knows_neighbour_to_north_of_a_cell);
	tcase_add_test(tc_game, test_Game_knows_neighbour_to_north_east_of_a_cell);
	tcase_add_test(tc_game, test_Game_knows_neighbour_to_east_of_a_cell);
	tcase_add_test(tc_game, test_Game_knows_neighbour_to_south_east_of_a_cell);
	tcase_add_test(tc_game, test_Game_knows_neighbour_to_south_of_a_cell);
	tcase_add_test(tc_game, test_Game_knows_neighbour_to_south_west_of_a_cell);
	tcase_add_test(tc_game, test_Game_knows_neighbour_to_west_of_a_cell);
	tcase_add_test(tc_game, test_Game_knows_neighbour_to_north_west_of_a_cell);
	tcase_add_test(tc_game, test_Game_knows_living_cell_count_around_an_occupied_location);
	tcase_add_test(tc_game, test_Game_knows_living_cell_count_around_an_unoccupied_location);
	tcase_add_test(tc_game, test_Game_knows_all_cell_locations_near_all_living_cells);
	tcase_add_test(tc_game, test_Game_is_visitable_for_each_cell_of_current_generation);
	tcase_add_test(tc_game, test_Game_visits_accept_custom_data);
	tcase_add_test(tc_game, test_Game_is_visitable_for_each_cell_of_previous_generation);
	tcase_add_test(tc_game, test_Game_tick_preserves_previous_generation);
	suite_add_tcase(s, tc_game);

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

