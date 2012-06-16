#include "../game_of_life.h"
#include "main_loop.h"

static void draw_cell(long int x, long int y, void *data)
{
	Graphics_Draw_At((Graphics*)data, x, y);
}

int main(int argc, char *argv[])
{
	initialize_signal_handlers();

	char *file_name = handle_command_line_arguments(argc, argv);
	World *world = World_Create_From_File(file_name);
	Graphics *graphics = Graphics_Initialize();

	MainLoop *main_loop = MainLoop_Initialize(world, graphics, draw_cell);
	MainLoop_Begin(main_loop);

	MainLoop_Destroy(main_loop);
	World_Destroy(world);
	Graphics_Destroy(graphics);

	return 0;
}
