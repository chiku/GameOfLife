#ifndef FLTK_GRAPHICS_H
#define FLTK_GRAPHICS_H

#include <FL/Fl_Double_Window.H>

const int SCREEN = 700;
const int SQUARE = 5;

typedef struct Graphics Graphics;

struct Graphics
{
	Fl_Double_Window *window;
	Fl_Color orange;
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

