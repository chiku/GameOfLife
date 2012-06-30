#include "../game_of_life.h"
#include "main_loop.h"

static void draw_cell(Coordinates coordinates, void *data)
{
	Graphics_Draw_At((Graphics*)data, coordinates.x, coordinates.y);
}

int main(int argc, char *argv[])
{
	initialize_signal_handlers();

	char *file_name = handle_command_line_arguments(argc, argv);
	Game *game = Game_Create_From_File(file_name);
	Graphics *graphics = Graphics_Initialize();

	MainLoop *main_loop = MainLoop_Initialize(game, graphics, draw_cell);
	MainLoop_Begin(main_loop);

	MainLoop_Destroy(main_loop);
	Game_Destroy(game);
	Graphics_Destroy(graphics);

	return 0;
}
