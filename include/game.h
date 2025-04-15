#pragma once
#include "../include/grid.h"
#include "../src/blocks.cpp"

class Game{
private:
    bool IsBlockOutside();
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    void RotateBlock();
    void LockBlock();

public:
    Game();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    void Draw();
    void HandleInput();
    void MoveBlockLeft();
    void MoveBlockRight();
    void MoveBlockDown();
    bool BlockFits();
    Grid grid;
};
