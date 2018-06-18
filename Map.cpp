#include "Map.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <string>
#include "Defines.h"

Map::Map()
{

}

Map::~Map()
{
    Release(terrainMesh);
    Release(skyscrapperMesh);
}

void Map::loadMapFromFile(const std::string filename)
{
    std::fstream file;
    file.open(filename.c_str(), std::ios::in);

    assert(file.is_open());

    while (!file.eof())
    {
        std::vector<Skycrapper> loader;
        readAndSaveRow(file, loader);

        if (!loader.empty())
            mapOfSkyscrappers.push_back(loader);
    }

    file.close();
}

void Map::readAndSaveRow(std::fstream& file, std::vector<Skycrapper>& dataStruct)
{
    char singleChar = 0;
    std::string strNumber = "";
    unsigned int number = 0;
    
    while (singleChar != '\n' && !file.eof())
    {
        file.get(singleChar);

        if (singleChar == '/')
        {
            std::string trash;
            std::getline(file, trash);
            continue;
        }

        if (singleChar == ',' || singleChar == ' ' || singleChar == ';' || singleChar == '\n' || singleChar == '-' || file.eof())
        {
            if (!strNumber.empty())
            {
                number = atoi(strNumber.c_str());
                Skycrapper skycrapper(number);
                dataStruct.push_back(skycrapper);
                strNumber.clear();
            }
        }
        else
        {
            strNumber += singleChar;
        }
    }
}

void Map::loadMapMeshFromFile(char filenameForTerrain[], char filenameForSkycrapper[])
{
    terrainMesh = LoadFromFile(filenameForTerrain);
    skyscrapperMesh = LoadFromFile(filenameForSkycrapper);
}

void Map::initializeCity()
{
    const int ROWS = mapOfSkyscrappers.size();
    const int COLUMNS = mapOfSkyscrappers[0].size();

    const float SPACES_ROWS = SIZE_OF_GROUND_X / (ROWS);
    const float SPACES_COLUMNS = SIZE_OF_GROUND_Y / (COLUMNS);

    for (int row = 0; row < ROWS; row++)
    {
        for (int column = 0; column < COLUMNS; column++)
        {
            const D3DXVECTOR3 position(-50.0f + (SPACES_ROWS / 2) + (row * SPACES_ROWS), -0.5f, -50.0f + (SPACES_COLUMNS / 2) + (column * SPACES_COLUMNS));
            mapOfSkyscrappers[row][column].setAttributes(position, BUILDING_ROTATION, BUILDING_SCALE, BUILDING_COLOR);
        }
    }
}

void Map::renderTerrain()
{
     Render(terrainMesh, TERRAIN_POSITION, TERRAIN_ROTATION, TERRAIN_SCALE, TERRAIN_COLOR);
}

void Map::renderCity()
{
    for (auto& row : mapOfSkyscrappers)
    {
        for (auto& skycrapper : row)
        {
            skycrapper.renderSkycrapper(skyscrapperMesh);
        }
    }
}


