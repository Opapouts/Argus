#include "../../vendor/raylib/src/raylib.h"

int main(void)
{
    // 1. Initialize the window
    InitWindow(800, 450, "Aerosphere - Radar Active");
    SetTargetFPS(60);

    // 2. The Game Loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        DrawText("Raylib is successfully linked!", 190, 200, 20, LIGHTGRAY);
        
        EndDrawing();
    }

    // 3. Clean up
    CloseWindow();
    return (0);
}
