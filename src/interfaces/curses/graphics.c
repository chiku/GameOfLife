#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#include "graphics.h"

Graphics* Graphics_Initialize()
{
	Graphics *self = (Graphics*)(malloc( sizeof(Graphics) ));

	initscr();
	start_color();
	curs_set(0);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(1));

	return self;
}

void Graphics_Destroy(Graphics *self)
{
	free(self);
}

void Graphics_Callback_Handler(Graphics *self, double time_in_s)
{
	usleep( (long)(time_in_s * 1000000) );
}

void Graphics_Draw_At(Graphics *self, long int x, long int y)
{
	mvaddch(y + LINES/2, x + COLS/2, ACS_DIAMOND);
}

void Graphics_Flush(Graphics *self)
{
	refresh();
}

void Graphics_Clear(Graphics *self)
{
	erase();
}

void Graphics_Set_Draw_Color(Graphics *self) { }

void Graphics_Set_Erase_Color(Graphics *self) { }

