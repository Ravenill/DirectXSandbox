#pragma once
#include "CPR_Framework.h"
#include "Drawable.h"

class Skycrapper : public Drawable
{
public:
    Skycrapper();
    Skycrapper(int height);
    Skycrapper(const D3DXVECTOR3 position_, const D3DXVECTOR3 rotation_, const D3DXVECTOR3 scale_, const D3DXVECTOR4 color_, const int height_);
    Skycrapper& Skycrapper::operator =(const Skycrapper& a);
    ~Skycrapper();

public:
    const int getHeight() const;
    const D3DXVECTOR3 getPosition() const;
    void changeColor(const D3DXVECTOR4 color_);

    void setAttributes(const D3DXVECTOR3 position_, const D3DXVECTOR3 rotation_, const D3DXVECTOR3 scale_, const D3DXVECTOR4 color_);

    void renderSkycrapper(Mesh* skyscrapperMesh);

private:
    int height;
};

