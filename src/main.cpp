#include <raylib.h>
#include "../include/game.h"
#include "../include/colors.h"

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
    constexpr int screenWidth = 500;
    constexpr int screenHeight = 620;

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