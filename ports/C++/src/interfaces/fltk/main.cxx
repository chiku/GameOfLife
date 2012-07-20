#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include "game.hh"
#include "fltk/window.hh"
#include "fltk/runner.hh"

int main()
{
	GameOfLife::Game *game = new GameOfLife::Game();
	(*game).addCellAt(0, 0)
	       .addCellAt(1, -1)
	       .addCellAt(2, -1)
	       .addCellAt(3, -1)
	       .addCellAt(-3, -1)
	       .addCellAt(-2, -1)
	       .addCellAt(-2, 1);

	GameOfLife::FLTK::Window *window = new GameOfLife::FLTK::Window();

	GameOfLife::FLTK::Runner runner(game, window);
	return runner.init();
}
