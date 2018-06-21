#pragma once
#include "CPR_Framework.h"
#include "Crosshair.h"
#include "CrosshairPrimitive.h"
#include "Player.h"

class GUI
{
public:
    GUI(HWND& window_, Player& player_);
    ~GUI();

public:
    void init();
    void update();
    void render();

private:
    HWND& window;
    //Crosshair crosshair;
    CrosshairPrimitive crosshair;
};

