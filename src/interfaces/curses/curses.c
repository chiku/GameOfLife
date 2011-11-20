#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#include "graphics.h"

void cleanup_on_signal()
{
	curs_set(1);
	endwin();
}

void draw_cell(long int x, long int y, void *data)
{
	Graphics_Draw_At((Graphics*)data, x, y);
}

