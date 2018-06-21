#include "Skycrapper.h"

Skycrapper::Skycrapper()
: Drawable()
, height(0)
{

}

Skycrapper::Skycrapper(const D3DXVECTOR3 position_, const D3DXVECTOR3 rotation_, const D3DXVECTOR3 scale_, const D3DXVECTOR4 color_, const int height_)
: Drawable(position_, rotation_, scale_, color_)
, height(height_)
{

}

Skycrapper & Skycrapper::operator=(const Skycrapper & a)
{
    position = a.position;
    rotation = a.rotation;
    scale = a.scale;
    color = a.color;

    height = a.height;

    return *this;
}

Skycrapper::Skycrapper(const int height_)
: Drawable()
, height(height_)
{

}

Skycrapper::~Skycrapper()
{

}

const int Skycrapper::getHeight() const
{
    return height;
}

const D3DXVECTOR3 Skycrapper::getPosition() const
{
    return position;
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
