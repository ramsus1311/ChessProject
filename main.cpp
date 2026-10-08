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

    board.placePiece(6, 4, make_unique<Pawn>(PieceColor::White));

    printf("Square (6, 4) has a piece: %s\n", board.getSquare(6, 4).hasPiece() ? "true" : "false");

    board.movePiece(6, 4, 4, 4);

    printf("Square (6, 4) has a piece: %s\n", board.getSquare(6, 4).hasPiece() ? "true" : "false");
    printf("Square (4, 4) has a piece: %s\n", board.getSquare(4, 4).hasPiece() ? "true" : "false");

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