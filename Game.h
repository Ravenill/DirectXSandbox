#pragma once
#include "Camera.h"
#include "AIController.h"
#include "Map.h"
#include "Player.h"

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
    void update(float deltaTime);
    void render();

private:
    Map map;
    Camera camera;
    AIController AI;
    Player player;
};

