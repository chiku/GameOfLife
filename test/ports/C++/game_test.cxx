#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GameOfLife

#include <set>
#include <utility>
#include <fstream>
#include <string>
#include <boost/test/unit_test.hpp>

#include "game.hh"

class GameOfLifeTestFixture
{
public:
    GameOfLifeTestFixture() {}
    ~GameOfLifeTestFixture() {}
};

BOOST_FIXTURE_TEST_SUITE(GameOfLifeTest, GameOfLifeTestFixture)

BOOST_AUTO_TEST_CASE(Empty_game_has_a_cell_count_0)
{
    GameOfLife::Game emptyGame;
    BOOST_CHECK_EQUAL(emptyGame.cellCount(), 0);
}

BOOST_AUTO_TEST_CASE(Game_after_one_cell_has_a_cell_count_1)
{
    GameOfLife::Game game;
    game.addCellAt(1, 0);
    BOOST_CHECK_EQUAL(game.cellCount(), 1);
}

BOOST_AUTO_TEST_CASE(Game_after_two_cells_has_a_cell_count_1)
{
    GameOfLife::Game game;
    game.addCellAt(1, 0).addCellAt(0, 1);
    BOOST_CHECK_EQUAL(game.cellCount(), 2);
}

BOOST_AUTO_TEST_CASE(Game_has_cell_where_it_is_created)
{
    GameOfLife::Game game;
    game.addCellAt(1, 0);
    BOOST_CHECK(game.hasCellAt(1, 0));
}

BOOST_AUTO_TEST_CASE(Game_does_not_have_cell_where_it_is_not_created)
{
    GameOfLife::Game game;
    game.addCellAt(1, 0);
    BOOST_CHECK(!game.hasCellAt(0, 1));
}

BOOST_AUTO_TEST_CASE(Blinker_after_a_tick_has_three_cells_at_opposite_fringes_of_the_original)
{
    GameOfLife::Game game;
    game.addCellAt(-1, 0).addCellAt(0, 0).addCellAt(1, 0);
    game.tick();
    BOOST_CHECK_EQUAL(game.cellCount(), 3);
    BOOST_CHECK(game.hasCellAt(0, -1));
    BOOST_CHECK(game.hasCellAt(0, 0));
    BOOST_CHECK(game.hasCellAt(0, 1));
}

BOOST_AUTO_TEST_CASE(Stress_test_blinker)
{
    GameOfLife::Game game;
    game.addCellAt(-1, 0).addCellAt(0, 0).addCellAt(1, 0);

    for (long int i = 0; i < 1000; i++) {
        game.tick();
    }
    BOOST_CHECK_EQUAL(game.cellCount(), 3);
}

BOOST_AUTO_TEST_CASE(Game_has_the_coordinates_of_the_current_generation_of_cells)
{
    GameOfLife::Game game;
    game.addCellAt(-1, 0).addCellAt(0, -1).addCellAt(1, 0).addCellAt(5, 5);
    std::set <std::pair <long int, long int> > coordinates = game.currentGeneration();

    BOOST_CHECK_EQUAL(coordinates.size(), 4);
    BOOST_CHECK(coordinates.find(std::make_pair(-1L,  0L)) != coordinates.end());
    BOOST_CHECK(coordinates.find(std::make_pair( 0L, -1L)) != coordinates.end());
    BOOST_CHECK(coordinates.find(std::make_pair( 1L,  0L)) != coordinates.end());
    BOOST_CHECK(coordinates.find(std::make_pair( 5L,  5L)) != coordinates.end());
}

BOOST_AUTO_TEST_CASE(Current_generation_is_not_cached)
{
    GameOfLife::Game game;
    game.addCellAt(-1, 0).addCellAt(-2, 0).addCellAt(-3, 0);
    game.tick();
    std::set <std::pair <long int, long int> > coordinates = game.currentGeneration();

    BOOST_CHECK_EQUAL(coordinates.size(), 3);
    BOOST_CHECK(coordinates.find(std::make_pair(-2L, -1L)) != coordinates.end());
    BOOST_CHECK(coordinates.find(std::make_pair(-2L,  0L)) != coordinates.end());
    BOOST_CHECK(coordinates.find(std::make_pair(-2L,  1L)) != coordinates.end());
}

