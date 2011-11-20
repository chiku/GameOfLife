#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "game_of_life.h"
#include "event_loop/event_loop.h"
#include "graphics.h"

void cleanup_on_signal()
{
	curs_set(1);
	endwin();
}

void draw_cell(long int x, long int y, void *data)
{
	mvaddch(y + LINES/2, x + COLS/2, ACS_DIAMOND);
}

