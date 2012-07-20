#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include "fltk/mark_cell.hh"

GameOfLife::FLTK::MarkCell::MarkCell(long int width, long int height) : WIDTH(width), HEIGHT(height)
{
}

void GameOfLife::FLTK::MarkCell::markCellAt(long int x, long int y, Fl_Color colour)
{
	long int x1 = x * SIZE + WIDTH / 2 - SIZE / 2;
	long int y1 = y * SIZE + HEIGHT / 2 - SIZE / 2;

	fl_rectf(x1, y1, SIZE - 1, SIZE - 1, colour);
}

void GameOfLife::FLTK::MarkCell::aliveAt(long int x, long int y)
{
	markCellAt(x, y, ALIVE);
}

void GameOfLife::FLTK::MarkCell::deadAt(long int x, long int y)
{
	markCellAt(x, y, DEAD);
}
