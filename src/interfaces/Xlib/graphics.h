#include <X11/Xlib.h>

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

void Graphics_Draw_Square(Graphics *self, long int x, long int y);
void Graphics_Flush(Graphics *self);
void Graphics_Set_Foreground(Graphics *self);
void Graphics_Set_Reverse_Foreground(Graphics *self);

