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

}

void Map::loadMapFromFile(std::string filename)
{
    std::fstream file;
    file.open(filename.c_str(), std::ios::in);

    assert(file.is_open());

    while (!file.eof())
    {
        char singleChar = 0;
        std::string strNumber = "";
        unsigned int number = 0;

        std::vector<unsigned int> loader;

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
                    loader.push_back(number);
                    strNumber = "";
                }
            }
            else
            {
                strNumber += singleChar;
            }
        }
        if (!loader.empty())
            mapOfSkyscrappers.push_back(loader);
    }
}


