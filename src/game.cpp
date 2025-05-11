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
    gameSpeed=0.4;
    defaultGameSpeed=0.4;
    level=1;
    linesToClearLevel=0;
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
        DrawTextEx(font, "GAME OVER", {320, 500}, 38, 2, WHITE);
    } 
    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

    char scoreText[10];
    sprintf(scoreText, "%d", score);
    Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

    DrawTextEx(font, scoreText, {320 + (170 - textSize.x)/2, 65}, 38, 2, WHITE);
    DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

    DrawRectangleRounded({320, 440, 170, 40}, 0.3, 6, lightBlue);
    DrawTextEx(font, "Level", {363, 400}, 38, 2, WHITE);
    char levelText[3];
    sprintf(levelText, "%d", level);
    Vector2 levelTextSize = MeasureTextEx(font, levelText, 38, 2);
    DrawTextEx(font, levelText, {320 + (170 - levelTextSize.x)/2, 440}, 38, 2, WHITE);
    
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
    
        case KEY_UP:
        case KEY_W:
            RotateBlock();
            break;
    }

    if(IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)){
        gameSpeed=defaultGameSpeed/4;
    }
    else{
        gameSpeed=defaultGameSpeed;
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
    gameSpeed=0.4;
    defaultGameSpeed=0.4;
    level=1;
    linesToClearLevel=0;

}

void Game::UpdateScore(int linesCleared, int moveDownPoints){
    switch (linesCleared)
    {
    case 1:
        linesToClearLevel+=1;
        score+=linesToClearLevel*level*100;
        break;

    case 2:
        linesToClearLevel+=3;
        score+=linesToClearLevel*level*100;
        break;

    case 3:
        linesToClearLevel+=5;
        score+=linesToClearLevel*level*100;
        break;

    case 4:
        linesToClearLevel+=8;
        score+=linesToClearLevel*level*100;
        break;

    default:
        break;
    }

    score+=moveDownPoints;

    if(linesToClearLevel >= 10){
        linesToClearLevel -= 10;
        level+=1;
        ChangeColors(1);
        grid.UpdateColors();
        currentBlock.UpdateColors();
        nextBlock.UpdateColors();
        defaultGameSpeed=defaultGameSpeed/1.1;
    }
}