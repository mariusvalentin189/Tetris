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
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);


public:
    Grid();
    void Initialize();
    void Print();
    bool ICellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    int ClearFullRows();
    int grid[20][10];
    void UpdateColors();

    void Draw();
};