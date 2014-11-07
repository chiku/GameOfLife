#include <set>
#include <utility>
#include <string>

extern "C" {
	#include <game_of_life.h>
}

#ifndef GAME_OF_LIFE_HH
#define GAME_OF_LIFE_HH


namespace GameOfLife
{
	typedef std::set< std::pair<long int, long int> > Coors;

	class Game
	{
	public:
		Game();

		long int cellCount() const;
		Game read(const std::string filename);
		Game addCellAt(long int x, long int y);
		bool hasCellAt(long int x, long int y) const;
		Game tick();
		Coors currentGeneration() const;
		Coors previousGeneration() const;
		Coors cellsToRemove() const;
		Coors cellsToAdd() const;

	private:
		::Game *game;
		Coors *currentCoordinates;
		Coors *previousCoordinates;

		void syncGenerations();
		static void accumulationVisitor(::Cell cell, void* data);
		static Coors differencesBetween(const Coors *first, const Coors *second);
	};
}

#endif
