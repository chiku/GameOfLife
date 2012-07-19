#include <FL/Fl.H>
#include <FL/Fl_Box.H>

#include "game.hh"

#ifndef __GAME_OF_LIFE_RUNNER_CXX__
#define __GAME_OF_LIFE_RUNNER_CXX__

namespace GameOfLife
{
	class Runner : public Fl_Box
	{
	private:
		const Fl_Color ALIVE_COLOUR = FL_RED;
		const Fl_Color DEAD_COLOUR = FL_GRAY;
		const int SIZE = 4;
		const int WIDTH = 1280;
		const int HEIGHT = 800;
		static constexpr double timeout = 0.50;

		Game game;

		void draw();
		static void Timer_CB(void *userdata);

	public:
		Runner(GameOfLife::Game game_);
	};
}

#endif
