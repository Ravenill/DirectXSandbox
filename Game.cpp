#include "Game.h"
#include "Defines.h"
#include <ctime>

Game::Game()
: window(GetActiveWindow())
, map()
, playerController(map)
, AI(map, playerController.getPlayer().getRedBallList())
, gui(window, playerController.getPlayer())
{
    std::srand(static_cast<unsigned int>(time(NULL)));
    SetWindowPos(window, HWND_TOP, 0, 0, SIZE_SCREEN_X, SIZE_SCREEN_Y, SWP_NOMOVE | SWP_NOREPOSITION | SWP_NOZORDER | SWP_SHOWWINDOW);
}

Game::~Game()
{

}

Map& Game::getMap()
{
    return map;
}

PlayerController& Game::getPlayerController()
{
    return playerController;
}

AIController& Game::getAI()
{
    return AI;
}

void Game::init()
{
    window = GetActiveWindow();

    map.loadMapFromFile("resources/city.txt");
    map.loadMapMeshFromFile("resources/meshes/unitbox.x", "resources/meshes/unitbox.x");
    map.initializeCity();

    AI.loadBirdMeshFromFile("resources/meshes/unitsphere.x");
    AI.createFlocks(AMOUNT_OF_FLOCKS, AMOUNT_OF_BIRDS_IN_FLOCK);

    playerController.init();
    gui.init();
}

void Game::update(float deltaTime)
{
    playerController.update(deltaTime);
    AI.update(deltaTime);
    gui.update();
}

void Game::render()
{
    map.renderTerrain();
    map.renderCity();
    AI.renderFlocks();
    playerController.render();
    gui.render();
}
