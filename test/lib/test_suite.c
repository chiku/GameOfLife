#include "minunit.h"

#include "coordinates_test.c"
#include "cell_test.c"
#include "world_test.c"
#include "rules_test.c"
#include "game_test.c"

MU_TEST_SUITE(game_of_life_suite)
{
	MU_RUN_TEST(test_Coordinates_have_an_abscissa);
	MU_RUN_TEST(test_Coordinates_have_an_ordinate);
	MU_RUN_TEST(test_Coordinates_match_when_absicca_and_ordinate_are_equal);
	MU_RUN_TEST(test_Coordinates_do_not_match_when_absicca_are_not_equal);
	MU_RUN_TEST(test_Coordinates_do_not_match_when_ordinate_are_not_equal);
	MU_RUN_TEST(test_Coordinates_is_created_at_location_shifted_from_an_existing_coordinate);

	MU_RUN_TEST(test_Cell_is_created_at_specified_location);
	MU_RUN_TEST(test_Cell_is_created_from_coordinates);
	MU_RUN_TEST(test_Cell_is_at_first_generation_upon_creation);
	MU_RUN_TEST(test_Cell_generation_can_be_incremented_when_created);
	MU_RUN_TEST(test_Cell_is_at_location_when_its_coordinates_match);
	MU_RUN_TEST(test_Cell_is_not_at_location_when_its_x_coordinates_do_not_match);
	MU_RUN_TEST(test_Cell_is_not_at_location_when_its_y_coordinates_do_not_match);

	MU_RUN_TEST(test_World_adds_cell);
	MU_RUN_TEST(test_World_does_not_add_cell_if_cell_already_exists_in_the_world);
	MU_RUN_TEST(test_World_creation_is_allocation_followed_by_initialization);
	MU_RUN_TEST(test_World_knows_its_cell_count);
	MU_RUN_TEST(test_World_has_a_cell_at_specified_location);
	MU_RUN_TEST(test_World_knows_the_generation_for_a_cell_specified_by_its_coordinates_is_the_actual_cell_generation);
	MU_RUN_TEST(test_World_knows_the_generation_for_a_non_existing_cell_is_zero);
	MU_RUN_TEST(test_World_does_not_have_a_cell_at_specified_location_when_cell_is_in_different_world);
	MU_RUN_TEST(test_World_knows_count_of_neighbours_around_locations);
	MU_RUN_TEST(test_World_knows_does_not_count_cell_not_present_in_pool);
	MU_RUN_TEST(test_World_knows_all_cell_locations_near_a_set);
	MU_RUN_TEST(test_World_at_cells_is_visitable);
	MU_RUN_TEST(test_World_visits_accept_custom_data);

	MU_RUN_TEST(test_Rule_1_Any_live_cell_with_zero_live_neighbours_dies_As_if_caused_by_under_population);
	MU_RUN_TEST(test_Rule_1_Any_live_cell_with_one_live_neighbour_dies_As_if_caused_by_under_population);
	MU_RUN_TEST(test_Rule_2_Any_live_cell_with_two_live_neighbours_lives_on_to_the_next_generation);
	MU_RUN_TEST(test_Rule_2_Any_live_cell_with_three_live_neighbours_lives_on_to_the_next_generation);
	MU_RUN_TEST(test_Rule_3_Any_live_cell_with_more_than_three_live_neighbours_dies_As_if_by_overcrowding);
	MU_RUN_TEST(test_Rule_4_Any_dead_cell_with_exactly_three_live_neighbours_becomes_a_live_cell_As_if_by_reproduction);
	MU_RUN_TEST(test_Rule_4_Any_dead_cell_with_two_live_neighbours_does_not_become_a_live_cell);
	MU_RUN_TEST(test_Rule_4_Any_dead_cell_with_four_live_neighbours_does_not_become_a_live_cell);

	MU_RUN_TEST(test_Game_adds_cell);
	MU_RUN_TEST(test_Game_creation_from_file_is_proper);
	MU_RUN_TEST(test_Game_neglects_lines_that_begin_with_hash_when_reading_file);
	MU_RUN_TEST(test_Game_creation_is_allocation_followed_by_initialization);
	MU_RUN_TEST(test_Game_knows_neighbour_to_north_of_a_cell);
	MU_RUN_TEST(test_Game_knows_neighbour_to_north_east_of_a_cell);
	MU_RUN_TEST(test_Game_knows_neighbour_to_east_of_a_cell);
	MU_RUN_TEST(test_Game_knows_neighbour_to_south_east_of_a_cell);
	MU_RUN_TEST(test_Game_knows_neighbour_to_south_of_a_cell);
	MU_RUN_TEST(test_Game_knows_neighbour_to_south_west_of_a_cell);
	MU_RUN_TEST(test_Game_knows_neighbour_to_west_of_a_cell);
	MU_RUN_TEST(test_Game_knows_neighbour_to_north_west_of_a_cell);
	MU_RUN_TEST(test_Game_does_not_consider_far_away_cell_as_neighbours);
	MU_RUN_TEST(test_Game_knows_living_cell_count_around_an_occupied_location);
	MU_RUN_TEST(test_Game_knows_living_cell_count_around_an_unoccupied_location);
	MU_RUN_TEST(test_Game_knows_all_cell_locations_near_all_living_cells);
	MU_RUN_TEST(test_Game_is_visitable_for_each_cell_of_current_generation);
	MU_RUN_TEST(test_Game_visits_accept_custom_data);
	MU_RUN_TEST(test_Game_is_visitable_for_each_cell_of_previous_generation);
	MU_RUN_TEST(test_Game_tick_preserves_previous_generation);
	MU_RUN_TEST(test_Game_increases_the_number_of_generations_its_cells_have_been_alive_for_on_survival);
	MU_RUN_TEST(test_Game_sets_number_of_generations_for_a_cell_to_zero_on_death);
}

int main(int argc, char *argv[])
{
	MU_RUN_SUITE(game_of_life_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
