#include <X11/Xlib.h>

#ifndef XLIB_GRAPHICS_H
#define XLIB_GRAPHICS_H

#define SCREEN 800
#define SQUARE 5

typedef struct Graphics Graphics;

struct Graphics
{
	Display *display;
	int screen;
	Window window;
	GC graphical_context;
};

Graphics* Graphics_Initialize();
void Graphics_Destroy(Graphics *self);

void Graphics_Draw_At(Graphics *self, long int x, long int y);
void Graphics_Callback_Handler(Graphics *self, double time_in_s);
void Graphics_Flush(Graphics *self);
void Graphics_Clear(Graphics *self);
void Graphics_Set_Draw_Color(Graphics *self);
void Graphics_Set_Erase_Color(Graphics *self);

#endif

