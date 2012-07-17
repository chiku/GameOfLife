#include <set>
#include <algorithm>
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
			std::set <std::pair <long int, long int> > *currentCoordinates;
			std::set <std::pair <long int, long int> > *previousCoordinates;

			bool currentCoordinatesCached;
			bool previousCoordinatesCached;

			void burstCache()
			{
				currentCoordinatesCached = false;
				previousCoordinatesCached = false;
			}

			static void yield_visitor(::Coordinates coordinates_, void* data_)
			{
				std::set< std::pair <long int, long int> > *allCoordinates = (std::set< std::pair <long int, long int> >*)(data_);
				std::pair <long int, long int>coordinates = std::make_pair(Coordinates_X(coordinates_), Coordinates_Y(coordinates_));
				allCoordinates->insert(coordinates);
			}

		public:
			Game()
			{
				burstCache();
				game = Game_New();
				currentCoordinates = new std::set <std::pair <long int, long int> >;
				previousCoordinates = new std::set <std::pair <long int, long int> >;
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
				burstCache();
				Game_Tick(game);
				return *this;
			}

			std::set <std::pair <long int, long int> > currentGeneration()
			{
				if (!currentCoordinatesCached) {
					currentCoordinates->clear();
					Game_At_Each_Cell(game, yield_visitor, (void*)currentCoordinates);
					currentCoordinatesCached = true;
				}

				return *currentCoordinates;
			}

			std::set <std::pair <long int, long int> > previousGeneration()
			{
				if (!previousCoordinatesCached) {
					previousCoordinates->clear();
					Game_At_Each_Old_Cell(game, yield_visitor, (void*)previousCoordinates);
					previousCoordinatesCached = true;
				}

				return *previousCoordinates;
			}

			std::set< std::pair<long int, long int> > cellsToRemove()
			{
				std::set< std::pair <long int, long int> > result;
				currentGeneration();
				previousGeneration();
				std::set_difference(previousCoordinates->begin(), previousCoordinates->end(),
				                    currentCoordinates->begin(), currentCoordinates->end(),
				                    std::inserter(result, result.end()));
				return result;
			}

			std::set< std::pair<long int, long int> > cellsToAdd()
			{
				std::set< std::pair <long int, long int> > result;
				currentGeneration();
				previousGeneration();
				std::set_difference(currentCoordinates->begin(), currentCoordinates->end(),
									previousCoordinates->begin(), previousCoordinates->end(),
				                    std::inserter(result, result.end()));
				return result;
			}
	};
}
