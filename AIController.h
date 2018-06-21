#pragma once
#include "BirdFlock.h"
#include "Map.h"
#include "RedBall.h"

class AIController
{
public:
    AIController(Map& map_, std::vector<RedBall>& redBallList_);
    ~AIController();

public:
    void loadBirdMeshFromFile(char filename[]);
    void createFlocks(const int amountOfFlocks, const int amoutOfBirdsInFlock);

    void update(float deltaTime);
    void renderFlocks();

    std::vector<BirdFlock>& getBirdFlocks();

private:
    std::vector<BirdFlock> birdFlocks;
    Mesh* birdMesh;
    Map& map;
    std::vector<RedBall>& redBallList;
};

