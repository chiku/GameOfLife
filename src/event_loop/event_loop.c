#include <stdio.h>
#include <stdlib.h>

#include "../game_of_life.h"
#include "event_loop.h"

#include <ncurses.h>

EventLoop* EventLoop_Initialize(World *world, Graphics *graphics, void (*draw_cell)(long int, long int, void *))
{
	EventLoop *self = (EventLoop*)(malloc( sizeof(EventLoop) ));

	self->world = world;
	self->graphics = graphics;
	self->draw_cell = draw_cell;

	return self;
}

void EventLoop_Destroy(EventLoop *self)
{
	free(self);
}

void EventLoop_Begin(EventLoop *self)
{
	Graphics_Callback_Handler(self->graphics, 0.01);

	for(;;) {
		EventLoop_Draw(self);
		Graphics_Callback_Handler(self->graphics, 0.5);

		EventLoop_Erase(self);
		Graphics_Callback_Handler(self->graphics, 0.0);

		EventLoop_Cleanup(self);
		Graphics_Callback_Handler(self->graphics, 0.0);
	}
}

void EventLoop_Draw(EventLoop *self)
{
	Graphics_Set_Draw_Color(self->graphics);
	World_At_Each_Cell(self->world, self->draw_cell, self->graphics);
	Graphics_Flush(self->graphics);
}

void EventLoop_Erase(EventLoop *self)
{
	Graphics_Set_Erase_Color(self->graphics);
	World_At_Each_Cell(self->world, self->draw_cell, self->graphics);
	Graphics_Flush(self->graphics);
}

void EventLoop_Cleanup(EventLoop *self)
{
	self->world = World_Tick(self->world);
	Graphics_Clear(self->graphics);
}

