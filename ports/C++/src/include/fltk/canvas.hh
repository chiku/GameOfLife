#include <FL/Fl.H>

#include "game.hh"
#include "fltk/mark_cell.hh"

#ifndef __GAME_OF_LIFE_CANVAS_CXX__
#define __GAME_OF_LIFE_CANVAS_CXX__

namespace GameOfLife
{
	namespace FLTK
	{
		class Canvas : public Fl_Widget
		{
		private:
			static constexpr double TIMEOUT = 0.50;

			GameOfLife::Game *game;
			MarkCell *markCell;

			void draw();
			static void Timer_CB(void *userdata);

		public:
			Canvas(long int width, long int height);
			~Canvas();
			void attachGame(GameOfLife::Game *game_);
		};
	}
}

#endif
