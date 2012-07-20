#include "game.hh"
#include "fltk/window.hh"

#ifndef __GAME_OF_LIFE_RUNNER_CXX__
#define __GAME_OF_LIFE_RUNNER_CXX__

namespace GameOfLife
{
	namespace FLTK
	{
		class Runner
		{
		public:
			Runner(GameOfLife::Game *game, GameOfLife::FLTK::Window *window);
			int init();
		};
	}
}

#endif
