#include <stdio.h>
#include <stdlib.h>

#include "game_of_life.h"
#include "main_loop/main_loop.h"

MainLoop* MainLoop_Initialize(Game *game, Graphics *graphics, void (*draw_cell)(Coordinates coordinates, void *))
{
	MainLoop *self = (MainLoop*)(malloc( sizeof(MainLoop) ));

	self->game = game;
	self->graphics = graphics;
	self->draw_cell = draw_cell;

	return self;
}

void MainLoop_Destroy(MainLoop *self)
{
	free(self);
}

void MainLoop_Begin(MainLoop *self)
{
	Graphics_Callback_Handler(self->graphics, 0.0);

	for(;;) {
		MainLoop_Erase(self);
		Graphics_Callback_Handler(self->graphics, 0.0);

		MainLoop_Draw(self);
		Graphics_Callback_Handler(self->graphics, 0.005);

		MainLoop_Tick(self);
		Graphics_Callback_Handler(self->graphics, 0.0);
	}
}

void MainLoop_Draw(MainLoop *self)
{
	Graphics_Set_Draw_Color(self->graphics);
	Game_At_Each_Cell(self->game, self->draw_cell, self->graphics);
	Graphics_Flush(self->graphics);
}

void MainLoop_Erase(MainLoop *self)
{
	Graphics_Set_Erase_Color(self->graphics);
	Game_At_Each_Old_Cell(self->game, self->draw_cell, self->graphics);
}

void MainLoop_Tick(MainLoop *self)
{
	self->game = Game_Tick(self->game);
}
