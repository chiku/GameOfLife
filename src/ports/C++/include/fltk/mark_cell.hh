#include <FL/Fl.H>

#ifndef __GAME_OF_LIFE_MARK_CELL_CXX__
#define __GAME_OF_LIFE_MARK_CELL_CXX__

namespace GameOfLife
{
	namespace FLTK
	{
		class MarkCell
		{
		public:
			MarkCell(long int width, long int height);
			void aliveAt(long int x, long int y);
			void deadAt(long int x, long int y);

		private:
			const long int WIDTH;
			const long int HEIGHT;
			const int SIZE;

			const Fl_Color ALIVE;
			const Fl_Color DEAD;

			void markCellAt(long int x, long int y, Fl_Color colour);
		};
	}
}

#endif
