#include "Game.h"
#include "Defines.h"
#include <ctime>

Game::Game()
: map()
, playerController()
, AI(map)
{
    std::srand(static_cast<unsigned int>(time(NULL)));
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
    map.loadMapFromFile("resources/city.txt");
    map.loadMapMeshFromFile("resources/meshes/unitbox.x", "resources/meshes/unitbox.x");
    map.initializeCity();

    AI.loadBirdMeshFromFile("resources/meshes/unitsphere.x");
    AI.createFlocks(AMOUNT_OF_FLOCKS, AMOUNT_OF_BIRDS_IN_FLOCK);
}

void Game::update(float deltaTime)
{
    playerController.update(deltaTime);
    AI.update(deltaTime);
}

void Game::render()
{
    map.renderTerrain();
    map.renderCity();
    AI.renderFlocks();
}
