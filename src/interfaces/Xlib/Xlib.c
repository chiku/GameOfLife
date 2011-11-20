#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "game_of_life.h"
#include "event_loop/event_loop.h"
#include "graphics.h"

void cleanup_on_signal() { }

void draw_cell(long int x, long int y, void *data)
{
	Graphics_Draw_Square((Graphics*)data, x, y);
}

int main(int argc, char *argv[])
{
	initialize_signal_handlers();

	char *file_name = handle_command_line_arguments(argc, argv);
	World *world = World_Create_From_File(file_name);

	Graphics *graphics = Graphics_Initialize();

	for (;;) {
		Graphics_Set_Foreground(graphics);
		World_At_Each_Cell(world, draw_cell, graphics);

		Graphics_Flush(graphics);
		usleep(500000L);

		Graphics_Set_Reverse_Foreground(graphics);
		World_At_Each_Cell(world, draw_cell, graphics);

		world = World_Tick(world);
	}

	Graphics_Destroy(graphics);

	return 0;
}

