#pragma once
#include "CPR_Framework.h"
#include "Camera.h"

class Player
{
public:
    Player(Camera& camera_);
    ~Player();

private:
    Camera& camera;

    D3DXVECTOR3& position;
    D3DXVECTOR3& direction;
    D3DXVECTOR3& directionLook;

};

