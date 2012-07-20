#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>

#include "game.hh"
#include "fltk/window.hh"

int main()
{
	GameOfLife::Game *game = new GameOfLife::Game();
	game->addCellAt(0, 0);
	game->addCellAt(1, -1);
	game->addCellAt(2, -1);
	game->addCellAt(3, -1);
	game->addCellAt(-3, -1);
	game->addCellAt(-2, -1);
	game->addCellAt(-2, 1);

	GameOfLife::FLTK::Window window(game);
	window.show();

	return Fl::run();
}
