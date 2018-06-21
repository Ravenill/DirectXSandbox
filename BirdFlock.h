#pragma once
#include "Bird.h"
#include <vector>
#include "Map.h"
#include "RedBall.h"

class BirdFlock
{
public:
    BirdFlock(const int amountOfBirds, const float heightOfFlight, Map& map_, std::vector<RedBall>& redBallList_);
    ~BirdFlock();

public:
    void initializeFlock(const D3DXVECTOR3 startingPosition);
    void updateFlock(float deltaTime);
    void changeFlockTarget();

    void renderFlock(Mesh* mesh);

private:
    void checkCollisionWithRedBalls();
    void addNewBird();

private:
    std::vector<Bird> birds;
    D3DXVECTOR3 flockTarget;
    Map& map;
    std::vector<RedBall>& redBallList;

    float heightOfFlight;
};

