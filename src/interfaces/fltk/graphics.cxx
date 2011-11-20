#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

extern "C" {
	#include "graphics.h"
}

Graphics* Graphics_Initialize()
{
	Graphics *self = (Graphics*)(malloc( sizeof(Graphics) ));
	self->window = new Fl_Double_Window(SCREEN, SCREEN, "Conway's Game of Life");
	self->orange = fl_rgb_color(200, 100, 50);

	self->window->end();
	self->window->show();
	Fl::wait();

	return self;
}

void Graphics_Destroy(Graphics *self)
{
	self->window->clear();
	free(self);
}

void Graphics_Draw_At(Graphics *self, long int x, long int y)
{
	Fl_Box *box = new Fl_Box(
		SCREEN/2 + x * SQUARE,
		SCREEN/2 + y * SQUARE,
		SQUARE - 1, SQUARE - 1,
		""
	);
	box->box(FL_FLAT_BOX);
	box->color(self->orange);
	self->window->add(box);
}

void Graphics_Flush(Graphics *self)
{
	self->window->redraw();
	Fl::flush();
}

void Graphics_Clear(Graphics *self)
{
	self->window->clear();
}

void Graphics_Redraw(Graphics *self)
{
}

