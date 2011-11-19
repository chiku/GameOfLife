#include <FL/Fl_Double_Window.H>

const int SCREEN = 700;
const int SQUARE = 5;

class Graphics
{
public:
	Fl_Double_Window *window;
	Fl_Color orange;


public:
	Graphics();
	~Graphics();

	void Draw_Square(long int x, long int y);
	void Flush();
	void Clear();
	void Redraw();
	void Wait();
};

