#ifndef GOL_MAIN_LOOP_H
#define GOL_MAIN_LOOP_H

#include "game_of_life.h"

typedef struct Graphics Graphics;
typedef struct MainLoop MainLoop;

struct MainLoop
{
	Game *game;
	Graphics *graphics;
	void (*draw_cell)(Cell cell, void *);
};

/* Member methods */
MainLoop* MainLoop_New(Game *game, Graphics *graphics, void (*draw_cell)(Cell cell, void *));
void MainLoop_Destroy(MainLoop *self);

void MainLoop_Begin(MainLoop *self);

void MainLoop_Draw(const MainLoop *self);
void MainLoop_Erase(const MainLoop *self);
void MainLoop_Tick(MainLoop *self);
void MainLoop_Delay(long int time_in_ms);
/* Member methods */

/* Interface of Graphics */
extern Graphics* Graphics_New();
extern void Graphics_Destroy(Graphics *self);

extern void Graphics_Draw_At(const Graphics *self, long int x, long int y);
extern void Graphics_Flush(const Graphics *self);
extern void Graphics_Clear(const Graphics *self);
extern void Graphics_Set_Draw_Color(const Graphics *self);
extern void Graphics_Set_Erase_Color(const Graphics *self);
/* Interface of Graphics */

/* Interface of signal handling and main */
extern void cleanup_on_signal();
void initialize_signal_handlers(void);
char *file_name_on_valid_command_line_arguments(int argc, char *argv[]);
/* Interface of signal handling and main */

#endif
