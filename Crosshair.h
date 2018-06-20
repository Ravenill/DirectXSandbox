#pragma once
#include "CPR_Framework.h"
#include "Drawable.h"

/* wellp - that's very sad, because i don't see hInstance and cannot use typical WINAPI function for rendering crosshair*/

class Crosshair : public Drawable
{
public:
    Crosshair();
    ~Crosshair();

private:
};

