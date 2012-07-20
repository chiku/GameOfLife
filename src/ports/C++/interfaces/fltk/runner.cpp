#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include "game.hh"
#include "fltk/runner.hh"

void GameOfLife::Runner::draw()
{
	auto toAdd = game.cellsToAdd();
	auto toRemove = game.cellsToRemove();

	for (auto it = toRemove.begin(); it != toRemove.end(); ++it)
	{
		long int x1 = it->first * SIZE + WIDTH / 2 - SIZE / 2;
		long int y1 = it->second * SIZE + HEIGHT / 2 - SIZE / 2;

		fl_rectf(x1, y1, SIZE - 1, SIZE - 1, DEAD_COLOUR);
	}

	for (auto it = toAdd.begin(); it != toAdd.end(); ++it)
	{
		long int x1 = it->first * SIZE + WIDTH / 2 - SIZE / 2;
		long int y1 = it->second * SIZE + HEIGHT / 2 - SIZE / 2;

		fl_rectf(x1, y1, SIZE - 1, SIZE - 1, ALIVE_COLOUR);
	}

	game.tick();
}

void GameOfLife::Runner::Timer_CB(void *userdata)
{
	Runner *o = (Runner*)userdata;
	o->redraw();
	Fl::repeat_timeout(timeout, Timer_CB, userdata);
}

GameOfLife::Runner::Runner(GameOfLife::Game game_) : Fl_Widget(0, 0, 1280, 800, "")
{
	game = game_;
	Fl::add_timeout(timeout, Timer_CB, (void*)this);
}
