#include <vector>
#include <utility>

extern "C" {
	#include <game_of_life.h>
}


namespace GameOfLife
{
	class Game
	{
		private:
			::Game *game;
			std::vector <std::pair <long int, long int> > *currentCoordinates;
			std::vector <std::pair <long int, long int> > *previousCoordinates;

		public:
			Game()
			{
				game = Game_New();
				currentCoordinates = new std::vector <std::pair <long int, long int> >;
				previousCoordinates = new std::vector <std::pair <long int, long int> >;
			}

			~Game()
			{
				// Game_Destroy(game);
			}

			long int cellCount()
			{
				return Game_Cell_Count(game);
			}

			Game addCellAt(long int x, long int y)
			{
				Game_Add_Cell_At(game, x, y);
				return *this;
			}

			bool hasCellAt(long int x, long int y)
			{
				return Game_Has_Cell_At(game, x, y) == 1 ? true : false;
			}

			Game tick()
			{
				Game_Tick(game);
				return *this;
			}

			std::vector <std::pair <long int, long int> > currentGeneration()
			{
				currentCoordinates->clear();
				Game_At_Each_Cell(game, yield_visitor, (void*)currentCoordinates);
				return *currentCoordinates;
			}

			std::vector <std::pair <long int, long int> > previousGeneration()
			{
				previousCoordinates->clear();
				Game_At_Each_Old_Cell(game, yield_visitor, (void*)previousCoordinates);
				return *previousCoordinates;
			}

		private:
			static void yield_visitor(::Coordinates coordinates_, void* data_)
			{
				std::vector< std::pair <long int, long int> > *allCoordinates = (std::vector< std::pair <long int, long int> >*)(data_);
				std::pair <long int, long int>coordinates = std::make_pair(Coordinates_X(coordinates_), Coordinates_Y(coordinates_));

				allCoordinates->push_back(coordinates);
			}
	};
}
