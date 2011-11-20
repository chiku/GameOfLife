#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include <FL/Fl.H>

using namespace std;

extern "C" {
	#include "game_of_life.h"
	#include "event_loop/event_loop.h"
	#include "graphics.h"
}

#include "graphics.h"

void cleanup_on_signal() { }

void draw_cell(long int x, long int y, void *data)
{
	Graphics_Draw_At((Graphics*)data, x, y);
}

Graphics *graphics;
World *world;

static void repeat(void*)
{
	World_At_Each_Cell(world, draw_cell, graphics);
	Graphics_Flush(graphics);

	world = World_Tick(world);

	Graphics_Clear(graphics);
	Fl::repeat_timeout(0.5, repeat);
}

int main(int argc, char *argv[])
{
	initialize_signal_handlers();

	char *file_name = handle_command_line_arguments(argc, argv);
	world = World_Create_From_File(file_name);

	graphics = Graphics_Initialize();

	Fl::add_timeout(0.5, repeat);
	return Fl::run();
}

