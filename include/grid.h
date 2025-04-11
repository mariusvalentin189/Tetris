#pragma once

class Grid
{
private:
    int numRows;
    int numColumns;
    int cellSize;
public:
    Grid();
    void Initialize();
    void Print();
    int grid[20][10];
};