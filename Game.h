#pragma once
#include "Camera.h"
#include "AIController.h"
#include "Map.h"


class Game
{
public:
    Game();
    ~Game();

public:
    Map& getMap();
    Camera& getCamera();
    AIController& getAI();

    void init();
    void update();
    void render();

private:
    Map map;
    Camera camera;
    AIController AI;
};

