#pragma once
#include "../include/grid.h"
#include "../src/blocks.cpp"

class Game{
private:
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;

public:
    Game();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    void Draw();
    Grid grid;
};
