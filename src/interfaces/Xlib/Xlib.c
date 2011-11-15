#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <game_of_life.h>
#include "graphics.h"

#include "signal_handlers.c"

void handle_signal_for(char *message, int exit_status)
{
	printf(message);
	exit(exit_status);
}

static void draw_cell(long int x, long int y, void *data)
{
	Graphics_Draw_Rectangle((Graphics*)data, y, x);
}

int main(int argc, char *argv[])
{
	initialize_signal_handlers();

	char *file_name = handle_command_line_arguments(argc, argv);
	World *world = create_world_with_file(file_name);

	Graphics *graphics = Graphics_Initialize();
	Graphics_Start_Loop(graphics);

	for (;;) {
		Graphics_Set_Foreground(graphics);
		World_At_Each_Cell(world, draw_cell, graphics);

		usleep(5000L);

		Graphics_Set_Reverse_Foreground(graphics);
		World_At_Each_Cell(world, draw_cell, graphics);

		world = World_Tick(world);
	}

	Graphics_Destroy(graphics);

	return 0;
}

