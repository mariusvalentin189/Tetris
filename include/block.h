#pragma once
#include <map>
#include "../include/position.h"
#include "../include/colors.h"

class Block
{
private:
    int cellSize;
    int rotationState;
    std::vector<Color> colors;
    int rowOffset;
    int columnOffset;

public:
    int id;
    std::map<int, std::vector<Position>> cells;
    Block();
    void Draw();
    void Move(int rows, int columns);
    void Rotate();
    void UndoRotation();
    std::vector<Position> GetCellPositions();
};