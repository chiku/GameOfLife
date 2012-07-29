#include "game_of_life.h"
#include "main_loop/main_loop.h"

static void draw_cell(Cell cell, void *data)
{
	Graphics_Draw_At((Graphics*)data, cell.coordinates.x, cell.coordinates.y);
}

int main(int argc, char *argv[])
{
	initialize_signal_handlers();

	char *file_name = file_name_on_valid_command_line_arguments(argc, argv);
	long int delay = 5;
	Game *game = Game_Create_From_File(file_name);
	Graphics *graphics = Graphics_New();

	MainLoop *main_loop = MainLoop_New(game, graphics, draw_cell);
	MainLoop_Begin(main_loop, delay);

	MainLoop_Destroy(main_loop);
	Game_Destroy(game);
	Graphics_Destroy(graphics);

	return 0;
}
