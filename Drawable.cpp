#include "Drawable.h"



Drawable::Drawable()
: position(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, rotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, color(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f))
{

}

Drawable::Drawable(D3DXVECTOR3 position_, D3DXVECTOR3 rotation_, D3DXVECTOR3 scale_, D3DXVECTOR4 color_)
: position(position_)
, rotation(rotation_)
, scale(scale_)
, color(color_)
{

}


Drawable::~Drawable()
{

}

void Drawable::render(Mesh * mesh)
{

}
