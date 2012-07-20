#include "fltk/runner.hh"

GameOfLife::FLTK::Runner::Runner(GameOfLife::Game *game, GameOfLife::FLTK::Window *window)
{
	window->attachGameToCanvas(game);
}

int GameOfLife::FLTK::Runner::init()
{
	return Fl::run();
}
