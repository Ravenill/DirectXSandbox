#include "Skycrapper.h"



Skycrapper::Skycrapper()
: position(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, rotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, color(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f))
, height(0)
{

}

Skycrapper::Skycrapper(const D3DXVECTOR3 position_, const D3DXVECTOR3 rotation_, const D3DXVECTOR3 scale_, const D3DXVECTOR4 color_, const int height_)
: position(position_)
, rotation(rotation_)
, scale(scale_)
, color(color_)
, height(height_)
{

}

Skycrapper::Skycrapper(const int height_)
: position(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, rotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
, color(D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f))
, height(height_)
{

}


Skycrapper::~Skycrapper()
{

}

int Skycrapper::getHeight() const
{
    return height;
}

void Skycrapper::changeColor(const D3DXVECTOR4 color_)
{
    color = color_;
}

void Skycrapper::setAttributes(const D3DXVECTOR3 position_, const D3DXVECTOR3 rotation_, const D3DXVECTOR3 scale_, const D3DXVECTOR4 color_)
{
    position = position_;
    rotation = rotation_;
    scale = scale_;
    color = color_;
}

void Skycrapper::renderSkycrapper(Mesh* skyscrapperMesh)
{
    for (int i = 0; i < height; i++)
    {
        D3DXVECTOR3 correctedPosition = position;
        correctedPosition.y += (i * scale.y);
        Render(skyscrapperMesh, correctedPosition, rotation, scale, color);
    }
}
