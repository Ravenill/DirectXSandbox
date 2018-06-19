#pragma once
#include "CPR_Framework.h"
#include "Camera.h"
#include "RedBall.h"
#include <vector>

class Player
{
public:
    Player(Camera& camera_);
    ~Player();

public:
    void update(float deltaTick);
    void shoot();

private:
    void updateRedBalls();

private:
    Camera& camera;

    D3DXVECTOR3& position;
    D3DXVECTOR3& direction;
    D3DXVECTOR3& directionLook;

    std::vector<RedBall> redBallList;
};

