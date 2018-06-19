#pragma once
#include "Player.h"

class PlayerController
{
public:
    PlayerController();
    ~PlayerController();

public:
    void update(float deltaTick);

private:
    void handleSteering(float deltaTick);

private:
    Camera camera;
    Player player;
};

