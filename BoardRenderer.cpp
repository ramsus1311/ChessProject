#include "BoardRenderer.h"

BoardRenderer::BoardRenderer(const Board& board, int squareSize) : board(board), squareSize(squareSize) {}

void BoardRenderer::render() const {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            const Square& square = board.getSquare(row, col);

            bool isLightSquare = (row + col) % 2 == 0;
            Color squareColor = isLightSquare ? RAYWHITE : DARKGRAY;
            DrawRectangle(col * squareSize, row * squareSize, squareSize, squareSize, squareColor);
        }
    }
    
}