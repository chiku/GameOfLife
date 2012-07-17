#include <vector>
#include <utility>
#include <igloo/igloo_alt.h>

#include "../../../src/ports/C++/ext/game.hh"

using namespace igloo;

Describe(GameOfLife_Game) {
	Describe(when_empty) {
		GameOfLife::Game emptyGame;

		It(has_a_cell_count_of_zero) {
			Assert::That(emptyGame.cellCount(), Equals(0));
		}
	};

	Describe(after_adding_one_cell) {
		GameOfLife::Game game;

		void SetUp() {
			game.addCellAt(1, 0);
		}

		It(has_cell_count_of_one) {
			Assert::That(game.cellCount(), Equals(1));
		}

		It(knows_where_the_cell_is_present) {
			Assert::That(game.hasCellAt(1, 0), IsTrue());
			Assert::That(game.hasCellAt(1, 1), IsFalse());
		}
	};

	Describe(after_adding_two_cells) {
		GameOfLife::Game game;

		void SetUp() {
			game.addCellAt(1, 0).addCellAt(0, 1);
		}

		It(has_cell_count_of_two) {
			Assert::That(game.cellCount(), Equals(2));
		}
	};

	Describe(blinker_after_a_tick) {
		GameOfLife::Game game;

		void SetUp() {
			game.addCellAt(-1, 0).addCellAt(0, 0).addCellAt(1, 0);
			game.tick();
		}

		It(has_three_cells) {
			Assert::That(game.cellCount(), Equals(3));
		}

		It(has_cells_at_new_positions) {
			Assert::That(game.hasCellAt(0, -1), IsTrue());
			Assert::That(game.hasCellAt(0, 0), IsTrue());
			Assert::That(game.hasCellAt(0, 1), IsTrue());
		}
	};

	It(is_stressed) {
		GameOfLife::Game game;
		game.addCellAt(-1, 0).addCellAt(0, 0).addCellAt(1, 0);

		for (long int i = 0; i < 1000; i++) {
			game.tick();
		}
	}

	Describe(current_generation_cells) {
		It(can_be_visited) {
			GameOfLife::Game pattern;
			pattern.addCellAt(-1, 0).addCellAt(0, -1).addCellAt(1, 0).addCellAt(5, 5);
			std::vector <std::pair <long int, long int> > coordinates = pattern.currentGeneration();

			std::vector <std::pair <long int, long int> > expectedCoordinates;
			expectedCoordinates.push_back(std::make_pair(-1, 0));
			expectedCoordinates.push_back(std::make_pair(0, -1));
			expectedCoordinates.push_back(std::make_pair(1, 0));
			expectedCoordinates.push_back(std::make_pair(5, 5));
			Assert::That(coordinates, Equals(expectedCoordinates));
		}

		It(is_not_cached) {
			GameOfLife::Game pattern;
			pattern.addCellAt(-1, 0).addCellAt(-2, 0).addCellAt(-3, 0);
			pattern.tick();
			std::vector <std::pair <long int, long int> > coordinates = pattern.currentGeneration();

			std::vector <std::pair <long int, long int> > expectedCoordinates;
			expectedCoordinates.push_back(std::make_pair(-2, -1));
			expectedCoordinates.push_back(std::make_pair(-2, 0));
			expectedCoordinates.push_back(std::make_pair(-2, 1));
			Assert::That(coordinates, Equals(expectedCoordinates));
		}
	};

	Describe(previous_generation_cells) {
		It(can_be_visited) {
			GameOfLife::Game pattern;
			pattern.addCellAt(-1, 0).addCellAt(0, -1).addCellAt(1, 0).addCellAt(5, 5).tick();
			std::vector <std::pair <long int, long int> > coordinates = pattern.previousGeneration();

			std::vector <std::pair <long int, long int> > expectedCoordinates;
			expectedCoordinates.push_back(std::make_pair(-1, 0));
			expectedCoordinates.push_back(std::make_pair(0, -1));
			expectedCoordinates.push_back(std::make_pair(1, 0));
			expectedCoordinates.push_back(std::make_pair(5, 5));
			Assert::That(coordinates, Equals(expectedCoordinates));
		}

		It(is_not_cached) {
			GameOfLife::Game pattern;
			pattern.addCellAt(-1, 0).addCellAt(-2, 0).addCellAt(-3, 0);
			pattern.tick().tick();
			std::vector <std::pair <long int, long int> > coordinates = pattern.previousGeneration();

			std::vector <std::pair <long int, long int> > expectedCoordinates;
			expectedCoordinates.push_back(std::make_pair(-2, -1));
			expectedCoordinates.push_back(std::make_pair(-2, 0));
			expectedCoordinates.push_back(std::make_pair(-2, 1));
			Assert::That(coordinates, Equals(expectedCoordinates));
		}
	};

};

int main()
{
	return TestRunner::RunAllTests();
}