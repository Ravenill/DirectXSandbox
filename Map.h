#pragma once
#include <vector>
#include "CPR_Framework.h"
#include "Skycrapper.h"

class Map
{
public:
    Map();
    ~Map();

private:
    class Proxy;

public:
    void loadMapFromFile(const std::string filename);
    void loadMapMeshFromFile(char filenameForTerrain[], char filenameForSkycrapper[]);
    void initializeCity();

    void renderTerrain();
    void renderCity();

    Proxy operator[] (size_t row) { return Proxy(mapOfSkyscrappers[row]); }

private:
    class Proxy
    {
    public:
        Proxy(std::vector<Skycrapper>& _row) : row(_row) {}
        Skycrapper operator[] (size_t column) { return row[column]; }
    private:
        std::vector<Skycrapper>& row;
    };

private:
    void readAndSaveRow(std::fstream& file, std::vector<Skycrapper>& dataStruct);

private:
    std::vector<std::vector<Skycrapper>> mapOfSkyscrappers;
    Mesh* terrainMesh;
    Mesh* skyscrapperMesh;
};
