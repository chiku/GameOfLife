#include <FL/Fl_Double_Window.H>

#include "fltk/canvas.hh"
#include "fltk/window.hh"

GameOfLife::FLTK::Window::Window()
{
	window = new Fl_Double_Window(1280, 800);
	canvas = new GameOfLife::FLTK::Canvas(WIDTH, HEIGHT);
	setPropertiesOnWindow();
}

GameOfLife::FLTK::Window::~Window()
{
	delete window;
}

void GameOfLife::FLTK::Window::setPropertiesOnWindow()
{
	window->fullscreen();
	window->label("Conway's Game of life");
	window->add(canvas);
	window->end();
	window->show();
}

void GameOfLife::FLTK::Window::attachGameToCanvas(GameOfLife::Game *game)
{
	canvas->attachGame(game);
}
