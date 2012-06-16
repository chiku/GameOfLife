#include <stdio.h>
#include <stdlib.h>

#include "../game_of_life.h"
#include "main_loop.h"

MainLoop* MainLoop_Initialize(World *world, Graphics *graphics, void (*draw_cell)(Coordinates coordinates, void *))
{
	MainLoop *self = (MainLoop*)(malloc( sizeof(MainLoop) ));

	self->world = world;
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
		MainLoop_Draw(self);
		Graphics_Callback_Handler(self->graphics, 0.5);

		MainLoop_Erase(self);
		Graphics_Callback_Handler(self->graphics, 0.0);

		MainLoop_Cleanup(self);
		Graphics_Callback_Handler(self->graphics, 0.0);
	}
}

void MainLoop_Draw(MainLoop *self)
{
	Graphics_Set_Draw_Color(self->graphics);
	World_At_Each_Cell(self->world, self->draw_cell, self->graphics);
	Graphics_Flush(self->graphics);
}

void MainLoop_Erase(MainLoop *self)
{
	Graphics_Set_Erase_Color(self->graphics);
	World_At_Each_Cell(self->world, self->draw_cell, self->graphics);
	Graphics_Flush(self->graphics);
}

void MainLoop_Cleanup(MainLoop *self)
{
	self->world = World_Tick(self->world);
	Graphics_Clear(self->graphics);
}
