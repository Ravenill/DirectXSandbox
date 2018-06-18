#include "BirdFlock.h"

BirdFlock::BirdFlock(const int amountOfBirds, Map & map_)
: map(map_)
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
    D3DXVECTOR3 position = startingPosition;
    const D3DXVECTOR3 rotation(0.0f, 0.0f, 0.0f);
    const D3DXVECTOR3 scale(1.0f, 1.0f, 1.0f);
    const D3DXVECTOR4 color(0.93f, 0.93f, 0.0f, 1.0f);
    
    for (auto& bird : birds)
    {
        int numberOfBird = (&bird - &*(birds.begin())) - 1;
        bird.initialize(position, rotation, scale, color, 0.010f, 0.005f);
    }
}

void BirdFlock::updateFlock()
{
    for (auto& bird : birds)
    {
        bird.update();
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
    float x = static_cast<float>((rand() % 100) - 50);
    float z = static_cast<float>((rand() % 100) - 50);

    const D3DXVECTOR3 newTarget(x, 10.0f, z);
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
