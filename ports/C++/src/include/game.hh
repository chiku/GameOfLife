#include <set>
#include <utility>

extern "C" {
	#include <game_of_life.h>
}

#ifndef __GAME_OF_LIFE_CXX__
#define __GAME_OF_LIFE_CXX__


namespace GameOfLife
{
	typedef std::set< std::pair<long int, long int> > Coors;

	class Game
	{
	private:
		::Game *game;
		Coors *currentCoordinates;
		Coors *previousCoordinates;

		void syncGenerations();
		static void accumulationVisitor(::Coordinates coordinates, void* data);
		static Coors differencesBetween(const Coors *first, const Coors *second);

	public:
		Game();

		long int cellCount() const;
		Game read(const char filename[]);
		Game addCellAt(long int x, long int y);
		bool hasCellAt(long int x, long int y) const;
		Game tick();
		Coors currentGeneration() const;
		Coors previousGeneration() const;
		Coors cellsToRemove() const;
		Coors cellsToAdd() const;
	};
}

#endif
