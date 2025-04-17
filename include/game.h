#pragma once
#include "../include/grid.h"
#include "../src/blocks.cpp"

class Game{
private:
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    Grid grid;
    Font font;

    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    void MoveBlockLeft();
    void MoveBlockRight();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    void Reset();
    void UpdateScore(int linesCleared, int moveDownPoints);


public:
    bool gameOver;
    int score;

    Game();
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    bool BlockFits();
};
