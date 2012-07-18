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
		static Cors differencesBetween(const Cors *first, const Cors *second);

	public:
		Game();

		long int cellCount() const;
		Game addCellAt(long int x, long int y);
		bool hasCellAt(long int x, long int y) const;
		Game tick();
		Cors currentGeneration() const;
		Cors previousGeneration() const;
		Cors cellsToRemove() const;
		Cors cellsToAdd() const;
	};
}

#endif
