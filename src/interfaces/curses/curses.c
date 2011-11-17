#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <ncurses.h>

#include <game_of_life.h>

#include "signal_handlers.c"

void handle_signal_for(char *message, int exit_status)
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

int main(int argc, char *argv[])
{
	initialize_signal_handlers();

	char *file_name = handle_command_line_arguments(argc, argv);
	World *world = create_world_with_file(file_name);

	initscr();
	noecho();
	curs_set(0);

	for (;;) {
		World_At_Each_Cell(world, print_cell, NULL);
		refresh();
		usleep(500000L);
		erase();
		world = World_Tick(world);
	}
	endwin();

	return 0;
}

