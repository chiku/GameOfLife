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

			Game game;
			MarkCell *markCell;

			void draw();
			static void Timer_CB(void *userdata);

		public:
			Canvas(GameOfLife::Game game_, long int width, long int height);
			~Canvas();
		};
	}
}

#endif
