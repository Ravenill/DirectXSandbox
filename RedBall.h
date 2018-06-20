#pragma once
#include "CPR_Framework.h"
#include "Map.h"
#include "Drawable.h"

class RedBall : public Drawable
{
public:
    RedBall(Map& map_, D3DXVECTOR3 position_, D3DXVECTOR3 direction_, D3DXVECTOR3 rotation_, D3DXVECTOR3 scale_, D3DXVECTOR4 color_);
    ~RedBall();

public:
    void update(float deltaTime);

    void render(Mesh* mesh);

private:
    void decreasingVelocity();
    bool isColideWithBuilding();

private:
    D3DXVECTOR3 direction;
    float velocity;

    Map& map;
};

