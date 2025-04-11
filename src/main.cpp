#include <raylib.h>
#include "../include/grid.h"

int main() 
{
    constexpr Color darkBlue = {0, 0, 139, 255};
    constexpr int screenWidth = 300;
    constexpr int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);

    Grid grid = Grid();
    grid.Print();
    
    while (!WindowShouldClose())
    {      
        BeginDrawing();
        ClearBackground(darkBlue);
        EndDrawing();
    }
    
    CloseWindow();
}