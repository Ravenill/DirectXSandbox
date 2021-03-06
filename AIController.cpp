#include "AIController.h"
#include "Defines.h"

AIController::AIController(Map& map_, std::vector<RedBall>& redBallList_)
: birdMesh(0)
, map(map_)
, redBallList(redBallList_)
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
    D3DXVECTOR3 pos(SIZE_OF_GROUND_X / 2, static_cast<float>((rand() % 4) + MIN_FLIGHT_HEIGHT), SIZE_OF_GROUND_Z / 2);

    birdFlocks.reserve(amountOfFlocks);

    for (int i = 0; i < amountOfFlocks; i++)
    {
        int modifier = (rand() % 2) ? -1 : 1;
        pos.x *= modifier;
        pos.y = static_cast<float>((rand() % 4) + MIN_FLIGHT_HEIGHT);
        pos.z *= modifier;
        BirdFlock birdFlock(amoutOfBirdsInFlock, pos.y, map, redBallList);
        birdFlock.initializeFlock(pos);
        birdFlocks.push_back(birdFlock);
    }
}

void AIController::update(float deltaTime)
{
    for (auto& flock : birdFlocks)
    {
        flock.updateFlock(deltaTime);
    }
}

void AIController::renderFlocks()
{
    for (auto& flock : birdFlocks)
    {
        flock.renderFlock(birdMesh);
    }
}

std::vector<BirdFlock>& AIController::getBirdFlocks()
{
    return birdFlocks;
}
