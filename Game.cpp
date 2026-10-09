#include "Game.h"

Game::Game(Board& board, int squareSize) : board(board), squareSize(squareSize), hasSelection(false), startRow(0), startCol(0) {}

void Game::handleInput(){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePosition = GetMousePosition();

        int col = static_cast<int>(mousePosition.x) / squareSize;
        int row = static_cast<int>(mousePosition.y) / squareSize;

        if (row >= 0 && row < 8 && col >= 0 && col < 8) {
            if (!hasSelection) {
                if (board.getSquare(row, col).hasPiece()) {
                    startRow = row;
                    startCol = col;
                    hasSelection = true;
                }
            } else {
                board.movePiece(startRow, startCol, row, col);
                hasSelection = false;
            }
        }
    }
};