BOOST_AUTO_TEST_CASE(Game_has_the_coordinates_of_the_previous_generation_of_cells)
{
    GameOfLife::Game game;
    game.addCellAt(-1, 0).addCellAt(0, -1).addCellAt(1, 0).addCellAt(5, 5).tick();
    std::set <std::pair <long int, long int> > coordinates = game.previousGeneration();

    BOOST_CHECK_EQUAL(coordinates.size(), 4);
    BOOST_CHECK(coordinates.find(std::make_pair(-1L,  0L)) != coordinates.end());
    BOOST_CHECK(coordinates.find(std::make_pair( 0L, -1L)) != coordinates.end());
    BOOST_CHECK(coordinates.find(std::make_pair( 1L,  0L)) != coordinates.end());
    BOOST_CHECK(coordinates.find(std::make_pair( 5L,  5L)) != coordinates.end());
}

BOOST_AUTO_TEST_CASE(Previous_generation_is_not_cached)
{
    GameOfLife::Game game;
    game.addCellAt(-1, 0).addCellAt(-2, 0).addCellAt(-3, 0);
    game.tick().tick();
    std::set <std::pair <long int, long int> > coordinates = game.previousGeneration();

    BOOST_CHECK_EQUAL(coordinates.size(), 3);
    BOOST_CHECK(coordinates.find(std::make_pair(-2L, -1L)) != coordinates.end());
    BOOST_CHECK(coordinates.find(std::make_pair(-2L,  0L)) != coordinates.end());
    BOOST_CHECK(coordinates.find(std::make_pair(-2L,  1L)) != coordinates.end());
}

BOOST_AUTO_TEST_CASE(Cells_that_exist_in_previous_generation_but_not_in_current_are_removed)
{
    GameOfLife::Game game;
    game.addCellAt(-1, 0).addCellAt(0, 0).addCellAt(1, 0);
    game.tick();
    std::set <std::pair <long int, long int> > coordinates = game.cellsToRemove();

    BOOST_CHECK_EQUAL(coordinates.size(), 2);
    BOOST_CHECK(coordinates.find(std::make_pair(-1L, 0L)) != coordinates.end());
    BOOST_CHECK(coordinates.find(std::make_pair( 1L, 0L)) != coordinates.end());
}

BOOST_AUTO_TEST_CASE(Cells_that_exist_in_previous_and_current_generations_are_not_removed)
{
    GameOfLife::Game game;
    game.addCellAt(0, 0).addCellAt(0, 1).addCellAt(1, 0).addCellAt(1, 1);
    game.tick();
    std::set <std::pair <long int, long int> > coordinates = game.cellsToRemove();

    BOOST_CHECK_EQUAL(coordinates.size(), 0);
}

BOOST_AUTO_TEST_CASE(Cells_that_dont_exist_in_previous_generation_but_in_current_are_added)
{
    GameOfLife::Game game;
    game.addCellAt(-1, 0).addCellAt(0, 0).addCellAt(1, 0);
    game.tick();
    std::set <std::pair <long int, long int> > coordinates = game.cellsToAdd();

    BOOST_CHECK_EQUAL(coordinates.size(), 2);
    BOOST_CHECK(coordinates.find(std::make_pair(0L, -1L)) != coordinates.end());
    BOOST_CHECK(coordinates.find(std::make_pair(0L,  1L)) != coordinates.end());
}

BOOST_AUTO_TEST_CASE(Cells_that_exist_in_previous_and_current_generations_are_not_added)
{
    GameOfLife::Game game;
    game.addCellAt(0, 0).addCellAt(0, 1).addCellAt(1, 0).addCellAt(1, 1);
    game.tick();
    std::set <std::pair <long int, long int> > coordinates = game.cellsToAdd();

    BOOST_CHECK_EQUAL(coordinates.size(), 0);
}

BOOST_AUTO_TEST_CASE(Game_reads_cells_from_file)
{
    const char *fileName = "test.lif";
    std::ofstream file(fileName);
    file << "-1 0" << std::endl << "-2 0" << std::endl <<"-3 1";
    file.close();
    GameOfLife::Game game;
    game.read(fileName);

    BOOST_CHECK_EQUAL(game.cellCount(), 3);
    BOOST_CHECK(game.hasCellAt(-1L, 0L));
    BOOST_CHECK(game.hasCellAt(-2L, 0L));
    BOOST_CHECK(game.hasCellAt(-3L, 1L));
    remove(fileName);
}

BOOST_AUTO_TEST_SUITE_END()
