#include "raylib.h"
#include <string>
using namespace std;
#include "stdio.h"
#include "Board.h"
#include "BoardRenderer.h"
#include "Square.h"
#include "Pawn.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 800;
    const int squareSize = screenWidth / 8;

    InitWindow(screenWidth, screenHeight, "C++ Chess");
    SetTargetFPS(60);

    Board board;
    BoardRenderer boardRenderer(board, squareSize);
    Square square(0, 0);
    printf("Square has piece: %s\n", square.hasPiece() ? "true" : "false");
    square.setPiece(make_unique<Pawn>(PieceColor::Black));
    printf("Square has piece: %s\n", square.hasPiece() ? "true" : "false");
    printf("Square piece: %p\n", square.getPiece());

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