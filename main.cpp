#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 800;
    const int squareSize = screenWidth / 8;

    InitWindow(screenWidth, screenHeight, "C++ Chess");
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        
        // 1. UPDATE STATE (Handle mouse clicks here later)
        
        // 2. DRAW
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the 8x8 board
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                // Alternate colors based on grid position
                bool isLightSquare = (row + col) % 2 == 0;
                Color squareColor = isLightSquare ? RAYWHITE : DARKGRAY;
                
                // Calculate pixel coordinates
                int xPos = col * squareSize;
                int yPos = row * squareSize;

                DrawRectangle(xPos, yPos, squareSize, squareSize, squareColor);
            }
        }
        
        // (Draw pieces here later by looping through your board array)

        EndDrawing();
    }

    CloseWindow();
    return 0;
}