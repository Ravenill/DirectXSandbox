#include "Collision.h"
#include "Defines.h"

Collision::Collision()
{
}


Collision::~Collision()
{
}

bool Collision::detectBuildings(Map& map, const D3DXVECTOR3& position, const float detectingRange, std::vector<Skycrapper>& detectedSkycrappers)
{
    const int ROWS = map.getNumberOfRows();
    const int COLUMNS = map.getNumberOfColumns();

    for (int row = 0; row < ROWS; row++)
    {
        const D3DXVECTOR3& POSITION_OF_BUILDING = map[row][0].getPosition();

        if ((POSITION_OF_BUILDING.x >= (position.x - detectingRange)) && (POSITION_OF_BUILDING.x <= (position.x + detectingRange)))
        {
            for (int column = 0; column < COLUMNS; column++)
            {
                const D3DXVECTOR3& POSITION_OF_NEXT_BUILDING = map[row][column].getPosition();

                if ((POSITION_OF_NEXT_BUILDING.z >= (position.z - detectingRange)) && (POSITION_OF_NEXT_BUILDING.z <= (position.z + detectingRange)))
                {
                    const float HEIGHT_OF_BUILDING = (BUILDING_SCALE.y * map[row][column].getHeight()) + TERRAIN_POSITION.y;

                    if (position.y <= HEIGHT_OF_BUILDING)
                    {
                        detectedSkycrappers.push_back(map[row][column]);
                    }
                }
            }
        }
    }

    if (detectedSkycrappers.empty())
        return false;

    return true;
}
