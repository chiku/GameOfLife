#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include "game.hh"
#include "fltk/mark_cell.hh"
#include "fltk/canvas.hh"

void GameOfLife::FLTK::Canvas::draw()
{
	auto toAdd = game->cellsToAdd();
	auto toRemove = game->cellsToRemove();

	for (auto it = toRemove.begin(); it != toRemove.end(); ++it)
		markCell->deadAt(it->first, it->second);

	for (auto it = toAdd.begin(); it != toAdd.end(); ++it)
		markCell->aliveAt(it->first, it->second);

	game->tick();
}

void GameOfLife::FLTK::Canvas::Timer_CB(void *userdata)
{
	Canvas *o = (Canvas*)userdata;
	o->redraw();
	Fl::repeat_timeout(TIMEOUT, Timer_CB, userdata);
}

GameOfLife::FLTK::Canvas::Canvas(GameOfLife::Game *game_, long int width, long int height) : Fl_Widget(0, 0, 1280, 800, ""), game(game_)
{
	markCell = new MarkCell(width, height);
	Fl::add_timeout(TIMEOUT, Timer_CB, (void*)this);
}

GameOfLife::FLTK::Canvas::~Canvas()
{
	delete markCell;
}
