#include "GUI.h"

GUI::GUI(HWND & window_, Player& player_)
: window(window_)
//, crosshair(window_)
, crosshair(player_)
{

}

GUI::~GUI()
{

}

void GUI::init()
{
    crosshair.init();
}

void GUI::update()
{
    crosshair.update();
}

void GUI::render()
{
    //crosshair.render();
    crosshair.render();
}
