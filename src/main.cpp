#include <raylib.h>

int main() 
{
    
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {      
        BeginDrawing();
        ClearBackground({0,0,0,255});
        EndDrawing();
    }
    
    CloseWindow();
}