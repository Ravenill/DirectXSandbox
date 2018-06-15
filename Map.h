#pragma once
#include <vector>

class Map
{
public:
    Map();
    ~Map();

private:
    class Proxy;

public:
    void loadMapFromFile(std::string filename);
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
    std::vector<std::vector<unsigned int>> mapOfSkyscrappers;
};
