#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <set>
#include <utility>
#include <fstream>
#include <string>

#include "game.hh"
#include "doctest.hh"

class GameOfLifeTestFixture
{
public:
    GameOfLifeTestFixture() {}
    ~GameOfLifeTestFixture() {}
};

TEST_CASE("Empty game has a cell count 0")
{
    GameOfLife::Game emptyGame;
    CHECK(emptyGame.cellCount() == 0);
}

TEST_CASE("Game after one cell has a cell count 1")
{
    GameOfLife::Game game;
    game.addCellAt(1, 0);
    CHECK(game.cellCount() == 1);
}

TEST_CASE("Game after two cells has a cell count 1")
{
    GameOfLife::Game game;
    game.addCellAt(1, 0).addCellAt(0, 1);
    CHECK(game.cellCount() == 2);
}

TEST_CASE("Game has cell where it is created")
{
    GameOfLife::Game game;
    game.addCellAt(1, 0);
    CHECK(game.hasCellAt(1, 0));
}

TEST_CASE("Game does not have cell where it is not created")
{
    GameOfLife::Game game;
    game.addCellAt(1, 0);
    CHECK(!game.hasCellAt(0, 1));
}

TEST_CASE("Blinker after a tick has three cells at opposite fringes of the original")
{
    GameOfLife::Game game;
    game.addCellAt(-1, 0).addCellAt(0, 0).addCellAt(1, 0);
    game.tick();
    REQUIRE(game.cellCount() == 3);
    CHECK(game.hasCellAt(0, -1));
    CHECK(game.hasCellAt(0, 0));
    CHECK(game.hasCellAt(0, 1));
}

TEST_CASE("Stress test blinker")
{
    GameOfLife::Game game;
    game.addCellAt(-1, 0).addCellAt(0, 0).addCellAt(1, 0);

    for (long int i = 0; i < 1000; i++) {
        game.tick();
    }
    CHECK(game.cellCount() == 3);
}

TEST_CASE("Game has the coordinates of the current generation of cells")
{
    GameOfLife::Game game;
    game.addCellAt(-1, 0).addCellAt(0, -1).addCellAt(1, 0).addCellAt(5, 5);
    std::set <std::pair <long int, long int> > coordinates = game.currentGeneration();

    REQUIRE(coordinates.size() == 4);
    CHECK(coordinates.find(std::make_pair(-1L,  0L)) != coordinates.end());
    CHECK(coordinates.find(std::make_pair( 0L, -1L)) != coordinates.end());
    CHECK(coordinates.find(std::make_pair( 1L,  0L)) != coordinates.end());
    CHECK(coordinates.find(std::make_pair( 5L,  5L)) != coordinates.end());
}

TEST_CASE("Current generation is not cached")
{
    GameOfLife::Game game;
    game.addCellAt(-1, 0).addCellAt(-2, 0).addCellAt(-3, 0);
    game.tick();
    std::set <std::pair <long int, long int> > coordinates = game.currentGeneration();

    REQUIRE(coordinates.size() == 3);
    CHECK(coordinates.find(std::make_pair(-2L, -1L)) != coordinates.end());
    CHECK(coordinates.find(std::make_pair(-2L,  0L)) != coordinates.end());
    CHECK(coordinates.find(std::make_pair(-2L,  1L)) != coordinates.end());
}

TEST_CASE("Game has the coordinates of the previous generation of cells")
{
    GameOfLife::Game game;
    game.addCellAt(-1, 0).addCellAt(0, -1).addCellAt(1, 0).addCellAt(5, 5).tick();
    std::set <std::pair <long int, long int> > coordinates = game.previousGeneration();

    REQUIRE(coordinates.size() == 4);
    CHECK(coordinates.find(std::make_pair(-1L,  0L)) != coordinates.end());
    CHECK(coordinates.find(std::make_pair( 0L, -1L)) != coordinates.end());
    CHECK(coordinates.find(std::make_pair( 1L,  0L)) != coordinates.end());
    CHECK(coordinates.find(std::make_pair( 5L,  5L)) != coordinates.end());
}

TEST_CASE("Previous generation is not cached")
{
    GameOfLife::Game game;
    game.addCellAt(-1, 0).addCellAt(-2, 0).addCellAt(-3, 0);
    game.tick().tick();
    std::set <std::pair <long int, long int> > coordinates = game.previousGeneration();

    REQUIRE(coordinates.size() == 3);
    CHECK(coordinates.find(std::make_pair(-2L, -1L)) != coordinates.end());
    CHECK(coordinates.find(std::make_pair(-2L,  0L)) != coordinates.end());
    CHECK(coordinates.find(std::make_pair(-2L,  1L)) != coordinates.end());
}

TEST_CASE("Cells that exist in previous generation but not in current are removed")
{
    GameOfLife::Game game;
    game.addCellAt(-1, 0).addCellAt(0, 0).addCellAt(1, 0);
    game.tick();
    std::set <std::pair <long int, long int> > coordinates = game.cellsToRemove();

    REQUIRE(coordinates.size() == 2);
    CHECK(coordinates.find(std::make_pair(-1L, 0L)) != coordinates.end());
    CHECK(coordinates.find(std::make_pair( 1L, 0L)) != coordinates.end());
}

TEST_CASE("Cells that exist in previous and current generations are not removed")
{
    GameOfLife::Game game;
    game.addCellAt(0, 0).addCellAt(0, 1).addCellAt(1, 0).addCellAt(1, 1);
    game.tick();
    std::set <std::pair <long int, long int> > coordinates = game.cellsToRemove();

    CHECK(coordinates.size() == 0);
}

TEST_CASE("Cells that dont exist in previous generation but in current are added")
{
    GameOfLife::Game game;
    game.addCellAt(-1, 0).addCellAt(0, 0).addCellAt(1, 0);
    game.tick();
    std::set <std::pair <long int, long int> > coordinates = game.cellsToAdd();

    REQUIRE(coordinates.size() == 2);
    CHECK(coordinates.find(std::make_pair(0L, -1L)) != coordinates.end());
    CHECK(coordinates.find(std::make_pair(0L,  1L)) != coordinates.end());
}

TEST_CASE("Cells that exist in previous and current generations are not added")
{
    GameOfLife::Game game;
    game.addCellAt(0, 0).addCellAt(0, 1).addCellAt(1, 0).addCellAt(1, 1);
    game.tick();
    std::set <std::pair <long int, long int> > coordinates = game.cellsToAdd();

    CHECK(coordinates.size() == 0);
}

TEST_CASE("Game reads cells from file")
{
    const char *fileName = "test.lif";
    std::ofstream file(fileName);
    file << "-1 0" << std::endl << "-2 0" << std::endl <<"-3 1";
    file.close();
    GameOfLife::Game game;
    game.read(fileName);

    REQUIRE(game.cellCount() == 3);
    CHECK(game.hasCellAt(-1L, 0L));
    CHECK(game.hasCellAt(-2L, 0L));
    CHECK(game.hasCellAt(-3L, 1L));
    remove(fileName);
}
