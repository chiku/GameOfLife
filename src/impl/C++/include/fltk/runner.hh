#include "game.hh"
#include "fltk/window.hh"

#ifndef GAME_OF_LIFE_RUNNER_HH
#define GAME_OF_LIFE_RUNNER_HH

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
