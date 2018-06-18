#pragma once
#include "Bird.h"
#include <vector>
#include "Map.h"

class BirdFlock
{
public:
    BirdFlock(const int amountOfBirds, Map& map_);
    ~BirdFlock();

public:
    void initializeFlock(const D3DXVECTOR3 startingPosition);
    void updateFlock();
    void changeFlockTarget();

    void renderFlock(Mesh* mesh);

private:
    std::vector<Bird> birds;
    D3DXVECTOR3 flockTarget;
    Map& map;
};

