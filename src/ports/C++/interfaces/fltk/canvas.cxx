#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include "game.hh"
#include "fltk/mark_cell.hh"
#include "fltk/canvas.hh"

GameOfLife::FLTK::Canvas::Canvas(long int width, long int height) : Fl_Widget(0, 0, width, height, "")
{
	markCell = new MarkCell(width, height);
	Fl::add_timeout(GameOfLife::FLTK::Canvas::Timeout(), Timer_CB, (void*)this);
}

GameOfLife::FLTK::Canvas::~Canvas()
{
	delete markCell;
}

void GameOfLife::FLTK::Canvas::attachGame(GameOfLife::Game *game_)
{
	game = game_;
}

void GameOfLife::FLTK::Canvas::draw()
{
	Coors toAdd = game->cellsToAdd();
	Coors toRemove = game->cellsToRemove();

	for (Coors::iterator it = toRemove.begin(); it != toRemove.end(); ++it)
		markCell->deadAt(it->first, it->second);

	for (Coors::iterator it = toAdd.begin(); it != toAdd.end(); ++it)
		markCell->aliveAt(it->first, it->second);

	game->tick();
}

double GameOfLife::FLTK::Canvas::Timeout()
{
	return 0.5;
}

void GameOfLife::FLTK::Canvas::Timer_CB(void *userdata)
{
	Canvas *o = (Canvas*)userdata;
	o->redraw();
	Fl::repeat_timeout(Timeout(), Timer_CB, userdata);
}
