#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include "game.hh"
#include "fltk/canvas.hh"

#ifndef __GAME_OF_LIFE_WINDOW_CXX__
#define __GAME_OF_LIFE_WINDOW_CXX__

namespace GameOfLife
{
	namespace FLTK
	{
		class Window
		{
		public:
			Window();
			~Window();
			void attachGameToCanvas(GameOfLife::Game *game);

		private:
			const long int WIDTH;
			const long int HEIGHT;

			Fl_Double_Window *window;
			GameOfLife::FLTK::Canvas *canvas;

			void setPropertiesOnWindow();
		};
	}
}

#endif
