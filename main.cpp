#include "raylib.h"
#include <string>
using namespace std;
#include "stdio.h"

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

        for (int row = 7; row >= 0; row--) {
            for (int col = 0; col <= 7; col++) {
                bool isLightSquare = (row + col) % 2 == 0;

                Color squareColor = isLightSquare ? RAYWHITE : DARKGRAY;
                
                int xPos = col * squareSize;
                int yPos = row * squareSize;

                DrawRectangle(xPos, yPos, squareSize, squareSize, squareColor);
                
                if (row == 7) {
                    char file = 'a' + col;
                    string text(1, file);

                    int x = col * squareSize + 10;
                    int y = row * squareSize + squareSize - 30;

                    DrawText(text.c_str(), x, y, 20, BLACK);
                }

                if (col == 7){
                    int rank = row + 1;
                    string text = to_string(rank);

                    int x = col * squareSize + 80;
                    int y = row * squareSize + 10;

                    DrawText(text.c_str(), x, y, 20, BLACK);
                }
            }
        }
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}