#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include "fltk/runner.hh"

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

	Fl_Double_Window window(1280, 800);
	window.fullscreen();
	window.label("Conway's Game of life");

	GameOfLife::Runner runner(game);
	window.add(runner);
	window.show();

	return Fl::run();
}
