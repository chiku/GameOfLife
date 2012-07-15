#define _POSIX_C_SOURCE 199506L

#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#include "interfaces/curses.h"

const int DRAW = 1;
const int ERASE = 2;

Graphics* Graphics_Allocate()
{
	return (Graphics*)(malloc( sizeof(Graphics) ));
}

Graphics* Graphics_Initialize(Graphics *self)
{
	self->draw_colour_palate = 1;
	self->erase_colour_palate = 2;

	initscr();
	start_color();
	curs_set(0);
	init_pair(DRAW, COLOR_RED, COLOR_BLACK);
	init_pair(ERASE, COLOR_BLACK, COLOR_BLACK);

	self->draw_colour_palate = COLOR_PAIR(DRAW);
	self->erase_colour_palate = COLOR_PAIR(ERASE);
	self->drawing_symbol = ACS_DIAMOND;

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
	attroff(self->draw_colour_palate);
	attroff(self->erase_colour_palate);
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
