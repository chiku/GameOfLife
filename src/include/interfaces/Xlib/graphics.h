#include <X11/Xlib.h>

#ifndef GOL_XLIB_GRAPHICS_H
#define GOL_XLIB_GRAPHICS_H

#define SCREEN 800
#define SQUARE 5

typedef struct Graphics Graphics;

struct Graphics
{
	Display *display;
	int screen;
	Window window;
	XColor orange, grey;
	GC current_gc, orange_gc, grey_gc;
};

Graphics* Graphics_Initialize();
void Graphics_Destroy(Graphics *self);
void Graphics_Cleanup_On_Signal(Graphics *self);

void Graphics_Draw_At(Graphics *self, long int x, long int y);
void Graphics_Callback_Handler(Graphics *self, double time_in_s);
void Graphics_Flush(Graphics *self);
void Graphics_Clear(Graphics *self);
void Graphics_Set_Draw_Color(Graphics *self);
void Graphics_Set_Erase_Color(Graphics *self);

#endif

