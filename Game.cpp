#include "Game.h"

Game::Game(Board& board, int squareSize) : board(board), squareSize(squareSize), hasSelection(false), startRow(0), startCol(0), currentTurn(PieceColor::White) {}

void Game::handleInput(){
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePosition = GetMousePosition();

        int col = static_cast<int>(mousePosition.x) / squareSize;
        int row = static_cast<int>(mousePosition.y) / squareSize;

        if (row >= 0 && row < 8 && col >= 0 && col < 8) {
            if (!hasSelection) {
                if (board.getSquare(row, col).hasPiece() && board.getSquare(row, col).getPiece()->color == currentTurn) {
                    startRow = row;
                    startCol = col;
                    hasSelection = true;
                }
            } else {
                if (row == startRow && col == startCol) {
                    hasSelection = false;
                } else {
                    bool pieceMoved = board.movePiece(startRow, startCol, row, col);
                    if (pieceMoved) {
                        hasSelection = false;
                        switchTurn();
                    }
                }
            }
        }
    }
}

void Game::switchTurn() {
    if (currentTurn == PieceColor::White) {
        currentTurn = PieceColor::Black;
    } else {
        currentTurn = PieceColor::White;
    }
}

bool Game::isSelected() const {
    return hasSelection;
}

int Game::getSelectedRow() const {
    return startRow;
}

int Game::getSelectedCol() const {
    return startCol;
}