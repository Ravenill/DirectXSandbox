#include "BirdFlock.h"
#include "Defines.h"

BirdFlock::BirdFlock(const int amountOfBirds, const float height, Map& map_)
: map(map_)
, heightOfFlight(height)
{
    for (int i = 0; i < amountOfBirds; i++)
    {
        Bird newBird(map);
        birds.push_back(newBird);
    }
}

BirdFlock::~BirdFlock()
{

}

void BirdFlock::initializeFlock(const D3DXVECTOR3 startingPosition)
{  
    const float SPACE = 2.0f;

    int modifier = -1;
    for (auto& bird : birds)
    {
        D3DXVECTOR3 position = startingPosition;
        int numberOfBird = (&bird - &*(birds.begin())) + 1;
        int diff = numberOfBird / 2;

        position.x += (diff * SPACE * modifier);
        position.z += (diff * SPACE);
        bird.initialize(position, BIRD_ROTATION, BIRD_SCALE, BIRD_COLOR, MAX_BIRD_SPEED, INITIAL_BIRD_SPEED);
        modifier = -modifier;
    }
    changeFlockTarget();
}

void BirdFlock::updateFlock(float deltaTime)
{
    for (auto& bird : birds)
    {
        bird.update(deltaTime);
    }

    for (auto& bird : birds)
    {
        if (bird.isReachedTarget())
        {
            changeFlockTarget();
        }
    }
}

void BirdFlock::changeFlockTarget()
{
    float x = static_cast<float>((rand() % (static_cast<int>(SIZE_OF_GROUND_X) + 20)) - (SIZE_OF_GROUND_X / 2));
    float z = static_cast<float>((rand() % (static_cast<int>(SIZE_OF_GROUND_Z) + 20)) - (SIZE_OF_GROUND_Z / 2));

    const D3DXVECTOR3 newTarget(x, heightOfFlight, z);
    flockTarget = newTarget;

    for (auto& bird : birds)
    {
        bird.setTarget(newTarget);
    }
}

void BirdFlock::renderFlock(Mesh* mesh)
{
    for (auto& bird : birds)
    {
        bird.render(mesh);
    }
}
