#pragma once
#include "CPR_Framework.h"
#include "Crosshair.h"

class GUI
{
public:
    GUI(HWND& window_);
    ~GUI();

public:
    void init();
    void render();

private:
    HWND& window;
    Crosshair crosshair;
};

