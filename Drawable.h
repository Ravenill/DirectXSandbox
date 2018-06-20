#pragma once
#include "CPR_Framework.h"

class Drawable
{
public:
    Drawable();
    Drawable(D3DXVECTOR3 position_, D3DXVECTOR3 rotation, D3DXVECTOR3 scale, D3DXVECTOR4 color);
    ~Drawable();

public:
    virtual void render(Mesh* mesh);

protected:
    D3DXVECTOR3 position;
    D3DXVECTOR3 rotation;
    D3DXVECTOR3 scale;
    D3DXVECTOR4 color;
};

