#pragma once
#include "CPR_Framework.h"

class Skycrapper
{
public:
    Skycrapper();
    Skycrapper(int height);
    Skycrapper(const D3DXVECTOR3 position_, const D3DXVECTOR3 rotation_, const D3DXVECTOR3 scale_, const D3DXVECTOR4 color_, const int height_);
    ~Skycrapper();

    int getHeight() const;
    void changeColor(const D3DXVECTOR4 color_);

    void setAttributes(const D3DXVECTOR3 position_, const D3DXVECTOR3 rotation_, const D3DXVECTOR3 scale_, const D3DXVECTOR4 color_);
    void renderSkycrapper(Mesh* skyscrapperMesh);

private:
    D3DXVECTOR3 position;
    D3DXVECTOR3 rotation;
    D3DXVECTOR3 scale;
    D3DXVECTOR4 color;

    const int height;
};
