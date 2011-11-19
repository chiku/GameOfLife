#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <unistd.h>

using namespace std;

extern "C" {
	#include <game_of_life.h>
	#include "signal_handlers.c"
}

#include "graphics.h"

void handle_signal_for(const char *message, int exit_status)
{
	fprintf((exit_status ? stderr : stdout), message);
	exit(exit_status);
}

static void draw_cell(long int x, long int y, void *data)
{
	((Graphics*)data)->Draw_Square(x, y);
}

int main(int argc, char *argv[])
{
	initialize_signal_handlers();

	char *file_name = handle_command_line_arguments(argc, argv);
	World *world = create_world_with_file(file_name);

	Graphics *graphics = new Graphics();

	for (;;) {
		World_At_Each_Cell(world, draw_cell, graphics);
		graphics->Redraw();
		graphics->Flush();

		usleep(500000L);
		world = World_Tick(world);

		graphics->Clear();
	}

	return 0;
}

