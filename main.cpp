#include "raylib.h"
#include <string>
using namespace std;
#include "stdio.h"
#include "Board.h"
#include "BoardRenderer.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 800;
    const int squareSize = screenWidth / 8;

    InitWindow(screenWidth, screenHeight, "C++ Chess");
    SetTargetFPS(60);

    Board board;
    BoardRenderer boardRenderer(board, squareSize);

    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        boardRenderer.render();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}