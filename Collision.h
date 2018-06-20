#pragma once
#include "CPR_Framework.h"
#include <vector>
#include "Skycrapper.h"
#include "Map.h"

class Collision
{
public:
    Collision();
    ~Collision();

public:
    static bool detectBuildings(Map& map, const D3DXVECTOR3& position, const float detectingRange, std::vector<Skycrapper>& detectedSkycrappers);
};

