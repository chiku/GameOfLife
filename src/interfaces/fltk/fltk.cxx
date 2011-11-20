#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <unistd.h>

#include <FL/Fl.H>

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

Graphics *graphics;
World *world;

static void repeat(void*)
{
	World_At_Each_Cell(world, draw_cell, graphics);
	graphics->Redraw();
	graphics->Flush();

	world = World_Tick(world);

	graphics->Clear();
	Fl::repeat_timeout(0.5, repeat);
}

int main(int argc, char *argv[])
{
	initialize_signal_handlers();

	char *file_name = handle_command_line_arguments(argc, argv);
	world = create_world_with_file(file_name);

	graphics = new Graphics();

	Fl::add_timeout(0.5, repeat);
	return Fl::run();
}

