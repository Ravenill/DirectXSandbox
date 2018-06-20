#pragma once
#include "CPR_Framework.h"
#include "Drawable.h"

class Crosshair : public Drawable
{
public:
    Crosshair(HWND& window_);
    ~Crosshair();

public:
    void init();
    void render();

private:
    void Crosshair::drawRectangle(int x, int y, int w, int h);

private:
    HWND& window;
    IDirect3DDevice9Ex* device;
};

