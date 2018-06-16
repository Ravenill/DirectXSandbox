#pragma once
#include <vector>
#include "CPR_Framework.h"

class Map
{
public:
    Map();
    ~Map();

private:
    class Proxy;

public:
    void loadMapFromFile(std::string filename);
    void loadMapMeshFromFile(char filename[]);
    void renderTerrain();

    Proxy operator[] (size_t row) { return Proxy(mapOfSkyscrappers[row]); }

private:
    class Proxy
    {
    public:
        Proxy(std::vector<unsigned int>& _row) : row(_row) {}
        int operator[] (size_t column) { return row[column]; }
    private:
        std::vector<unsigned int>& row;
    };

private:
    void getLine(std::fstream& file, std::vector<unsigned int>& dataStruct);

private:
    std::vector<std::vector<unsigned int>> mapOfSkyscrappers;
    Mesh* terrainMesh;
};
