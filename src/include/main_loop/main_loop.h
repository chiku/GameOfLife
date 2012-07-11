#ifndef GOL_MAIN_LOOP_H
#define GOL_MAIN_LOOP_H

#include "game_of_life.h"

typedef struct Graphics Graphics;
typedef struct MainLoop MainLoop;

struct MainLoop
{
	Game *game;
	Graphics *graphics;
	void (*draw_cell)(Coordinates coordinates, void *);
};

/* Member methods */
MainLoop* MainLoop_Initialize(Game *game, Graphics *graphics, void (*draw_cell)(Coordinates coordinates, void *));
void MainLoop_Destroy(MainLoop *self);

void MainLoop_Begin(MainLoop *self);

void MainLoop_Draw(MainLoop *self);
void MainLoop_Erase(MainLoop *self);
void MainLoop_Tick(MainLoop *self);
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
