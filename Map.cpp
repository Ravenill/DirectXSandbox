#include "Map.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include <string>

Map::Map()
{

}

Map::~Map()
{
    Release(terrainMesh);
}

void Map::loadMapFromFile(std::string filename)
{
    std::fstream file;
    file.open(filename.c_str(), std::ios::in);

    assert(file.is_open());

    while (!file.eof())
    {
        std::vector<unsigned int> loader;
        getLine(file, loader);

        if (!loader.empty())
            mapOfSkyscrappers.push_back(loader);
    }
}

void Map::getLine(std::fstream& file, std::vector<unsigned int>& dataStruct)
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
                dataStruct.push_back(number);
                strNumber.clear();
            }
        }
        else
        {
            strNumber += singleChar;
        }
    }
}

void Map::loadMapMeshFromFile(char filename[])
{
    terrainMesh = LoadFromFile(filename);
}

void Map::renderTerrain()
{
     D3DXVECTOR3 pos( 0.0f, -1.0f, 0.0f );
     D3DXVECTOR3 rot( 0.0f, 0.0f, 0.0f );
     D3DXVECTOR3 sca( 100.0f, 0.1f, 100.0f );
     D3DXVECTOR4 color( 1.0f, 0.5f, 0.0f, 1.0f );
     Render(terrainMesh, pos, rot, sca, color );
}


