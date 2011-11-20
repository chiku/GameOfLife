#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <ncurses.h>

#include "game_of_life.h"
#include "event_loop/event_loop.h"

#include "signal_handlers.c"

void handle_signal_for(const char *message, int exit_status)
{
	curs_set(1);
	endwin();
	fprintf((exit_status ? stderr : stdout), message);
	exit(exit_status);
}

static void print_cell(long int x, long int y, void *data)
{
	mvaddch(y + LINES/2, x + COLS/2, ACS_DIAMOND);
}

struct Graphics
{
	int current_color;
};

Graphics* Graphics_Initialize()
{
	Graphics *self = (Graphics*)(malloc( sizeof(Graphics) ));

	initscr();
	start_color();
	curs_set(0);
	init_pair(1, COLOR_RED, COLOR_BLACK);

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

void Graphics_Flush(Graphics *self)
{
	refresh();
}

void Graphics_Clear(Graphics *self)
{
	erase();
}

void Graphics_Set_Draw_Color(Graphics *self)
{
	attron(COLOR_PAIR(1));
}

void Graphics_Set_Erase_Color(Graphics *self)
{
	attron(COLOR_PAIR(1));
}


int main(int argc, char *argv[])
{
	initialize_signal_handlers();

	char *file_name = handle_command_line_arguments(argc, argv);
	World *world = create_world_with_file(file_name);
	Graphics *graphics = Graphics_Initialize();

	EventLoop *event_loop = EventLoop_Initialize(world, graphics, print_cell);
	EventLoop_Begin(event_loop);

	EventLoop_Destroy(event_loop);
	World_Destroy(world);
	Graphics_Destroy(graphics);

	return 0;
}

