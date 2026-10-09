using namespace std;
#include "raylib.h"
#include "Board.h"
#include "BoardRenderer.h"
#include "Game.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 800;
    const int squareSize = screenWidth / 8;

    InitWindow(screenWidth, screenHeight, "C++ Chess");
    SetTargetFPS(60);

    Board board;
    BoardRenderer boardRenderer(board, squareSize);
    Game game(board, squareSize);

    while (!WindowShouldClose()) {

        game.handleInput();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        boardRenderer.render();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}