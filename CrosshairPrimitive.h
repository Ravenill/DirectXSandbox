#pragma once
#include "CPR_Framework.h"
#include "Player.h"

class CrosshairPrimitive
{
public:
    CrosshairPrimitive(Player& player_);
    ~CrosshairPrimitive();

public:
    void init();
    void update();
    void render();

private:
    Mesh* mesh;

    D3DXVECTOR3 position;
    D3DXVECTOR3 rotation;
    D3DXVECTOR3& playerPosition;
    D3DXVECTOR3& playerLookDirection;

    D3DXMATRIX& rotationLookDirMatrix;
};

