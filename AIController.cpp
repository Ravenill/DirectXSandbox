#include "AIController.h"

AIController::AIController(Map& map_)
: birdMesh(0)
, map(map_)
{

}


AIController::~AIController()
{
    Release(birdMesh);
}

void AIController::loadBirdMeshFromFile(char filename[])
{
    birdMesh = LoadFromFile(filename);
}

void AIController::createFlocks(const int amountOfFlocks, const int amoutOfBirdsInFlock)
{
    D3DXVECTOR3 pos(0.0f, 10.0f, 0.0f);

    for (int i = 0; i < amountOfFlocks; i++)
    {
        BirdFlock birdFlock(amoutOfBirdsInFlock, map);
        birdFlock.initializeFlock(pos);
        birdFlocks.push_back(birdFlock);
    }
}

void AIController::update()
{
    for (auto& flock : birdFlocks)
    {
        flock.updateFlock();
    }
}

void AIController::renderFlocks()
{
    for (auto& flock : birdFlocks)
    {
        flock.renderFlock(birdMesh);
    }
}
