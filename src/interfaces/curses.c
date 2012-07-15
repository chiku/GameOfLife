#define _POSIX_C_SOURCE 199506L

#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "interfaces/curses.h"

Graphics* Graphics_Allocate()
{
	return (Graphics*)(malloc( sizeof(Graphics) ));
}

Graphics* Graphics_Initialize(Graphics *self)
{
	const int DRAW_PAIR = 1;
	const int ERASE_PAIR = 2;

	initscr();
	start_color();
	curs_set(0);

	self->draw_colour_palate = 1;
	self->erase_colour_palate = 2;
	self->draw_colour_palate = COLOR_PAIR(DRAW_PAIR);
	self->erase_colour_palate = COLOR_PAIR(ERASE_PAIR);
	self->drawing_symbol = ACS_DIAMOND;

	init_color(COLOR_RED, 900, 100, 200);
	init_color(COLOR_GREEN, 100, 200, 100);
	init_pair(DRAW_PAIR, COLOR_RED, COLOR_BLACK);
	init_pair(ERASE_PAIR, COLOR_GREEN, COLOR_BLACK);

	attron(self->draw_colour_palate);
	return self;
}

Graphics* Graphics_New()
{
	return Graphics_Initialize(Graphics_Allocate());
}

void Graphics_Destroy(Graphics *self)
{
	free(self);
}

void Graphics_Draw_At(Graphics *self, long int x, long int y)
{
	mvaddch(LINES/2 - y, COLS/2 + x, self->drawing_symbol);
}

void Graphics_Flush(Graphics *self)
{
	refresh();
}

void Graphics_Set_Draw_Color(Graphics *self)
{
	attroff(self->erase_colour_palate);
	attron(self->draw_colour_palate);
}

void Graphics_Set_Erase_Color(Graphics *self)
{
	attroff(self->draw_colour_palate);
	attron(self->erase_colour_palate);
}

/* Signal handing */
void cleanup_on_signal()
{
	curs_set(1);
	endwin();
}
