#pragma once
#include "Player.h"
#include "Map.h"

class PlayerController
{
public:
    PlayerController(Map& map_);
    ~PlayerController();

public:
    void init();
    void update(float deltaTick);
    void render();

private:
    void handleSteering(float deltaTick);

private:
    Camera camera;
    Player player;
};

