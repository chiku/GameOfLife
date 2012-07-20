#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include "game.hh"
#include "fltk/window.hh"

int main()
{
	GameOfLife::Game game;
	game.addCellAt(0, 0)
		.addCellAt(1, -1)
		.addCellAt(2, -1)
		.addCellAt(3, -1)
		.addCellAt(-3, -1)
		.addCellAt(-2, -1)
		.addCellAt(-2, 1);

	GameOfLife::FLTK::Window window(game);

	return Fl::run();
}
