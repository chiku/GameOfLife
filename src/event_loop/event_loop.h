#include "../game_of_life.h"

#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

typedef struct Graphics Graphics;
typedef struct EventLoop EventLoop;

struct EventLoop
{
	World *world;
	Graphics *graphics;
	void (*draw_cell)(long int, long int, void *);
};

/* Member methods */
EventLoop* EventLoop_Initialize(World *world, Graphics *graphics, void (*draw_cell)(long int, long int, void *));
void EventLoop_Destroy(EventLoop *self);

void EventLoop_Begin(EventLoop *self);

void EventLoop_Draw(EventLoop *self);
void EventLoop_Erase(EventLoop *self);
void EventLoop_Cleanup(EventLoop *self);
/* Member methods */

/* Interface of Graphics */
extern Graphics* Graphics_Initialize();
extern void Graphics_Destroy(Graphics *self);

extern void Graphics_Callback_Handler(Graphics *self, double time_in_ms);

extern void Graphics_Draw_At(Graphics *self, long int x, long int y);
extern void Graphics_Flush(Graphics *self);
extern void Graphics_Clear(Graphics *self);
extern void Graphics_Set_Draw_Color(Graphics *self);
extern void Graphics_Set_Erase_Color(Graphics *self);
/* Interface of Graphics */

/* Interface of signal handling and main */
extern void cleanup_on_signal();
void initialize_signal_handlers(void);
char *handle_command_line_arguments(int argc, char *argv[]);
/* Interface of signal handling and main */

#endif

