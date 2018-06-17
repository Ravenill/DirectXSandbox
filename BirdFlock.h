#pragma once
#include "Bird.h"
#include <vector>

class BirdFlock
{
public:
    BirdFlock();
    ~BirdFlock();

public:
    void initializeFlock();

private:
    std::vector<Bird> birds;
};

