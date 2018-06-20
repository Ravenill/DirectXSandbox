#pragma once
#include "AIController.h"
#include "Map.h"
#include "PlayerController.h"
#include "GUI.h"

class Game
{
public:
    Game();
    ~Game();

public:
    Map& getMap();
    PlayerController& getPlayerController();
    AIController& getAI();

    void init();
    void update(float deltaTime);
    void render();

private:
    HWND window;

    Map map;
    PlayerController playerController;
    AIController AI;
    GUI gui;
};

