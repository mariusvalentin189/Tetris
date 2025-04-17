#include "../include/game.h"
#include<random>
#include <iostream>

Game::Game(){
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver=false;
    score=0;
    font = LoadFontEx("Font/monogram.ttf",64,0,0);
}

Block Game::GetRandomBlock(){
    if(blocks.empty()){
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

std::vector<Block> Game::GetAllBlocks(){
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw(){

    DrawTextEx(font, "Score", {363, 15}, 38, 2, WHITE);
    DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);

    if(gameOver){
        DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
    } 
    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

    char scoreText[10];
    sprintf(scoreText, "%d", score);
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

    DrawTextEx(font, scoreText, {320 + (170 - textSize.x)/2, 65}, 38, 2, WHITE);
    DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
    
    grid.Draw();
    currentBlock.Draw(11,11);
    switch (nextBlock.id)
    {
    case 3:
        nextBlock.Draw(255, 290);
        break;

    case 4:
        nextBlock.Draw(255, 280);
        break;

    default:
        nextBlock.Draw(270, 270);
        break;
    }
    
}

void Game::HandleInput(){
    int keyPressed = GetKeyPressed();
    if(gameOver && keyPressed){
        gameOver=false;
        Reset();
    }
    switch (keyPressed)
    {
        case KEY_LEFT:
        case KEY_A:
            MoveBlockLeft();
            break;
        
        case KEY_RIGHT:
        case KEY_D:
            MoveBlockRight();
            break;
            
        case KEY_DOWN:
        case KEY_S:
            MoveBlockDown();
            break;
    
        case KEY_UP:
        case KEY_W:
            RotateBlock();
            break;
    }
}

void Game::MoveBlockLeft(){
    if(!gameOver){
        currentBlock.Move(0,-1);
        if(IsBlockOutside() || !BlockFits())
        {
            currentBlock.Move(0,1);
        }
    }
}

void Game::MoveBlockRight(){
    if(!gameOver){
        currentBlock.Move(0,1);
        if(IsBlockOutside() || !BlockFits())
        {
            currentBlock.Move(0,-1);
        }
    }
}

void Game::MoveBlockDown(){
    if(!gameOver){
        currentBlock.Move(1,0);
        if(IsBlockOutside() || !BlockFits())
        {
            currentBlock.Move(-1,0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside(){
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item:tiles){
        if(grid.ICellOutside(item.row, item.column)){
            return true;
        }
    }
    return false;
}

void Game::RotateBlock(){
    if(!gameOver){
        currentBlock.Rotate();
        if(IsBlockOutside() || !BlockFits())
        {
            currentBlock.UndoRotation();
        }
    }
}
void Game::LockBlock(){
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item: tiles){
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if(!BlockFits()){
        gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    UpdateScore(rowsCleared, 0);
}

bool Game::BlockFits(){
    std::vector<Position> tiles = currentBlock.GetCellPositions();
    for(Position item: tiles){
        if(!grid.IsCellEmpty(item.row, item.column)){
            return false;
        }
    }
    return true;
}

void Game::Reset(){
    grid.Initialize();
    blocks=GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score=0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints){
    switch (linesCleared)
    {
    case 1:
        score+=100;
        break;

    case 2:
        score+=300;
        break;

    case 3:
        score+=500;
        break;

    default:
        break;
    }

    score+=moveDownPoints;
}