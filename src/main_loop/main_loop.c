#define _POSIX_C_SOURCE 199506L

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game_of_life.h"
#include "main_loop/main_loop.h"

MainLoop* MainLoop_New(Game *game, Graphics *graphics, void (*draw_cell)(Coordinates coordinates, void *))
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
	while(1) {
		MainLoop_Erase(self);
		MainLoop_Delay(0.0);

		MainLoop_Draw(self);
		MainLoop_Delay(0.005);

		MainLoop_Tick(self);
		MainLoop_Delay(0.0);
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

void MainLoop_Delay(double time_in_s)
{
	struct timespec tim;
	tim.tv_sec = 0;
	tim.tv_nsec = time_in_s * 1000000000L;
	nanosleep(&tim, NULL);
}
