#include <raylib.h>
#include "../include/game.h"

double lastUpdateTime = 0;

bool EventTrigered(double interval){
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}
int main() 
{
    constexpr Color darkBlue = {0, 0, 139, 255};
    constexpr int screenWidth = 300;
    constexpr int screenHeight = 600;
    
    InitWindow(screenWidth, screenHeight, "Tetris");
    SetTargetFPS(60);

    Game game = Game();

    while (!WindowShouldClose())
    {
        game.HandleInput();
        if(EventTrigered(0.2))
        {
            game.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(darkBlue);
        game.Draw();
        EndDrawing();
    }
    
    CloseWindow();
}