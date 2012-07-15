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
	initscr();
	start_color();
	curs_set(0);
	init_pair(DRAW, COLOR_RED, COLOR_BLACK);
	init_pair(ERASE, COLOR_BLACK, COLOR_BLACK);
	attron(COLOR_PAIR(DRAW));

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
	mvaddch(LINES/2 - y, COLS/2 + x, ACS_DIAMOND);
}

void Graphics_Flush(Graphics *self)
{
	refresh();
}

void Graphics_Set_Draw_Color(Graphics *self)
{
	attron(COLOR_PAIR(DRAW));
}

void Graphics_Set_Erase_Color(Graphics *self)
{
	attron(COLOR_PAIR(ERASE));
}

/* Signal handing */
void cleanup_on_signal()
{
	curs_set(1);
	endwin();
}
