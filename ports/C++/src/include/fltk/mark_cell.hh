#include <FL/Fl.H>

#ifndef __GAME_OF_LIFE_MARK_CELL_CXX__
#define __GAME_OF_LIFE_MARK_CELL_CXX__

namespace GameOfLife
{
	namespace FLTK
	{
		class MarkCell
		{
		private:
			const long int WIDTH;
			const long int HEIGHT;
			const int SIZE = 4;

			const Fl_Color ALIVE = fl_rgb_color(220, 80, 120);
			const Fl_Color DEAD = fl_rgb_color(210, 240, 190);

			void markCellAt(long int x, long int y, Fl_Color colour);

		public:
			MarkCell(long int width, long int height);
			void aliveAt(long int x, long int y);
			void deadAt(long int x, long int y);
		};
	}
}

#endif
