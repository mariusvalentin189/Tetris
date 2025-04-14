#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
private:
    int numRows;
    int numColumns;
    int cellSize;
    std::vector<Color> colors;


public:
    Grid();
    void Initialize();
    void Print();
    int grid[20][10];

    void Draw();
};