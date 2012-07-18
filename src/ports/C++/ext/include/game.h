#include <set>
#include <utility>

extern "C" {
	#include <game_of_life.h>
}

#ifndef __GAME_OF_LIFE_CXX__
#define __GAME_OF_LIFE_CXX__

typedef std::set< std::pair<long int, long int> > Cors;

namespace GameOfLife
{
	class Game
	{
	private:
		::Game *game;
		Cors *currentCoordinates;
		Cors *previousCoordinates;

		void syncGenerations();
		static void accumulationVisitor(::Coordinates coordinates_, void* data_);
		Cors differencesBetween(Cors *first, Cors *second);

	public:
		Game();

		long int cellCount();
		Game addCellAt(long int x, long int y);
		bool hasCellAt(long int x, long int y);
		Game tick();
		Cors currentGeneration();
		Cors previousGeneration();
		Cors cellsToRemove();
		Cors cellsToAdd();
	};
}

#endif
