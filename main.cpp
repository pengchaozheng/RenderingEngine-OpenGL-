#include "window.h"
Window* g_window;
int main()
{
	Window* window = new Window(800, 600, "Outline Drawing");
	g_window = window;
	window->Initialize();
	window->Run();
	window->Shutdown();
	delete window;
}