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
		private:
			const long int WIDTH = 1280;
			const long int HEIGHT = 800;

			Fl_Double_Window *window;
			GameOfLife::FLTK::Canvas *canvas;

			void draw();
			static void Timer_CB(void *userdata);

		public:
			Window(GameOfLife::Game game);
			~Window();
		};
	}
}

#endif
