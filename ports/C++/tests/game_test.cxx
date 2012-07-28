#include <set>
#include <utility>
#include <fstream>
#include <string>
#include <igloo/igloo_alt.h>

#include "game.hh"

using namespace igloo;

Describe(GameOfLife_Game)
{
	Describe(when_empty)
	{
		GameOfLife::Game emptyGame;

		It(has_a_cell_count_of_zero)
		{
			Assert::That(emptyGame.cellCount(), Equals(0));
		}
	};

	Describe(after_adding_one_cell)
	{
		GameOfLife::Game game;

		void SetUp()
		{
			game.addCellAt(1, 0);
		}

		It(has_cell_count_of_one)
		{
			Assert::That(game.cellCount(), Equals(1));
		}

		It(knows_where_the_cell_is_present)
		{
			Assert::That(game.hasCellAt(1, 0), IsTrue());
			Assert::That(game.hasCellAt(1, 1), IsFalse());
		}
	};

	Describe(after_adding_two_cells)
	{
		GameOfLife::Game game;

		void SetUp()
		{
			game.addCellAt(1, 0).addCellAt(0, 1);
		}

		It(has_cell_count_of_two)
		{
			Assert::That(game.cellCount(), Equals(2));
		}
	};

	Describe(blinker_after_a_tick)
	{
		GameOfLife::Game game;

		void SetUp()
		{
			game.addCellAt(-1, 0).addCellAt(0, 0).addCellAt(1, 0);
			game.tick();
		}

		It(has_three_cells)
		{
			Assert::That(game.cellCount(), Equals(3));
		}

		It(has_cells_at_new_positions)
		{
			Assert::That(game.hasCellAt(0, -1), IsTrue());
			Assert::That(game.hasCellAt(0, 0), IsTrue());
			Assert::That(game.hasCellAt(0, 1), IsTrue());
		}
	};

	It(is_stressed)
	{
		GameOfLife::Game game;
		game.addCellAt(-1, 0).addCellAt(0, 0).addCellAt(1, 0);

		for (long int i = 0; i < 1000; i++)
		{
			game.tick();
		}
	}

	Describe(current_generation_cells)
	{
		It(can_be_visited)
		{
			GameOfLife::Game pattern;
			pattern.addCellAt(-1, 0).addCellAt(0, -1).addCellAt(1, 0).addCellAt(5, 5);
			std::set <std::pair <long int, long int> > coordinates = pattern.currentGeneration();

			Assert::That(coordinates.size(), Equals(4));
			Assert::That(coordinates, Contains(std::make_pair(-1L, 0L)));
			Assert::That(coordinates, Contains(std::make_pair(0L, -1L)));
			Assert::That(coordinates, Contains(std::make_pair(1L, 0L)));
			Assert::That(coordinates, Contains(std::make_pair(5L, 5L)));
		}

		It(is_not_cached)
		{
			GameOfLife::Game pattern;
			pattern.addCellAt(-1, 0).addCellAt(-2, 0).addCellAt(-3, 0);
			pattern.tick();
			std::set <std::pair <long int, long int> > coordinates = pattern.currentGeneration();

			Assert::That(coordinates.size(), Equals(3));
			Assert::That(coordinates, Contains(std::make_pair(-2L, -1L)));
			Assert::That(coordinates, Contains(std::make_pair(-2L, 0L)));
			Assert::That(coordinates, Contains(std::make_pair(-2L, 1L)));
		}
	};

	Describe(previous_generation_cells)
	{
		It(can_be_visited)
		{
			GameOfLife::Game pattern;
			pattern.addCellAt(-1, 0).addCellAt(0, -1).addCellAt(1, 0).addCellAt(5, 5).tick();
			std::set <std::pair <long int, long int> > coordinates = pattern.previousGeneration();

			Assert::That(coordinates.size(), Equals(4));
			Assert::That(coordinates, Contains(std::make_pair(-1L, 0L)));
			Assert::That(coordinates, Contains(std::make_pair(0L, -1L)));
			Assert::That(coordinates, Contains(std::make_pair(1L, 0L)));
			Assert::That(coordinates, Contains(std::make_pair(5L, 5L)));
		}

		It(is_not_cached)
		{
			GameOfLife::Game pattern;
			pattern.addCellAt(-1, 0).addCellAt(-2, 0).addCellAt(-3, 0);
			pattern.tick().tick();
			std::set <std::pair <long int, long int> > coordinates = pattern.previousGeneration();

			Assert::That(coordinates.size(), Equals(3));
			Assert::That(coordinates, Contains(std::make_pair(-2L, -1L)));
			Assert::That(coordinates, Contains(std::make_pair(-2L, 0L)));
			Assert::That(coordinates, Contains(std::make_pair(-2L, 1L)));
		}
	};

	Describe(cells_to_remove)
	{
		It(are_the_cells_that_exist_in_previous_generation_but_not_in_current)
		{
			GameOfLife::Game pattern;
			pattern.addCellAt(-1, 0).addCellAt(0, 0).addCellAt(1, 0);
			pattern.tick();
			std::set <std::pair <long int, long int> > coordinates = pattern.cellsToRemove();

			Assert::That(coordinates.size(), Equals(2));
			Assert::That(coordinates, Contains(std::make_pair(-1L, 0L)));
			Assert::That(coordinates, Contains(std::make_pair(1L, 0L)));
		}

		It(dont_include_unchanged_cell)
		{
			GameOfLife::Game pattern;
			pattern.addCellAt(0, 0).addCellAt(0, 1).addCellAt(1, 0).addCellAt(1, 1);
			pattern.tick();
			std::set <std::pair <long int, long int> > coordinates = pattern.cellsToRemove();

			Assert::That(coordinates.size(), Equals(0));
		}
	};

	Describe(cells_to_add)
	{
		It(are_the_cells_that_exist_in_current_generation_but_not_in_previous)
		{
			GameOfLife::Game pattern;
			pattern.addCellAt(-1, 0).addCellAt(0, 0).addCellAt(1, 0);
			pattern.tick();
			std::set <std::pair <long int, long int> > coordinates = pattern.cellsToAdd();

			Assert::That(coordinates.size(), Equals(2));
			Assert::That(coordinates, Contains(std::make_pair(0L, -1L)));
			Assert::That(coordinates, Contains(std::make_pair(0L, 1L)));
		}

		It(dont_include_unchanged_cell)
		{
			GameOfLife::Game pattern;
			pattern.addCellAt(0, 0).addCellAt(0, 1).addCellAt(1, 0).addCellAt(1, 1);
			pattern.tick();
			std::set <std::pair <long int, long int> > coordinates = pattern.cellsToAdd();

			Assert::That(coordinates.size(), Equals(0));
		}
	};

	Describe(when_created_from_a_file)
	{
		GameOfLife::Game game;
		char fileName[L_tmpnam];

		void SetUp()
		{
			tmpnam(fileName);
			std::ofstream file(fileName);
			file << "-1 0" << std::endl << "-2 0" << std::endl <<"-3 1";
			file.close();

			game.read(std::string(fileName));
		}

		void TearDown()
		{
			remove(fileName);
		}

		It(has_correct_cell_count)
		{
			Assert::That(game.cellCount(), Equals(3));
		}

		It(has_cells)
		{
			Assert::That(game.hasCellAt(-1L, 0L), IsTrue());
			Assert::That(game.hasCellAt(-2L, 0L), IsTrue());
			Assert::That(game.hasCellAt(-3L, 1L), IsTrue());
		}
	};
};

int main()
{
	return TestRunner::RunAllTests();
}
