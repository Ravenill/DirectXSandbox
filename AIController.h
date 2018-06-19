#pragma once
#include "BirdFlock.h"
#include "Map.h"

class AIController
{
public:
    AIController(Map& map_);
    ~AIController();

public:
    void loadBirdMeshFromFile(char filename[]);
    void createFlocks(const int amountOfFlocks, const int amoutOfBirdsInFlock);

    void update(float deltaTime);
    void renderFlocks();

private:
    std::vector<BirdFlock> birdFlocks;
    Mesh* birdMesh;
    Map& map;
};

