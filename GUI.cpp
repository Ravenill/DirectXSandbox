#include "GUI.h"

GUI::GUI(HWND & window_)
: window(window_)
, crosshair(window_)
{

}

GUI::~GUI()
{

}

void GUI::init()
{
    crosshair.init();
}

void GUI::render()
{
    crosshair.render();
}
